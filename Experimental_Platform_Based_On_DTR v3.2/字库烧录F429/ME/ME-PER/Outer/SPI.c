
#include "uart.h"
#include "spi.h"
#include "delay.h"
/****************
MISO:PC11 ����
MOSI:PC12 ���
SCLK:PC10 ���
SS:	 PA15 ���
*****************/
void Spi_IO_Init()
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD, ENABLE);	 //ʹ��PA�˿�ʱ��
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_12;//PC10 �������,���Ƹ�λ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ�� SCLK | MOSI
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_15;//PA15 �������,���Ƹ�λ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ�� SS
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3;//PD3 �������,���Ƹ�λ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Low_Speed;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_SetBits(GPIOD, GPIO_Pin_3);
			 
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//	PC11 ����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ�� MISO	
	
} 

 
 
 
void SPI3_Init(void)
{	 
  GPIO_InitTypeDef  GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD, ENABLE);//ʹ��GPIO A C Dʱ��

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);//ʹ��SPI3ʱ��
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_15;//PA15 �������,���Ƹ�λ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//����
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ�� SS
	GPIO_ResetBits(GPIOA, GPIO_Pin_15);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3;//PD3 �������,���Ƹ�λ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Low_Speed;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_SetBits(GPIOD, GPIO_Pin_3);
 
  //GPIOC 10 11 12��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;//PC10~12���ù������	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_SPI3); //PB3����Ϊ SPI1
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_SPI3); //PB4����Ϊ SPI1
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_SPI3); //PB5����Ϊ SPI1
 
	//����ֻ���SPI�ڳ�ʼ��
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3,ENABLE);//��λSPI1
	
	SPI_Cmd(SPI3, DISABLE);
	//GPIO_SetBits(GPIOC,GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12);  //PC10/11/12����

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//����ͬ��ʱ�ӵĿ���״̬Ϊ�͵�ƽ
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//����ͬ��ʱ�ӵĵ�һ�������أ��������½������ݱ�����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
	SPI_Init(SPI3, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
 
	SPI_Cmd(SPI3, ENABLE); //ʹ��SPI����
	//SPI3_ReadWriteByte(0xff);//��������		 
}   
//SPI1�ٶ����ú���
//SPI�ٶ�=fAPB2/��Ƶϵ��
//@ref SPI_BaudRate_Prescaler:SPI_BaudRatePrescaler_2~SPI_BaudRatePrescaler_256  
//fAPB2ʱ��һ��Ϊ84Mhz��
void SPI3_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//�ж���Ч��
	SPI3->CR1&=0XFFC7;//λ3-5���㣬�������ò�����
	SPI3->CR1|=SPI_BaudRatePrescaler;	//����SPI3�ٶ� 
	SPI_Cmd(SPI3,ENABLE); //ʹ��SPI1
} 
//SPI1 ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 SPI3_ReadWriteByte(u8 TxData)
{		 			 
 
  while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET);//�ȴ���������  
	
	SPI_I2S_SendData(SPI3, TxData); //ͨ������SPIx����һ��byte  ����
		
  while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET); //�ȴ�������һ��byte  
 
	return SPI_I2S_ReceiveData(SPI3); //����ͨ��SPIx������յ�����	
 		    
}

u8 SPIWriteByte(u8 Byte)
{
	while((SPI3->SR&0X02)==0);		//�ȴ���������	  
	SPI3->DR=Byte;	 	            //����һ��byte   
	while((SPI3->SR&0X01)==0);      //�ȴ�������һ��byte  
	return SPI3->DR;          	    //�����յ�������			
}



