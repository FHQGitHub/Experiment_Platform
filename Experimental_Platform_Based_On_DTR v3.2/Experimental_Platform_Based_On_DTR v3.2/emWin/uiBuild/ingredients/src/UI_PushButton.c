#include "uiBuild.h"

static void _cbPushButtonText(WM_MESSAGE *pMsg)
{
	char pButtonText[15];
	WM_HWIN hButton;
	hButton = pMsg->hWin;
	switch (pMsg->MsgId) {
	case WM_PAINT:
		BUTTON_GetText(hButton, pButtonText, 15);
		if (BUTTON_IsPressed(hButton)) {
			GUI_SetBkColor(0x00FFFCF9);
			GUI_Clear();
			GUI_SetColor(0x00C1A844);
			GUI_SetAlpha(0x40);
			GUI_FillRoundedRect(0, 0, WM_GetWindowSizeX(hButton), WM_GetWindowSizeY(hButton), WM_GetWindowSizeX(hButton) / 8);
			GUI_SetColor(0x009B5C0A);
			GUI_SetTextMode(GUI_TEXTMODE_TRANS);
			GUI_SetFont(BUTTON_GetFont(hButton));
			GUI_DispStringAt(pButtonText, 15, 0);
			GUI_SetAlpha(0x00);
		} else {
			GUI_SetBkColor(0x00FFFCF9);
			GUI_Clear();
			GUI_SetColor(0x009B5C0A);
			GUI_SetFont(BUTTON_GetFont(hButton));
			GUI_DispStringAt(pButtonText, 15, 0);
		}
		break;
	default:
		BUTTON_Callback(pMsg);
	}
}

void pushButtonTextInitDialog(void)
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

void connectButtonTextInitDialog(void)
{
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

