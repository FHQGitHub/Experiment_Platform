#ifndef __MAIN_H
#define __MAIN_H

/**-------------------------头文件--------------------------**/

//系统级头文件
#include "stm32f4xx.h" 
#include "delay.h"
#include "includes.h"
#include "string.h"


//应用级头文件
#include "redirprintf.h"
#include "UART.h"
#include "GUI.h"
#include "WM.h"
#include "timer.h"
//#include "GUIDemo.h"   //更换驱动的时候跑demo


//ICONS头文件
#include "icons.h"





//外设级头文件
#include "malloc.h"
#include "redirprintf.h"	
#include "touch.h"
#include "stmflash.h"
#include "ILI93xx.h"
#include "spi.h"
#include "bsp_spi_flash.h"
#include "rc522.h"

/**-------------------------头文件--------------------------**/

#define PRICE													2

#define ID_WINDOW_MAIN_0   					 	(GUI_ID_USER + 0x03)
#define ID_IMAGE_MAIN_0    						(GUI_ID_USER + 0x04)
#define ID_TEXT_MAIN_0   						 	(GUI_ID_USER + 0x05)
#define ID_TEXT_MAIN_1    						(GUI_ID_USER + 0x06)
#define ID_TEXT_MAIN_2    						(GUI_ID_USER + 0x07)
#define ID_TEXT_MAIN_3    						(GUI_ID_USER + 0x08)
#define ID_EDIT_MAIN_0    						(GUI_ID_USER + 0x09) 
#define ID_EDIT_MAIN_1    						(GUI_ID_USER + 0x0A) 
#define ID_EDIT_MAIN_2    						(GUI_ID_USER + 0x0B) 

#define ID_FRAMEWIN_STATISTIC_0    		(GUI_ID_USER + 0x00)
#define ID_EDIT_STATISTIC_0    				(GUI_ID_USER + 0x01)
#define ID_TEXT_STATISTIC_0    				(GUI_ID_USER + 0x02)
#define ID_TEXT_STATISTIC_1    				(GUI_ID_USER + 0x03)
#define ID_EDIT_STATISTIC_1    				(GUI_ID_USER + 0x04)

#define ID_FRAMEWIN_AFFIRM_0    			(GUI_ID_USER + 0x00)
#define ID_BUTTON_AFFIRM_0    				(GUI_ID_USER + 0x03)
#define ID_BUTTON_AFFIRM_1   				 	(GUI_ID_USER + 0x04)
#define ID_TEXT_AFFIRM_0    					(GUI_ID_USER + 0x05)

typedef struct
{
	u8 cid[10];
	u16 num;
	u16 csp;
}_dev_info;

extern GUI_FONT     	YaHei24_Font;
extern GUI_FONT     	YaHei20_Font;

extern _dev_info _current_info;
extern _dev_info _stat_info[100];

extern u8 Card_Serial_Number[MAXRLEN];
extern u8 Card_Read_Buf[16];
extern int value;
	
extern WM_HWIN hStatistic;
extern WM_HWIN hMain;
extern WM_HWIN hAffirm;

extern GUI_CONST_STORAGE GUI_BITMAP bmJinjie_Icon;

void CreateStatisticWindow(void);
void CreateAffirmWindow(void);
#include "key.h"





#endif
