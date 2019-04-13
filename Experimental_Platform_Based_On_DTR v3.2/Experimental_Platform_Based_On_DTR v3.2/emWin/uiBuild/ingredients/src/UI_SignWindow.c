#include "WM.h"
#include "DIALOG.h"
#include "uiBuild.h"
#include "app_exp_routine.h"

#define ID_WINDOW_SIGN                  (GUI_ID_USER + 0x00)
#define ID_IMAGE_FUNCTION_AREA_1        (GUI_ID_USER + 0x01)
#define ID_IMAGE_FUNCTION_AREA_2        (GUI_ID_USER + 0x02)
#define ID_IMAGE_FUNCTION_AREA_3        (GUI_ID_USER + 0x03)
#define ID_IMAGE_LOGOUT                 (GUI_ID_USER + 0x04)

#define ID_TEXT_TITLE                   (GUI_ID_USER + 0x10)
#define ID_TEXT_SUBTITLE                (GUI_ID_USER + 0x11)
#define ID_TEXT_CONTENT_1               (GUI_ID_USER + 0x12)
#define ID_TEXT_CONTENT_2               (GUI_ID_USER + 0x13)
#define ID_TEXT_CONTENT_3               (GUI_ID_USER + 0x14)
#define ID_TEXT_SCORE                   (GUI_ID_USER + 0x19)
#define ID_TEXT_QUEUE                   (GUI_ID_USER + 0x1B)
#define ID_BUTTON_BEGIN                 (GUI_ID_USER + 0x15)
#define ID_BUTTON_SUBMIT                (GUI_ID_USER + 0x16)
#define ID_BUTTON_QUESTION              (GUI_ID_USER + 0x17)
#define ID_BUTTON_LOGOUT                (GUI_ID_USER + 0x18)

#define ID_EDIT_SCORE                   (GUI_ID_USER + 0x1A)

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

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
        { WINDOW_CreateIndirect, "Window", ID_WINDOW_SIGN, 0, 0, 400, 350, 0, 0x0, 0 },
        { IMAGE_CreateIndirect, "Image", ID_IMAGE_FUNCTION_AREA_1, 167, 230, 66, 67, 0, 0, 0 },
        { TEXT_CreateIndirect, "Text", ID_TEXT_TITLE, 0, 42, 400, 40, 0, 0x0, 0 },
        { TEXT_CreateIndirect, "Text", ID_TEXT_SUBTITLE, 0, 98, 400, 27, 0, 0x0, 0 },
        { BUTTON_CreateIndirect, "Button", ID_BUTTON_SIGN, 128, 310, 144, 40, 0, 0x0, 0 },
};

static void _cbDialog(WM_MESSAGE * pMsg) {
        
        WM_HWIN      hItem;
        int NCode;
        int Id;
        uint32_t ulValue;
        
        switch (pMsg->MsgId) {
        case WM_INIT_DIALOG:

                hItem = pMsg->hWin;
                WINDOW_SetBkColor(hItem, 0x00FFFCF9);

                hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_FUNCTION_AREA_1);
                hFunctionImage1 = hItem;
                IMAGE_SetBitmap(hItem, &bmhdu_logo);

                hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_FUNCTION_AREA_2);
                hFunctionImage2 = hItem;
                IMAGE_SetBitmap(hItem, &bmsubmit);

                hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_FUNCTION_AREA_3);
                hFunctionImage3 = hItem;
                IMAGE_SetBitmap(hItem, &bmquestion);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_LOGOUT);
                hLogoutImage = hItem;
                IMAGE_SetBitmap(hItem, &bmlogout);

                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_TITLE);
                hExpTitle = hItem;
                TEXT_SetFont(hItem,  &YaHei_36_Font);
                TEXT_SetTextColor(hItem, 0x009B5C0A);
                TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_TOP);
                TEXT_SetText(hItem, routine.main_exp.mainExpName);

                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SUBTITLE);
                hExpSubTitle = hItem;
                TEXT_SetFont(hItem,  &YaHei_24B_Font);
                TEXT_SetTextColor(hItem, 0x009B5C0A);
                TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_TOP);
                TEXT_SetText(hItem, "");

                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_CONTENT_1);
                hExpContent1 = hItem;
                TEXT_SetFont(hItem,  &YaHei_24_Font);
                TEXT_SetTextColor(hItem, 0x00868380);
                TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
                TEXT_SetText(hItem, "");

                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_CONTENT_2);
                hExpContent2 = hItem;
                TEXT_SetFont(hItem,  &YaHei_24_Font);
                TEXT_SetTextColor(hItem, 0x00868380);
                TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
                TEXT_SetText(hItem, "");

                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_CONTENT_3);
                hExpContent3 = hItem;
                TEXT_SetFont(hItem,  &YaHei_24_Font);
                TEXT_SetTextColor(hItem, 0x00868380);
                TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
                TEXT_SetText(hItem, "");
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_SCORE);
                hScoreText = hItem;
                TEXT_SetFont(hItem,  &YaHei_36_Font);
                TEXT_SetTextColor(hItem, 0x00868380);
                TEXT_SetText(hItem, "请对实验评分");
                WM_HideWindow(hItem);
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_QUEUE);
                hQueueText = hItem;
                TEXT_SetFont(hItem,  &YaHei_36_Font);
                TEXT_SetTextColor(hItem, 0x00868380);
                TEXT_SetText(hItem, "等待人数:2");
                TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
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

                hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_BEGIN);
                hFunctionButton1 = hItem;

                hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_SUBMIT);
                hFunctionButton2 = hItem;

                hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_QUESTION);
                hFunctionButton3 = hItem; 
                
                hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_LOGOUT);
                hLogoutButton = hItem; 

                pushButtonTextInitDialog();
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
                                element_bounce(hFunctionImage1, 2);
                                if(present_bar_status == ACTION_EXP_DETAIL) {
                                        if(routine.flags.flagStudentLogin != flag_set) {
                                                routine.flags.flagStudentLogin = flag_set;
                                                routine.flags.flagExpStart = flag_set;
                                        }
                                        else if(routine.main_exp.sub_exp[present_list_status - 1].status == exp_waiting) 
                                                routine.main_exp.sub_exp[present_list_status - 1].status = exp_lasting;
                                        reconstruct_list_content(present_bar_status, present_list_status);
                                }
                                else if(present_bar_status == ACTION_EXP_SCORE) {
                                        if(routine.flags.flagTeacherLogin == flag_reset) {
                                                routine.flags.flagTeacherLogin = flag_set;
                                                reconstruct_list_content(present_bar_status, present_list_status);
                                        }
                                        
                                        else if(routine.main_exp.sub_exp[present_list_status - 1].status == exp_submitted || routine.main_exp.sub_exp[present_list_status - 1].status == exp_grading) {
                                                routine.main_exp.sub_exp[present_list_status - 1].status = exp_grading;
                                                reconstruct_list_content(present_bar_status, present_list_status);
                                                WM_ShowWindow(hKeyboard);
                                        }
                                }
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
                                reconstruct_list_content(present_bar_status, present_list_status);
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
                                        reconstruct_list_content(present_bar_status, present_list_status);
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

WM_HWIN subExpWindowOnCreate(void);
WM_HWIN subExpWindowOnCreate(void) {
        WM_HWIN hWin;
        hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
        WM_AttachWindowAt(hWin, hMainWin, 800, 10);
        WM_HideWindow(hWin);
        return hWin;
}

/*************************** End of file ****************************/
