#include "ep_app.h"

#define ID_WINDOW_MAIN                  (GUI_ID_USER + 0x00)
#define ID_IMAGE_FUNCTION_AREA_1        (GUI_ID_USER + 0x01)
#define ID_IMAGE_FUNCTION_AREA_2        (GUI_ID_USER + 0x02)
#define ID_IMAGE_FUNCTION_AREA_3        (GUI_ID_USER + 0x03)
#define ID_IMAGE_LOGOUT                 (GUI_ID_USER + 0x04)

#define ID_TEXT_TITLE                   (GUI_ID_USER + 0x10)
#define ID_TEXT_SUBTITLE                (GUI_ID_USER + 0x11)
#define ID_TEXT_CONTENT_1               (GUI_ID_USER + 0x12)
#define ID_TEXT_CONTENT_2               (GUI_ID_USER + 0x13)
#define ID_TEXT_CONTENT_3               (GUI_ID_USER + 0x14)
#define ID_BUTTON_BEGIN                 (GUI_ID_USER + 0x15)
#define ID_BUTTON_SUBMIT                (GUI_ID_USER + 0x16)
#define ID_BUTTON_QUESTION              (GUI_ID_USER + 0x17)
#define ID_BUTTON_LOGOUT                (GUI_ID_USER + 0x18)
#define ID_TEXT_SCORE                   (GUI_ID_USER + 0x19)
#define ID_TEXT_QUEUE                   (GUI_ID_USER + 0x1B)


#define ID_EDIT_SCORE                   (GUI_ID_USER + 0x1A)

#define ID_LISTVIEW_SIGN                (GUI_ID_USER + 0x20)


WM_HWIN hSubExpWin;

WM_HWIN hFunctionImage1;
WM_HWIN hFunctionImage2;
WM_HWIN hFunctionImage3;
WM_HWIN hLogoutImage;
WM_HWIN hFunctionButton1;
WM_HWIN hFunctionButton2;
WM_HWIN hFunctionButton3;
WM_HWIN hLogoutButton;
WM_HWIN hExpTitle;
WM_HWIN hExpSubTitle;
WM_HWIN hExpContent1;
WM_HWIN hExpContent2;
WM_HWIN hExpContent3;
WM_HWIN hScoreText;
WM_HWIN hScoreEdit;
WM_HWIN hQueueText;
WM_HWIN hSignList;

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
        { WINDOW_CreateIndirect, "Window", ID_WINDOW_MAIN, 0, 0, 400, 370, 0, 0x0, 0 },
        { IMAGE_CreateIndirect, "Image", ID_IMAGE_FUNCTION_AREA_1, 167, 230, 66, 67, 0, 0, 0 },
        { IMAGE_CreateIndirect, "Image", ID_IMAGE_FUNCTION_AREA_2, 80, 230, 60, 60, 0, 0, 0 },
        { IMAGE_CreateIndirect, "Image", ID_IMAGE_FUNCTION_AREA_3, 245, 230, 60, 60, 0, 0, 0 },
        { IMAGE_CreateIndirect, "Image", ID_IMAGE_LOGOUT, 263, 10, 60, 60, 0, 0, 0 },
        { TEXT_CreateIndirect, "Text", ID_TEXT_TITLE, 0, 42, 400, 40, 0, 0x0, 0 },
        { TEXT_CreateIndirect, "Text", ID_TEXT_SUBTITLE, 0, 98, 400, 27, 0, 0x0, 0 },
        { TEXT_CreateIndirect, "Text", ID_TEXT_CONTENT_1, 0, 142, 400, 27, 0, 0x0, 0 },
        { TEXT_CreateIndirect, "Text", ID_TEXT_CONTENT_2, 0, 169, 400, 27, 0, 0x0, 0 },
        { TEXT_CreateIndirect, "Text", ID_TEXT_CONTENT_3, 0, 196, 400, 27, 0, 0x0, 0 },
        { TEXT_CreateIndirect, "Text", ID_TEXT_SCORE, 0, 180, 120 , 40, 0, 0x0, 0 },
        { TEXT_CreateIndirect, "Text", ID_TEXT_QUEUE, 203, 302, 144, 40, 0, 0x0, 0 },
        { EDIT_CreateIndirect, "Edit", ID_EDIT_SCORE, 0, 240, 120, 40, 0, 0x0, 0 },
        { BUTTON_CreateIndirect, "Button", ID_BUTTON_BEGIN, 128, 310, 144, 40, 0, 0x0, 0 },
        { BUTTON_CreateIndirect, "Button", ID_BUTTON_SUBMIT, 38, 302, 144, 40, 0, 0x0, 0 },
        { BUTTON_CreateIndirect, "Button", ID_BUTTON_QUESTION, 203, 302, 144, 40, 0, 0x0, 0 },
        { BUTTON_CreateIndirect, "Button", ID_BUTTON_LOGOUT, 294, 13, 96, 27, 0, 0x0, 0 },
        { LISTVIEW_CreateIndirect, "Listview", ID_LISTVIEW_SIGN, 66, 138, 260, 227, 0, 0x0, 0 },
};

