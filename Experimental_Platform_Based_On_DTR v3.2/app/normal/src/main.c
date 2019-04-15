#include "ep_app.h"

//任务优先级
#define START_TASK_PRIO		1
#define TIMER_TASK_PRIO		2
#define TOUCH_TASK_PRIO		9
#define GUI_TASK_PRIO		4
#define WIFI_TASK_PRIO		5
#define QRSCANNER_TASK_PRIO	6
#define CONSOLE_TASK_PRIO	7
#define INIT_TASK_PRIO	        8
#define RC522_TASK_PRIO	        10
#define MENU_TASK_PRIO	        3

//任务堆栈大小
#define START_STK_SIZE 		128
#define TIMER_STK_SIZE 		512
#define TOUCH_STK_SIZE 		1024
#define GUI_STK_SIZE 		1024
#define WIFI_STK_SIZE 		1024
#define QRSCANNER_STK_SIZE 	1024
#define CONSOLE_STK_SIZE 	128
#define INIT_STK_SIZE 	        256
#define RC522_STK_SIZE 	        512
#define MENU_STK_SIZE 	        1024

//任务句柄
TaskHandle_t StartTask_Handler;
TaskHandle_t TimerTask_Handler;
TaskHandle_t TouchTask_Handler;
TaskHandle_t GuiTask_Handler;
TaskHandle_t WifiTask_Handler;
TaskHandle_t QRScannerTask_Handler;
TaskHandle_t ConsoleTask_Handler;
TaskHandle_t InitTask_Handler;
TaskHandle_t RC522Task_Handler;
TaskHandle_t MenuTask_Handler;

void start_task(void *pvParameters);
void timer_task(void *pvParameters);
void touch_task(void *pvParameters);
void gui_task(void *pvParameters);
void wifi_task(void *pvParameters);
void scanner_task(void *pvParameters);
void console_task(void *pvParameters);
void init_task(void *pvParameters);
void rc522_task(void *pvParameters);
void menu_task(void *pvParameters);
void vTimerCallback(xTimerHandle pxTimer);

enum flag_t wifiStateChangeFlag = flag_reset;
enum flag_t mqttPingFlag = flag_reset;
enum flag_t httpGetTimeFlag = flag_reset;

char pStrSysDate[20];
char pStrSysTime[15];
char pTaskStatusBuffer[500];
char volumeString[20];

sys_config_t sys_config;
TimerHandle_t xTimerWifiConnect = NULL;
TimerHandle_t xTimerTcpCheck = NULL;
QueueHandle_t xQueueWifi = NULL;
QueueHandle_t xQueueUiLogic = NULL;

void init_wifi_queue(wifi_config_t wifi_config)
{
	memset(&wifi_config, 0, sizeof(wifi_config));
	if(pdFAIL == xQueueReset(xQueueWifi))			
		notify_show("队列清空失败", "请稍后");
	wifi_config.setting.event = wifi_connect_check;
	if(errQUEUE_FULL == xQueueSend(xQueueWifi, (const void *)(&wifi_config), 50)) 
		notify_show("操作无效", "请稍后");
	wifi_config.setting.event = wifi_ping_check;
	if(errQUEUE_FULL == xQueueSend(xQueueWifi, (const void *)(&wifi_config), 50)) 
		notify_show("操作无效", "请稍后");
	wifi_config.setting.event = wifi_tcp_check;
	if(errQUEUE_FULL == xQueueSend(xQueueWifi, (const void *)(&wifi_config), 50)) 
		notify_show("操作无效", "请稍后");
	wifi_config.setting.event = 0;
	wifi_config.http_notify.event = http_sync_time;
	wifi_config.mqtt_notify.event = mqtt_init;
	if(errQUEUE_FULL == xQueueSend(xQueueWifi, (const void *)&wifi_config, 50)) 
		notify_show("操作无效", "请稍后");
	wifi_config.http_notify.event = 0;
	wifi_config.mqtt_notify.event = mqtt_restart;
	if(errQUEUE_FULL == xQueueSend(xQueueWifi, (const void *)&wifi_config, 50)) 
			notify_show("操作无效", "请稍后");
	wifi_config.mqtt_notify.event = mqtt_init;
	if(errQUEUE_FULL == xQueueSend(xQueueWifi, (const void *)&wifi_config, 50)) 
			notify_show("操作无效", "请稍后");
}
int main()
{
	bsp_Init();
	expGetRoutineContents();
	ui_init();
	voiceInitCheck();

	sprintf((char *)volumeString, "[v%d][m52][s6]", 1);
	voiceDispString(volumeString);
	sys_config.voice = on;
	voiceDispString(voiceWelcome);
	xTaskCreate((TaskFunction_t )start_task,                //任务函数
	            (const char*    )"start_task",                  //任务名称
	            (uint16_t       )START_STK_SIZE,                //任务堆栈大小
	            (void*          )NULL,                          //传递给任务函数的参数
	            (UBaseType_t    )START_TASK_PRIO,               //任务优先级
	            (TaskHandle_t*  )&StartTask_Handler);           //任务句柄

	xQueueWifi = xQueuecreate(10, sizeof(wifi_config_t));
	xTimerWifiConnect = xTimercreate("Timer", 20000, pdFALSE, (void *) 1, vTimerCallback); 
	xTimerTcpCheck = xTimercreate("Timer", 1000, pdFALSE, (void *) 2, vTimerCallback); 
	vTaskStartScheduler();                                  //开启任务调度

	while(1) {

	}
}

