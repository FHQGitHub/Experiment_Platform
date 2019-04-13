#include "QR.h"	

u8 QR_On_key[9]={0x7E,0x00,0x08,0x01,0x00,0x02,0x01,0xAB,0xCD};  //开启扫描指令
u8 QR_On_res[7]={0x02,0x00,0x00,0x01,0x00,0x33,0x31};            //模块返回信息

//二维码扫描模块开启扫描函数
//返回值：0,开启成功;1,接收数据错误;2,接收超时
u8 QR_On(void)
{
	u8 j=0;
	u8 res=0;
	u8 waittime=30;
	u8 strx=0;
	UART4_RX_STA=0;
	for(j=0;j<9;j++)//循环发送数据
	{
		 while(USART_GetFlagStatus(UART4,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕
		USART_SendData(UART4,QR_On_key[j]);  
	}
	while(--waittime)
	{
		delay_xms(10);
		if(UART4_RX_STA&0x8000)   //等待扫描模块返回信息
		{
			strx=memcmp(UART4_RX_BUF,QR_On_res,7);
			if(strx!=0)          
			{
				res=1;        //开启失败
				printf("开启失败\r\n");
			}
			else
			{
				printf("开启成功\r\n");
			}
			UART4_RX_STA=0;
			break;
		}
	}
	if(waittime==0)
	{
		res=2;           //接收超时
	}		
	return res;          
}


//二维码读取函数
//rxDat:接收数组；check:检查响应
//返回值：1，响应匹配；0，响应不匹配或读取失败
u8 QR_RX_Data(u8 rxDat[],char* check)
{
	u8 res=0;
	char *strx=0;
	UART4_RX_STA=0;
	while(!(UART4_RX_STA&0x8000));   //等待扫描模块返回信息
	if(UART4_RX_STA&0x8000)   
	{
		UART4_RX_BUF[UART4_RX_STA&0X3FFF]=0;//添加结束符
		strx=strstr((const char*)UART4_RX_BUF,"FAIL");
		if(strx)
		{
			UART4_RX_STA=0;           //读取失败          
		}
		else                          //读取成功
		{
			UART4_RX_STA=0; 
			strx=strstr((const char*)UART4_RX_BUF,check);
			if(strx)
			{
				strcpy((char*)rxDat,strx+4);           //响应为sid:或tid: 则截取其后部分数据
				printf("%s\r\n",UART4_RX_BUF);
				res=1;
			}
		}
	}
	return res;
}

