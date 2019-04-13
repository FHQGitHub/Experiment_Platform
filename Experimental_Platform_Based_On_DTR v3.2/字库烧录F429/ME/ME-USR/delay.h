#ifndef __DELAY_H
#define __DELAY_H 			   
#include "stm32f4xx.h"	  

void DELAY_Init(u8 SYSCLK);
void DELAY_Tiny(u8 delayTime);
void DELAY_US(u32 delayTime);
void delay_xms(u16 nms);
void DELAY_MS(u16 delayTime);
#endif





