/**
* start_task - 开始任务
*
* @brief
*       创建其他系统任务
*
**/
void start_task(void *pvParameters)
{
	taskENTER_CRITICAL();                                           //进入临界区

	xTaskCreate((TaskFunction_t )timer_task,                        //任务函数
	            (const char*    )"timer_task",                          //任务名称
	            (uint16_t       )TIMER_STK_SIZE,                        //任务堆栈大小
	            (void*          )NULL,                                  //传递给任务函数的参数
	            (UBaseType_t    )TIMER_TASK_PRIO,                       //任务优先级
	            (TaskHandle_t*  )&TimerTask_Handler);                   //任务句柄

	xTaskCreate((TaskFunction_t )touch_task,                        //任务函数
	            (const char*    )"touch_task",                          //任务名称
	            (uint16_t       )TOUCH_STK_SIZE,                        //任务堆栈大小
	            (void*          )NULL,                                  //传递给任务函数的参数
	            (UBaseType_t    )TOUCH_TASK_PRIO,                       //任务优先级
	            (TaskHandle_t*  )&TouchTask_Handler);                   //任务句柄

	xTaskCreate((TaskFunction_t )gui_task,                          //任务函数
	            (const char*    )"gui_task",                            //任务名称
	            (uint16_t       )GUI_STK_SIZE,                          //任务堆栈大小
	            (void*          )NULL,                                  //传递给任务函数的参数
	            (UBaseType_t    )GUI_TASK_PRIO,                         //任务优先级
	            (TaskHandle_t*  )&GuiTask_Handler);                     //任务句柄

	xTaskCreate((TaskFunction_t )wifi_task,                         //任务函数
	            (const char*    )"wifi_task",                           //任务名称
	            (uint16_t       )WIFI_STK_SIZE,                         //任务堆栈大小
	            (void*          )NULL,                                  //传递给任务函数的参数
	            (UBaseType_t    )WIFI_TASK_PRIO,                        //任务优先级
	            (TaskHandle_t*  )&WifiTask_Handler);                    //任务句柄

	xTaskCreate((TaskFunction_t )scanner_task,                      //任务函数
	            (const char*    )"scanner_task",                        //任务名称
	            (uint16_t       )QRSCANNER_STK_SIZE,                    //任务堆栈大小
	            (void*          )NULL,                                  //传递给任务函数的参数
	            (UBaseType_t    )QRSCANNER_TASK_PRIO,                   //任务优先级
	            (TaskHandle_t*  )&QRScannerTask_Handler);               //任务句柄

	xTaskCreate((TaskFunction_t )console_task,                      //任务函数
	            (const char*    )"console_task",                        //任务名称
	            (uint16_t       )CONSOLE_STK_SIZE,                      //任务堆栈大小
	            (void*          )NULL,                                  //传递给任务函数的参数
	            (UBaseType_t    )CONSOLE_TASK_PRIO,                     //任务优先级
	            (TaskHandle_t*  )&ConsoleTask_Handler);                 //任务句柄

	xTaskCreate((TaskFunction_t )init_task,                         //任务函数
	            (const char*    )"init_task",                           //任务名称
	            (uint16_t       )INIT_STK_SIZE,                         //任务堆栈大小
	            (void*          )NULL,                                  //传递给任务函数的参数
	            (UBaseType_t    )INIT_TASK_PRIO,                        //任务优先级
	            (TaskHandle_t*  )&InitTask_Handler);                    //任务句柄

	xTaskCreate((TaskFunction_t )rc522_task,                        //任务函数
	            (const char*    )"rc522_task",                          //任务名称
	            (uint16_t       )RC522_STK_SIZE,                        //任务堆栈大小
	            (void*          )NULL,                                  //传递给任务函数的参数
	            (UBaseType_t    )RC522_TASK_PRIO,                       //任务优先级
	            (TaskHandle_t*  )&RC522Task_Handler);                   //任务句柄
                    
        xTaskCreate((TaskFunction_t )menu_task,                        //任务函数
	            (const char*    )"menu_task",                          //任务名称
	            (uint16_t       )MENU_STK_SIZE,                        //任务堆栈大小
	            (void*          )NULL,                                  //传递给任务函数的参数
	            (UBaseType_t    )MENU_TASK_PRIO,                       //任务优先级
	            (TaskHandle_t*  )&MenuTask_Handler);                   //任务句柄


	vTaskDelete(StartTask_Handler);                                 //删除开始任务
	taskEXIT_CRITICAL();                                            //退出临界区
}

