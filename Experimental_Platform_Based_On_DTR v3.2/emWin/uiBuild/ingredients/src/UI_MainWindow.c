#include "DIALOG.h"
#include "ep_app.h"

#define ID_WINDOW_MAIN          (GUI_ID_USER + 0x00)
#define ID_IMAGE_HDU_PIC        (GUI_ID_USER + 0x01)
#define ID_IMAGE_SIDE_BAR       (GUI_ID_USER + 0x02)
#define ID_IMAGE_BOTTOM_BAR     (GUI_ID_USER + 0x03)
#define ID_IMAGE_HDU_LOGO       (GUI_ID_USER + 0x04)
#define ID_TEXT_EXP_DETAIL      (GUI_ID_USER + 0x05)
#define ID_TEXT_EXP_SCORE       (GUI_ID_USER + 0x06)
#define ID_TEXT_MAC_SETTING     (GUI_ID_USER + 0x07)
#define ID_TEXT_MAC_INFO        (GUI_ID_USER + 0x08)
#define ID_TEXT_DATE            (GUI_ID_USER + 0x09)
#define ID_TEXT_TIME            (GUI_ID_USER + 0x0A)
#define ID_TEXT_SUB_TITLE_1     (GUI_ID_USER + 0x0B)
#define ID_TEXT_SUB_CONTENT_1   (GUI_ID_USER + 0x0C)
#define ID_TEXT_SUB_TITLE_2     (GUI_ID_USER + 0x0D)
#define ID_TEXT_SUB_CONTENT_2   (GUI_ID_USER + 0x0E)
#define ID_TEXT_SUB_TITLE_3     (GUI_ID_USER + 0x0F)
#define ID_TEXT_SUB_CONTENT_3   (GUI_ID_USER + 0x10)
#define ID_TEXT_EXP_NAME        (GUI_ID_USER + 0x11)
#define ID_TEXT_EXP_STEP        (GUI_ID_USER + 0x12)
#define ID_TEXT_EXP_CONTENT_1   (GUI_ID_USER + 0x13)
#define ID_TEXT_EXP_CONTENT_2   (GUI_ID_USER + 0x14)
#define ID_TEXT_EXP_CONTENT_3   (GUI_ID_USER + 0x15)
#define ID_TEXT_EXPIRED_NOTE    (GUI_ID_USER + 0x16)
#define ID_TEXT_EXPIRED_TIME    (GUI_ID_USER + 0x17)
#define ID_IMAGE_HIGHLIGHT_BAR  (GUI_ID_USER + 0x18)
#define ID_IMAGE_HIGHLIGHT_LIST (GUI_ID_USER + 0x19)
#define ID_IMAGE_EXP_STATUS_1   (GUI_ID_USER + 0x1A)
#define ID_IMAGE_EXP_STATUS_2   (GUI_ID_USER + 0x1B)
#define ID_IMAGE_EXP_STATUS_3   (GUI_ID_USER + 0x1C)
#define ID_IMAGE_WIFI_STATE	(GUI_ID_USER + 0x1D)

WM_HWIN hMainWin;
WM_HWIN hBarWin;
WM_HWIN hListWin;
WM_HWIN hDateWin;
WM_HWIN hTimeWin;

WM_HWIN hSubListTitle1;
WM_HWIN hSubListTitle2;
WM_HWIN hSubListTitle3;
WM_HWIN hSubListContent1;
WM_HWIN hSubListContent2;
WM_HWIN hSubListContent3;

