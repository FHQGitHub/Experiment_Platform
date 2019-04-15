#include "uiBuild.h"
#include "app_exp_routine.h"

menu_t menu;

int present_bar_status = AREA_EXP_DETAIL;
int ex_bar_status = AREA_EXP_DETAIL;
int present_list_status = AREA_SUBLIST_1;
int ex_list_status = AREA_SUBLIST_1;

static list_element_t *menu_list_element_traverse(list_element_t *element_root)
{
        list_element_t *element_index = element_root;
        while(NULL != element_index && NULL != element_index->next)
                element_index = element_index->next;
        return element_index;
}

static void menu_list_element_insert(list_element_t *element_root, list_element_t *element_node)
{
        list_element_t *element_index = NULL;
        
        element_index = menu_list_element_traverse(element_root);
        element_index->next = element_node;
        
}

static void menu_list_element_attach(int bar_index, int list_index, WM_HWIN hAttachWin, element_type_t etype, void *edata, element_state_t estate)     
{
        int i;
        list_element_t *element_new = mymalloc(SRAMIN, sizeof(list_element_t *));
        
        if(NULL == element_new)
                return;
        
        element_new->hAttachWin = hAttachWin;
        element_new->type = etype;
        element_new->element_data = edata;
        element_new->state = estate;
        menu_list_element_insert(&(menu.bar[bar_index - 1].subList[list_index - 1].elements), element_new);
}

static list_element_t *menu_list_element_search_v_hWin(list_element_t *list_element_head, WM_HWIN hWin)
{
        list_element_t *list_element_index = NULL;
        
        menu_list_element_for_each(list_element_index, list_element_head) {
                if(hWin == list_element_index->hAttachWin)
                        return list_element_index;
        }
        return NULL;
}
      
static void menu_list_elements_hide(list_element_t *list_element_index)
{
        if(NULL != list_element_index->hAttachWin)
                WM_HideWindow(list_element_index->hAttachWin);
        else;
}

static void menu_list_elements_show(list_element_t *list_element_index)
{
        
        if(NULL != list_element_index->hAttachWin) {
                if(NULL != list_element_index->element_data) {
                        switch(list_element_index->type) {
                        case element_text :
                                TEXT_SetText(list_element_index->hAttachWin, (char *)(list_element_index->element_data));
                        break;
                        
                        case element_image :
                                IMAGE_SetBitmap(list_element_index->hAttachWin, (GUI_CONST_STORAGE GUI_BITMAP *)(list_element_index->element_data));
                        break;
                        
                        case element_button : 
                                BUTTON_SetText(list_element_index->hAttachWin, (char *)(list_element_index->element_data));
                        break;
                        
                        default :
                                
                        break;
                        }
                }
                
                if(element_visible == list_element_index->state)
                        WM_ShowWindow(list_element_index->hAttachWin);
        }
        else;
}

static void menu_list_elements_hide_all(list_element_t *list_element_head)
{
        list_element_t *list_element_index = NULL;
        
        menu_list_element_for_each(list_element_index, list_element_head) {
               menu_list_elements_hide(list_element_index);
        }
}

static void menu_list_elements_show_all(list_element_t *list)
{
        list_element_t *list_element_index = NULL;
        
        menu_list_element_for_each(list_element_index, list) {
                menu_list_elements_show(list_element_index);
        }
}

static void menu_list_elements_switch(list_element_t *old_list, list_element_t *new_list)
{
        menu_list_elements_hide_all(old_list);
        menu_list_elements_show_all(new_list);
}

static void bar_reset()
{
	bar_highlight_slide(ex_bar_status, 1);
	ex_bar_status = 1;
	present_bar_status = 1;
}

static void list_reset()
{
	list_highlight_slide(ex_list_status, 1);
	present_list_status = 1;
}

void menu_list_element_set_visible(int bar_index, int list_index, WM_HWIN hWin, int state)
{
        list_element_t *element_index = menu_list_element_search_v_hWin(&(menu.bar[bar_index - 1].subList[list_index - 1].elements), hWin);
        
        if(NULL == element_index)
                return;
        if(0 == state)
                element_index->state = element_invisible;
        else
                element_index->state = element_visible;
}

