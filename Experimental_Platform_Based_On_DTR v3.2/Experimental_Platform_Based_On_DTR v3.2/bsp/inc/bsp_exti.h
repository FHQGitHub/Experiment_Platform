#ifndef __EXTI_H
#define __EXIT_H	 

#include "stm32f4xx.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//�ⲿ�ж� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/4
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

#define Nready 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11) //PA11
#define Nlink		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12) //PA12

void EXTIX_Init(void);	//�ⲿ�жϳ�ʼ��		 					    
#endif

























