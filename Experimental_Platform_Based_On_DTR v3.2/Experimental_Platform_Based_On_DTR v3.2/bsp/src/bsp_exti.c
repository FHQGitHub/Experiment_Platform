#include "ep_app.h"

//外部中断11,12服务程序
void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line12) == SET)
	{
		if(0 == Nlink)
			bit_wifi_status = WIFI_OK;
		else
			bit_wifi_status = WIFI_ERR;
		wifiStateChangeFlag = flag_set;
		EXTI_ClearITPendingBit(EXTI_Line12);//清除LINE12上的中断标志位 
	}
}

	   
//外部中断初始化程序
//初始化nReady,bit_wifi_status外部中断
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource11); //nReady 连接到中断线2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource12); //bit_wifi_status  连接到中断线3

	/* 配置EXTI_Line2,3,4 */
//	EXTI_InitStructure.EXTI_Line = EXTI_Line11 | EXTI_Line12;
	EXTI_InitStructure.EXTI_Line = EXTI_Line12;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
	EXTI_Init(&EXTI_InitStructure);//配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//外部中断10-15
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);//配置
}