void timer_task(void *pvParameters)
{
	wifi_config_t wifi_config;

	while(1) {
		memset(&wifi_config, 0 , sizeof(wifi_config));
		sprintf(pStrSysDate, "%d年%d月%d日 ", system_time.year, system_time.month, system_time.day);
		sprintf(pStrSysTime, "%d%d : %d%d : %d%d", system_time.hour / 10, system_time.hour % 10, system_time.min / 10, system_time.min % 10, system_time.sec / 10, system_time.sec % 10);
		TEXT_SetText(hDateWin, pStrSysDate);
		TEXT_SetText(hTimeWin, pStrSysTime);

		if(system_time.min % 10 == 0 && system_time.sec == 0 && httpGetTimeFlag == flag_set) {
			wifi_config.http_notify.event = http_sync_time;
			if(errQUEUE_FULL == xQueueSend(xQueueWifi, (const void *)(&wifi_config), 50))
				notify_show("时间校准失败", "请稍后");
			/*避免一秒内校准多次时间，填满消息队列*/
			GUI_Delay(1000);
		}
		if(system_time.sec == 30 && mqttPingFlag == flag_set) {
			wifi_config.mqtt_notify.event = mqtt_pingque;
			if(errQUEUE_FULL == xQueueSend(xQueueWifi, (const void *)(&wifi_config), 50))
				notify_show("同步失败", "请稍后");
			/*避免一秒内校准多次时间，填满消息队列*/
			GUI_Delay(1000);
		}
		GUI_Delay(20);
	}
}

void touch_task(void *pvParameters)
{
	menu_reconstruct_bar_content(1);
	menu_reconstruct_list_content(1, 1);
	while(1) {
		ui_action();
		GUI_Delay(20);
	}
}

void gui_task(void *pvParameters)
{
	BaseType_t xResult;
	uint32_t ulValue;
	ui_effect_t *effect;
	int bounce_cnt = 0;

	while(1) {
		xTaskNotifyWait((uint32_t)0x00,
		                (uint32_t)0xffffffffUL,
		                &ulValue,
		                (TickType_t)portMAX_DELAY
		               );
		effect = (ui_effect_t *)ulValue;
		if(effect->status == effect_start) {
			vTaskSuspend(TouchTask_Handler);
			while(1) {
				xResult = xTaskNotifyWait((uint32_t)0x00,
				                          (uint32_t)0xffffffffUL,
				                          &ulValue,
				                          (TickType_t)10
				                         );
				if(xResult == pdPASS) {
					if(((ui_effect_t *)ulValue)->status == effect_stop) {
						vTaskResume(TouchTask_Handler);
						bounce_cnt = 0;
						break;
					}
				}
				element_bounce(effect->hWin, 1);
			}

		}
		GUI_Delay(10);
	}
}