void menu_list_element_set_data(int bar_index, int list_index, WM_HWIN hWin, void *edata)
{
        int i;
        list_element_t *element_index = menu_list_element_search_v_hWin(&(menu.bar[bar_index - 1].subList[list_index - 1].elements), hWin);
        
        if(NULL == element_index)
                return;
        element_index->element_data = edata;
}

void menu_list_element_roleplay()
{
        int i;
        if(flag_reset == routine.flags.flagExpStart) {
                for(i = 0; i < 3; i++) {
                        menu_list_element_set_data(2, i + 1, hExpSubTitle, (void *)&"请等待教师开始实验");
                        menu_list_element_set_visible(2, i + 1, hExpContent1, 0);
                        menu_list_element_set_visible(2, i + 1, hExpContent2, 0);
                        menu_list_element_set_visible(2, i + 1, hExpContent3, 0);
                        menu_list_element_set_visible(2, i + 1, hFunctionImage1, 0);
                        menu_list_element_set_visible(2, i + 1, hFunctionButton1, 0);
                }
        }
        else {
                if(flag_reset == routine.flags.flagStudentLogin) {
                        for(i = 0; i < 3; i++) {
                                menu_list_element_set_data(2, i + 1, hExpSubTitle, (void *)&"请先签到");
                                menu_list_element_set_visible(2, i + 1, hExpContent1, 0);
                                menu_list_element_set_visible(2, i + 1, hExpContent2, 0);
                                menu_list_element_set_visible(2, i + 1, hExpContent3, 0);
                                menu_list_element_set_visible(2, i + 1, hFunctionImage1, 0);
                                menu_list_element_set_visible(2, i + 1, hFunctionButton1, 0);
                        }
                }
                else {
                        for(i = 0; i < 3; i++) {
                                switch(routine.main_exp.sub_exp[i].status) {
                                case exp_waiting : 
                                        menu_list_element_set_data(2, i + 1, hExpSubTitle, (void *)&routine.main_exp.sub_exp[i].subExpName);
                                        menu_list_element_set_data(2, i + 1, hExpContent1, (void *)&routine.main_exp.sub_exp[i].subExpDetail);
                                        menu_list_element_set_visible(2, i + 1, hFunctionImage1, 1);
                                        menu_list_element_set_visible(2, i + 1, hFunctionButton1, 1);
                                        menu_list_element_set_visible(2, i + 1, hFunctionImage2, 0);
                                        menu_list_element_set_visible(2, i + 1, hFunctionButton2, 0);
                                        menu_list_element_set_visible(2, i + 1, hFunctionImage3, 0);
                                        menu_list_element_set_visible(2, i + 1, hFunctionButton3, 0);
                                break; 
                                        
                                case exp_lasting : 
                                        menu_list_element_set_visible(2, i + 1, hFunctionImage1, 0);
                                        menu_list_element_set_visible(2, i + 1, hFunctionButton1, 0);
                                        menu_list_element_set_visible(2, i + 1, hFunctionImage2, 1);
                                        menu_list_element_set_visible(2, i + 1, hFunctionButton2, 1);
                                        menu_list_element_set_visible(2, i + 1, hFunctionImage3, 1);
                                        menu_list_element_set_visible(2, i + 1, hFunctionButton3, 1);
                                break; 
                                
                                case exp_submitted : 
                                        menu_list_element_set_data(2, i + 1, hExpSubTitle, (void *)&"请等待教师评分");
                                        menu_list_element_set_data(2, i + 1, hFunctionImage2, (void *)&"重新提交");
                                        menu_list_element_set_visible(2, i + 1, hFunctionImage1, 0);
                                        menu_list_element_set_visible(2, i + 1, hFunctionButton1, 0);
                                        menu_list_element_set_visible(2, i + 1, hFunctionImage2, 1);
                                        menu_list_element_set_visible(2, i + 1, hFunctionButton2, 1);
                                        menu_list_element_set_visible(2, i + 1, hFunctionImage3, 1);
                                        menu_list_element_set_visible(2, i + 1, hFunctionButton3, 1);
                                break; 
                                
                                case exp_grading : 
                                        menu_list_element_set_data(2, i + 1, hExpSubTitle, (void *)&"请等待教师评分");
                                        menu_list_element_set_data(2, i + 1, hFunctionImage2, (void *)&"重新提交");
                                        menu_list_element_set_visible(2, i + 1, hFunctionImage1, 0);
                                        menu_list_element_set_visible(2, i + 1, hFunctionButton1, 0);
                                        menu_list_element_set_visible(2, i + 1, hFunctionImage2, 1);
                                        menu_list_element_set_visible(2, i + 1, hFunctionButton2, 1);
                                        menu_list_element_set_visible(2, i + 1, hFunctionImage3, 1);
                                        menu_list_element_set_visible(2, i + 1, hFunctionButton3, 1);
                                break; 
                                
                                case exp_finished : 
                                        menu_list_element_set_data(2, i + 1, hExpSubTitle, (void *)&"实验已完成");
                                        menu_list_element_set_visible(2, i + 1, hFunctionImage1, 0);
                                        menu_list_element_set_visible(2, i + 1, hFunctionButton1, 0);
                                        menu_list_element_set_visible(2, i + 1, hFunctionImage2, 0);
                                        menu_list_element_set_visible(2, i + 1, hFunctionButton2, 0);
                                        menu_list_element_set_visible(2, i + 1, hFunctionImage3, 0);
                                        menu_list_element_set_visible(2, i + 1, hFunctionButton3, 0);
                                break; 
                                
                                default :
                                        
                                break;
                                }
                        }
                }
        }
        
        if(flag_reset == routine.flags.flagTeacherLogin) {
                menu_list_element_set_data(3, 1, hExpSubTitle, (void *)&"请教师验证身份");
                menu_list_element_set_visible(3, 1, hExpContent1, 0);
                menu_list_element_set_visible(3, 1, hExpContent2, 0);
                menu_list_element_set_visible(3, 1, hExpContent3, 0);
        }
        else;
        
        
}
      

