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
void SPI3_Init(void);			 //��ʼ��SPI1��
void SPI3_SetSpeed(u8 SpeedSet); //����SPI1�ٶ�   
u8 SPI3_ReadWriteByte(u8 TxData);//SPI1���߶�дһ���ֽ�


#endif