void wifi_task(void *pvParameters)
{
	u8 i, j;
	u8 request[200];
	static u8 recheck_times = 0;
	
	BaseType_t xResult;
	uint32_t ulNotifiedValue;
	wifi_config_t notify;
	mqttStatus mqttRetVal;
	wifiStatus wifiRetVal;
	httpStatus httpRetVal;
	
	WM_MESSAGE pmsg;
//	usr_c322_init();
	init_wifi_queue(notify);
	xTimerStart(xTimerWifiConnect, 100);
	while(1) {
		usr_c322_wifista_mqtt_check(uart.uart_2->pRx_buffer);
		
		memset(&notify, 0, sizeof(notify));
		xResult =  xQueueReceive( xQueueWifi,
		                          (void *)&notify,
		                          (TickType_t)0
		                        );
		if(xResult == pdPASS) {
			memset(request, 0, sizeof(request));
			switch (notify.setting.event) {
			case wifi_scan:
				notify.setting.status = usr_c322_wifista_scan();

				uart.uart_x->rx_status = 0;
				memset(uart.uart_x->pRx_buffer, 0, uart.uart_x->rx_buffer_len);
				pmsg.hWin = hSettingWindow;
				pmsg.MsgId = WM_WIFI_SCAN_CB;
				pmsg.Data.p = &notify;
				WM_SendMessage(hSettingWindow, &pmsg);
				GUI_Exec();
				break;

			case wifi_connect:
				mqttPingFlag = flag_reset;
				httpGetTimeFlag = flag_reset;
				usr_c322_wifista_connect(wifi_data.name, wifi_data.password);
				notify.setting.event = wifi_connect_check;
				if(errQUEUE_FULL == xQueueSend(xQueueWifi, (const void *)&notify, 50)) 
						notify_show("操作无效", "请稍后");

				uart.uart_x->rx_status = 0;
				memset(uart.uart_x->pRx_buffer, 0, uart.uart_x->rx_buffer_len);
				xTimerStart(xTimerWifiConnect, 100);
				break;

			case wifi_connect_check:
				if(bit_wifi_status == WIFI_OK) {
					if(usr_c322_check_wifi_connect() == WIFI_OK) {
						xTimerStop(xTimerWifiConnect, 100);
						
						notify.setting.status = WIFI_OK;
						pmsg.hWin = hMainWin;
						pmsg.MsgId = WM_WIFI_CONNECT_CB;
						pmsg.Data.p = &notify;
						WM_SendMessage(hMainWin, &pmsg);
						GUI_Exec();
					}
				}
				else if(notify.setting.status == WIFI_ERR) {
					pmsg.hWin = hMainWin;
					pmsg.MsgId = WM_WIFI_CONNECT_CB;
					pmsg.Data.p = &notify;
					WM_SendMessage(hMainWin, &pmsg);
					GUI_Exec();
					
					memset(&notify, 0, sizeof(notify));
				}
				else {
					if(errQUEUE_FULL == xQueueSendToFront(xQueueWifi, (const void *)&notify, 50)) 
							notify_show("操作无效", "请稍后");
				}
			break;
			
			case wifi_ping_check:
				notify.setting.status = usr_c322_check_ping();

				if(notify.setting.status == WIFI_ERR)
					httpGetTimeFlag = flag_reset;
				uart.uart_x->rx_status = 0;
				memset(uart.uart_x->pRx_buffer, 0, uart.uart_x->rx_buffer_len);
				pmsg.hWin = hMainWin;
				pmsg.MsgId = WM_WIFI_CONNECT_CB;
				pmsg.Data.p = &notify;
				WM_SendMessage(hMainWin, &pmsg);
				GUI_Exec();
				break;
			
			case wifi_tcp_check:
				notify.setting.status = usr_c322_check_tcp_connect();

				if(notify.setting.status == WIFI_ERR)
					httpGetTimeFlag = flag_reset;
				else
					httpGetTimeFlag = flag_set;
				uart.uart_x->rx_status = 0;
				memset(uart.uart_x->pRx_buffer, 0, uart.uart_x->rx_buffer_len);
				pmsg.hWin = hMainWin;
				pmsg.MsgId = WM_WIFI_CONNECT_CB;
				pmsg.Data.p = &notify;
				WM_SendMessage(hMainWin, &pmsg);
				GUI_Exec();
				break;

			default:
				break;
			}
			switch (notify.http_notify.event) {
			case http_submit_dev_id:
				sprintf((char *)request, "https://%s/openApi/experiment/gateway/addNode.json?gatewayId=100.2.254.1&nodeId=%s", http_wifista_ip, sys_config.dev_id);
				usr_c322_wifista_HTTP_request(request);
				httpRetVal = httpSubmitDevId((char*)uart.uart_x->pRx_buffer);
				if(HTTP_NO_DATA == httpRetVal)
					notify_show("网络连接错误", "节点上传失败");
				else if(HTTP_FALSE == httpRetVal)
					notify_show("请求失败", "节点上传失败");
				else if(HTTP_ERR == httpRetVal)
					notify_show("系统错误", "请稍后");
				
				uart.uart_x->rx_status = 0;
				memset(uart.uart_x->pRx_buffer, 0, uart.uart_x->rx_buffer_len);
			break;
				
                        case http_get_appointment:
				sprintf((char *)request, "https://%s/openApi/experiment/info.json?id=%s", http_wifista_ip, sys_config.dev_id);
				usr_c322_wifista_HTTP_request(request);
				httpRetVal = httpGetAppointment((char*)uart.uart_x->pRx_buffer);
				if(HTTP_NO_DATA == httpRetVal)
					notify_show("网络连接错误", "实验信息获取失败");
				else if(HTTP_FALSE == httpRetVal)
					notify_show("请求失败", "实验信息获取失败");
				else if(HTTP_ERR == httpRetVal)
					notify_show("系统错误", "请稍后");
				
				uart.uart_x->rx_status = 0;
				memset(uart.uart_x->pRx_buffer, 0, uart.uart_x->rx_buffer_len);
                                break;
                        
			case http_student_login_check:
				sprintf((char *)request, "%s?type=STUDENT&id=%s", notify.http_notify.param, sys_config.dev_id);
				usr_c322_wifista_HTTP_request(request);
				notify.http_notify.status = httpStudentLoginCheck((char*)uart.uart_x->pRx_buffer);

				uart.uart_x->rx_status = 0;
				memset(uart.uart_x->pRx_buffer, 0, uart.uart_x->rx_buffer_len);
				pmsg.hWin = hSubExpWin;
				pmsg.MsgId = WM_BUTTON_BEGIN_CB;
				pmsg.Data.p = &notify;
				WM_SendMessage(hSubExpWin, &pmsg);
				GUI_Exec();
				break;

			case http_teacher_login_check:
				sprintf((char *)request, "%s?type=TEACHER&id=%s", notify.http_notify.param, sys_config.dev_id);
				usr_c322_wifista_HTTP_request(request);
				notify.http_notify.status = httpTeacherLoginCheck((char*)uart.uart_x->pRx_buffer);

				uart.uart_x->rx_status = 0;
				memset(uart.uart_x->pRx_buffer, 0, uart.uart_x->rx_buffer_len);
				pmsg.hWin = hSubExpWin;
				pmsg.MsgId = WM_BUTTON_BEGIN_CB;
				pmsg.Data.p = &notify;
				WM_SendMessage(hSubExpWin, &pmsg);
				GUI_Exec();
				break;
			
			case http_student_start_exp:
				sprintf((char *)request, "https://%s/openApi/experiment/stu/startExpe.json?moduleId=%d&userId=%s", 
							  http_wifista_ip, present_list_status, routine.online_uid_list[0]);
				if(strcmp(routine.class_id, "NULL") != 0)
					snprintf((char *)request, sizeof(request), "&tClzId=%s", routine.class_id);
				else;
				if(routine.appointed_expid != -1)
					snprintf((char *)request, sizeof(request), "&expeArrangementId=%d", routine.appointed_expid);
				else;
				usr_c322_wifista_HTTP_request(request);
				notify.http_notify.status = httpStudentStartExp((char*)uart.uart_x->pRx_buffer);
				
				uart.uart_x->rx_status = 0;
				memset(uart.uart_x->pRx_buffer, 0, uart.uart_x->rx_buffer_len);
				pmsg.hWin = hSubExpWin;
				pmsg.MsgId = WM_BUTTON_SCORE_CB;
				pmsg.Data.p = &notify;
				WM_SendMessage(hSubExpWin, &pmsg);
				GUI_Exec();
			break;

			case http_exp_score:
				sprintf((char *)request, "https://%s/openApi/experiment/mark.json?moduleId=%d&score=%d&studentId=%s&teacherId=%s", 
					http_wifista_ip, present_list_status, routine.main_exp.sub_exp[present_list_status - 1].subExpScore, routine.online_uid_list[0], routine.online_tid);
				if(strcmp(routine.class_id, "NULL") != 0)
					snprintf((char *)request, sizeof(request), "&tClzId=%s", routine.class_id);
				else;
				if(routine.appointed_expid != -1)
					snprintf((char *)request, sizeof(request), "&expeArrangementId=%d", routine.appointed_expid);
				else;
				usr_c322_wifista_HTTP_request(request);
				notify.http_notify.status = httpExpScore((char*)uart.uart_x->pRx_buffer);

				uart.uart_x->rx_status = 0;
				memset(uart.uart_x->pRx_buffer, 0, uart.uart_x->rx_buffer_len);
				pmsg.hWin = hSubExpWin;
				pmsg.MsgId = WM_BUTTON_SCORE_CB;
				pmsg.Data.p = &notify;
				WM_SendMessage(hSubExpWin, &pmsg);
				GUI_Exec();
				break;

			case http_logout_check:
				sprintf((char *)request, "https://%s/openApi/experiment/signOut.json?id=%s&userId=%s", http_wifista_ip, sys_config.dev_id, routine.appointed_uid[0]);
				usr_c322_wifista_HTTP_request(request);
				notify.http_notify.status = httpLogoutCheck((char*)uart.uart_x->pRx_buffer);

				uart.uart_x->rx_status = 0;
				memset(uart.uart_x->pRx_buffer, 0, uart.uart_x->rx_buffer_len);
				pmsg.hWin = hSubExpWin;
				pmsg.MsgId = WM_BUTTON_BEGIN_CB;
				pmsg.Data.p = &notify;
				WM_SendMessage(hSubExpWin, &pmsg);
				GUI_Exec();
				break;

			case http_record_update:
				sprintf((char *)request, "https://%s/openApi/experiment/log/refresh.json?id=%s&log=", http_wifista_ip, sys_config.dev_id);
				usr_c322_wifista_HTTP_request(request);
				notify.http_notify.status = httpRecordUpdate((char*)uart.uart_x->pRx_buffer);

				uart.uart_x->rx_status = 0;
				memset(uart.uart_x->pRx_buffer, 0, uart.uart_x->rx_buffer_len);
				break;

			case http_record_download:
				sprintf((char *)request, "https://%s/openApi/experiment/log/download.json?id=%s", http_wifista_ip, sys_config.dev_id);
				usr_c322_wifista_HTTP_request(request);
				notify.http_notify.status = httpRecordDownload((char*)uart.uart_x->pRx_buffer);

				uart.uart_x->rx_status = 0;
				memset(uart.uart_x->pRx_buffer, 0, uart.uart_x->rx_buffer_len);
				break;

			case http_sync_time:
				sprintf((char *)request, "https://%s/openApi/serverTime.json", http_wifista_ip);
				usr_c322_wifista_HTTP_request(request);
				httpRetVal = httpSyncTime((char*)uart.uart_x->pRx_buffer);
				if(HTTP_NO_DATA == httpRetVal)
					notify_show("网络连接错误", "时间校准失败");
				else if(HTTP_FALSE == httpRetVal)
					notify_show("请求失败", "时间校准失败");
				else if(HTTP_ERR == httpRetVal)
					notify_show("系统错误", "请稍后");
				
				uart.uart_x->rx_status = 0;
				memset(uart.uart_x->pRx_buffer, 0, uart.uart_x->rx_buffer_len);
				break;

			default:
				break;
			}
			switch (notify.mqtt_notify.event) {
				case mqtt_init:
					memset(&notify, 0, sizeof(notify));
					mqttRetVal = usr_c322_wifista_mqtt_init();
					if(MQTT_TIMEOUT == mqttRetVal) {
						notify_show("同步失败", "服务器登录超时");
						mqttPingFlag = flag_reset;
					}
					if(MQTT_OK == mqttRetVal) {
						if(pdFAIL == xQueueReset(xQueueWifi))			
							notify_show("队列清空失败", "请稍后");
						
						notify_show("同步成功", "初始化成功");
						mqttPingFlag = flag_set;
					}
				break;
				
				case mqtt_pingque:
					memset(&notify, 0, sizeof(notify));
					if(MQTT_TIMEOUT == usr_c322_wifista_mqtt_ping()) {
						notify_show("同步失败", "正在重试");
						notify.mqtt_notify.event = mqtt_restart;
						if(errQUEUE_FULL == xQueueSend(xQueueWifi, (const void *)&notify, 50)) 
							notify_show("操作无效", "请稍后");
						notify.mqtt_notify.event = mqtt_init;
						if(errQUEUE_FULL == xQueueSend(xQueueWifi, (const void *)&notify, 50)) 
							notify_show("操作无效", "请稍后");
						mqttPingFlag = flag_reset;
					}
				break;
				
				case mqtt_restart:
					memset(&notify, 0, sizeof(notify));
					wifiRetVal = usr_c322_wifista_mqtt_restart();
					if(WIFI_TCP_ERR == wifiRetVal) {
						if(pdFAIL == xQueueReset(xQueueWifi))			//每次重连WiFi都是新的开始
							notify_show("队列清空失败", "请稍后");
						notify_show("同步失败", "服务器连接超时");
					}
					else;
				break;
					
				case mqtt_subscribe:
					memset(&notify, 0, sizeof(notify));
					sprintf((char *)request, "experiment_control/%s", routine.online_uid_list[0]);
					if(MQTT_TIMEOUT == usr_c322_wifista_mqtt_subscribe(request)) {
						notify_show("同步失败", "正在重试");
						mqttPingFlag = flag_reset;
					}
					else if(MQTT_OK == mqttRetVal)
						if(pdFAIL == xQueueReset(xQueueWifi))			
							notify_show("队列清空失败", "请稍后");
				break;
				
				default:
				break;
			}
		}
		if(flag_set == wifiStateChangeFlag) {
			if(notify.setting.event != wifi_connect_check) {
				if(bit_wifi_status == WIFI_ERR) {
					notify.setting.event = wifi_connect_check;
					notify.setting.status = WIFI_ERR;

					pmsg.hWin = hMainWin;
					pmsg.MsgId = WM_WIFI_CONNECT_CB;
					pmsg.Data.p = &notify;
					WM_SendMessage(hMainWin, &pmsg);
					
					mqttPingFlag = flag_reset;
				} 
				else
					init_wifi_queue(notify);
			}
			wifiStateChangeFlag = flag_reset;
		} else;
		vTaskDelay(15);
	}
}