void menu_reconstruct_bar_content(int bar_index)
{
	list_reset();
	WM_HideWindow(hExpStatusImage1);
	WM_HideWindow(hExpStatusImage2);
	WM_HideWindow(hExpStatusImage3);
	list_content_slide(dir_shallow);
	GUI_Delay(50);

	switch(bar_index) {
	case ACTION_LOGIN :
		WM_HideWindow(hExpStatusImage1);
		WM_HideWindow(hExpStatusImage2);
		WM_HideWindow(hExpStatusImage3);
		TEXT_SetText(hSubListTitle1, "学生签到");
		TEXT_SetText(hSubListTitle2, "学生签退");
		TEXT_SetText(hSubListTitle3, "签到情况");

		TEXT_SetText(hSubListContent1, "签到入口");
		TEXT_SetText(hSubListContent2, "签退入口");
		TEXT_SetText(hSubListContent3, "签到情况");
		break;

	case ACTION_EXP_DETAIL :
		WM_ShowWindow(hExpStatusImage1);
		WM_ShowWindow(hExpStatusImage2);
		WM_ShowWindow(hExpStatusImage3);

	case ACTION_EXP_SCORE :
		WM_ShowWindow(hExpStatusImage1);
		WM_ShowWindow(hExpStatusImage2);
		WM_ShowWindow(hExpStatusImage3);
		TEXT_SetText(hSubListTitle1, "子实验一");
		TEXT_SetText(hSubListTitle2, "子实验二");
		TEXT_SetText(hSubListTitle3, "子实验三");

		TEXT_SetText(hSubListContent1, routine.main_exp.sub_exp[0].subExpName);
		TEXT_SetText(hSubListContent2, routine.main_exp.sub_exp[1].subExpName);
		TEXT_SetText(hSubListContent3, routine.main_exp.sub_exp[2].subExpName);
		break;

	case 4 :
		TEXT_SetText(hSubListTitle1, "连接设置");
		TEXT_SetText(hSubListTitle2, "偏好设置");
		TEXT_SetText(hSubListTitle3, "关于本机");

		TEXT_SetText(hSubListContent1, "连接设置");
		TEXT_SetText(hSubListContent2, "偏好设置");
		TEXT_SetText(hSubListContent3, "关于本机");
		break;

	default :

		break;
	}

	list_content_slide(dir_deep);
       
}