WM_HWIN hWifiStateImage;
WM_HWIN hExpStatusImage1;
WM_HWIN hExpStatusImage2;
WM_HWIN hExpStatusImage3;

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
	{ WINDOW_CreateIndirect, "Window", ID_WINDOW_MAIN, 0, 0, 800, 480, 0, 0x0, 0 },
	{ IMAGE_CreateIndirect, "Image", ID_IMAGE_HDU_PIC, 0, 0, 126, 123, 0, 0, 0 },
	{ IMAGE_CreateIndirect, "Image", ID_IMAGE_SIDE_BAR, 126, 1, 29, 478, 0, 0, 0 },
	{ IMAGE_CreateIndirect, "Image", ID_IMAGE_BOTTOM_BAR, 2, 464, 124, 14, 0, 0, 0 },
	{ IMAGE_CreateIndirect, "Image", ID_IMAGE_HDU_LOGO, 30, 382, 66, 67, 0, 0, 0 },
	{ IMAGE_CreateIndirect, "Image", ID_IMAGE_WIFI_STATE, 365, 0, 30, 30, 0, 0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_EXP_DETAIL, 0, 164, 126, 27, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_EXP_SCORE, 0, 218, 126, 27, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_MAC_SETTING, 0, 272, 126, 27, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_MAC_INFO, 0, 326, 126, 27, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_DATE, 155, 20, 203, 40, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_TIME, 155, 60, 203, 40, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_SUB_TITLE_1, 159, 124, 196, 27, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_SUB_CONTENT_1, 155, 158, 196, 27, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_SUB_TITLE_2, 159, 206, 196, 27, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_SUB_CONTENT_2, 155, 242, 196, 27, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_SUB_TITLE_3, 159, 292, 196, 27, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_SUB_CONTENT_3, 155, 325, 196, 27, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_EXPIRED_NOTE, 155, 390, 204, 40, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_EXPIRED_TIME, 155, 430, 204, 40, 0, 0x0, 0 },
	{ IMAGE_CreateIndirect, "Image", ID_IMAGE_HIGHLIGHT_BAR, 0, 158, 126, 38, 0, 0, 0 },
	{ IMAGE_CreateIndirect, "Image", ID_IMAGE_HIGHLIGHT_LIST, 154, 115, 201, 80, 0, 0, 0 },
	{ IMAGE_CreateIndirect, "Image", ID_IMAGE_EXP_STATUS_1, 320, 126, 20, 20, 0, 0, 0 },
	{ IMAGE_CreateIndirect, "Image", ID_IMAGE_EXP_STATUS_2, 320, 208, 20, 20, 0, 0, 0 },
	{ IMAGE_CreateIndirect, "Image", ID_IMAGE_EXP_STATUS_3, 320, 294, 20, 20, 0, 0, 0 }
};

