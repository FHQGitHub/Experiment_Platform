#ifndef _RELAY_H
#define _RELAY_H
#include "stm32f4xx.h" 


#define RELAY_ON() GPIO_ResetBits(GPIOD,GPIO_Pin_3); //PA3 高电平 继电器开
#define RELAY_OFF() GPIO_SetBits(GPIOD,GPIO_Pin_3); //PA3 低电平 继电器关

#define RELAY1_ON() GPIO_ResetBits(GPIOD,GPIO_Pin_6); //PA6 高电平 继电器开
#define RELAY1_OFF() GPIO_SetBits(GPIOD,GPIO_Pin_6); //PA6 低电平 继电器关

void relay_init(void);


#endif


