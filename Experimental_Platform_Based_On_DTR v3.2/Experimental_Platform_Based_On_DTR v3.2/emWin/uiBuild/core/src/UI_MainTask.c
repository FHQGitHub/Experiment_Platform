#include "uiBuild.h"

void ui_init()
{
	
#if GUI_WINSUPPORT
	WM_SetCreateFlags(WM_CF_MEMDEV);
#endif
	GUI_Init();
	GUI_EnableAlpha(1);
#if GUI_WINSUPPORT
	WM_MULTIBUF_Enable(1);
#endif

	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
	FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
	CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
	DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
	SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
	SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
	HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
	RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
	MULTIPAGE_SetDefaultSkin(MULTIPAGE_SKIN_FLEX);

	GUI_SetXBF();
	GUI_UC_SetEncodeUTF8();

	WM_SetDesktopColor(0x00FFFCF9);

	hMainWin = mainWindowOnCreate();
	hSubExpWin = subExpWindowOnCreate();
	menu.bar[ACTION_LOGIN - 1].subList[0].hContentWin = hSubExpWin;
	menu.bar[ACTION_LOGIN - 1].subList[1].hContentWin = hSubExpWin;
	menu.bar[ACTION_LOGIN - 1].subList[2].hContentWin = hSubExpWin;

	menu.bar[ACTION_EXP_DETAIL - 1].subList[0].hContentWin = hSubExpWin;
	menu.bar[ACTION_EXP_DETAIL - 1].subList[1].hContentWin = hSubExpWin;
	menu.bar[ACTION_EXP_DETAIL - 1].subList[2].hContentWin = hSubExpWin;

	menu.bar[ACTION_EXP_SCORE - 1].subList[0].hContentWin = hSubExpWin;
	menu.bar[ACTION_EXP_SCORE - 1].subList[1].hContentWin = hSubExpWin;
	menu.bar[ACTION_EXP_SCORE - 1].subList[2].hContentWin = hSubExpWin;

	hSettingWindow = infomationWindowOnCreate();
	menu.bar[ACTION_SETTING - 1].subList[0].hContentWin = hSettingWindow;
	menu.bar[ACTION_SETTING - 1].subList[1].hContentWin = hSettingWindow;
	menu.bar[ACTION_SETTING - 1].subList[2].hContentWin = hSettingWindow;

	hConfirmWindow = confirmWindowOnCreate();
	hNotifyWindow = notifyWindowOnCreate();
	hConnectWindow = connectWindowOnCreate();
	hKeyboard = keyboardPageOnCreate();
	hFullKeyboard = fullKeyboardOnCreate();
        
        menu_init();
}