void menu_reconstruct_list_content(int bar_index, int list_index)
{

        WM_HideWindow(hKeyboard);
        WM_HideWindow(hFullKeyboard);
        WM_HideWindow(hConnectList);
        
        display_board_slide(menu.bar[ex_bar_status - 1].subList[ex_list_status - 1].hContentWin, 800);       
        menu_list_elements_switch(element_list_of(ex_bar_status, ex_list_status), element_list_of(bar_index, list_index));
        display_board_slide(menu.bar[bar_index - 1].subList[list_index - 1].hContentWin, 400);
}

void menu_init()
{
        WM_ShowWindow(hSubExpWin);
        WM_ShowWindow(hSettingWindow);
        
        menu_list_element_attach(1, 1, hExpTitle, element_text, (void *)&routine.main_exp.mainExpName, element_visible);
        menu_list_element_attach(1, 1, hExpSubTitle, element_text, (void *)&"请签到", element_visible);
        menu_list_element_attach(1, 1, hFunctionImage1, element_image, (void *)&bmhdu_logo, element_visible);
        menu_list_element_attach(1, 1, hFunctionButton1, element_button, (void *)&"签到入口", element_visible);
        
        menu_list_element_attach(1, 2, hExpTitle, element_text, (void *)&routine.main_exp.mainExpName, element_visible);
        menu_list_element_attach(1, 2, hExpSubTitle, element_text, (void *)&"请签退", element_visible);
        menu_list_element_attach(1, 2, hFunctionImage1, element_image, (void *)&bmhdu_logo, element_visible);
        menu_list_element_attach(1, 2, hFunctionButton1, element_button, (void *)&"签退入口", element_visible);
        
        menu_list_element_attach(1, 3, hExpTitle, element_text, (void *)&routine.main_exp.mainExpName, element_visible);
        menu_list_element_attach(1, 3, hExpSubTitle, element_text, (void *)&"签到情况", element_visible);
        menu_list_element_attach(1, 3, hSignList, element_win, NULL, element_visible);
        
        menu_list_element_attach(2, 1, hExpTitle, element_text, (void *)&routine.main_exp.mainExpName, element_visible);
        menu_list_element_attach(2, 1, hExpSubTitle, element_text, (void *)"请等待教师开始实验", element_visible);
        menu_list_element_attach(2, 1, hExpContent1, element_text, (void *)&routine.main_exp.sub_exp[0].subExpDetail, element_invisible);
        menu_list_element_attach(2, 1, hExpContent2, element_text, (void *)&"实验原理", element_invisible);
        menu_list_element_attach(2, 1, hExpContent3, element_text, (void *)&"实验原理", element_invisible);
        menu_list_element_attach(2, 1, hFunctionImage1, element_image, (void *)&bmhdu_logo, element_invisible);
        menu_list_element_attach(2, 1, hFunctionImage2, element_image, NULL, element_invisible);
        menu_list_element_attach(2, 1, hFunctionImage3, element_image, NULL, element_invisible);
        menu_list_element_attach(2, 1, hFunctionButton1, element_button, (void *)&"开始实验", element_invisible);
        menu_list_element_attach(2, 1, hFunctionButton2, element_button, (void *)&"提交实验", element_invisible);
        menu_list_element_attach(2, 1, hFunctionButton3, element_button, (void *)&"问题解答", element_invisible);
        menu_list_element_attach(2, 1, hQueueText, element_text, NULL, element_invisible);
        
        menu_list_element_attach(2, 2, hExpTitle, element_text, (void *)&routine.main_exp.mainExpName, element_visible);
        menu_list_element_attach(2, 2, hExpSubTitle, element_text, (void *)"请等待教师开始实验", element_visible);
        menu_list_element_attach(2, 2, hExpContent1, element_text, (void *)&routine.main_exp.sub_exp[1].subExpDetail, element_invisible);
        menu_list_element_attach(2, 2, hExpContent2, element_text, (void *)&"实验原理", element_invisible);
        menu_list_element_attach(2, 2, hExpContent3, element_text, (void *)&"实验原理", element_invisible);
        menu_list_element_attach(2, 2, hFunctionImage1, element_image, NULL, element_invisible);
        menu_list_element_attach(2, 2, hFunctionImage2, element_image, NULL, element_invisible);
        menu_list_element_attach(2, 2, hFunctionImage3, element_image, NULL, element_invisible);
        menu_list_element_attach(2, 2, hFunctionButton1, element_button, (void *)&"开始实验", element_invisible);
        menu_list_element_attach(2, 2, hFunctionButton2, element_button, (void *)&"提交实验", element_invisible);
        menu_list_element_attach(2, 2, hFunctionButton3, element_button, (void *)&"问题解答", element_invisible);
        menu_list_element_attach(2, 2, hQueueText, element_text, NULL, element_invisible);
        
        menu_list_element_attach(2, 3, hExpTitle, element_text, (void *)&routine.main_exp.mainExpName, element_visible);
        menu_list_element_attach(2, 3, hExpSubTitle, element_text, (void *)"请等待教师开始实验", element_visible);
        menu_list_element_attach(2, 3, hExpContent1, element_text, (void *)&routine.main_exp.sub_exp[2].subExpDetail, element_invisible);
        menu_list_element_attach(2, 3, hExpContent2, element_text, (void *)&"实验原理", element_invisible);
        menu_list_element_attach(2, 3, hExpContent3, element_text, (void *)&"实验原理", element_invisible);
        menu_list_element_attach(2, 3, hFunctionImage1, element_image, NULL, element_invisible);
        menu_list_element_attach(2, 3, hFunctionImage2, element_image, NULL, element_invisible);
        menu_list_element_attach(2, 3, hFunctionImage3, element_image, NULL, element_invisible);
        menu_list_element_attach(2, 3, hFunctionButton1, element_button, (void *)&"开始实验", element_invisible);
        menu_list_element_attach(2, 3, hFunctionButton2, element_button, (void *)&"提交实验", element_invisible);
        menu_list_element_attach(2, 3, hFunctionButton3, element_button, (void *)&"问题解答", element_invisible);
        menu_list_element_attach(2, 3, hQueueText, element_text, NULL, element_invisible);
        
        menu_list_element_attach(3, 1, hExpTitle, element_text, (void *)&routine.main_exp.mainExpName, element_visible);
        menu_list_element_attach(3, 1, hExpSubTitle, element_text, (void *)&"请教师验证身份", element_visible);
        menu_list_element_attach(3, 1, hFunctionImage1, element_image, NULL, element_visible);
        menu_list_element_attach(3, 1, hFunctionButton1, element_button, (void *)&"教师入口", element_visible);
        menu_list_element_attach(3, 1, hLogoutButton, element_button, (void *)&"退出", element_invisible);
        menu_list_element_attach(3, 1, hScoreEdit, element_edit, NULL, element_invisible);
        menu_list_element_attach(3, 1, hScoreText, element_text, NULL, element_invisible);
        menu_list_element_attach(3, 1, hKeyboard, element_win, NULL, element_invisible);
        
        menu_list_element_attach(3, 2, hExpTitle, element_text, (void *)&routine.main_exp.mainExpName, element_visible);
        menu_list_element_attach(3, 2, hExpSubTitle, element_text, (void *)&"请教师验证身份", element_visible);
        menu_list_element_attach(3, 2, hFunctionImage1, element_image, NULL, element_visible);
        menu_list_element_attach(3, 2, hFunctionButton1, element_button, (void *)&"教师入口", element_visible);
        menu_list_element_attach(3, 2, hLogoutButton, element_button, (void *)&"退出", element_invisible);
        menu_list_element_attach(3, 2, hScoreEdit, element_edit, NULL, element_invisible);
        menu_list_element_attach(3, 2, hScoreText, element_text, NULL, element_invisible);
        menu_list_element_attach(3, 2, hKeyboard, element_win, NULL, element_invisible);
        
        menu_list_element_attach(3, 3, hExpTitle, element_text, (void *)&routine.main_exp.mainExpName, element_visible);
        menu_list_element_attach(3, 3, hExpSubTitle, element_text, (void *)&"请教师验证身份", element_visible);
        menu_list_element_attach(3, 3, hFunctionImage1, element_image, NULL, element_visible);
        menu_list_element_attach(3, 3, hFunctionButton1, element_button, (void *)&"教师入口", element_visible);
        menu_list_element_attach(3, 3, hLogoutButton, element_button, (void *)&"退出", element_invisible);
        menu_list_element_attach(3, 3, hScoreEdit, element_edit, NULL, element_invisible);
        menu_list_element_attach(3, 3, hScoreText, element_text, NULL, element_invisible);
        menu_list_element_attach(3, 3, hKeyboard, element_win, NULL, element_invisible);

        menu_list_element_attach(4, 1, hConnectList, element_win, NULL, element_invisible);
        menu_list_element_attach(4, 1, hWifiListButton, element_button, NULL, element_visible);
        menu_list_element_attach(4, 1, hRfidListButton, element_button, NULL, element_visible);
        menu_list_element_attach(4, 1, hBackImage, element_button, NULL, element_invisible);
        menu_list_element_attach(4, 1, hBackButton, element_button, NULL, element_invisible);
        menu_list_element_attach(4, 1, hScanButton, element_button, NULL, element_invisible);
        
        menu_list_element_attach(4, 2, hPreferenceText0, element_text, NULL, element_visible);
        menu_list_element_attach(4, 2, hPreferenceText1, element_text, NULL, element_visible);
        menu_list_element_attach(4, 2, hPreferenceTextMux, element_text, NULL, element_visible);
        menu_list_element_attach(4, 2, hPreferenceTextDevID, element_text, NULL, element_visible);
        menu_list_element_attach(4, 2, hVoiceButton, element_button, NULL, element_visible);
        menu_list_element_attach(4, 2, hVolumeSlider, element_win, NULL, element_visible);
        menu_list_element_attach(4, 2, hMuxButton, element_button, NULL, element_visible);
        menu_list_element_attach(4, 2, hDevIdEdit, element_button, NULL, element_visible);
        
        menu_list_element_attach(4, 3, hInfoText0, element_text, (void *)&"型号:             Epoch 1 Compact",      element_visible);
        menu_list_element_attach(4, 3, hInfoText1, element_text, (void *)&"版本号:         IIEES v1.0 2019.1",      element_visible);
        menu_list_element_attach(4, 3, hInfoText2, element_text, (void *)&"处理器:         STM32F429ZGT6",          element_visible);
        menu_list_element_attach(4, 3, hInfoText3, element_text, (void *)&"屏幕 :            4.3' TFT 800 * 480",   element_visible);
        menu_list_element_attach(4, 3, hInfoText4, element_text, (void *)&"系统版本:      FreeRTOS Kernel V10.0.1", element_visible);
        menu_list_element_attach(4, 3, hInfoText5, element_text, (void *)&"GUI版本:       STemWin V5.32",           element_visible);
        menu_list_element_attach(4, 3, hInfoText6, element_text, (void *)&"驱动框架:      DTR v1.0",                element_visible);
        menu_list_element_attach(4, 3, hInfoText7, element_text, (void *)&"设备ID:          1551",                  element_visible);
        menu_list_element_attach(4, 3, hInfoText8, element_text, (void *)&"开发团队:      Hdu-Microchip-Lab",       element_visible);
        menu_list_element_attach(4, 3, hInfoText9, element_text, (void *)&"(c) 2018 - 2022 Hdu-Microchip-Lab",      element_visible);
        

}

