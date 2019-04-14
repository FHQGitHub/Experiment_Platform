#include "DIALOG.h"
#include "ep_app.h"

#define ID_WINDOW_0    (GUI_ID_USER + 0x00)
#define ID_TEXT_INFO_0 (GUI_ID_USER + 0x01)
#define ID_TEXT_INFO_1 (GUI_ID_USER + 0x02)
#define ID_TEXT_INFO_2 (GUI_ID_USER + 0x03)
#define ID_TEXT_INFO_3 (GUI_ID_USER + 0x04)
#define ID_TEXT_INFO_4 (GUI_ID_USER + 0x05)
#define ID_TEXT_INFO_5 (GUI_ID_USER + 0x06)
#define ID_TEXT_INFO_6 (GUI_ID_USER + 0x07)
#define ID_TEXT_INFO_7 (GUI_ID_USER + 0x08)
#define ID_TEXT_INFO_8 (GUI_ID_USER + 0x09)
#define ID_TEXT_INFO_9 (GUI_ID_USER + 0x0A)

#define ID_TEXT_VOICE 						(GUI_ID_USER + 0x10)
#define ID_TEXT_VOLUME 						(GUI_ID_USER + 0x11)
#define ID_BUTTON_VOICE 					(GUI_ID_USER + 0x12)
#define ID_SLIDER_VOLUME 					(GUI_ID_USER + 0x13)
#define ID_BUTTON_WIFI_LIST 					(GUI_ID_USER + 0x14)
#define ID_BUTTON_RFID_LIST 					(GUI_ID_USER + 0x15)
#define ID_LISTVIEW_CONNECT_LIST 				(GUI_ID_USER + 0x16)
#define ID_IMAGE_BACK 						(GUI_ID_USER + 0x17)
#define ID_BUTTON_BACK 						(GUI_ID_USER + 0x18)
#define ID_BUTTON_WIFI_SCAN					(GUI_ID_USER + 0x19)
#define ID_TEXT_MUX 						(GUI_ID_USER + 0x1A)
#define ID_TEXT_DEVID						(GUI_ID_USER + 0x1B)
#define ID_BUTTON_MUX						(GUI_ID_USER + 0x1C)
#define ID_EDIT_DEVID						(GUI_ID_USER + 0x1D)
#define ID_IMAGE_ADMIN						(GUI_ID_USER + 0x1F)
#define ID_BUTTON_ADMIN						(GUI_ID_USER + 0x20)


WM_HWIN hSettingWindow;
WM_HWIN hInfoText0;
WM_HWIN hInfoText1;
WM_HWIN hInfoText2;
WM_HWIN hInfoText3;
WM_HWIN hInfoText4;
WM_HWIN hInfoText5;
WM_HWIN hInfoText6;
WM_HWIN hInfoText7;
WM_HWIN hInfoText8;
WM_HWIN hInfoText9;

WM_HWIN hPreferenceText0;
WM_HWIN hPreferenceText1;
WM_HWIN hPreferenceTextMux;
WM_HWIN hPreferenceTextDevID;
WM_HWIN hVoiceButton;
WM_HWIN hVolumeSlider;
WM_HWIN hMuxButton;
WM_HWIN hDevIdEdit;
WM_HWIN hConnectList;
WM_HWIN hWifiListButton;
WM_HWIN hRfidListButton;
WM_HWIN hBackImage;
WM_HWIN hBackButton;
WM_HWIN hScanButton;
WM_HWIN hVolumeSlider;
WM_HWIN hAdminImage;
WM_HWIN hAdminButton;

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
	{ WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 400, 350, 27, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_INFO_0, 50, 20, 370, 30, 27, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_INFO_1, 50, 50, 370, 30, 27, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_INFO_2, 50, 80, 370, 30, 27, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_INFO_3, 50, 110, 370, 30, 27, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_INFO_4, 50, 140, 370, 30, 27, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_INFO_5, 50, 170, 370, 30, 27, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_INFO_6, 50, 200, 370, 30, 27, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_INFO_7, 50, 230, 370, 30, 27, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_INFO_8, 50, 260, 370, 30, 27, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_INFO_9, 0, 320, 400, 30, 27, 0x0, 0 },

	{ TEXT_CreateIndirect, "Text", ID_TEXT_VOICE, 50, 80, 120, 40, 27, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_VOLUME, 50, 200, 120, 40, 27, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_MUX, 50, 140, 120, 40, 27, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_DEVID, 50, 260, 120, 40, 27, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_VOICE, 220, 80, 120, 38, 27, 0x0, 0 },
	{ SLIDER_CreateIndirect, "Slider", ID_SLIDER_VOLUME, 220, 200, 150, 30, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_MUX, 220, 150, 150, 38, 27, 0x0, 0},
	{ EDIT_CreateIndirect, "Edit", ID_EDIT_DEVID, 220, 260, 150, 30, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_WIFI_LIST, 30, 150, 140, 38, 27, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_RFID_LIST, 220, 150, 140, 38, 27, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_WIFI_SCAN, 30, 30, 140, 38, 27, 0x0, 0 },
	{ LISTVIEW_CreateIndirect, "Listview", ID_LISTVIEW_CONNECT_LIST, 0, 80, 400, 250, 27, 0x0, 0 },

	{ IMAGE_CreateIndirect, "Image", ID_IMAGE_BACK, 263, 10, 60, 60, 0, 0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_BACK, 294, 13, 96, 27, 0, 0x0, 0 },
	
	{ IMAGE_CreateIndirect, "Image", ID_IMAGE_ADMIN, 167, 230, 66, 67, 0, 0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_ADMIN, 128, 310, 144, 40, 0, 0x0, 0 },
};