void pushButtonInitDialog(void)
{
	BUTTON_SetFont(hFunctionButton1,  &YaHei_36_Font);
	BUTTON_SetTextColor(hFunctionButton1, BUTTON_CI_DISABLED, 0x009B5C0A);
	BUTTON_SetTextColor(hFunctionButton1, BUTTON_CI_PRESSED, 0x009B5C0A);
	BUTTON_SetTextColor(hFunctionButton1, BUTTON_CI_UNPRESSED, 0x009B5C0A);
	BUTTON_SetText(hFunctionButton1, "开始实验");
	WM_SetCallback(hFunctionButton1, _cbPushButtonText);

	BUTTON_SetFont(hFunctionButton2,  &YaHei_36_Font);
	BUTTON_SetTextColor(hFunctionButton2, BUTTON_CI_DISABLED, 0x009B5C0A);
	BUTTON_SetTextColor(hFunctionButton2, BUTTON_CI_PRESSED, 0x009B5C0A);
	BUTTON_SetTextColor(hFunctionButton2, BUTTON_CI_UNPRESSED, 0x009B5C0A);
	BUTTON_SetText(hFunctionButton2, "提交实验");
	WM_SetCallback(hFunctionButton2, _cbPushButtonText);

	BUTTON_SetFont(hFunctionButton3,  &YaHei_36_Font);
	BUTTON_SetTextColor(hFunctionButton3, BUTTON_CI_DISABLED, 0x009B5C0A);
	BUTTON_SetTextColor(hFunctionButton3, BUTTON_CI_PRESSED, 0x009B5C0A);
	BUTTON_SetTextColor(hFunctionButton3, BUTTON_CI_UNPRESSED, 0x009B5C0A);
	BUTTON_SetText(hFunctionButton3, "问题解答");
	WM_SetCallback(hFunctionButton3, _cbPushButtonText);

	BUTTON_SetFont(hLogoutButton,  &YaHei_24_Font);
	BUTTON_SetTextColor(hLogoutButton, BUTTON_CI_DISABLED, GUI_BLACK);
	BUTTON_SetTextColor(hLogoutButton, BUTTON_CI_PRESSED, GUI_BLACK);
	BUTTON_SetTextColor(hLogoutButton, BUTTON_CI_UNPRESSED, GUI_BLACK);
	BUTTON_SetText(hLogoutButton, "教师签退");
	WM_SetCallback(hLogoutButton, _cbPushButtonText);

}

