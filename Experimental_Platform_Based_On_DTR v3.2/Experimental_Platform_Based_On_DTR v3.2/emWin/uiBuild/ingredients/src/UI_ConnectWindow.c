#include "ep_app.h"

#define ID_FRAMEWIN_CONNECT_0  (GUI_ID_USER + 0x20)
#define ID_TEXT_CONNECT_0      (GUI_ID_USER + 0x22)
#define ID_TEXT_CONNECT_1      (GUI_ID_USER + 0x23)
#define ID_TEXT_CONNECT_2      (GUI_ID_USER + 0x24)
#define ID_TEXT_CONNECT_3      (GUI_ID_USER + 0x25)
#define ID_TEXT_CONNECT_4      (GUI_ID_USER + 0x26)
#define ID_EDIT_CONNECT_0      (GUI_ID_USER + 0x27)
#define ID_CHECKBOX_CONNECT_0  (GUI_ID_USER + 0x28)
#define ID_BUTTON_CONNECT_0    (GUI_ID_USER + 0x29)
#define ID_BUTTON_CONNECT_1    (GUI_ID_USER + 0x2A)
#define ID_TEXT_CONNECT_5      (GUI_ID_USER + 0x2B)

WM_HWIN hConnectWindow;
WM_HWIN hConnectContentText1;
WM_HWIN hConnectContentText2;
WM_HWIN hConnectContentText3;
WM_HWIN hConnectEdit;

WM_HWIN hConnectButton0;
WM_HWIN hConnectPromptText1;
WM_HWIN hConnectPromptText2;
WM_HWIN hConnectPromptText3;

