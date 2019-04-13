#ifndef __TIMER_H
#define __TIMER_H

#include "stm32f4xx.h"

void TIM7_Int_Init(u16 arr,u16 psc); 

//void TIM3_DelayTicks(uint32_t ticks);
//void TIM3_InstallCallback(void (*callbackFunc)(void));
void TIM7_IRQHandler(void);
void TIM3_Int_Init(u16 arr,u16 psc);
void TIM4_Int_Init(u16 arr,u16 psc);

#endif