static void pushButtonInitDialog(void)
{
	BUTTON_SetFont(hAdminButton,  &YaHei_36_Font);
	BUTTON_SetTextColor(hAdminButton, BUTTON_CI_DISABLED, 0x009B5C0A);
	BUTTON_SetTextColor(hAdminButton, BUTTON_CI_PRESSED, 0x009B5C0A);
	BUTTON_SetTextColor(hAdminButton, BUTTON_CI_UNPRESSED, 0x009B5C0A);
	BUTTON_SetText(hAdminButton, "管理员入口");
	WM_SetCallback(hAdminButton, _cbPushButtonText);
	
	BUTTON_SetFont(hWifiListButton,  &YaHei_36_Font);
	BUTTON_SetTextColor(hWifiListButton, BUTTON_CI_DISABLED, 0x009B5C0A);
	BUTTON_SetTextColor(hWifiListButton, BUTTON_CI_PRESSED, 0x009B5C0A);
	BUTTON_SetTextColor(hWifiListButton, BUTTON_CI_UNPRESSED, 0x009B5C0A);
	BUTTON_SetText(hWifiListButton, "WIFI设置");
	WM_SetCallback(hWifiListButton, _cbPushButtonText);

	BUTTON_SetFont(hRfidListButton,  &YaHei_36_Font);
	BUTTON_SetTextColor(hRfidListButton, BUTTON_CI_DISABLED, 0x009B5C0A);
	BUTTON_SetTextColor(hRfidListButton, BUTTON_CI_PRESSED, 0x009B5C0A);
	BUTTON_SetTextColor(hRfidListButton, BUTTON_CI_UNPRESSED, 0x009B5C0A);
	BUTTON_SetText(hRfidListButton, "匹配设备");
	WM_SetCallback(hRfidListButton, _cbPushButtonText);

	BUTTON_SetFont(hScanButton,  &YaHei_36_Font);
	BUTTON_SetTextColor(hScanButton, BUTTON_CI_DISABLED, 0x009B5C0A);
	BUTTON_SetTextColor(hScanButton, BUTTON_CI_PRESSED, 0x009B5C0A);
	BUTTON_SetTextColor(hScanButton, BUTTON_CI_UNPRESSED, 0x009B5C0A);
	BUTTON_SetText(hScanButton, "刷新列表");
	WM_SetCallback(hScanButton, _cbPushButtonText);

	BUTTON_SetFont(hBackButton,  &YaHei_24B_Font);
	BUTTON_SetTextColor(hBackButton, BUTTON_CI_DISABLED, GUI_BLACK);
	BUTTON_SetTextColor(hBackButton, BUTTON_CI_PRESSED, GUI_BLACK);
	BUTTON_SetTextColor(hBackButton, BUTTON_CI_UNPRESSED, GUI_BLACK);
	BUTTON_SetText(hBackButton, "返回");
	WM_SetCallback(hBackButton, _cbPushButtonText);

}

