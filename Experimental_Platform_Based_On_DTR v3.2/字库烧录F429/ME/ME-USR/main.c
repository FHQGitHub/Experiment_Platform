#include "redirprintf.h"	
#include "bsp_spi_flash.h"
#include "delay.h"
#include "timer.h"

unsigned char font_buf[100];

u8 HAL_InitAll(void)
{				

	SPI_FLASH_Init();

	UART1_Init(115200);
	
	TIM3_Int_Init(999,83); 	//1KHZ 定时器3设置为1ms
	TIM7_Int_Init(100-1,8400-1);		//100ms中断      
	return 0;
}

int main(void)
{
	DELAY_Init(168);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	//中断分组配置
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC,ENABLE);//开启CRC时钟
	
	HAL_InitAll();
	
	SPI_FLASH_Erase_Chip();
	SPI_FLASH_BufferRead(font_buf, 0, sizeof(font_buf));
	
	while(1)
	{
		//MainTask();
	}
}

