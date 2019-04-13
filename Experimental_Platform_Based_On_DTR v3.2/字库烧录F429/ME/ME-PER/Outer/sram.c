#include "sram.h"



//ʹ��NOR/SRAM�� Bank1.sector3,��ַλHADDR[27,26]=10 
//��IS61LV25616/IS62WV25616,��ַ�߷�ΧΪA0~A17 
//��IS61LV51216/IS62WV51216,��ַ�߷�ΧΪA0~A18

#define Bank1_SRAM3_ADDR		(u32)(0x68000000)

//��ʼ���ⲿSRAM
void FMC_SRAM_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	FMC_NORSRAMInitTypeDef FMC_NORSRAMInitStructure;
	FMC_NORSRAMTimingInitTypeDef FMC_ReadWriteTimingStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOG,ENABLE); //ʹ��PD,PE,PF,PGʱ��
	
	GPIO_InitStructure.GPIO_Pin =( GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10 \
																|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //PD0,1,4,5,8,9,10,11,12,13,14,15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //100Mʱ��
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //����ģʽ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11 \
																|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //PE0,1,7,8,9,10,11,12,13,14,15
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_12 \
																|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); //PF0,1,2,3,4,5,12,13,14,15
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_10 ; //PG0,1,2,3,4,5,10
	GPIO_Init(GPIOG,&GPIO_InitStructure);
	
	//GPIOD��������
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource0,GPIO_AF_FMC);  //PD0
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource1,GPIO_AF_FMC);  //PD1
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource4,GPIO_AF_FMC);  //PD4
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_FMC);  //PD5
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_FMC);  //PD8
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_FMC);  //PD9
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource10,GPIO_AF_FMC); //PD10
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource11,GPIO_AF_FMC); //PD11
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_FMC); //PD12
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_FMC); //PD13
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_FMC); //PD14
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_FMC); //PD15
	
	//GPIOE��������
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource0,GPIO_AF_FMC);  //PE0
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource1,GPIO_AF_FMC);  //PE1
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource7,GPIO_AF_FMC);  //PE7
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_FMC);  //PE8
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_FMC);  //PE9
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF_FMC); //PE10
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_FMC); //PE11
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_FMC); //PE12
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_FMC); //PE13
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_FMC); //PE14
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource15,GPIO_AF_FMC); //PE15
	
	//GPIOF��������
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource0,GPIO_AF_FMC);  //PF0
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource1,GPIO_AF_FMC);  //PF1
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource2,GPIO_AF_FMC);  //PF2
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource3,GPIO_AF_FMC);  //PF3
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource4,GPIO_AF_FMC);  //PF4
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource5,GPIO_AF_FMC);  //PF5
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource12,GPIO_AF_FMC); //PF12
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource13,GPIO_AF_FMC); //PF13
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource14,GPIO_AF_FMC); //PF14
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource15,GPIO_AF_FMC); //PF15
	
	//GPIOG��������
	GPIO_PinAFConfig(GPIOG,GPIO_PinSource0,GPIO_AF_FMC);  //PG0
	GPIO_PinAFConfig(GPIOG,GPIO_PinSource1,GPIO_AF_FMC);  //PG1
	GPIO_PinAFConfig(GPIOG,GPIO_PinSource2,GPIO_AF_FMC);  //PG2
	GPIO_PinAFConfig(GPIOG,GPIO_PinSource3,GPIO_AF_FMC);  //PG3
	GPIO_PinAFConfig(GPIOG,GPIO_PinSource4,GPIO_AF_FMC);  //PG4
	GPIO_PinAFConfig(GPIOG,GPIO_PinSource5,GPIO_AF_FMC);  //PG5
	GPIO_PinAFConfig(GPIOG,GPIO_PinSource10,GPIO_AF_FMC); //PG10
	
	FMC_ReadWriteTimingStructure.FMC_AddressSetupTime = 0X00; //��ַ����ʱ��0��HCLK 0ns
	FMC_ReadWriteTimingStructure.FMC_AddressHoldTime = 0x00;  //��ַ����ʱ��,ģʽAδ�õ�
	FMC_ReadWriteTimingStructure.FMC_DataSetupTime = 0x09;    //���ݱ���ʱ��,9��HCLK��6*9=54ns
	FMC_ReadWriteTimingStructure.FMC_BusTurnAroundDuration = 0x00;
	FMC_ReadWriteTimingStructure.FMC_CLKDivision = 0x00;
	FMC_ReadWriteTimingStructure.FMC_DataLatency = 0x00;
	FMC_ReadWriteTimingStructure.FMC_AccessMode = FMC_AccessMode_A; //ģʽA
	
	FMC_NORSRAMInitStructure.FMC_Bank = FMC_Bank1_NORSRAM3;  //NOR/SRAM��Bank3
	FMC_NORSRAMInitStructure.FMC_DataAddressMux = FMC_DataAddressMux_Disable; //���ݺ͵�ַ�߲�����
	FMC_NORSRAMInitStructure.FMC_MemoryType = FMC_MemoryType_SRAM; //SRAM�洢ģʽ
	FMC_NORSRAMInitStructure.FMC_MemoryDataWidth = FMC_NORSRAM_MemoryDataWidth_16b; //16λ���ݿ��
	FMC_NORSRAMInitStructure.FMC_BurstAccessMode = FMC_BurstAccessMode_Disable; //FLASHʹ�õ�,SRAMδʹ��
	FMC_NORSRAMInitStructure.FMC_AsynchronousWait = FMC_AsynchronousWait_Disable; //�Ƿ�ʹ��ͬ������ģʽ�µĵȴ��ź�,�˴�δ�õ�
	FMC_NORSRAMInitStructure.FMC_WaitSignalPolarity = FMC_WaitSignalPolarity_Low; //�ȴ��źŵļ���,����ͻ��ģʽ����������
	FMC_NORSRAMInitStructure.FMC_WrapMode = FMC_WrapMode_Disable;  //�Ƿ�ʹ�ܻ�·ͻ��ģʽ,�˴�δ�õ�
	FMC_NORSRAMInitStructure.FMC_WaitSignalActive = FMC_WaitSignalActive_BeforeWaitState; //�洢�����ڵȴ�����֮ǰ��һ��ʱ�����ڻ��ǵȴ������ڼ�ʹ��NWAIT
	FMC_NORSRAMInitStructure.FMC_WriteOperation = FMC_WriteOperation_Enable; //�洢��дʹ��
	FMC_NORSRAMInitStructure.FMC_WaitSignal = FMC_WaitSignal_Disable;   //�ȴ�ʹ��λ,�˴�δ�õ�
	FMC_NORSRAMInitStructure.FMC_ExtendedMode = FMC_ExtendedMode_Disable; //��дʹ����ͬ��ʱ��
	FMC_NORSRAMInitStructure.FMC_WriteBurst = FMC_WriteBurst_Disable;  //�첽�����ڼ�ĵȴ��ź�
	FMC_NORSRAMInitStructure.FMC_ReadWriteTimingStruct = &FMC_ReadWriteTimingStructure;
	FMC_NORSRAMInitStructure.FMC_WriteTimingStruct = &FMC_ReadWriteTimingStructure;
	FMC_NORSRAMInit(&FMC_NORSRAMInitStructure);  //FMC_SRAM��ʼ��
	
	FMC_NORSRAMCmd(FMC_Bank1_NORSRAM3,ENABLE);  //ʹ��NOR/SRAM����
}

