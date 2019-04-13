#ifndef __UIBUILD_H
#define __UIBUILD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "GUI.h"
#include "DIALOG.h"
#include "WM.h"

#include "bsp.h"

#include "icons.h"
#include "UI_Font.h"
#include "UI_Touch.h"
#include "UI_Effect.h"
#include "UI_Logic.h"
#include "UI_PushButton.h"
#include "UI_SpecializedSkin.h"
#include "WIDGET_keyboard.h"
                           
#define ACTION_LOGIN            1
#define ACTION_EXP_DETAIL       2
#define ACTION_EXP_SCORE        3
#define ACTION_SETTING          4

#define ACTION_LIST_1           1
#define ACTION_LIST_2           2
#define ACTION_LIST_3           3

#define WM_BUTTON_BEGIN_CB 				(WM_USER + 0x00) 
#define WM_BUTTON_SUBMIT_CB 			(WM_USER + 0x01) 
#define WM_BUTTON_QUESTION_CB 			(WM_USER + 0x02) 
#define WM_BUTTON_LOGOUT_CB 			(WM_USER + 0x03) 
#define WM_BUTTON_SCORE_CB 				(WM_USER + 0x04) 

#define WM_WIFI_SCAN_CB 			(WM_USER + 0x05)
#define WM_WIFI_CONNECT_CB			(WM_USER + 0x06)
#define WM_RFID_MATCH_CB			(WM_USER + 0x07)

extern WM_HWIN hMainWin;
extern WM_HWIN hSubExpWin;
extern WM_HWIN hBarWin;
extern WM_HWIN hListWin;
extern WM_HWIN hDateWin;
extern WM_HWIN hTimeWin;
extern WM_HWIN hSubListTitle1;
extern WM_HWIN hSubListTitle2;
extern WM_HWIN hSubListTitle3;
extern WM_HWIN hSubListContent1;
extern WM_HWIN hSubListContent2;
extern WM_HWIN hSubListContent3;

extern WM_HWIN hFunctionImage1;
extern WM_HWIN hFunctionImage2;
extern WM_HWIN hFunctionImage3;
extern WM_HWIN hLogoutImage;
extern WM_HWIN hFunctionButton1;
extern WM_HWIN hFunctionButton2;
extern WM_HWIN hFunctionButton3;
extern WM_HWIN hLogoutButton;
extern WM_HWIN hExpTitle;
extern WM_HWIN hExpSubTitle;
extern WM_HWIN hExpContent1;
extern WM_HWIN hExpContent2;
extern WM_HWIN hExpContent3;
extern WM_HWIN hExpStatusImage1;
extern WM_HWIN hExpStatusImage2;
extern WM_HWIN hExpStatusImage3;
extern WM_HWIN hWifiStateImage;
extern WM_HWIN hScoreEdit;
extern WM_HWIN hScoreText;
extern WM_HWIN hQueueText;
extern WM_HWIN hSignList;

extern WM_HWIN hConfirmWindow;
extern WM_HWIN hConfirmText1;
extern WM_HWIN hConfirmText2;
extern WM_HWIN hConfirmEdit1;

extern WM_HWIN hSettingWindow;
extern WM_HWIN hInfoText0;
extern WM_HWIN hInfoText1;
extern WM_HWIN hInfoText2;
extern WM_HWIN hInfoText3;
extern WM_HWIN hInfoText4;
extern WM_HWIN hInfoText5;
extern WM_HWIN hInfoText6;
extern WM_HWIN hInfoText7;
extern WM_HWIN hInfoText8;
extern WM_HWIN hInfoText9;
extern WM_HWIN hPreferenceText0;
extern WM_HWIN hPreferenceText1;
extern WM_HWIN hPreferenceTextMux;
extern WM_HWIN hPreferenceTextDevID;
extern WM_HWIN hVoiceButton;
extern WM_HWIN hVolumeSlider;
extern WM_HWIN hMuxButton;
extern WM_HWIN hDevIdEdit;
extern WM_HWIN hConnectList;
extern WM_HWIN hWifiListButton;
extern WM_HWIN hRfidListButton;
extern WM_HWIN hBackImage;
extern WM_HWIN hBackButton;
extern WM_HWIN hScanButton;

extern WM_HWIN hNotifyWindow;
extern WM_HWIN hNotifyText1;
extern WM_HWIN hNotifyText2;

extern WM_HWIN hConnectWindow;
extern WM_HWIN hConnectContentText1;
extern WM_HWIN hConnectContentText2;
extern WM_HWIN hConnectContentText3;
extern WM_HWIN hConnectEdit;
extern WM_HWIN hConnectButton0;
extern WM_HWIN hConnectPromptText1;
extern WM_HWIN hConnectPromptText2;
extern WM_HWIN hConnectPromptText3;

extern WM_HWIN hKeyboard;

void ui_init(void);

WM_HWIN mainWindowOnCreate(void);
WM_HWIN subExpWindowOnCreate(void);
WM_HWIN confirmWindowOnCreate(void);
WM_HWIN keyboardPageOnCreate(void);
WM_HWIN fullKeyboardPageOnCreate(void);
WM_HWIN fullKeyboardOnCreate(void);
WM_HWIN infomationWindowOnCreate(void);
WM_HWIN notifyWindowOnCreate(void);
WM_HWIN connectWindowOnCreate(void);

#endif