void scanner_task(void *pvParameters)
{
	wifi_config_t notify;
	u8 res;
	static u8 QR_Data[100];
	while(1) {
		if(ulTaskNotifyTake(pdTRUE, 0) > 0) {
			memset(&notify, 0, sizeof(notify));
			
			ui_effect.hWin = hFunctionImage1;
			ui_effect.status = effect_start;
			xTaskNotify(GuiTask_Handler, (uint32_t)(&ui_effect), eSetValueWithOverwrite);

			memset(QR_Data, 0, 100);
			QR_On();
			res = QR_RX_Data(QR_Data, http_wifista_ip);
			if(1 == res) {
				 if(present_bar_status == ACTION_LOGIN) {
                                        if(present_list_status == 1)
						notify.http_notify.event = http_student_login_check;
					else if(present_list_status == 2)
						notify.http_notify.event = http_logout_check;
					else;
				}
				else if(present_bar_status == ACTION_EXP_SCORE)
					notify.http_notify.event = http_teacher_login_check;
				else;
				notify.http_notify.param = (char *)QR_Data;
				if(errQUEUE_FULL == xQueueSend(xQueueWifi, (const void *)&notify, 50))
					notify_show("操作无效", "请稍后");
			} else if(0xff == res) {
				ui_effect.hWin = hFunctionImage1;
				ui_effect.status = effect_stop;
				xTaskNotify(GuiTask_Handler, (uint32_t)(&ui_effect), eSetValueWithOverwrite);

				notify_show("扫描超时", "请重试");
			} else {
				ui_effect.hWin = hFunctionImage1;
				ui_effect.status = effect_stop;
				xTaskNotify(GuiTask_Handler, (uint32_t)(&ui_effect), eSetValueWithOverwrite);

				notify_show("二维码错误", "请重试");
			}
		}
		vTaskDelay(20);
	}
}

