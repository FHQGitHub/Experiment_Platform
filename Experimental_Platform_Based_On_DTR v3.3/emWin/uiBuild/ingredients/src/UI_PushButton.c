#include "uiBuild.h"

void _cbPushButtonText(WM_MESSAGE *pMsg)
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

void _cbPushButtonBitmap(WM_MESSAGE *pMsg)
{
	int i;
	WM_HWIN hButton;
	hButton = pMsg->hWin;
	switch (pMsg->MsgId) {
	case WM_PAINT:

		GUI_SetBkColor(0x00FFFCF9);
		GUI_Clear();
		GUI_DrawBitmap(BUTTON_GetBitmap(hButton, BUTTON_BI_PRESSED), 0, 0);

		break;

	default:
		BUTTON_Callback(pMsg);
	}
}


