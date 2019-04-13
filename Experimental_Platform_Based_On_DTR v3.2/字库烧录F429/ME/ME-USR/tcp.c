#include "tcp.h"

u8 *number;
//usmart֧�ֲ���
//���յ������ݷ���������
///mode:0 ������USART2_RX_STA;
//       1 ����USART2_RX_STA��

void usr_tcp232_at_response(u8 mode)
{
	if(USART2_RX_STA&0X8000)		//���ܵ�һ��������
	{ 
		USART2_RX_BUF[USART2_RX_STA&0X7FFF]=0;//��ӽ�����
		printf("%s",USART2_RX_BUF);	//���͵�����
		if(mode)USART2_RX_STA=0;
	} 
}




//USR_TCP232���������,�����յ���Ӧ��
//str:�ڴ���Ӧ����
//����ֵ:0,û�еõ��ڴ���Ӧ����
//    ����,�ڴ�Ӧ������λ��(str��λ��)
u8 *usr_tcp232_check_cmd(u8 *str)
{
	
	char *strx=0;
	if(USART2_RX_STA&0X8000)		//���յ�һ��������
	{ 
		USART2_RX_BUF[USART2_RX_STA&0X7FFF]=0;//��ӽ�����
		strx=strstr((const char*)USART2_RX_BUF,(const char*)str);
	} 
	return (u8*)strx;
}



//��usr_tcp232��������
//cmd:���͵������ַ���(����Ҫ��ӻس���)
//ack:�ڴ���Ӧ����,���Ϊ��,���ʾ����Ҫ�ȴ�Ӧ��
//waittime:�ȴ�ʱ��(��λ:10ms)
//����ֵ:0,���ͳɹ�(�õ����ڴ���Ӧ����)
//       1,����ʧ��
u8 usr_tcp232_send_cmd1(u8 *cmd,u8 *ack,u16 waittime)
{
	u8 res=0; 
	USART2_RX_STA=0;
	u2_printf("%s\r",cmd);	//��������
	if(ack&&waittime)		//��Ҫ�ȴ�Ӧ��
	{
		while(--waittime)	//�ȴ�����ʱ
		{
			DELAY_MS(10);
			if(USART2_RX_STA&0X8000)//���յ��ڴ���Ӧ����
			{
				if(usr_tcp232_check_cmd(ack))break;//�õ���Ч���� 
				USART2_RX_STA=0;
			} 
		}
		if(waittime==0)res=1; 
	}
	return res;
} 



////��õ�һ�η��ͻص�ʵ����
////�������ȴ�ʱ��͵�һ�η��͵�����
////waittime :�ȴ�ʱ��
//u8 usr_tcp232_getnumber(u8 *a,u16 waittime)
//{
//	 u8  number[6];
//	 u8  act[7];
//	 u8 res;
//	 u8 i=0,j=0;
//	u2_printf("%s\r",a);
//	while(--waittime)	//�ȴ�����ʱ
//		{
//			DELAY_MS(10);
//			if(USART2_RX_STA&0X8000)//���յ��ڴ���Ӧ����
//			{
//				res=USART_ReceiveData(USART2);	
//				for(i=0;i<5;i++)
//				{
//					act[i]=USART2_RX_BUF[j];
//					j++;
//					if(usr_tsp232_check_data(act,"0001|1"))
//					{
//						for(i=0,j=j+1;i<5;i++)
//						{  
//							 number[i]=USART2_RX_BUF[j];
//							j++;
//						 }
//					}
//			  } 

//		}
//		if(waittime==0)res=1; 
//	return res;

//}

//}


//�õ�ʵ����
u8 usr_tcp232_getdata(u8 *p)
{
//	u8 i=0;
	u8 res=0;
	//u8 *number;
	do{
		p++;
	}
		while(*p=='|');
	p++;
	if(*p)
	{
		for(;*p!=';';p++)
		{
			number=p;
			number++;
		}
	*number='\0';
		return  res;
	}
	//else
	return 1;
	
}




//usr_tcp232�������������֤����
//���� ѧ��ID ʱ�� ����
//����ֵ���ɹ���0��ʧ�ܻ�1������Ŀǰ��û�н��к���
//��������
u8 usr_tcp232_send_Verdata(u8* id,u8 *table)
	{
	u8 a[200];
	sprintf((char*)a,"0001|%s;%s;",id,table);
    u2_printf("%s\r",a);
	DELAY_MS(10);
	if(usr_tcp232_getdata(USART2_RX_BUF))
	{return 1;
	}
	usr_tcp232_at_response(0);
  return 0;	
  }
	
//����������ͳɼ�
//ʵ������� ѧ��ID��ʱ�� ʵ���� ���� �ɼ�
	//Ŀǰ��ʵ������ǿ���趨�ģ��������ͨ��������������
u8 usr_tcp232_send_Gradedata(u8* id,u8* table,u8* grade)
  {
	u8 a[200];
	u8 res=0;
	//u8* number;
	//number="ME001";
	sprintf((char*)a,"0002|%s;%s;ME0001;%s;",id,table,grade);
	DELAY_MS(10);
	if(usr_tcp232_send_cmd1(a,"0002|1;",200))
	{
		   res=1;
	}
	usr_tcp232_at_response(0);
   return res;	
  }

	
	//�����������txt�ļ�
	//���� ID�� �ļ��� �ļ�����
	//Ŀǰֻ�ܷ����ļ���������Ҫ�ӹ�
u8 usr_tcp232_send_file(u8* id,u8* filename,u8* content)
  {
	u8 res=0;
	u8 a[200];
	sprintf((char*)a,"0003|%s;%s;%s;",id,filename,content);
	DELAY_MS(10);
	if(usr_tcp232_send_cmd1(a,"0003|1;",200))
	{
		res=1;
	}
	usr_tcp232_at_response(0);	
	return res;
  }




















