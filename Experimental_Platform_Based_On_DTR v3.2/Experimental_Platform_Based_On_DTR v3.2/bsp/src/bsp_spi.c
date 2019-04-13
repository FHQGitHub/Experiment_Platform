#include "bsp.h"
/****************
MISO:PB14 输入
MOSI:PB15 输出
SCLK:PB13 输出
SS:  PB12 输出
*****************/
void Spi_IO_Init()
{
        GPIO_InitTypeDef  GPIO_InitStructure;

        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOE, ENABLE);	 //使能PA端口时钟

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
        GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化 SS | SCLK | MOSI


        GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2;//PD3 推挽输出,控制复位
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
        GPIO_InitStructure.GPIO_Speed = GPIO_Low_Speed;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Init(GPIOE, &GPIO_InitStructure);
        GPIO_SetBits(GPIOE, GPIO_Pin_3);//初始化RST
                         
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//	PC11 输入
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输出模式
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
        GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化 MISO	
	
} 

 
 
 
void SPI3_Init(void)
{	 
        GPIO_InitTypeDef  GPIO_InitStructure;
        SPI_InitTypeDef  SPI_InitStructure;

        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD, ENABLE);//使能GPIO A C D时钟

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);//使能SPI3时钟

        GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_15;//PA15 推挽输出,控制复位
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//上拉
        GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化 SS
        GPIO_ResetBits(GPIOA, GPIO_Pin_15);

        GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3;//PD3 推挽输出,控制复位
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
        GPIO_InitStructure.GPIO_Speed = GPIO_Low_Speed;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
        GPIO_SetBits(GPIOD, GPIO_Pin_3);

        //GPIOC 10 11 12初始化设置
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;//PC10~12复用功能输出	
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
        GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化

        GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_SPI3); //PB3复用为 SPI1
        GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_SPI3); //PB4复用为 SPI1
        GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_SPI3); //PB5复用为 SPI1

        //这里只针对SPI口初始化
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3,ENABLE);//复位SPI1

        SPI_Cmd(SPI3, DISABLE);
        //GPIO_SetBits(GPIOC,GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12);  //PC10/11/12上拉

        SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
        SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
        SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
        SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//串行同步时钟的空闲状态为低电平
        SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//串行同步时钟的第一个跳变沿（上升或下降）数据被采样
        SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
        SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//定义波特率预分频的值:波特率预分频值为256
        SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
        SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
        SPI_Init(SPI3, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器

        SPI_Cmd(SPI3, ENABLE); //使能SPI外设
	//SPI3_ReadWriteByte(0xff);//启动传输		 
}   
//SPI1速度设置函数
//SPI速度=fAPB2/分频系数
//@ref SPI_BaudRate_Prescaler:SPI_BaudRatePrescaler_2~SPI_BaudRatePrescaler_256  
//fAPB2时钟一般为84Mhz：
void SPI3_SetSpeed(u8 SPI_BaudRatePrescaler)
{
        assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//判断有效性
        SPI3->CR1&=0XFFC7;//位3-5清零，用来设置波特率
        SPI3->CR1|=SPI_BaudRatePrescaler;	//设置SPI3速度 
        SPI_Cmd(SPI3,ENABLE); //使能SPI1
} 
//SPI1 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
u8 SPI3_ReadWriteByte(u8 TxData)
{		 			 
 
        while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET);//等待发送区空  

        SPI_I2S_SendData(SPI3, TxData); //通过外设SPIx发送一个byte  数据
                
        while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET); //等待接收完一个byte  

        return SPI_I2S_ReceiveData(SPI3); //返回通过SPIx最近接收的数据	
 		    
}

u8 SPIWriteByte(u8 Byte)
{
        while((SPI3->SR&0X02)==0);		//等待发送区空	  
        SPI3->DR=Byte;	 	            //发送一个byte   
        while((SPI3->SR&0X01)==0);      //等待接收完一个byte  
        return SPI3->DR;          	    //返回收到的数据			
}



