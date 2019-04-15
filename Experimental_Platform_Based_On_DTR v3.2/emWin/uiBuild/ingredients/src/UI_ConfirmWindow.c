#include "DIALOG.h"
#include "ep_app.h"

#define ID_FRAMEWIN_0 (GUI_ID_USER + 0x00)
#define ID_BUTTON_0 (GUI_ID_USER + 0x01)
#define ID_BUTTON_1 (GUI_ID_USER + 0x02)
#define ID_TEXT_0 (GUI_ID_USER + 0x03)
#define ID_TEXT_1 (GUI_ID_USER + 0x04)

WM_HWIN hConfirmWindow;
WM_HWIN hConfirmText1;
WM_HWIN hConfirmText2;
WM_HWIN hConfirmEdit1;

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
        { FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 240, 180, 0, 0x0, 0 },
        { BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 15, 95, 80, 30, 0, 0x0, 0 },
        { BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 135, 95, 80, 30, 0, 0x0, 0 },
        { TEXT_CreateIndirect, "Text", ID_TEXT_0, 45, 25, 144, 27, 0, 0x0, 0 },
        { TEXT_CreateIndirect, "Text", ID_TEXT_1, 45, 52, 144, 27, 0, 0x0, 0 },
};

static void _cbDialog(WM_MESSAGE * pMsg)
{
        WM_HWIN hItem;
        int     NCode;
        int     Id;
        
        switch (pMsg->MsgId) {
        case WM_INIT_DIALOG:
                hItem = pMsg->hWin;
                FRAMEWIN_SetTitleHeight(hItem, 24);
                FRAMEWIN_SetFont(hItem, &YaHei_24_Font);
                FRAMEWIN_SetText(hItem, "确认");

                hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
                BUTTON_SetFont(hItem,  &YaHei_24_Font);
                BUTTON_SetText(hItem,  "确定");
        
                hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
                BUTTON_SetFont(hItem,  &YaHei_24_Font);
                BUTTON_SetText(hItem,  "取消");
        
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
                hConfirmText1 = hItem;
                TEXT_SetFont(hItem,  &YaHei_24_Font);
                TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_TOP);
                TEXT_SetText(hItem, "");
        
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
                hConfirmText2 = hItem;
                TEXT_SetFont(hItem,  &YaHei_24_Font);
                TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_TOP);
                TEXT_SetText(hItem, "");
                WM_HideWindow(hItem);
				
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
                                WM_HideWindow(hConfirmWindow);
                                if(present_bar_status == ACTION_LOGIN) {
                                        routine.flags.flagStudentLogin = flag_reset;
					notify_show("16041538", "成功签退");
                                }
                                else if(present_bar_status == ACTION_EXP_DETAIL) {
                                        routine.main_exp.sub_exp[present_list_status - 1].status = exp_submitted;
                                        menu_reconstruct_list_content(present_bar_status, present_list_status);
                                }
                                else if(present_bar_status == ACTION_EXP_SCORE) {
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
                                        menu_reconstruct_list_content(present_bar_status, present_list_status);
                                }
								else;
                        break;
                        
                        }
                break;
                case ID_BUTTON_1: 
                        switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:
                                
                        break;
                        case WM_NOTIFICATION_RELEASED:
                                WM_HideWindow(hConfirmWindow);
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

WM_HWIN confirmWindowOnCreate(void) 
{
        WM_HWIN hWin;

        hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
        WM_AttachWindowAt(hWin, hSubExpWin, 40, 50);
        WM_HideWindow(hWin);
        return hWin;
}

/*************************** End of file ****************************/
