#include "systask.h"

extern TaskHandle_t xHandleTaskStudentwin;

static WM_HWIN create(void);
static void open(void);
static void close(void);
static void studentwin_task(void);

UI_studentwinInfoStructTypedef studentwin = {
	(WM_HWIN)0,
	
	create,
	open,
	close,
	studentwin_task
};

static WM_HWIN create(void)
{
	ui.studentwin->hwin = StudentPageOnCreate();
	
	return ui.studentwin->hwin;
}

static void close()
{
	WM_HideWin(ui.studentwin->hwin);
}

static void open()
{
	WM_BringToTop(ui.studentwin->hwin);
	WM_ShowWin(ui.studentwin->hwin);
}

static void student_event(void)
{
	switch(ui_state.studentwin_state)
	{
		case STATE_STUDENT_INIT:
			TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"等待教师开始实验 ");
			EDIT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_EDIT_STUDENT_1),"");  //姓名
			EDIT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_EDIT_STUDENT_2),"");  //学号
			EDIT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_EDIT_STUDENT_3)," "); //实验编号
			
			ui.studentwin->open();
			WM_ShowWindow(WM_GetDialogItem(ui.studentwin->hwin, ID_BUTTON_STUDENT_2));
			WM_HideWindow(WM_GetDialogItem(ui.studentwin->hwin, ID_EDIT_STUDENT_4));
			WM_HideWindow(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_4));
		
			ui_state.studentwin_state = STATE_STUDENT_WAITING;
		break;
		
		case STATE_STUDENT_SWITCH_TO_TEACHERWIN:
			ui.switchover(ui.studentwin->hwin,ui.teacherwin->hwin);
			ui_state.studentwin_state = STATE_STUDENT_WAITING;
		break;
		
		case STATE_STUDENT_SWITCH_TO_SETTINGWIN:
			ui.switchover(ui.studentwin->hwin,ui.settingwin->hwin);
			ui_state.studentwin_state = STATE_STUDENT_WAITING;
		break;
		
		case STATE_STUDENT_START_EXPERIMENT:
			
			if(running_state & STATE_RUNNING_STUDENT_WITHOUT_WIFI)
				xTaskNotify(xHandleTaskQRScanner,
							bitQRScannerOn,
							eSetValueWithOverwrite);
			else if(running_state & STATE_RUNNING_WAITING_EXP_WITHOUT_WIFI)
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"尚未开始实验 ");
			else
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"当前实验尚未结束 ");

			ui_state.studentwin_state = STATE_STUDENT_WAITING;
		break;
		
		case STATE_STUDENT_WAITING:
		break;
		
		default:
		break;
	}
}

static void studentwin_task(void)
{
	BaseType_t xResult;
	uint32_t ulValue;
	while(1)
	{
		xResult = xTaskNotifyWait(	(uint32_t)0x00,		
									(uint32_t)0xffffffffUL,
									&ulValue,
									(TickType_t)0	);
		
		if(xResult == pdPASS)
		{
			if(ulValue == bitClose ) {
				studentwin.close();
				GUI_Exec();
			}
			
			if(ulValue == bitOpen ) {
				studentwin.open();
				GUI_Exec();
			}
			
			if(ulValue == bitWifiConnected )
			{
				IMAGE_SetBitmap(WM_GetDialogItem(ui.studentwin->hwin, ID_IMAGE_STUDENT_6),&bmwifi);
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"无线网络连接成功 ");
			}
			
			if(ulValue == bitWifiConnectError )
			{
				IMAGE_SetBitmap(WM_GetDialogItem(ui.studentwin->hwin, ID_IMAGE_STUDENT_6),&bmwifi_off);
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"无线网络连接失败 ");
			}
			
			if(ulValue == bitWifiConnecting )
			{
				IMAGE_SetBitmap(WM_GetDialogItem(ui.studentwin->hwin, ID_IMAGE_STUDENT_6),&bmwifi_off);
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"正在连接无线网络 ");
			}
			
			if(ulValue == bitQRScannerOn )
			{
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"请扫描您的二维码 ");
			}
			
			if(ulValue == bitQRScannerOnError )
			{
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"二维码扫描器开启失败 ");
			}
			
			if(ulValue == bitQRScannerScanError )
			{
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"二维码识别失败 ");
			}
			
			if(ulValue == bitQRScannerScanOvertime )
			{
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"扫描超时,请重试 ");
			}
			
			if(ulValue == bitQRScannerScanRight )
			{
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"二维码识别成功 ");
				
				xTaskNotify(xHandleTaskWifi,
							bitWifiHttpRequesting,
							eSetValueWithOverwrite);
			}
			
			if(ulValue == bitWifiHttpRequesting )
			{
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"正在连接服务器 ");
			}
			
			if(ulValue == bitWifiHttpRequestRight )
			{
				running_state &= ~STATE_RUNNING_STUDENT_WITHOUT_WIFI;					//学生状态结束 1011 1111
				running_state |= STATE_RUNNING_TEACHER_IDENTIFY_WITHOUT_WIFI;			//进入教师验证状态
				
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"签到成功 ");
				TEXT_SetText(WM_GetDialogItem(ui.teacherwin->hwin, ID_TEXT_TEACHER_0),"请点击右方按钮进行身份验证 ");
				
				EDIT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_EDIT_STUDENT_2),(const char*)student.id);
				EDIT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_EDIT_STUDENT_1),(const char*)student.name);
				EDIT_SetText(WM_GetDialogItem(ui.teacherwin->hwin, ID_EDIT_TEACHER_1),(const char*)student.id);
				EDIT_SetText(WM_GetDialogItem(ui.teacherwin->hwin, ID_EDIT_TEACHER_0),(const char*)student.name);
				
				WM_HideWindow(WM_GetDialogItem(ui.studentwin->hwin, ID_BUTTON_STUDENT_2));
				WM_ShowWindow(WM_GetDialogItem(ui.studentwin->hwin, ID_EDIT_STUDENT_4));
				WM_ShowWindow(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_4));
				
				timer6_notify.count_down_per_sec = 0;
				TIM_SetCounter(TIM6,0);
			}
			
			if(ulValue == bitWifiHttpRequestWrong )
			{
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"签到失败 ");
			}
			
			if(ulValue == bitWifiHttpRequestError )
			{
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"签到上传超时 ");
			}
			
			if(ulValue == bitWifiMqttWaiting)
			{
				running_state &= ~STATE_RUNNING_WAITING_EXP_WITHOUT_WIFI;		//开始实验
				running_state |= STATE_RUNNING_STUDENT_WITHOUT_WIFI;			//进入学生状态
				
				EDIT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_EDIT_STUDENT_3),(const char*)experimentIDNum);
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"请点击右方按钮进行签到 ");
			}
			
			if(ulValue == bitWifiMqttConnectError)
			{
				TEXT_SetText(WM_GetDialogItem(ui.studentwin->hwin, ID_TEXT_STUDENT_0),"MQTT服务器连接失败 ");
			}
		}
		student_event();
		vTaskDelay(10);
	}
}


