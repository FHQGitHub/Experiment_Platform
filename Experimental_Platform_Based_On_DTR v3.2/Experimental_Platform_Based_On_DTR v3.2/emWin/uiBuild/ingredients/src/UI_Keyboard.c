#include "DIALOG.h"
#include "ep_app.h"

#define ID_WINDOW_KEYBOARD      (GUI_ID_USER + 0x00)
#define ID_BUTTON_0             (GUI_ID_USER + 0x01)
#define ID_BUTTON_1             (GUI_ID_USER + 0x02)
#define ID_BUTTON_2             (GUI_ID_USER + 0x03)
#define ID_BUTTON_3             (GUI_ID_USER + 0x04)
#define ID_BUTTON_4             (GUI_ID_USER + 0x05)
#define ID_BUTTON_5             (GUI_ID_USER + 0x06)
#define ID_BUTTON_6             (GUI_ID_USER + 0x07)
#define ID_BUTTON_7             (GUI_ID_USER + 0x08)
#define ID_BUTTON_8             (GUI_ID_USER + 0x09)
#define ID_BUTTON_9             (GUI_ID_USER + 0x0A)
#define ID_BUTTON_DEL           (GUI_ID_USER + 0x0B)
#define ID_BUTTON_ENTER         (GUI_ID_USER + 0x0C)
#define ID_BUTTON_LEFT          (GUI_ID_USER + 0x0D)
#define ID_BUTTON_RIGHT         (GUI_ID_USER + 0x0E)

#define KEYBOARD_MAX_SIZE       100

WM_HWIN hKeyboard;
char score[100];

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_KEYBOARD, 550, 140, 240, 240, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_7, 8, 8, 50, 50, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_8, 66, 8, 50, 50, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_9, 124, 8, 50, 50, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_4, 8, 66, 50, 50, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_5, 66, 66, 50, 50, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_6, 124, 66, 50, 50, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 8, 124, 50, 50, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_2, 66, 124, 50, 50, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_3, 124, 124, 50, 50, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 66, 182, 50, 50, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_DEL, 182, 8, 50, 108, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_ENTER, 182, 124, 50, 108, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_LEFT, 8, 182, 50, 50, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_RIGHT, 124, 182, 50, 50, 0, 0x0, 0 },
};

static void _cbPushButtonComplex(WM_MESSAGE *pMsg)						
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
                        GUI_DrawBitmap(BUTTON_GetBitmap(hButton, BUTTON_BI_PRESSED), 0, 0);	
                        
                        GUI_SetTextMode(GUI_TEXTMODE_TRANS); 
                        GUI_SetColor(BUTTON_GetTextColor(hButton, BUTTON_CI_PRESSED)); 
                        GUI_SetFont(BUTTON_GetFont(hButton)); 
                        GUI_DispStringAt(pButtonText, 8, 8);
		}
		else {       
                        GUI_SetBkColor(0x00FFFCF9);
                        GUI_Clear();
                        GUI_DrawBitmap(BUTTON_GetBitmap(hButton, BUTTON_BI_UNPRESSED), 0, 0);
                        
                        GUI_SetTextMode(GUI_TEXTMODE_TRANS); 
                        GUI_SetColor(BUTTON_GetTextColor(hButton, BUTTON_CI_UNPRESSED)); 
                        GUI_SetFont(BUTTON_GetFont(hButton)); 
                        GUI_DispStringAt(pButtonText, 8, 3);
		}
		break;
	default:
		BUTTON_Callback(pMsg);
	}
}