//��ָ����ַ(WriteAddr+Bank1_SRAM3_ADDR)��ʼ,����д��n���ֽ�.
//pBuffer:�ֽ�ָ��
//WriteAddr:Ҫд��ĵ�ַ
//n:Ҫд����ֽ���
void FMC_SRAM_WriteBuffer(u8 *pBuffer,u32 WriteAddr,u32 n)
{
	for(;n!=0;n--)
	{
		*(vu8*)(Bank1_SRAM3_ADDR + WriteAddr) = *pBuffer; 
		WriteAddr++;
		pBuffer++;
	}
}

//��ָ����ַ((WriteAddr+Bank1_SRAM3_ADDR))��ʼ,��������n���ֽ�.
//pBuffer:�ֽ�ָ��
//ReadAddr:Ҫ��������ʼ��ַ
//n:Ҫд����ֽ���
void FMC_SRAM_ReadBuffer(u8 *pBuffer,u32 ReadAddr,u32 n)
{
	for(;n!=0;n--)
	{
		*pBuffer ++=*(vu8*)(Bank1_SRAM3_ADDR + ReadAddr);
		ReadAddr++;
	}
}

////////////////////////////////////////////////////////////////////////////////////////
//���Ժ���
//��ָ����ַд��1���ֽ�
//addr:��ַ
//data:Ҫд�������
void FMC_sram_test_write(u32 addr,u8 data)
{
	FMC_SRAM_WriteBuffer(&data,addr,1);//д��һ���ֽ�
}

//��ȡ1���ֽ�
//addr:Ҫ��ȡ�ĵ�ַ
//����ֵ:��ȡ��������
u8 FMC_sram_test_read(u32 addr)
{
	u8 data;
	FMC_SRAM_ReadBuffer(&data,addr,1);
	return data;
}

