#ifndef __SNSPI_H
#define __SNSPI_H

#include "stm32f4xx.h"

#define SPI_TYPE				uint8_t		

#define del_time				30

#define SPI_SCLK				PCout(10)
#define SPI_MOSI				PCout(12)
#define SPI_MISO				PCin(11)
#define SPI_SS					PAout(15)

void Spi_IO_Init(void);
void SPI3_Init(void);			 //初始化SPI1口
void SPI3_SetSpeed(u8 SpeedSet); //设置SPI1速度   
u8 SPI3_ReadWriteByte(u8 TxData);//SPI1总线读写一个字节


#endif