static void _cbDialog(WM_MESSAGE * pMsg)
{
	const void * pData;
	WM_HWIN      hItem;
	U32          FileSize;
	wifi_config_t notify;
	static u8 recheck_times = 10;

	switch (pMsg->MsgId) {
	case WM_INIT_DIALOG:

		hItem = pMsg->hWin;
		WINDOW_SetBkColor(hItem, 0x00FFFCF9);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_HDU_PIC);
		IMAGE_SetBitmap(hItem, &bmhdu_pic);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_SIDE_BAR);
		IMAGE_SetBitmap(hItem, &bmright_side_bar);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_BOTTOM_BAR);
		IMAGE_SetBitmap(hItem, &bmbuttom_bar);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_HDU_LOGO);
		IMAGE_SetBitmap(hItem, &bmhdu_logo);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_HDU_PIC);
		IMAGE_SetBitmap(hItem, &bmhdu_pic);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_WIFI_STATE);
		hWifiStateImage = hItem;
		IMAGE_SetBitmap(hItem, &bmwifi_off);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_EXP_STATUS_1);
		hExpStatusImage1 = hItem;
		IMAGE_SetBitmap(hItem, &bmunfinished);
		WM_HideWindow(hItem);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_EXP_STATUS_2);
		hExpStatusImage2 = hItem;
		IMAGE_SetBitmap(hItem, &bmunfinished);
		WM_HideWindow(hItem);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_EXP_STATUS_3);
		hExpStatusImage3 = hItem;
		IMAGE_SetBitmap(hItem, &bmunfinished);
		WM_HideWindow(hItem);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_EXP_DETAIL);
		TEXT_SetFont(hItem,  &YaHei_24_Font);
		TEXT_SetTextColor(hItem, 0x00868380);
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_TOP);
		TEXT_SetText(hItem, "学生签到");

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_EXP_SCORE);
		TEXT_SetFont(hItem,  &YaHei_24_Font);
		TEXT_SetTextColor(hItem, 0x00868380);
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_TOP);
		TEXT_SetText(hItem, "实验详情");

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_MAC_SETTING);
		TEXT_SetFont(hItem,  &YaHei_24_Font);
		TEXT_SetTextColor(hItem, 0x00868380);
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_TOP);
		TEXT_SetText(hItem, "实验评分");

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_MAC_INFO);
		TEXT_SetFont(hItem,  &YaHei_24_Font);
		TEXT_SetTextColor(hItem, 0x00868380);
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_TOP);
		TEXT_SetText(hItem, "机器设置");

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_DATE);
		hDateWin = hItem;
		TEXT_SetFont(hItem,  &YaHei_36_Font);
		TEXT_SetTextColor(hItem, 0x00868380);
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_TOP);
		TEXT_SetText(hItem, "");

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_TIME);
		hTimeWin = hItem;
		TEXT_SetFont(hItem,  &YaHei_36_Font);
		TEXT_SetTextColor(hItem, 0x00868380);
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_TOP);
		TEXT_SetText(hItem, "");

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SUB_TITLE_1);
		hSubListTitle1 = hItem;
		TEXT_SetFont(hItem,  &YaHei_24_Font);
		TEXT_SetTextColor(hItem, 0x00868380);
		TEXT_SetTextAlign(hItem, GUI_TA_TOP);
		TEXT_SetText(hItem, "");

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SUB_CONTENT_1);
		hSubListContent1 = hItem;
		TEXT_SetFont(hItem,  &YaHei_24_Font);
		TEXT_SetTextColor(hItem, 0x00868380);
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_TOP);
		TEXT_SetText(hItem, "");

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SUB_TITLE_2);
		hSubListTitle2 = hItem;
		TEXT_SetFont(hItem,  &YaHei_24_Font);
		TEXT_SetTextColor(hItem, 0x00868380);
		TEXT_SetTextAlign(hItem, GUI_TA_TOP);
		TEXT_SetText(hItem, "");

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SUB_CONTENT_2);
		hSubListContent2 = hItem;
		TEXT_SetFont(hItem,  &YaHei_24_Font);
		TEXT_SetTextColor(hItem, 0x00868380);
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_TOP);
		TEXT_SetText(hItem, "");

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SUB_TITLE_3);
		hSubListTitle3 = hItem;
		TEXT_SetFont(hItem,  &YaHei_24_Font);
		TEXT_SetTextColor(hItem, 0x00868380);
		TEXT_SetTextAlign(hItem, GUI_TA_TOP);
		TEXT_SetText(hItem, "");

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SUB_CONTENT_3);
		hSubListContent3 = hItem;
		TEXT_SetFont(hItem,  &YaHei_24_Font);
		TEXT_SetTextColor(hItem, 0x00868380);
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_TOP);
		TEXT_SetText(hItem, "");

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_EXPIRED_NOTE);
		TEXT_SetFont(hItem,  &YaHei_36_Font);
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_TOP);
		TEXT_SetTextColor(hItem, 0x00868380);
		TEXT_SetText(hItem, "剩余时间");

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_EXPIRED_TIME);
		TEXT_SetFont(hItem,  &YaHei_36_Font);
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_TOP);
		TEXT_SetTextColor(hItem, 0x00F0B62B);
		TEXT_SetText(hItem, "45 : 00");

		hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_HIGHLIGHT_BAR);
		hBarWin = hItem;
		IMAGE_SetBitmap(hItem, &bmrect_bar);
		WM_BringToBottom(hItem);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_HIGHLIGHT_LIST);
		hListWin = hItem;
		IMAGE_SetBitmap(hItem, &bmrect_sublist);
		WM_BringToBottom(hItem);
		break;

	case WM_PAINT :
		GUI_SetColor(0x00E1DDD8);
		GUI_DrawHLine(100, 159, 159 + 184);
		GUI_DrawHLine(383, 159, 159 + 184);
		GUI_DrawVLine(358, 10, 10 + 450);

		GUI_SetColor(0x00F9F2D4);
		GUI_FillRect(363, 385, 363 + 432, 385 + 84);

		GUI_SetBkColor(0x00F9F2D4);
		GUI_SetFont(&YaHei_24_Font);
		GUI_SetColor(0x009B5C0A);
		GUI_DispStringAt("经典书籍推荐", 374, 394);
		GUI_SetColor(0x00868380);
		GUI_DispStringAt("\"深入理解计算机系统 \"", 479, 432);
		break;

	case WM_WIFI_CONNECT_CB:
		memcpy(&notify, pMsg->Data.p, sizeof(notify));
		switch(notify.setting.event) {
			case wifi_connect_check:
				switch(notify.setting.status) {
					case WIFI_OK:
						notify_show((char *)wifi_data.name, "连接成功");
					break;
					
					case WIFI_ERR:
						if(pdFAIL == xQueueReset(xQueueWifi))		
							notify_show("队列清空失败", "请稍后");
					
						ui_effect.hWin = hWifiStateImage;
						ui_effect.status = effect_stop;
						xTaskNotify(GuiTask_Handler, (uint32_t)(&ui_effect), eSetValueWithOverwrite );

						IMAGE_SetBitmap(hWifiStateImage, &bmwifi_off);
						notify_show("无线网络", "连接失败");
					break;
					
					default:
					break;
				}
			break;
			
			case wifi_ping_check:
				switch(notify.setting.status) {
					case WIFI_OK:

					break;
					
					case WIFI_SERVER_ERR:
						if(pdFAIL == xQueueReset(xQueueWifi))		
							notify_show("队列清空失败", "请稍后");
					
						ui_effect.hWin = hWifiStateImage;
						ui_effect.status = effect_stop;
						xTaskNotify(GuiTask_Handler, (uint32_t)(&ui_effect), eSetValueWithOverwrite );
						
						notify_show((char *)wifi_data.name, "无法连接到服务器");
					break;
					
					default:
					break;
				}
			break;
				
			case wifi_tcp_check:
				switch(notify.setting.status) {
					case WIFI_OK:
						ui_effect.hWin = hWifiStateImage;
						ui_effect.status = effect_stop;
						xTaskNotify(GuiTask_Handler, (uint32_t)(&ui_effect), eSetValueWithOverwrite );
						
						memset(&notify, 0 , sizeof(notify));
						IMAGE_SetBitmap(hWifiStateImage, &bmwifi);
					break;
					
					case WIFI_TCP_ERR:
						if(recheck_times > 0) {
							xTimerStart(xTimerTcpCheck, 100);
							recheck_times--;
						}
						else {
							if(pdFAIL == xQueueReset(xQueueWifi))		
								notify_show("队列清空失败", "请稍后");
							
							ui_effect.hWin = hWifiStateImage;
							ui_effect.status = effect_stop;
							xTaskNotify(GuiTask_Handler, (uint32_t)(&ui_effect), eSetValueWithOverwrite );
							
							recheck_times = 10;
							notify_show((char *)wifi_data.name, "服务器连接超时");
						}
							
					break;
					default:
						
					break;
				}
			break;
			
			default:
			break;
		}
		break;

	default:
		WM_DefaultProc(pMsg);
		break;
	}
}

WM_HWIN mainWindowOnCreate(void)
{
	WM_HWIN hWin, hOldWin;
	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);

	GUI_Exec();

	hOldWin = WM_SelectWindow(WM_GetClientWindow(hWin));
	GUI_SetColor(0x00E1DDD8);
	GUI_DrawHLine(100, 159, 159 + 184);
	GUI_DrawHLine(383, 159, 159 + 184);
	GUI_DrawVLine(358, 10, 10 + 450);

	GUI_SetColor(0x00F9F2D4);
	GUI_FillRect(363, 385, 363 + 432, 385 + 84);

	GUI_SetBkColor(0x00F9F2D4);
	GUI_SetFont(&YaHei_24_Font);
	GUI_SetColor(0x009B5C0A);
	GUI_DispStringAt("经典书籍推荐", 374, 394);
	GUI_SetColor(0x00868380);
	GUI_DispStringAt("\"深入理解计算机系统 \"", 479, 432);
	return hWin;
}

/*************************** End of file ****************************/
