#include "systask.h"

static WM_HWIN create(void);
static void open(void);
static void close(void);
static void wifi_connectwin_task(void);

UI_wifi_connectwinInfoStructTypedef wifi_connectwin = {
	(WM_HWIN)0,
	
	create,
	open,
	close,
	wifi_connectwin_task
};

static WM_HWIN create(void)
{
	ui.wifi_connectwin->hwin = WifiConnectPageOnCreate();
//	WM_AttachWindow(ui.wifi_connectwin->hwin, ui.settingwin->hwin);
//	WM_AttachWindow(gui.keyboard->hWin, ui.settingwin->hwin);
	return ui.wifi_connectwin->hwin;
}

static void open()
{
	WM_BringToTop(wifi_connectwin.hwin);
	WM_ShowWin(wifi_connectwin.hwin);
}

static void close()
{
	WM_HideWin(ui.wifi_connectwin->hwin);
}

static void wifi_connect_event(void)
{
	switch(ui_state.wifi_connectwin_state)
	{
		case STATE_WIFI_CONNECTWIN_CONNECT:
			
			WM_BringToBottom(ui.wifi_connectwin->hwin);
		    WM_HideWindow(ui.wifi_connectwin->hwin);
			WM_BringToBottom(gui.keyboard->hWin);
		    WM_HideWindow(gui.keyboard->hWin);
			WM_ShowWindow(WM_GetDialogItem(ui.settingwin->hwin, ID_LISTVIEW_0));
			
			if(gui.keyboard->content == gui.keyboard->content_index)
			{
				NowData.WifiPassword = "NONE";	
			}
		
			xTaskNotify(xHandleTaskWifi,
						bitWifiConnecting,
						eSetValueWithOverwrite);
		
			ui_state.wifi_connectwin_state = STATE_WIFI_CONNECTWIN_WAIT;
			break;
		
		case STATE_WIFI_CONNECTWIN_CANCEL:
			
			WM_BringToBottom(ui.wifi_connectwin->hwin);
		    WM_HideWindow(ui.wifi_connectwin->hwin);
			WM_BringToBottom(gui.keyboard->hWin);
		    WM_HideWindow(gui.keyboard->hWin);
			WM_ShowWindow(WM_GetDialogItem(ui.settingwin->hwin, ID_LISTVIEW_0));
	  
			NowData.WifiPassword = "NONE";
		
			ui_state.wifi_connectwin_state = STATE_WIFI_CONNECTWIN_WAIT;
			break;
		
		case STATE_WIFI_CONNECTWIN_SHOW_KEYBOARD:
			
			WM_ShowWindow(gui.keyboard->hWin);
			WM_BringToTop(gui.keyboard->hWin);
		
			ui_state.wifi_connectwin_state = STATE_WIFI_CONNECTWIN_WAIT;
			break;
		
		case STATE_WIFI_CONNECTWIN_WAIT:
			
			break;
	}
}

static void wifi_connectwin_task(void)
{
	while(1)
	{
		
		wifi_connect_event();
		vTaskDelay(10);
	}
}

