#ifndef __SNSPI_H
#define __SNSPI_H

#include "stm32f4xx.h"

#define SPI_TYPE				uint8_t		

#define del_time				30

#define SPI_SCLK				PBout(13)
#define SPI_MOSI				PBout(15)
#define SPI_MISO				PBin(14)
#define SPI_SS					PBout(12)

void Spi_IO_Init(void);
void SPI3_Init(void);			 //��ʼ��SPI1��
void SPI3_SetSpeed(u8 SpeedSet); //����SPI1�ٶ�   
u8 SPI3_ReadWriteByte(u8 TxData);//SPI1���߶�дһ���ֽ�


#endif
