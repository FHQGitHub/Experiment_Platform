#include "DIALOG.h"
#include "uiBuild.h"
#include "app_exp_routine.h"

#define ID_FRAMEWIN_0 (GUI_ID_USER + 0x00)
#define ID_TEXT_0 (GUI_ID_USER + 0x01)
#define ID_TEXT_1 (GUI_ID_USER + 0x02)

WM_HWIN hNotifyWindow;
WM_HWIN hNotifyText1;
WM_HWIN hNotifyText2;

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
        { FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 440, 60, 240, 160, 0, 0x0, 0 },
        { TEXT_CreateIndirect, "Text", ID_TEXT_0, 45, 25, 144, 27, 0, 0x0, 0 },
        { TEXT_CreateIndirect, "Text", ID_TEXT_1, 45, 62, 144, 27, 0, 0x0, 0 },
};

static void _cbDialog(WM_MESSAGE * pMsg) 
{
        WM_HWIN hItem;
        
        switch (pMsg->MsgId) {
        case WM_INIT_DIALOG:
                hItem = pMsg->hWin;
                FRAMEWIN_SetTitleHeight(hItem, 24);
                FRAMEWIN_SetFont(hItem, &YaHei_24_Font);
                FRAMEWIN_SetText(hItem, "通知");

                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
                hNotifyText1 = hItem;
                TEXT_SetFont(hItem,  &YaHei_24_Font);
                TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_TOP);
                TEXT_SetText(hItem, "");
        
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
                hNotifyText2 = hItem;
                TEXT_SetFont(hItem,  &YaHei_24_Font);
                TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_TOP);
                TEXT_SetText(hItem, "");
                
        break;

        default:
                WM_DefaultProc(pMsg);
        break;
        }
}

WM_HWIN notifyWindowOnCreate(void) 
{
        WM_HWIN hWin;

        hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
        WM_HideWindow(hWin);
        return hWin;
}

/*************************** End of file ****************************/
