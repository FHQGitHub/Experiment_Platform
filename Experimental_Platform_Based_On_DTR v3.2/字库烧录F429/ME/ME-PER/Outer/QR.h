#ifndef __QR_H
#define __QR_H	
#include "UART.h"
#include "string.h"
#include "delay.h"
#include "redirprintf.h"
#include "stm32f4xx.h"  

u8 QR_On(void);//二维码扫描模块开启扫描函数
u8 QR_RX_Data(u8 rxDat[],char* check);  //二维码读取函数


#endif


