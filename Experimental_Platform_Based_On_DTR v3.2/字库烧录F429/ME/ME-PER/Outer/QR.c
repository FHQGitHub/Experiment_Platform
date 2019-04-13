#include "QR.h"	

u8 QR_On_key[9]={0x7E,0x00,0x08,0x01,0x00,0x02,0x01,0xAB,0xCD};  //����ɨ��ָ��
u8 QR_On_res[7]={0x02,0x00,0x00,0x01,0x00,0x33,0x31};            //ģ�鷵����Ϣ

//��ά��ɨ��ģ�鿪��ɨ�躯��
//����ֵ��0,�����ɹ�;1,�������ݴ���;2,���ճ�ʱ
u8 QR_On(void)
{
	u8 j=0;
	u8 res=0;
	u8 waittime=30;
	u8 strx=0;
	UART4_RX_STA=0;
	for(j=0;j<9;j++)//ѭ����������
	{
		 while(USART_GetFlagStatus(UART4,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������
		USART_SendData(UART4,QR_On_key[j]);  
	}
	while(--waittime)
	{
		delay_xms(10);
		if(UART4_RX_STA&0x8000)   //�ȴ�ɨ��ģ�鷵����Ϣ
		{
			strx=memcmp(UART4_RX_BUF,QR_On_res,7);
			if(strx!=0)          
			{
				res=1;        //����ʧ��
				printf("����ʧ��\r\n");
			}
			else
			{
				printf("�����ɹ�\r\n");
			}
			UART4_RX_STA=0;
			break;
		}
	}
	if(waittime==0)
	{
		res=2;           //���ճ�ʱ
	}		
	return res;          
}


//��ά���ȡ����
//rxDat:�������飻check:�����Ӧ
//����ֵ��1����Ӧƥ�䣻0����Ӧ��ƥ����ȡʧ��
u8 QR_RX_Data(u8 rxDat[],char* check)
{
	u8 res=0;
	char *strx=0;
	UART4_RX_STA=0;
	while(!(UART4_RX_STA&0x8000));   //�ȴ�ɨ��ģ�鷵����Ϣ
	if(UART4_RX_STA&0x8000)   
	{
		UART4_RX_BUF[UART4_RX_STA&0X3FFF]=0;//��ӽ�����
		strx=strstr((const char*)UART4_RX_BUF,"FAIL");
		if(strx)
		{
			UART4_RX_STA=0;           //��ȡʧ��          
		}
		else                          //��ȡ�ɹ�
		{
			UART4_RX_STA=0; 
			strx=strstr((const char*)UART4_RX_BUF,check);
			if(strx)
			{
				strcpy((char*)rxDat,strx+4);           //��ӦΪsid:��tid: ���ȡ��󲿷�����
				printf("%s\r\n",UART4_RX_BUF);
				res=1;
			}
		}
	}
	return res;
}