static void _cbDialog(WM_MESSAGE * pMsg) {
	WM_HWIN hItem;
	int     NCode;
	int     Id;
	u8	i;
	u8 	selectRow;
	u8 	p[50];
	wifi_config_t wifi_config;
	memset(&wifi_config, 0, sizeof(wifi_config));

	switch (pMsg->MsgId) {
	case WM_INIT_DIALOG:

	hItem = pMsg->hWin;
	FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	FRAMEWIN_SetFont(hItem,  &YaHei_24_Font);
	FRAMEWIN_SetText(hItem, "连接设置");
	FRAMEWIN_SetTitleHeight(hItem, 24);

	hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_CONNECT_0);
	hConnectPromptText1 = hItem;
	TEXT_SetFont(hItem,  &YaHei_24_Font);
	TEXT_SetText(hItem, "WIFI名称:");

	hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_CONNECT_1);
	hConnectContentText1 = hItem;
	TEXT_SetFont(hItem,  &YaHei_24_Font);
	TEXT_SetText(hItem, "");

	hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_CONNECT_2);
	hConnectPromptText2 = hItem;
	TEXT_SetFont(hItem,  &YaHei_24_Font);
	TEXT_SetText(hItem, "加密状态:");

	hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_CONNECT_3);
	hConnectContentText2 = hItem;
	TEXT_SetFont(hItem,  &YaHei_24_Font);
	TEXT_SetText(hItem, "");

	hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_CONNECT_4);
	hConnectPromptText3 = hItem;
	TEXT_SetFont(hItem,  &YaHei_24_Font);
	TEXT_SetText(hItem, "WIFI密码:");
	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_CONNECT_5);
	hConnectContentText3 = hItem;
	TEXT_SetFont(hItem,  &YaHei_24_Font);
	TEXT_SetText(hItem, "");

	hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_CONNECT_0);
	hConnectButton0 = hItem;
	BUTTON_SetFont(hItem,  &YaHei_24_Font);
	BUTTON_SetText(hItem, "连接");

	hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_CONNECT_1);
	BUTTON_SetFont(hItem,  &YaHei_24_Font);
	BUTTON_SetText(hItem, "取消");

	hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_CONNECT_0);
	hConnectEdit = hItem;
	EDIT_SetFont(hItem,  &YaHei_24_Font);

	break;

	case WM_NOTIFY_PARENT:
	Id    = WM_GetId(pMsg->hWinSrc);
	NCode = pMsg->Data.v;
	switch(Id) {
	case ID_EDIT_CONNECT_0: 
	  switch(NCode) {
	  case WM_NOTIFICATION_CLICKED:
		  break;
	  }
	  break;
	case ID_BUTTON_CONNECT_0:                           			//连接WIFI键 切换状态
	  switch(NCode) {
	  case WM_NOTIFICATION_RELEASED:
			memset(p, 0, sizeof(p));
			BUTTON_GetText(hScanButton, (char *)p, sizeof(p));
			if(strstr("刷新列表", (char *)p)) {
				memset(wifi_data.password, 0, sizeof(wifi_data.password));
				EDIT_GetText(hConnectEdit, wifi_data.password, sizeof(wifi_data.password));
				IMAGE_SetBitmap(hWifiStateImage, &bmwifi_off);
											
				ui_effect.hWin = hWifiStateImage;
				ui_effect.status = effect_start;
				xTaskNotify(GuiTask_Handler, (uint32_t)(&ui_effect), eSetValueWithOverwrite );
				
				if(pdFAIL == xQueueReset(xQueueWifi))		//每次重连WiFi都是新的开始
					notify_show("队列清空失败", "请稍后");
				memset(&wifi_config.setting, 0, sizeof(wifi_config.setting));
				wifi_config.setting.event = wifi_connect;
				if(errQUEUE_FULL == xQueueSend(xQueueWifi, (const void *)(&wifi_config), 50)) 
					notify_show("操作无效", "请稍后");
				
				EDIT_SetText(hConnectEdit, "");
				WM_HideWindow(hFullKeyboard);
			}
			else if(strstr("开始匹配", (char *)p)) {
				memset(p, 0, sizeof(p));
				BUTTON_GetText(hConnectButton0, (char *)p, sizeof(p));
				if(strstr("连接", (char *)p)) {
					if(dev_list.number < 20) {
						for(i = 0; i < dev_list.number; i++) {
							if(0 == strcmp(dev_list.connected_dev[i].id, new_dev.id)) {
								notify_show("此设备已连接", "请选择其他设备");
								break;
							}
						}
						if(i == dev_list.number) {
							memcpy(&dev_list.connected_dev[dev_list.number], &new_dev, sizeof(new_dev));
							LISTVIEW_SetItemText(hConnectList, 0, dev_list.number + 1, new_dev.name);
							switch (new_dev.type) {
							case EPOCH_IIPCD :
								LISTVIEW_SetItemText(hConnectList, 1, dev_list.number + 1, "电源控制设备");
								break;
							default :
								break;
							}
							LISTVIEW_SetItemText(hConnectList, 2, dev_list.number + 1, &new_dev.id[13]);
							dev_list.number++;
							SPI_FLASH_BufferWrite((u8 *)&dev_list, ADDR_SETTING_DATA, sizeof(dev_list));
						}
					}
					else 
						notify_show("设备列表已满", "请删除某个设备");
				}
				else if(strstr("删除", (char *)p)) {
					selectRow = LISTVIEW_GetSel(hConnectList);
					LISTVIEW_DeleteRow(hConnectList, selectRow);
					LISTVIEW_AddRow(hConnectList, NULL);
					memset(&dev_list.connected_dev[selectRow - 1], 0, sizeof(epoch_dev_t));
					dev_list.number--;
					SPI_FLASH_BufferWrite((u8 *)&dev_list, ADDR_SETTING_DATA, sizeof(dev_list));
				}
			}
			WM_HideWindow(hConnectEdit);
			WM_HideWindow(hConnectContentText3);
			WM_HideWindow(hConnectWindow);
		  break;
	  }
	  break;
	case ID_BUTTON_CONNECT_1: 										//取消键
	  switch(NCode) {
	  case WM_NOTIFICATION_RELEASED:
			WM_HideWindow(hConnectEdit);
			WM_HideWindow(hConnectContentText3);
			WM_HideWindow(hFullKeyboard);
			WM_HideWindow(hConnectWindow);
		  break;
	  }
		break;

	}
	break;
	default:
	WM_DefaultProc(pMsg);
	break;
	}
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       createFramewin
*/
WM_HWIN connectWindowOnCreate(void);
WM_HWIN connectWindowOnCreate(void) {
	
  WM_HWIN hWin;
	
  GUI_WIDGET_CREATE_INFO _aDialogcreate[] = {
  { FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_CONNECT_0, 275, 40, 300, 160, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_CONNECT_0, 5, 5, 110, 30, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_CONNECT_1, 100, 5, 110, 30, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_CONNECT_2, 5, 35, 80, 30, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_CONNECT_3, 100, 35, 110, 30, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_CONNECT_4, 5, 65, 110, 30, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_CONNECT_5, 100, 65, 110, 30, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_CONNECT_0, 100, 65, 130, 26, 0, 0x64, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_CONNECT_0, 20, 95, 80, 25, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_CONNECT_1, 185, 95, 80, 25, 0, 0x0, 0 },
};
	
  hWin = GUI_CreateDialogBox(_aDialogcreate, GUI_COUNTOF(_aDialogcreate), _cbDialog, WM_HBKWIN, 0, 0);
  WM_HideWindow(hWin);
  return hWin;
}



// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
