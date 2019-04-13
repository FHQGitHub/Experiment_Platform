#include "delay.h"
#include "UART.h"
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"	  
#include "timer.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F4������
//����3��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/8/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//���ڷ��ͻ����� 	
__align(8) u8 UART5_TX_BUF[UART5_MAX_SEND_LEN]; //���ͻ���,���UART53_MAX_SEND_LEN�ֽ�
#ifdef UART5_RX_EN   								//���ʹ���˽���   	  
//���ڽ��ջ����� 	
u8 UART5_RX_BUF[UART5_MAX_RECV_LEN]; 				//���ջ���,���UART53_MAX_RECV_LEN���ֽ�.


//ͨ���жϽ�������2���ַ�֮���ʱ������100ms�������ǲ���һ������������.
//���2���ַ����ռ������100ms,����Ϊ����1����������.Ҳ���ǳ���100msû�н��յ�
//�κ�����,���ʾ�˴ν������.
//���յ�������״̬
//[15]:0,û�н��յ�����;1,���յ���һ������.
//[14]:0,�Ǵ˴��ڷ���ʱ��;1,�˴��ڷ���ʱ��.
//[13:0]:���յ������ݳ���
vu16 UART5_RX_STA=0; 
void UART5_IRQHandler(void)
{
	u8 res;	    
	static vu16 times=0;
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)//���յ�����
	{	 
		res =USART_ReceiveData(UART5);		
		if((UART5_RX_STA&(1<<15))==0)//�������һ������,��û�б�����,���ٽ�����������
		{ 
			if(times<UART5_MAX_RECV_LEN)		//�����Խ�������
			{
				TIM_SetCounter(TIM7,0);//��������� ���¼�ʱ ȷ��ÿ�����ַ����ʱ���Ƿ����100ms			 
				if(UART5_RX_STA==0)	//���յ���һ�����ݿ�ʼ��ʱ
				{
					UART5_RX_STA|=1<<14; //��Ƿ�����
					times=0;
					TIM_Cmd(TIM7, ENABLE);  //ʹ�ܶ�ʱ��7 
				}
				UART5_RX_BUF[times++]=res;		//��¼���յ���ֵ
				UART5_RX_STA++;			
			}
			else 
			{
				UART5_RX_STA|=1<<15;					//ǿ�Ʊ�ǽ������
			} 
		}  	
	}										 
}  
#endif	
//��ʼ��IO ����3
//bound:������	  
void UART5_init(u32 bound)
{  
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //ʹ��GPIOBʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); //ʹ��GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);//ʹ��UART53ʱ��

 	USART_DeInit(UART5);  //��λ����3
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5); //GPIOB11����ΪUART53
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource2,GPIO_AF_UART5); //GPIOB10����ΪUART53	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //GPIOB11��GPIOB10��ʼ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOC,&GPIO_InitStructure); //��ʼ��GPIOB11����GPIOB10
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //GPIOB11��GPIOB10��ʼ��
	GPIO_Init(GPIOD,&GPIO_InitStructure); //��ʼ��GPIOB11����GPIOB10
	
	USART_InitStructure.USART_BaudRate = bound;//������ 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  
	USART_Init(UART5, &USART_InitStructure); //��ʼ������3
 
	USART_Cmd(UART5, ENABLE);               //ʹ�ܴ��� 
	
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//�����ж�   
	
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���                          
	UART5_RX_STA=0;		//����
}

//����3,printf ����
//ȷ��һ�η������ݲ�����UART53_MAX_SEND_LEN�ֽ�
void u5_printf(char* fmt,...)  
{  
	u16 i,j;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)UART5_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)UART5_TX_BUF);//�˴η������ݵĳ���
	for(j=0;j<i;j++)//ѭ����������
	{
		 while(USART_GetFlagStatus(UART5,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
		USART_SendData(UART5,UART5_TX_BUF[j]);  
	}
}
 

//���ڷ��ͻ����� 	
__align(8) u8 UART4_TX_BUF[UART4_MAX_SEND_LEN]; 	//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�
#ifdef UART4_RX_EN   								//���ʹ���˽���   	  
//���ڽ��ջ����� 	
u8 UART4_RX_BUF[UART4_MAX_RECV_LEN]; 				//���ջ���,���USART3_MAX_RECV_LEN���ֽ�.


//ͨ���жϽ�������2���ַ�֮���ʱ������100ms�������ǲ���һ������������.
//���2���ַ����ռ������100ms,����Ϊ����1����������.Ҳ���ǳ���100msû�н��յ�
//�κ�����,���ʾ�˴ν������.
//���յ�������״̬
//[15]:0,û�н��յ�����;1,���յ���һ������.
//[14:0]:���յ������ݳ���
vu16 UART4_RX_STA=0;   	
void UART4_IRQHandler(void)
{
	u8 res;	    
	static vu16 times=0;
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)//���յ�����
	{	 
		res =USART_ReceiveData(UART4);		
		if((UART4_RX_STA&(1<<15))==0)//�������һ������,��û�б�����,���ٽ�����������
		{ 
			if(times<UART4_MAX_RECV_LEN)		//�����Խ�������
			{
				TIM_SetCounter(TIM7,0);//��������� ���¼�ʱ ȷ��ÿ�����ַ����ʱ���Ƿ����100ms			 
				if(UART4_RX_STA==0)	//���յ���һ�����ݿ�ʼ��ʱ
				{
					UART4_RX_STA|=1<<14; //��Ƿ�����
					times=0;
					TIM_Cmd(TIM7, ENABLE);  //ʹ�ܶ�ʱ��7 
				}
				UART4_RX_BUF[times++]=res;		//��¼���յ���ֵ
				UART4_RX_STA++;			
			}
			else 
			{
				UART4_RX_STA|=1<<15;					//ǿ�Ʊ�ǽ������
			} 
		}  	
	}										 
}  

