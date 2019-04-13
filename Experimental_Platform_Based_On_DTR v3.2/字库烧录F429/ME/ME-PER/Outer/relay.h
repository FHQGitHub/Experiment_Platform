#ifndef _RELAY_H
#define _RELAY_H
#include "stm32f4xx.h" 


#define RELAY_ON() GPIO_ResetBits(GPIOD,GPIO_Pin_3); //PA3 �ߵ�ƽ �̵�����
#define RELAY_OFF() GPIO_SetBits(GPIOD,GPIO_Pin_3); //PA3 �͵�ƽ �̵�����

#define RELAY1_ON() GPIO_ResetBits(GPIOD,GPIO_Pin_6); //PA6 �ߵ�ƽ �̵�����
#define RELAY1_OFF() GPIO_SetBits(GPIOD,GPIO_Pin_6); //PA6 �͵�ƽ �̵�����

void relay_init(void);


#endif


