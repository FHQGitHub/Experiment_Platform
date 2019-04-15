/*
*********************************************************************************************************
*
*	模块名称 : BSP模块
*	文件名称 : bsp.h
*	说    明 : 这是底层驱动模块所有的h文件的汇总文件。 应用程序只需 #include bsp.h 即可，
*			  不需要#include 每个模块的 h 文件
*
*	修改记录 :
*		版本号  日期         作者                  说明
*		V1.0    2018-01-28   HDU-Microchip_Lab.    正式发布
*
*	Copyright (C), 2015-2020
*
*********************************************************************************************************
*/

#ifndef __BSP_H
#define __BSP_H

#define		__USE_DRIVER_SYSTICK								(1)
#define		__USE_DRIVER_UART									(1)
#define		__USE_DRIVER_TIMER									(1)
#define		__USE_DRIVER_LCD									(1)
#define		__USE_DRIVER_TOUCH									(1)
#define         __USE_SPI_FLASH										(1)

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "stm32f4xx.h"
#include "oop.h"
#include "error.h"
#include "parson.h"
#include "malloc.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "croutine.h"
#include "event_groups.h"
#include "timers.h"

#include "ff.h"

#include "GUI.h"

#include "handler.h"

#include "bsp_systick.h"
#include "bsp_uart.h"
#include "bsp_timer.h"
#include "bsp_stmflash.h"
#include "bsp_lcd.h"
#include "bsp_gt9147.h"
#include "bsp_ctiic.h"
#include "bsp_touch.h"
#include "bsp_spi.h"
#include "bsp_spi_flash.h"
#include "bsp_exti.h"
#include "bsp_lp_rcc.h"
#include "bsp_rc522.h"

#define uart_x uart_3

typedef struct
{
	u16 touch_resume_per_sec;
	u16 count_down_per_sec;
	u16 standby_per_min;
}notify_type_struct;

typedef struct
{
	int msec;
	int  sec;
	int  min;
	int  hour;
	int  day;
	int  month;
	int  year;
}system_time_type_struct;

extern enum flag_t wifiStateChangeFlag;

extern notify_type_struct timer6_notify;
extern system_time_type_struct system_time;

extern TaskHandle_t StartTask_Handler;
extern TaskHandle_t TimerTask_Handler;
extern TaskHandle_t TouchTask_Handler;
extern TaskHandle_t GuiTask_Handler;
extern TaskHandle_t WifiTask_Handler;
extern TaskHandle_t QRScannerTask_Handler;
extern TaskHandle_t ConsoleTask_Handler;
extern TaskHandle_t InitTask_Handler;
extern TaskHandle_t RC522Task_Handler;
extern TaskHandle_t MenuTask_Handler;

extern QueueHandle_t xQueueWifi;
extern TimerHandle_t xTimerWifiConnect;
extern TimerHandle_t xTimerTcpCheck;

void bsp_Init(void);

#endif