static void _cbDialog(WM_MESSAGE * pMsg)
{
	WM_HWIN 	hItem;
	int     	NCode;
	int     	Id;
	int		i, j;
	u8 		slideValue = 0;
	u8 		volumeString[20];
	u8 		p[50];
	wifi_config_t 	*notify = NULL;
	epoch_dev_t 	*epoch_notify = NULL;
	wifi_config_t 	wifi_config;
	memset(&wifi_config, 0, sizeof(wifi_config));

	switch (pMsg->MsgId) {
	case WM_INIT_DIALOG:
		hItem = pMsg->hWin;
		WINDOW_SetBkColor(hItem, 0x00FFFCF9);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_CONNECT_LIST);
		hConnectList = hItem;
		LISTVIEW_SetAutoScrollV(hItem, 1);
		LISTVIEW_SetFont(hItem, &YaHei_24B_Font);
		LISTVIEW_SetHeaderHeight(hItem, 0);
		LISTVIEW_AddColumn(hItem, 133, "", GUI_TA_HCENTER | GUI_TA_VCENTER);
		LISTVIEW_AddColumn(hItem, 133, "", GUI_TA_HCENTER | GUI_TA_VCENTER);
		LISTVIEW_AddColumn(hItem, 133, "", GUI_TA_HCENTER | GUI_TA_VCENTER);

		for(i = 0; i < 20; i++)
			LISTVIEW_AddRow(hItem, NULL);

		LISTVIEW_SetGridVis(hItem, 1);
		LISTVIEW_DisableRow(hItem, 0);
		WM_HideWindow(hItem);
	
		hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_ADMIN);
                hAdminImage = hItem;
                IMAGE_SetBitmap(hItem, &bmhdu_logo);
                WM_HideWindow(hItem);
		
		hAdminButton = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_ADMIN);
		WM_HideWindow(hAdminButton);
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_INFO_0);
		hInfoText0 = hItem;
		TEXT_SetFont(hItem,  &YaHei_24_Font);
		TEXT_SetTextAlign(hItem, GUI_TA_VCENTER);
		TEXT_SetText(hItem, "");
		WM_HideWindow(hItem);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_INFO_1);
		hInfoText1 = hItem;
		TEXT_SetFont(hItem,  &YaHei_24_Font);
		TEXT_SetTextAlign(hItem, GUI_TA_VCENTER);
		TEXT_SetText(hItem, "");

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_INFO_2);
		hInfoText2 = hItem;
		TEXT_SetFont(hItem,  &YaHei_24_Font);
		TEXT_SetTextAlign(hItem, GUI_TA_VCENTER);
		TEXT_SetText(hItem, "");
		WM_HideWindow(hItem);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_INFO_3);
		hInfoText3 = hItem;
		TEXT_SetFont(hItem,  &YaHei_24_Font);
		TEXT_SetTextAlign(hItem, GUI_TA_VCENTER);
		TEXT_SetText(hItem, "");
		WM_HideWindow(hItem);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_INFO_4);
		hInfoText4 = hItem;
		TEXT_SetFont(hItem,  &YaHei_24_Font);
		TEXT_SetTextAlign(hItem, GUI_TA_VCENTER);
		TEXT_SetText(hItem, "");
		WM_HideWindow(hItem);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_INFO_5);
		hInfoText5 = hItem;
		TEXT_SetFont(hItem,  &YaHei_24_Font);
		TEXT_SetTextAlign(hItem, GUI_TA_VCENTER);
		TEXT_SetText(hItem, "");
		WM_HideWindow(hItem);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_INFO_6);
		hInfoText6 = hItem;
		TEXT_SetFont(hItem,  &YaHei_24_Font);
		TEXT_SetTextAlign(hItem, GUI_TA_VCENTER);
		TEXT_SetText(hItem, "");
		WM_HideWindow(hItem);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_INFO_7);
		hInfoText7 = hItem;
		TEXT_SetFont(hItem,  &YaHei_24_Font);
		TEXT_SetTextAlign(hItem, GUI_TA_VCENTER);
		TEXT_SetText(hItem, "");
		WM_HideWindow(hItem);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_INFO_8);
		hInfoText8 = hItem;
		TEXT_SetFont(hItem,  &YaHei_24_Font);
		TEXT_SetTextAlign(hItem, GUI_TA_VCENTER);
		TEXT_SetText(hItem, "");
		WM_HideWindow(hItem);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_INFO_9);
		hInfoText9 = hItem;
		TEXT_SetFont(hItem,  &YaHei_24_Font);
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		TEXT_SetText(hItem, "");
		WM_HideWindow(hItem);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VOICE);
		hPreferenceText0 = hItem;
		TEXT_SetFont(hItem,  &YaHei_36_Font);
		TEXT_SetTextColor(hItem, 0x009B5C0A);
		TEXT_SetTextAlign(hItem, GUI_TA_VCENTER);
		TEXT_SetText(hItem, "声音开关");
		WM_HideWindow(hItem);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VOLUME);
		hPreferenceText1 = hItem;
		TEXT_SetFont(hItem,  &YaHei_36_Font);
		TEXT_SetTextColor(hItem, 0x009B5C0A);
		TEXT_SetTextAlign(hItem, GUI_TA_VCENTER);
		TEXT_SetText(hItem, "音量设置");
		WM_HideWindow(hItem);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_MUX);
		hPreferenceTextMux = hItem;
		TEXT_SetFont(hItem,  &YaHei_36_Font);
		TEXT_SetTextColor(hItem, 0x009B5C0A);
		TEXT_SetTextAlign(hItem, GUI_TA_VCENTER);
		TEXT_SetText(hItem, "多人模式");
		WM_HideWindow(hItem);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_DEVID);
		hPreferenceTextDevID = hItem;
		TEXT_SetFont(hItem,  &YaHei_36_Font);
		TEXT_SetTextColor(hItem, 0x009B5C0A);
		TEXT_SetTextAlign(hItem, GUI_TA_VCENTER);
		TEXT_SetText(hItem, "设备编号");
		WM_HideWindow(hItem);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_VOICE);
		hVoiceButton = hItem;
		BUTTON_SetFocussable(hItem, 0);
		BUTTON_SetBitmap(hItem, BUTTON_BI_PRESSED, &bmswitch_on);
		WM_SetCallback(hItem, _cbPushButtonBitmap);
		WM_HideWindow(hItem);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_VOLUME);
		hVolumeSlider = hItem;
		BUTTON_SetFocussable(hItem, 0);
		WM_HideWindow(hItem);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_MUX);
		hMuxButton = hItem;
		BUTTON_SetFocussable(hItem, 0);
		BUTTON_SetBitmap(hItem, BUTTON_BI_PRESSED, &bmswitch_on);
		WM_SetCallback(hItem, _cbPushButtonBitmap);
		WM_HideWindow(hItem);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_DEVID);
		hDevIdEdit = hItem;
		EDIT_SetFont(hItem,  &YaHei_24_Font);
		EDIT_SetTextColor(hItem, EDIT_CI_ENABLED, 0x00868380);
		EDIT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		EDIT_SetMaxLen(hItem, 100);
		WM_SetFocus(hItem);
		EDIT_SetText(hItem, "100.2.217.1.1");
		EDIT_GetText(hItem, sys_config.dev_id, sizeof(sys_config.dev_id));
		WM_HideWindow(hItem);


		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_WIFI_LIST) ;
		hWifiListButton = hItem;
		WM_HideWindow(hItem);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_RFID_LIST);
		hRfidListButton = hItem;
		WM_HideWindow(hItem);

		hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_BACK);
		hBackImage = hItem;
		IMAGE_SetBitmap(hItem, &bmlogout);
		WM_HideWindow(hItem);

		hBackButton = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_BACK);
		WM_HideWindow(hBackButton);

		hScanButton = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_WIFI_SCAN);
		WM_HideWindow(hScanButton);

		hVolumeSlider = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_VOLUME);
		SLIDER_SetWidth(hVolumeSlider, 30);
		SLIDER_SetRange(hVolumeSlider, 10, 99);
		SLIDER_SetSkin(hVolumeSlider, SKIN_slider2C);
		WM_HideWindow(hVolumeSlider);

		
		pushButtonInitDialog();

		break;

	case WM_WIFI_SCAN_CB:
		notify = (wifi_config_t *)pMsg->Data.p;
		if(notify->setting.status == WIFI_OK) {
			for(i = 0; i < 20 && wifi_list[i][0]; i++) {
				LISTVIEW_SetItemText(hConnectList, 0, i + 1, (const char *) & (wifi_list[i][1]));
				switch(wifi_list[i][0]) {
				case '0' :
					LISTVIEW_SetItemText(hConnectList, 1, i + 1, "PUBIC");
					LISTVIEW_SetItemText(hConnectList, 2, i + 1, "OPEN");
					break;

				case '1' :
					LISTVIEW_SetItemText(hConnectList, 1, i + 1, "PRIVATE");
					LISTVIEW_SetItemText(hConnectList, 2, i + 1, "LOCKED");
					break;

				default:
					break;
				}
			}
		} else;
		break;

	case WM_RFID_MATCH_CB:
		TEXT_SetText(hConnectPromptText1, "设备名称");
		TEXT_SetText(hConnectPromptText2, "设备类型");
		TEXT_SetText(hConnectPromptText3, "设备ID");
		TEXT_SetText(hConnectContentText1, new_dev.name);
		TEXT_SetText(hConnectContentText3, &new_dev.id[13]);
		BUTTON_SetText(hConnectButton0, "连接");
		switch (new_dev.type) {
		case EPOCH_IIPCD :
			TEXT_SetText(hConnectContentText2, "电源控制设备");
			break;
		default :
			break;
		}
		WM_ShowWindow(hConnectContentText3);
		WM_ShowWindow(hConnectWindow);
		break;

	case WM_NOTIFY_PARENT:
		Id    = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch(Id) {
			
		case ID_BUTTON_ADMIN:
			switch(NCode) {
			case WM_NOTIFICATION_CLICKED:

				break;
			case WM_NOTIFICATION_RELEASED:
				expRoutineFlagSet(FLAG_ADMIN_LOGIN, 1);
				break;

			}
			break;
			
		case ID_BUTTON_VOICE:
			switch(NCode) {
			case WM_NOTIFICATION_CLICKED:

				break;
			case WM_NOTIFICATION_RELEASED:
				if(sys_config.voice == on) {
					sys_config.voice = off;
					BUTTON_SetBitmap(hVoiceButton, BUTTON_BI_PRESSED, &bmswitch_off);
				} else {
					sys_config.voice = on;
					BUTTON_SetBitmap(hVoiceButton, BUTTON_BI_PRESSED, &bmswitch_on);
				}
				break;

			}
			break;

		case ID_BUTTON_MUX:
			switch(NCode) {
			case WM_NOTIFICATION_CLICKED:

				break;
			case WM_NOTIFICATION_RELEASED:
				if(sys_config.mux == on) {
					sys_config.mux = off;
					BUTTON_SetBitmap(hMuxButton, BUTTON_BI_PRESSED, &bmswitch_off);
				} else {
					sys_config.mux = on;
					BUTTON_SetBitmap(hMuxButton, BUTTON_BI_PRESSED, &bmswitch_on);
				}
				break;

			}
			break;
		case ID_BUTTON_WIFI_LIST:
			switch(NCode) {
			case WM_NOTIFICATION_CLICKED:

				break;
			case WM_NOTIFICATION_RELEASED:
				WM_ShowWindow(hConnectList);
				WM_ShowWindow(hBackImage);
				WM_ShowWindow(hBackButton);
				WM_ShowWindow(hScanButton);
				WM_HideWindow(hWifiListButton);
				WM_HideWindow(hRfidListButton);

				LISTVIEW_SetItemBkColor(hConnectList, 0, 0, LISTVIEW_CI_DISABLED, 0x00A6EEBF);
				LISTVIEW_SetItemText(hConnectList, 0, 0, "WIFI名称");
				LISTVIEW_SetItemBkColor(hConnectList, 1, 0, LISTVIEW_CI_DISABLED, 0x00FFDAD5);
				LISTVIEW_SetItemText(hConnectList, 1, 0, "加密状态");
				LISTVIEW_SetItemBkColor(hConnectList, 2, 0, LISTVIEW_CI_DISABLED, 0x00FFDAD5);
				LISTVIEW_SetItemText(hConnectList, 2, 0, "WIFI状态");

				BUTTON_SetText(hScanButton, "刷新列表");

				for(i = 0; i < 20; i++) {
					LISTVIEW_SetItemText(hConnectList, 0, i + 1, "");
					LISTVIEW_SetItemText(hConnectList, 1, i + 1, "");
					LISTVIEW_SetItemText(hConnectList, 2, i + 1, "");
				}
				break;
			}
			break;
		case ID_BUTTON_RFID_LIST:
			switch(NCode) {
			case WM_NOTIFICATION_CLICKED:

				break;
			case WM_NOTIFICATION_RELEASED:
				WM_ShowWindow(hConnectList);
				WM_ShowWindow(hBackImage);
				WM_ShowWindow(hBackButton);
				WM_ShowWindow(hScanButton);
				WM_HideWindow(hWifiListButton);
				WM_HideWindow(hRfidListButton);

				LISTVIEW_SetItemBkColor(hConnectList, 0, 0, LISTVIEW_CI_DISABLED, 0x00A6EEBF);
				LISTVIEW_SetItemText(hConnectList, 0, 0, "设备名称");
				LISTVIEW_SetItemBkColor(hConnectList, 1, 0, LISTVIEW_CI_DISABLED, 0x00FFDAD5);
				LISTVIEW_SetItemText(hConnectList, 1, 0, "设备类型");
				LISTVIEW_SetItemBkColor(hConnectList, 2, 0, LISTVIEW_CI_DISABLED, 0x00FFDAD5);
				LISTVIEW_SetItemText(hConnectList, 2, 0, "设备ID");

				BUTTON_SetText(hScanButton, "开始匹配");

				for(i = 0; i < 20; i++) {
					LISTVIEW_SetItemText(hConnectList, 0, i + 1, "");
					LISTVIEW_SetItemText(hConnectList, 1, i + 1, "");
					LISTVIEW_SetItemText(hConnectList, 2, i + 1, "");
					if(i < dev_list.number) {
						LISTVIEW_SetItemText(hConnectList, 0, i + 1, dev_list.connected_dev[i].name);
						switch (dev_list.connected_dev[i].type) {
						case EPOCH_IIPCD :
							LISTVIEW_SetItemText(hConnectList, 1, i + 1, "电源控制设备");
							break;
						default :
							break;
						}
						LISTVIEW_SetItemText(hConnectList, 2, i + 1, &dev_list.connected_dev[i].id[13]);
					}
				}

				break;

			}
			break;
		case ID_BUTTON_WIFI_SCAN:
			switch(NCode) {
			case WM_NOTIFICATION_CLICKED:

				break;
			case WM_NOTIFICATION_RELEASED:
				memset(p, 0, sizeof(p));
				BUTTON_GetText(hScanButton, (char *)p, sizeof(p));
				if(strstr("刷新列表 ", (char *)p)) {
					wifi_config.setting.event = wifi_scan;
					if(errQUEUE_FULL == xQueueSend(xQueueWifi, (const void *)(&wifi_config), 50))
						notify_show("操作无效", "请稍后");

					for(i = 0; i < 20; i++) {
						LISTVIEW_SetItemText(hConnectList, 0, i + 1, "");
						LISTVIEW_SetItemText(hConnectList, 1, i + 1, "");
						LISTVIEW_SetItemText(hConnectList, 2, i + 1, "");
					}
				} else if(strstr("开始匹配", (char *)p)) {
					voiceDispString(voiceStatrMatch);
					xTaskNotifyGive(RC522Task_Handler);
				} else;

				break;

			}
			break;
		case ID_BUTTON_BACK:
			switch(NCode) {
			case WM_NOTIFICATION_CLICKED:

				break;
			case WM_NOTIFICATION_RELEASED:
				WM_HideWindow(hConnectList);
				WM_HideWindow(hBackButton);
				WM_HideWindow(hScanButton);
				WM_HideWindow(hBackImage);
				WM_ShowWindow(hWifiListButton);
				WM_ShowWindow(hRfidListButton);
				break;

			}
			break;
		case ID_EDIT_DEVID:
			switch(NCode) {
			case WM_NOTIFICATION_CLICKED:

				break;
			case WM_NOTIFICATION_RELEASED:
				EDIT_GetText(hDevIdEdit, sys_config.dev_id, sizeof(sys_config.dev_id));
				wifi_config.http_notify.event = http_submit_dev_id;
				if(errQUEUE_FULL == xQueueSend(xQueueWifi, (const void *)(&wifi_config), 50))
					notify_show("操作无效", "请稍后");
				break;

			}
			break;
		case ID_SLIDER_VOLUME:
			switch(NCode) {
			case WM_NOTIFICATION_VALUE_CHANGED:
				slideValue = SLIDER_GetValue(hVolumeSlider);
				sprintf((char*)volumeString, "[v%c]sound102", slideValue / 10 + '0');
				voiceDispString(volumeString);
				break;
			}
			break;
		case ID_LISTVIEW_CONNECT_LIST:
			switch(NCode) {
			case WM_NOTIFICATION_CLICKED:

				break;
			case WM_NOTIFICATION_RELEASED:
				memset(p, 0, sizeof(p));
				BUTTON_GetText(hScanButton, (char *)p, sizeof(p));
				if(strstr("刷新列表", (char *)p)) {
					TEXT_SetText(hConnectPromptText1, "WIFI名称");
					TEXT_SetText(hConnectPromptText2, "加密状态");
					TEXT_SetText(hConnectPromptText3, "WIFI密码");

					BUTTON_SetText(hConnectButton0, "连接");
					memset(wifi_data.name, 0, sizeof(wifi_data.name));
					LISTVIEW_GetItemText(hConnectList,
					                     0,
					                     LISTVIEW_GetSel(hConnectList),
					                     (char *)wifi_data.name,
					                     sizeof(wifi_data.name)
					                    );
					TEXT_SetText(hConnectContentText1, (const char *)wifi_data.name);

					memset(p, 0, sizeof(p));
					LISTVIEW_GetItemText(hConnectList,
					                     1,
					                     LISTVIEW_GetSel(hConnectList),
					                     (char *)p,
					                     sizeof(p)
					                    );
					TEXT_SetText(hConnectContentText2, (const char *)p);

					memset(p, 0, sizeof(p));
					LISTVIEW_GetItemText(hConnectList,
					                     2,
					                     LISTVIEW_GetSel(hConnectList),
					                     (char *)p,
					                     sizeof(p)
					                    );
					if(0 == strcmp((char *)p, "OPEN")) {
						EDIT_SetText(hConnectEdit, "NONE");
						WM_ShowWindow(hConnectEdit);
						WM_ShowWindow(hConnectWindow);
					} else if(*p != 0) {
						EDIT_SetText(hConnectEdit, "");
						WM_ShowWindow(hConnectEdit);
						WM_ShowWindow(hFullKeyboard);
						WM_ShowWindow(hConnectWindow);
					} else {
						WM_HideWindow(hFullKeyboard);
						WM_HideWindow(hConnectWindow);
					}
				} else if(strstr("开始匹配 ", (char *)p)) {
					TEXT_SetText(hConnectPromptText1, "设备名称");
					TEXT_SetText(hConnectPromptText2, "设备类型");
					TEXT_SetText(hConnectPromptText3, "设备ID");
					TEXT_SetText(hConnectContentText1, dev_list.connected_dev[LISTVIEW_GetSel(hConnectList) - 1].name);
					switch (dev_list.connected_dev[LISTVIEW_GetSel(hConnectList) - 1].type) {
					case EPOCH_IIPCD :
						TEXT_SetText(hConnectContentText2, "电源控制设备");
						break;
					default :
						break;
					}
					memset(p, 0, sizeof(p));
					LISTVIEW_GetItemText(hConnectList,
					                     2,
					                     LISTVIEW_GetSel(hConnectList),
					                     (char *)p,
					                     sizeof(p)
					                    );
					if(*p != 0) {
						TEXT_SetText(hConnectContentText3, &dev_list.connected_dev[LISTVIEW_GetSel(hConnectList) - 1].id[13]);
						BUTTON_SetText(hConnectButton0, "删除");
						WM_ShowWindow(hConnectContentText3);
						WM_ShowWindow(hConnectWindow);
					} else
						WM_HideWindow(hConnectWindow);
				}
				break;
			}
			break;
		default :

			break;
		}

	default:
		WM_DefaultProc(pMsg);
		break;
	}
}

WM_HWIN infomationWindowOnCreate(void)
{
	WM_HWIN hWin;
	SpecializedSkinTypedef *winBMP;
	static SpecializedSkinTypedef BMP_WIN_main;
	BMP_WIN_main.thumbM = &bmsliderThumb;
	BMP_WIN_main.thumbN = &bmsliderThumb;
	winBMP = &BMP_WIN_main;

	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	WM_SetUserData(hWin, &winBMP, sizeof(winBMP));
	WM_AttachWindowAt(hWin, hMainWin, 800, 10);
	WM_HideWindow(hWin);
	return hWin;
}


/*************************** End of file ****************************/