void console_task(void *pvParameters)
{
	while(1) {
		vTaskDelay(25);
	}
}


void init_task(void *pvParameters)
{
	SPI_FLASH_BufferRead((u8 *)&dev_list, ADDR_SETTING_DATA, 1);
	if(dev_list.number == 0xff)
		dev_list.number = 0;
	else
		SPI_FLASH_BufferRead((u8 *)&dev_list, ADDR_SETTING_DATA, sizeof(dev_list));
	while(1) {
		vTaskDelay(30);
	}
}

void rc522_task(void *pvParameters)
{
	int times = 0;
	char epoch_dev_report[50];
	WM_MESSAGE pmsg;
	while(1) {
		if(ulTaskNotifyTake(pdTRUE, 0) > 0) {
			while(1) {
				if(epoch_rfid_ok == epochMatchDevice()) {
					WM_SendMessageNoPara(hSettingWindow, WM_RFID_MATCH_CB);
					voiceDispString("sound103");
					bsp_delay_ms(400);
					memset(epoch_dev_report, 0, 50);
					sprintf(epoch_dev_report, "%s, %s", voiceMatchSuccess, &(new_dev.id[13]));
					voiceDispString(epoch_dev_report);
					break;
				} else if(epoch_rfid_err == epochMatchDevice()) {
					voiceDispString("sound117");
					bsp_delay_ms(400);
					voiceDispString(voiceMatchFail);
					break;
				} else;
				times++;
				if(times > 100) {
					times = 0;
					voiceDispString("sound120");
					bsp_delay_ms(400);
					voiceDispString(voiceMatchTimeExpired);
					break;
				}
				vTaskDelay(10);
			}
			times = 0;
		}
		vTaskDelay(10);
	}
}

