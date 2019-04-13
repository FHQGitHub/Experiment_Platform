#include "DIALOG.h"
#include "oneFS.h"
#include "systask.h"

#define FS_FLAG_IDLE								0x00
#define	FS_FLAG_RIGHTCLICKED_ELEMENT				0x01
#define	FS_FLAG_RIGHTCLICKED_BK						0x02
#define	FS_FLAG_RENAME								0x03

#define	FS_MAINLIST_DELETE							0x00
#define	FS_MAINLIST_RENAME							0x01
#define	FS_MAINLIST_NEW								0x02

#define	FS_SUBLIST_INDEX							0x03
#define	FS_SUBLIST_NEW_FOLDER						0x03
#define	FS_SUBLIST_NEW_FILE							0x04

#if (__USE_WIDGET_FS)

static void _cbFsMainWin(WM_MESSAGE * pMsg)
{
	GUI_RECT 			pRect;
	int  				NCode;
	int  				Id;
	int 				click_time 			= 0;
	int 				select_element	= 0; 
	static char	file_name[20] 	={0};
	static int	process_id 			= 0;
	static int	ExFlag 					= FS_FLAG_IDLE;
	static int											select_element_ex = -1;
	static WM_HWIN									pHandler 					= 0;
	static onefs_node_struct_type		*pIndex 					= NULL;

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
		
  break;
	
	case WM_TIMER: 
		if(ExFlag == 3)
			TEXT_SetText(pIndex->handler->hText, (const char *)gui.keyboard->content);
		WM_RestartTimer(pMsg->Data.v, 30);
			
	break;

  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
		
			case ID_WIDGET_FS_BUTTON_EXIT: 
				switch(NCode) {
					case WM_NOTIFICATION_CLICKED:
							 
					break;
					case WM_NOTIFICATION_RELEASED:
						if(!strcmp((const char *)onefs.index->path, "0:")) {
							WM_HideWin(onefs.hWin);
							
							xTaskNotify(xHandleTaskSettingwin,
										bitOpen,
										eSetValueWithOverwrite);
						}
						else	
							onefs.exit();
					break;
				}
			break;
			
			case ID_WIDGET_FS_MAINLIST: 
			switch(NCode) {
				case WM_NOTIFICATION_CLICKED:
					
				break;
				case WM_NOTIFICATION_RELEASED:
					select_element = LISTBOX_GetSel(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_MAINLIST));
					if(FS_MAINLIST_NEW == select_element) {
						if(WM_IsVisible(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_SUBLIST)))
							WM_HideWin(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_SUBLIST));
						else {
							LISTBOX_SetItemDisabled(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_SUBLIST), 0, 1);
							LISTBOX_SetItemDisabled(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_SUBLIST), 1, 1);
							WM_GetWindowRectEx(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_MAINLIST), &pRect);
							WM_MoveTo(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_SUBLIST), pRect.x0 + 79, pRect.y0 + 70);
							WM_BringToTop(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_SUBLIST));
							WM_ShowWin(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_SUBLIST));
						}
					}

					else if(select_element_ex == select_element) {
						
						switch (select_element) {
							case FS_MAINLIST_DELETE : 
								select_element_ex = -1;
								ExFlag = FS_FLAG_IDLE;
								if(WM_IsVisible(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_MAINLIST))) 	
									WM_HideWin(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_MAINLIST));
								if(WM_IsVisible(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_SUBLIST)))
									WM_HideWin(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_SUBLIST));
								
								onefs.remove(WM_GetDialogItem(pMsg->hWin, process_id));
							break;
								
							case FS_MAINLIST_RENAME : 
								select_element_ex = -1;
								ExFlag = FS_FLAG_IDLE;
								if(WM_IsVisible(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_MAINLIST))) 	
									WM_HideWin(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_MAINLIST));
								if(WM_IsVisible(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_SUBLIST)))
									WM_HideWin(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_SUBLIST));
								
								if(NULL != pIndex) {
									gui.keyboard->open();
									TEXT_GetText(pIndex->handler->hText, file_name, sizeof(file_name));
									strcpy((char *)gui.keyboard->content, (const char *)file_name);
									gui.keyboard->content_index += strlen((const char *)file_name);
									TEXT_SetBkColor(pIndex->handler->hText, GUI_LIGHTBLUE);
									ExFlag = FS_FLAG_RENAME;
								}
							break;
							
							default : 
								
							break;
						}
						
					}
					select_element_ex = select_element;
				break;
					
				case WM_NOTIFICATION_SEL_CHANGED:
				 
					break;
				default : break;
			}
			break;
				
			case ID_WIDGET_FS_SUBLIST: 
			switch(NCode) {
				case WM_NOTIFICATION_CLICKED:
				 
					break;
				case WM_NOTIFICATION_RELEASED:
					select_element = LISTBOX_GetSel(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_SUBLIST)) + FS_SUBLIST_INDEX;
					if(select_element_ex == select_element) {
						
						switch (select_element) {
							case FS_SUBLIST_NEW_FOLDER : 
								ExFlag = FS_FLAG_IDLE;
								select_element_ex = -1;
								if(WM_IsVisible(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_MAINLIST))) 	
									WM_HideWin(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_MAINLIST));
								if(WM_IsVisible(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_SUBLIST)))
									WM_HideWin(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_SUBLIST));
								onefs.create("new folder",onefs_directory);
							break;
								
							case FS_SUBLIST_NEW_FILE : 
								ExFlag = FS_FLAG_IDLE;
								select_element_ex = -1;
								if(WM_IsVisible(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_MAINLIST))) 	
									WM_HideWin(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_MAINLIST));
								if(WM_IsVisible(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_SUBLIST)))
									WM_HideWin(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_SUBLIST));
								onefs.create("new file.bin",onefs_file);
							break;
							}
						}
						select_element_ex = select_element;
					break;
				case WM_NOTIFICATION_SEL_CHANGED:
				 
					break;
			}
			break;
	
			default :
				process_id = Id;
				pIndex = onefs.index->child;
				pHandler = WM_GetDialogItem(pMsg->hWin, process_id);
				while(pIndex->handler->hImg != pHandler && NULL != pIndex)
					pIndex = pIndex->next;
				
				switch(NCode) {
					case WM_NOTIFICATION_CLICKED:
						while(touch.status) {
							click_time ++;
							GUI_Delay(20);
							if(click_time > 50) {
								click_time = 0;
								ExFlag = FS_FLAG_RIGHTCLICKED_ELEMENT;
								//LISTBOX_SetItemDisabled(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_MAINLIST), 0, 0);
								//LISTBOX_SetItemDisabled(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_MAINLIST), 1, 0);
								WM_MoveTo(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_MAINLIST), touch.coordXY[0].x + 5, touch.coordXY[0].y + 5);
								WM_BringToTop(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_MAINLIST));
								WM_ShowWin(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_MAINLIST));
							 return;
							}
						}
					break;
					case WM_NOTIFICATION_RELEASED:
						if(ExFlag != 1) 
							onefs.enter(WM_GetDialogItem(pMsg->hWin, Id));
						else;
					break;
				}
				break;
			}
		break;

		
		
		case WM_TOUCH :
			if(0 == touch.status) {
				
				if(2 == ExFlag) {
					ExFlag = FS_FLAG_IDLE;
					break;
				}
				
				if(3 == ExFlag) {
					ExFlag = FS_FLAG_IDLE;
					TEXT_SetBkColor(pIndex->handler->hText, GUI_WHITE);
					sprintf(pIndex->name, "%s",gui.keyboard->content);
					sprintf(pIndex->path, "%s%s/",onefs.index->path, pIndex->name);
					memset(gui.keyboard->content, 0, 100);
					gui.keyboard->content_index = gui.keyboard->content;
					gui.keyboard->close();
					break;
				}
				
				if(WM_IsVisible(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_MAINLIST)) && ExFlag != 2) {
					ExFlag = FS_FLAG_IDLE;
					WM_HideWin(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_MAINLIST));
					if(WM_IsVisible(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_SUBLIST)))
						WM_HideWin(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_SUBLIST));
				}
			}
				
			while(touch.status) {
					click_time ++;
					vTaskDelay(20);
					if(click_time > 50) {
						click_time = 0;
						ExFlag = FS_FLAG_RIGHTCLICKED_BK;
						WM_MoveTo(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_MAINLIST), touch.coordXY[0].x + 5, touch.coordXY[0].y + 5);
						LISTBOX_SetItemDisabled(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_MAINLIST), 0, 1);
						LISTBOX_SetItemDisabled(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_MAINLIST), 1, 1);
						WM_BringToTop(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_MAINLIST));
						WM_ShowWin(WM_GetDialogItem(pMsg->hWin, ID_WIDGET_FS_MAINLIST));
					 return;
					}
				}
			break;
		default:
			WM_DefaultProc(pMsg);
		break;
  }
		
}