static void _cbDialog(WM_MESSAGE * pMsg) 
{
        int NCode;
        int Id;
        int i;
        char button_text[15];
        WM_HWIN 	hItem;
	wifi_config_t 	wifi_config;
	memset(&wifi_config, 0, sizeof(wifi_config));
        
        switch (pMsg->MsgId) {
                case WM_INIT_DIALOG:
        
                hItem = pMsg->hWin;
                WINDOW_SetBkColor(hItem, 0x00FFFCF9);
          
                for(i = ID_BUTTON_0; i <= ID_BUTTON_RIGHT; i++ ) {
                        hItem = WM_GetDialogItem(pMsg->hWin, i);
                        BUTTON_SetBitmap(hItem, BUTTON_BI_PRESSED, &bmkey1_down);
                        BUTTON_SetBitmap(hItem, BUTTON_BI_UNPRESSED, &bmkey1_up);
                        BUTTON_SetFocussable(hItem, 0);
                        if(i >= ID_BUTTON_0 && i <= ID_BUTTON_9) {
                                sprintf(button_text, "%d", i -1 - GUI_ID_USER);
                                BUTTON_SetFont(hItem,  &YaHei_24B_Font);
                                BUTTON_SetTextColor(hItem, BUTTON_CI_DISABLED, GUI_BLACK);
                                BUTTON_SetTextColor(hItem, BUTTON_CI_PRESSED, GUI_BLACK);
                                BUTTON_SetTextColor(hItem, BUTTON_CI_UNPRESSED, GUI_BLACK);
                                BUTTON_SetText(hItem, button_text);
                        }
                        WM_SetCallback(hItem, _cbPushButtonComplex);
                }
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_LEFT);
                BUTTON_SetFont(hItem,  &YaHei_24B_Font);
                BUTTON_SetTextColor(hItem, BUTTON_CI_DISABLED, GUI_BLACK);
                BUTTON_SetTextColor(hItem, BUTTON_CI_PRESSED, GUI_BLACK);
                BUTTON_SetTextColor(hItem, BUTTON_CI_UNPRESSED, GUI_BLACK);
                BUTTON_SetText(hItem, "<");
                WM_SetCallback(hItem, _cbPushButtonComplex);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_RIGHT);
                BUTTON_SetFont(hItem,  &YaHei_24B_Font);
                BUTTON_SetTextColor(hItem, BUTTON_CI_DISABLED, GUI_BLACK);
                BUTTON_SetTextColor(hItem, BUTTON_CI_PRESSED, GUI_BLACK);
                BUTTON_SetTextColor(hItem, BUTTON_CI_UNPRESSED, GUI_BLACK);
                BUTTON_SetText(hItem, ">");
                WM_SetCallback(hItem, _cbPushButtonComplex);

                hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_DEL);
                BUTTON_SetBitmap(hItem, BUTTON_BI_PRESSED, &bmkey2_down);
                BUTTON_SetBitmap(hItem, BUTTON_BI_UNPRESSED, &bmkey2_up);
                BUTTON_SetFont(hItem,  &YaHei_24B_Font);
                BUTTON_SetTextColor(hItem, BUTTON_CI_DISABLED, GUI_BLACK);
                BUTTON_SetTextColor(hItem, BUTTON_CI_PRESSED, GUI_BLACK);
                BUTTON_SetTextColor(hItem, BUTTON_CI_UNPRESSED, GUI_BLACK);
                BUTTON_SetText(hItem, "D\r\n  E\r\n  L");
                BUTTON_SetFocussable(hItem, 0);
                WM_SetCallback(hItem, _cbPushButtonComplex);

                hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_ENTER);
                BUTTON_SetBitmap(hItem, BUTTON_BI_PRESSED, &bmkey2_down);
                BUTTON_SetBitmap(hItem, BUTTON_BI_UNPRESSED, &bmkey2_up);
                BUTTON_SetFont(hItem,  &YaHei_24B_Font);
                BUTTON_SetTextColor(hItem, BUTTON_CI_DISABLED, GUI_BLACK);
                BUTTON_SetTextColor(hItem, BUTTON_CI_PRESSED, GUI_BLACK);
                BUTTON_SetTextColor(hItem, BUTTON_CI_UNPRESSED, GUI_BLACK);
                BUTTON_SetText(hItem, "O\r\n  K");
                BUTTON_SetFocussable(hItem, 0);
                WM_SetCallback(hItem, _cbPushButtonComplex);
                break;
          
        case WM_NOTIFY_PARENT:
                Id    = WM_GetId(pMsg->hWinSrc);
                NCode = pMsg->Data.v;
                switch(Id) {
                case ID_BUTTON_0: 
                        switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:

                        break;
                        case WM_NOTIFICATION_RELEASED:
                                EDIT_AddKey(hScoreEdit, '0');
                        break;

                }
                break;
                case ID_BUTTON_1: 
                switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:

                        break;
                        case WM_NOTIFICATION_RELEASED:
                                EDIT_AddKey(hScoreEdit, '1');
                        break;

                }
                break;
                
                case ID_BUTTON_2: 
                switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:

                        break;
                        case WM_NOTIFICATION_RELEASED:
                                EDIT_AddKey(hScoreEdit, '2');
                        break;

                }
                break;
                
                case ID_BUTTON_3: 
                switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:

                        break;
                        case WM_NOTIFICATION_RELEASED:
                                EDIT_AddKey(hScoreEdit, '3');
                        break;

                }
                break;
                
                case ID_BUTTON_4: 
                        switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:

                        break;
                        case WM_NOTIFICATION_RELEASED:
                                EDIT_AddKey(hScoreEdit, '4');
                        break;

                }
                break;
                
                case ID_BUTTON_5: 
                        switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:

                        break;
                        case WM_NOTIFICATION_RELEASED:
                                EDIT_AddKey(hScoreEdit, '5');
                        break;

                        }
                break;
                        
                case ID_BUTTON_6: 
                        switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:

                        break;
                        case WM_NOTIFICATION_RELEASED:
                                EDIT_AddKey(hScoreEdit, '6');
                        break;

                        }
                break;
                        
                case ID_BUTTON_7: 
                        switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:

                        break;
                        case WM_NOTIFICATION_RELEASED:
                                EDIT_AddKey(hScoreEdit, '7');
                        break;

                        }
                break;
                        
                case ID_BUTTON_8: 
                        switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:

                        break;
                        case WM_NOTIFICATION_RELEASED:
                                EDIT_AddKey(hScoreEdit, '8');
                        break;

                        }
                break;
                        
                case ID_BUTTON_9: 
                        switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:

                        break;
                        case WM_NOTIFICATION_RELEASED:
                                EDIT_AddKey(hScoreEdit, '9');
                        break;

                        }
                break;
                        
                case ID_BUTTON_DEL: 
                        switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:

                        break;
                        case WM_NOTIFICATION_RELEASED:
                                EDIT_AddKey(hScoreEdit, '\b');
                        break;

                        }
                break;
                        
                case ID_BUTTON_ENTER: 
                        switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:

                        break;
                        case WM_NOTIFICATION_RELEASED:
                                EDIT_GetText(hScoreEdit, score, 100);
                                if(atoi(score) <= 100) {
                                        WM_HideWindow(hKeyboard);
                                        WM_HideWindow(hScoreEdit);
                                        EDIT_SetText(hScoreEdit, "");
                                        memset(score, 0, 100);
                                        routine.main_exp.sub_exp[present_list_status - 1].status = exp_finished;
                                        routine.main_exp.sub_exp[present_list_status - 1].subExpScore = atoi(score);
                                        
					wifi_config.http_notify.event = http_exp_score;
					if(pdPASS == xQueueSend(xQueueWifi, (const void *)(&wifi_config), 50))
						notify_show("正在操作中", "请稍后");
					else if(errQUEUE_FULL == xQueueSend(xQueueWifi, (const void *)(&wifi_config), 50))
						notify_show("操作无效", "请稍后");
                                }
                        break;

                        }
                break;
                        
                case ID_BUTTON_LEFT: 
                        switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:

                        break;
                        case WM_NOTIFICATION_RELEASED:
                                WM_SetFocus(hScoreEdit);
                                GUI_SendKeyMsg(GUI_KEY_LEFT, 1);
                        break;

                        }
                break;
                        
                case ID_BUTTON_RIGHT: 
                        switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:

                        break;
                        case WM_NOTIFICATION_RELEASED:
                                WM_SetFocus(hScoreEdit);
                                GUI_SendKeyMsg(GUI_KEY_RIGHT, 1);
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

WM_HWIN keyboardPageOnCreate(void)
{
        WM_HWIN hWin;

        hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
        WM_HideWindow(hWin);
        return hWin;
}


/*************************** End of file ****************************/