#endif	
//��ʼ��IO ����3
//bound:������	  
void UART4_init(u32 bound)
{  
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);//ʹ��USART3ʱ��

 	USART_DeInit(UART4);  //��λ����3
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_UART4); //GPIOB11����ΪUSART3
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_UART4); //GPIOB10����ΪUSART3	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; //GPIOB11��GPIOB10��ʼ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��GPIOB11����GPIOB10
	
	USART_InitStructure.USART_BaudRate = bound;//������ 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  
	USART_Init(UART4, &USART_InitStructure); //��ʼ������3
 
	USART_Cmd(UART4, ENABLE);               //ʹ�ܴ��� 
	
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//�����ж�   
	
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	UART4_RX_STA=0;		//����
}

//����3,printf ����
//ȷ��һ�η������ݲ�����USART3_MAX_SEND_LEN�ֽ�
void u4_printf(char* fmt,...)  
{  
	u16 i,j;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)UART4_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)UART4_TX_BUF);//�˴η������ݵĳ���
	for(j=0;j<i;j++)//ѭ����������
	{
		 while(USART_GetFlagStatus(UART4,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
		USART_SendData(UART4,UART4_TX_BUF[j]);  
	}
}

//���ڷ��ͻ����� 	
__align(8) u8 USART3_TX_BUF[USART3_MAX_SEND_LEN]; 	//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�
//���ڽ��ջ����� 	
u8 USART3_RX_BUF[USART3_MAX_RECV_LEN]; 				//���ջ���,���USART3_MAX_RECV_LEN���ֽ�.


//ͨ���жϽ�������2���ַ�֮���ʱ������10ms�������ǲ���һ������������.
//���2���ַ����ռ������10ms,����Ϊ����1����������.Ҳ���ǳ���10msû�н��յ�
//�κ�����,���ʾ�˴ν������.
//���յ�������״̬
//[15]:0,û�н��յ�����;1,���յ���һ������.
//[14:0]:���յ������ݳ���
vu16 USART3_RX_STA=0;   	 
void USART3_IRQHandler(void)
{
	u8 res;	    
	static vu16 times=0;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)//���յ�����
	{	 
		res =USART_ReceiveData(USART3);		
		if((USART3_RX_STA&(1<<15))==0)//�������һ������,��û�б�����,���ٽ�����������
		{ 
			if(times<USART3_MAX_RECV_LEN)		//�����Խ�������
			{
				TIM_SetCounter(TIM7,0);//��������� ���¼�ʱ ȷ��ÿ�����ַ����ʱ���Ƿ����100ms			 
				if(USART3_RX_STA==0)	//���յ���һ�����ݿ�ʼ��ʱ
				{
					USART3_RX_STA|=1<<14; //��Ƿ�����
					times=0;
					TIM_Cmd(TIM7, ENABLE);  //ʹ�ܶ�ʱ��7 
				}
				USART3_RX_BUF[times++]=res;		//��¼���յ���ֵ
				USART3_RX_STA++;			
			}
			else 
			{
				USART3_RX_STA|=1<<15;					//ǿ�Ʊ�ǽ������
			} 
		}  	
	}										 
}  
//��ʼ��IO ����3
//pclk1:PCLK1ʱ��Ƶ��(Mhz)
//bound:������ 
void USART3_init(u32 bound)
{  	
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
 
	USART_DeInit(USART3);  //��λ����3
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //ʹ��GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//ʹ��USART3ʱ��
	
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_10; //GPIOB11��GPIOB10��ʼ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOB,&GPIO_InitStructure); //��ʼ��GPIOB11����GPIOB10
	
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB11����ΪUSART3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOB10����ΪUSART3	  
	
	USART_InitStructure.USART_BaudRate = bound;//������һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART3, &USART_InitStructure); //��ʼ������3
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�  
		
	USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ��� 

	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	USART3_RX_STA=0;				//���� 
}

//����3,printf ����
//ȷ��һ�η������ݲ�����USART3_MAX_SEND_LEN�ֽ�
void u3_printf(char* fmt,...)  
{  
	u16 i,j;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART3_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART3_TX_BUF);//�˴η������ݵĳ���
	for(j=0;j<i;j++)//ѭ����������
	{
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);//ѭ������,ֱ���������   
		USART_SendData(USART3,(uint8_t)USART3_TX_BUF[j]);   
	}
}