WM_HWIN FsWinOnCreate(void);
WM_HWIN FsWinOnCreate(void) 
{
  WM_HWIN hMainWin;
	WM_HWIN hButton;
	WM_HWIN hMainList;
	WM_HWIN hSubList;
	WM_HWIN hPathText;
	
	static SpecializedSkinTypedef button_back_src;
	SpecializedSkinTypedef *button_back;
	
  hMainWin = FRAMEWIN_CreateEx(0, 0, 810, 485, 0, WM_CF_SHOW, 0, ID_WIDGET_FS_MAINWIN, "/", _cbFsMainWin);
	FRAMEWIN_SetTitleVis(hMainWin, 0);
	WM_SetCallback(hMainWin, _cbFsMainWin);
	
	hButton = BUTTON_CreateEx(10, 10, 40, 50, hMainWin, WM_CF_SHOW, 0, ID_WIDGET_FS_BUTTON_EXIT);
	button_back_src.normal = &bmback;
	button_back_src.mark =  &bmback;
	button_back = &button_back_src;
	WM_SetUserData(hButton, (const void *)&button_back, sizeof(button_back));
	BUTTON_SetSkin(hButton, SKIN_button2C);
	
	hMainList = LISTBOX_CreateEx(100, 100, 80, 150, hMainWin, WM_CF_SHOW, 0, ID_WIDGET_FS_MAINLIST, NULL);
	LISTBOX_SetItemSpacing(hMainList, 10);
	LISTBOX_SetBkColor(hMainList, LISTBOX_CI_SEL, GUI_WHITE);
	LISTBOX_SetBkColor(hMainList, LISTBOX_CI_SELFOCUS, GUI_LIGHTBLUE);
	LISTBOX_SetTextColor(hMainList, LISTBOX_CI_SEL, GUI_BLACK);
	LISTBOX_SetFont(hMainList, GUI_FONT_20_ASCII);
	LISTBOX_SetTextAlign(hMainList, GUI_TA_VCENTER | GUI_TA_HCENTER);
	LISTBOX_AddString(hMainList, "delete");
	LISTBOX_AddString(hMainList, "rename");
	LISTBOX_AddString(hMainList, "new");
	WM_HideWin(hMainList);
	
	hSubList = LISTBOX_CreateEx(0, 0, 80, 150, hMainWin, WM_CF_SHOW, 0, ID_WIDGET_FS_SUBLIST, NULL);
	LISTBOX_SetItemSpacing(hSubList, 10);
	LISTBOX_SetBkColor(hSubList, LISTBOX_CI_SEL, GUI_WHITE);
	LISTBOX_SetBkColor(hSubList, LISTBOX_CI_SELFOCUS, GUI_LIGHTBLUE);
	LISTBOX_SetTextColor(hSubList, LISTBOX_CI_SEL, GUI_BLACK);
	LISTBOX_SetFont(hSubList, GUI_FONT_20_ASCII);
	LISTBOX_SetTextAlign(hSubList, GUI_TA_VCENTER | GUI_TA_HCENTER);
	LISTBOX_AddString(hSubList, "folder");
	LISTBOX_AddString(hSubList, "file");
	WM_HideWin(hSubList);
	
	hPathText = TEXT_CreateEx(50, 10, 700, 20, hMainWin, WM_CF_SHOW, TEXT_CF_HCENTER | TEXT_CF_VCENTER, ID_WIDGET_FS_TEXT_PATH, "0:");
	TEXT_SetFont(hPathText, GUI_FONT_20_ASCII);
	
	WM_CreateTimer(hMainWin, 0, 30, 0);
	
  return hMainWin;
	
}

#endif