void menu_task(void *pvParameters)
{
        BaseType_t xResult;
        uint32_t ulValue;
        
	while(1) {
                xResult = xTaskNotifyWait((uint32_t)0x00, (uint32_t)0xffffffffUL, &ulValue, (TickType_t)0);
                if(xResult == pdPASS) {
                        menu_list_element_roleplay();
                        if(present_bar_status == ACTION_EXP_DETAIL || present_bar_status == ACTION_EXP_SCORE)
                                menu_reconstruct_list_content(present_bar_status, present_list_status);
                }
		vTaskDelay(10);
	}
}

void vTimerCallback(xTimerHandle pxTimer)
{
	wifi_config_t notify;
	WM_MESSAGE pmsg;
	uint32_t ulTimerID;
	memset(&notify, 0, sizeof(notify));
	
	configASSERT(pxTimer);
	
	if(pxTimer == xTimerWifiConnect) {
		xQueueReset(xQueueWifi);
		
		notify.setting.event = wifi_connect_check;
		notify.setting.status = WIFI_ERR;
		xQueueSend(xQueueWifi, (const void *)&notify, 50);
	}
	if(pxTimer == xTimerTcpCheck) {
		notify.setting.event = wifi_tcp_check;
		xQueueSend(xQueueWifi, (const void *)&notify, 50);
	}
}


