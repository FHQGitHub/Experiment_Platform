#include "bsp.h"

void enable(void);
void disable(void);

lowPower_rcc_typdef lp_rcc_setting = {
	enable,
	disable
};



void enable()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);
}

void disable()
{
	RCC_AHB1PeriphClockLPModeCmd(RCC_AHB1Periph_GPIOA,DISABLE);
	RCC_AHB1PeriphClockLPModeCmd(RCC_AHB1Periph_GPIOC,DISABLE);
	RCC_AHB1PeriphClockLPModeCmd(RCC_AHB1Periph_GPIOD,DISABLE);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,DISABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,DISABLE);
}