static void _cbDialog(WM_MESSAGE * pMsg)
{
        int NCode;
        int Id;
        int i;
	WM_HWIN      	hItem;
        uint32_t 	ulValue;
	BaseType_t 	xResult;
	wifi_config_t 	*notify;
	wifi_config_t 	wifi_config;
	memset(&wifi_config, 0, sizeof(wifi_config));
        
        switch (pMsg->MsgId) {
        case WM_INIT_DIALOG:

                hItem = pMsg->hWin;
                WINDOW_SetBkColor(hItem, 0x00FFFCF9);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_SIGN);
                hSignList = hItem;
                LISTVIEW_SetFont(hItem, &YaHei_24B_Font);
                LISTVIEW_SetHeaderHeight(hItem, 0);
                LISTVIEW_AddColumn(hItem, 130, "", GUI_TA_HCENTER | GUI_TA_VCENTER);
                LISTVIEW_AddColumn(hItem, 130, "", GUI_TA_HCENTER | GUI_TA_VCENTER);
                
                for(i = 0; i < 9; i++)
                        LISTVIEW_AddRow(hItem, NULL);
                
                LISTVIEW_SetGridVis(hItem, 1);
                LISTVIEW_SetItemBkColor(hItem, 0, 0, LISTVIEW_CI_DISABLED, 0x00A6EEBF);
                LISTVIEW_SetItemText(hItem, 0, 0, "已签到");
                LISTVIEW_SetItemBkColor(hItem, 1, 0, LISTVIEW_CI_DISABLED, 0x00FFDAD5);
                LISTVIEW_SetItemText(hItem, 1, 0, "已签退");
                LISTVIEW_DisableRow(hItem, 0);
                WM_HideWindow(hItem);
        
                hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_FUNCTION_AREA_1);
                hFunctionImage1 = hItem;
                IMAGE_SetBitmap(hItem, &bmhdu_logo);
                WM_HideWindow(hItem);

                hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_FUNCTION_AREA_2);
                hFunctionImage2 = hItem;
                IMAGE_SetBitmap(hItem, &bmsubmit);
                WM_HideWindow(hItem);

                hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_FUNCTION_AREA_3);
                hFunctionImage3 = hItem;
                IMAGE_SetBitmap(hItem, &bmquestion);
                WM_HideWindow(hItem);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_LOGOUT);
                hLogoutImage = hItem;
                IMAGE_SetBitmap(hItem, &bmlogout);
                WM_HideWindow(hItem);

                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_TITLE);
                hExpTitle = hItem;
                TEXT_SetFont(hItem,  &YaHei_36_Font);
                TEXT_SetTextColor(hItem, 0x009B5C0A);
                TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_TOP);
                TEXT_SetText(hItem, routine.main_exp.mainExpName);
                WM_HideWindow(hItem);

                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SUBTITLE);
                hExpSubTitle = hItem;
                TEXT_SetFont(hItem,  &YaHei_24B_Font);
                TEXT_SetTextColor(hItem, 0x009B5C0A);
                TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_TOP);
                TEXT_SetText(hItem, "");
                WM_HideWindow(hItem);

                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_CONTENT_1);
                hExpContent1 = hItem;
                TEXT_SetFont(hItem,  &YaHei_24_Font);
                TEXT_SetTextColor(hItem, 0x00868380);
                TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
                TEXT_SetText(hItem, "");
                WM_HideWindow(hItem);

                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_CONTENT_2);
                hExpContent2 = hItem;
                TEXT_SetFont(hItem,  &YaHei_24_Font);
                TEXT_SetTextColor(hItem, 0x00868380);
                TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
                TEXT_SetText(hItem, "");
                WM_HideWindow(hItem);

                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_CONTENT_3);
                hExpContent3 = hItem;
                TEXT_SetFont(hItem,  &YaHei_24_Font);
                TEXT_SetTextColor(hItem, 0x00868380);
                TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
                TEXT_SetText(hItem, "");
                WM_HideWindow(hItem);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SCORE);
                hScoreText = hItem;
                TEXT_SetFont(hItem,  &YaHei_36_Font);
                TEXT_SetTextColor(hItem, 0x00868380);
                TEXT_SetText(hItem, "实验得分");
                WM_HideWindow(hItem);
                WM_HideWindow(hItem);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_QUEUE);
                hQueueText = hItem;
                TEXT_SetFont(hItem,  &YaHei_36_Font);
                TEXT_SetTextColor(hItem, 0x00868380);
                TEXT_SetText(hItem, "等待人数:2");
                TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
                WM_HideWindow(hItem);
                WM_HideWindow(hItem);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_SCORE);
                hScoreEdit = hItem;
                EDIT_SetFont(hItem,  &YaHei_36_Font);
                EDIT_SetTextColor(hItem, EDIT_CI_ENABLED, 0x00868380);
                EDIT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
                EDIT_SetMaxLen(hItem, 100);
                WM_SetFocus(hItem);
                EDIT_SetText(hItem, "");
                WM_HideWindow(hItem);
                WM_HideWindow(hItem);

                hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_BEGIN);
                hFunctionButton1 = hItem;
                WM_HideWindow(hItem);

                hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_SUBMIT);
                hFunctionButton2 = hItem;
                WM_HideWindow(hItem);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_QUESTION);
                hFunctionButton3 = hItem; 
                WM_HideWindow(hItem);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_LOGOUT);
                hLogoutButton = hItem; 
                WM_HideWindow(hItem);

                pushButtonInitDialog();
        break;
		
        case WM_BUTTON_BEGIN_CB:
                notify = (wifi_config_t *)pMsg->Data.p;
                if(notify->http_notify.status == HTTP_OK) {
                        ui_effect.hWin = hFunctionImage1;
                        ui_effect.status = effect_stop;
                        xTaskNotify(GuiTask_Handler, (uint32_t)(&ui_effect), eSetValueWithOverwrite );
                        
                        switch (notify->http_notify.event) {
                        case http_student_login_check : 
                                if(routine.online_number == 0)
                                        routine.flags.flagStudentLogin = flag_set;
                                ++routine.online_number;
                                for(i = 1; i <= 9; i++ )
					LISTVIEW_SetItemText(hSignList, 0, i, routine.online_eid_list[i - 1]);
				
				wifi_config.mqtt_notify.event = mqtt_subscribe;
				if(errQUEUE_FULL == xQueueSend(xQueueWifi, (const void *)(&wifi_config), 50))
					notify_show("操作无效", "请稍后");
				
				notify_show(routine.online_eid_list[routine.online_number], "签到成功");
                        break;
                                
                        case http_logout_check :
                                --routine.online_number;
                                strcpy(routine.offline_eid_list[routine.offline_number], routine.online_eid_list[routine.online_number]);
                                memset(routine.online_eid_list[routine.online_number], 0, 9);
                                if(routine.online_number == 0)
                                        routine.flags.flagStudentLogin = flag_reset;
                                ++routine.offline_number;
                                for(i = 1; i <= 9; i++ ) {
                                        LISTVIEW_SetItemText(hSignList, 0, i, routine.online_eid_list[i - 1]);
                                        LISTVIEW_SetItemText(hSignList, 1, i, routine.offline_eid_list[i - 1]);
                                }
				notify_show(routine.offline_eid_list[routine.offline_number], "签退成功");

                        break;
                                    
                        case http_teacher_login_check :
                                if(routine.flags.flagTeacherLogin == flag_reset) {
                                        routine.flags.flagTeacherLogin = flag_set;
                                        menu_reconstruct_list_content(present_bar_status, present_list_status, 1);
                                }
                                
                        break;
                        
                        default :
                                
                        break;
                        }
                        
                        
                }
                else if(notify->http_notify.status == HTTP_ERR) {
                        ui_effect.hWin = hFunctionImage1;
                        ui_effect.status = effect_stop;
                        xTaskNotify(GuiTask_Handler, (uint32_t)(&ui_effect), eSetValueWithOverwrite);
			
			notify_show("网络连接错误", "身份验证失败");
                }
                else if(notify->http_notify.status == HTTP_NO_DATA) {
                        ui_effect.hWin = hFunctionImage1;
                        ui_effect.status = effect_stop;
                        xTaskNotify(GuiTask_Handler, (uint32_t)(&ui_effect), eSetValueWithOverwrite);
			
			notify_show("参数错误", "请检查您的凭证");
                }
                else;
        break;
                
        case WM_BUTTON_SCORE_CB:
		notify = (wifi_config_t *)pMsg->Data.p;
                if(notify->http_notify.status == HTTP_OK) {
                        if(present_list_status == 1)
                                IMAGE_SetBitmap(hExpStatusImage1, &bmfinished);
                        else if(present_list_status == 2)
                                IMAGE_SetBitmap(hExpStatusImage2, &bmfinished);
                        else
                                IMAGE_SetBitmap(hExpStatusImage3, &bmfinished);
			notify_show("操作成功", "");
                        expRoutineStateSwitch(present_list_status - 1, exp_finished);
                }
                else if(notify->http_notify.status == HTTP_ERR)
			notify_show("网络连接错误", "操作失败");
        break;

        case WM_NOTIFY_PARENT:
                Id = WM_GetId(pMsg->hWinSrc);
                NCode = pMsg->Data.v;
		switch(Id) {
                case ID_BUTTON_BEGIN :
                switch(NCode) {
			case WM_NOTIFICATION_CLICKED:
						
			break;
                        
			case WM_NOTIFICATION_RELEASED:
                                if(present_bar_status == ACTION_LOGIN) {
                                        if(present_list_status == 1) {
                                                if(routine.online_number >= 8)
							notify_show("人数超过上限", "签到失败");
                                                else {
                                                        voiceDispString(voiceShowQrCode);
							xTaskNotifyGive(QRScannerTask_Handler);
                                                }
                                        }
                                        else if(present_list_status == 2) {
                                                if(routine.online_number == 0)
							notify_show("当前无在线人员", "签退失败");
                                                else {
                                                        if(EXP_NOT_FINISHED) {
                                                                TEXT_SetText(hConfirmText1, "实验进程未结束");
                                                                TEXT_SetText(hConfirmText2, "确认签退?"); 
                                                                WM_ShowWindow(hConfirmText2);
                                                                WM_ShowWindow(hConfirmWindow);
                                                        }
                                                        else {
                                                                voiceDispString(voiceShowQrCode);
                                                                xTaskNotifyGive(QRScannerTask_Handler);	
                                                        }                                                                
                                                }
                                                
                                        }
                                }
                                else if(present_bar_status == ACTION_EXP_DETAIL) {
                                        if(routine.main_exp.sub_exp[present_list_status - 1].status == exp_waiting) 
						expRoutineStateSwitch(present_list_status - 1, exp_lasting);
//                                                routine.main_exp.sub_exp[present_list_status - 1].status = exp_lasting;
//                                        menu_reconstruct_list_content(present_bar_status, present_list_status);
                                }
                                else if(present_bar_status == ACTION_EXP_SCORE) {
                                        if(routine.flags.flagTeacherLogin == flag_reset) {
						expRoutineFlagSet(FLAG_TEACHER_LOGIN, 1);
//                                                voiceDispString(voiceShowQrCode);
//                                                xTaskNotifyGive(QRScannerTask_Handler);	
                                        }
                                        else if(routine.main_exp.sub_exp[present_list_status - 1].status == exp_submitted || routine.main_exp.sub_exp[present_list_status - 1].status == exp_grading) {
                                                expRoutineStateSwitch(present_list_status - 1, exp_grading);
//						routine.main_exp.sub_exp[present_list_status - 1].status = exp_grading;
//                                                menu_reconstruct_list_content(present_bar_status, present_list_status);
                                                WM_ShowWindow(hKeyboard);
                                        }
                                }
                                else;
			break;
                        }
		break; 

                case ID_BUTTON_SUBMIT :
                        switch(NCode) {
			case WM_NOTIFICATION_CLICKED:
						
			break;
			case WM_NOTIFICATION_RELEASED:

                                TEXT_SetText(hConfirmText1, "确认提交实验?");
                                WM_HideWindow(hConfirmText2);
                                WM_ShowWindow(hConfirmWindow);
                                
                        break;
                        }
		break; 

                case ID_BUTTON_QUESTION :
                        switch(NCode) {
			case WM_NOTIFICATION_CLICKED:
                        
			break;
			case WM_NOTIFICATION_RELEASED:
                                ui_effect.hWin = hFunctionImage3;
                                ui_effect.status = effect_start;
                                xTaskNotify( GuiTask_Handler,
                                             (uint32_t)(&ui_effect),
                                             eSetValueWithOverwrite
                                );
                        
                                GUI_Delay(1000);
                        
                                ui_effect.hWin = hFunctionImage3;
                                ui_effect.status = effect_stop;
                                xTaskNotify( GuiTask_Handler,
                                             (uint32_t)(&ui_effect),
                                             eSetValueWithOverwrite
                                );
                                routine.flags.flagQuestionSet = flag_set;
                                menu_reconstruct_list_content(present_bar_status, present_list_status, 1);
                        break;
                        }
		break;  
                        
                case ID_BUTTON_LOGOUT :
                        switch(NCode) {
			case WM_NOTIFICATION_CLICKED:
						
			break;
			case WM_NOTIFICATION_RELEASED:
                                
                                if(EXP_NOT_SCORED) { 
                                        TEXT_SetText(hConfirmText1, "仍有未评分实验");
                                        TEXT_SetText(hConfirmText2, "确认注销?"); 
                                        WM_ShowWindow(hConfirmText2);
                                        WM_HideWindow(hKeyboard);
                                        WM_ShowWindow(hConfirmWindow);
                                }
                                
                                else { 
                                        ui_effect.hWin = hLogoutImage;
                                        ui_effect.status = effect_start;
                                        xTaskNotify( GuiTask_Handler,
                                             (uint32_t)(&ui_effect),
					     eSetValueWithOverwrite
                                        );
                                        GUI_Delay(1000);
                                
                                        ui_effect.hWin = hLogoutImage;
                                        ui_effect.status = effect_stop;
                                        xTaskNotify( GuiTask_Handler,
                                                     (uint32_t)(&ui_effect),
                                                     eSetValueWithOverwrite
                                        );
                                        
                                        routine.flags.flagTeacherLogin = flag_reset;
                                        present_bar_status = ACTION_EXP_DETAIL;
                                        bar_highlight_slide(ex_bar_status, present_bar_status);
                                        ex_bar_status = present_bar_status;
                                        menu_reconstruct_bar_content(present_bar_status);
                                        menu_reconstruct_list_content(present_bar_status, present_list_status, 1);
                                }    
                        break;
                        }
		break;  
                
                case ID_EDIT_SCORE :
                        switch(NCode) {
			case WM_NOTIFICATION_CLICKED:
						
			break;
			case WM_NOTIFICATION_RELEASED:
                                WM_ShowWindow(hKeyboard);  
                        break;
                        }
		break; 
                        
                default :
                        
                break;
                }
        break;

        default:
                WM_DefaultProc(pMsg);
        break;
        }
}

WM_HWIN subExpWindowOnCreate(void) 
{
        WM_HWIN hWin;
        hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
        WM_AttachWindowAt(hWin, hMainWin, 800, 10);
        WM_HideWindow(hWin);
        return hWin;
}

/*************************** End of file ****************************/
