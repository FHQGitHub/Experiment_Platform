#include "tcp.h"

u8 *number;
//usmart支持部分
//将收到的数据返还给串口
///mode:0 不清零USART2_RX_STA;
//       1 清零USART2_RX_STA；

void usr_tcp232_at_response(u8 mode)
{
	if(USART2_RX_STA&0X8000)		//接受到一次数据了
	{ 
		USART2_RX_BUF[USART2_RX_STA&0X7FFF]=0;//添加结束符
		printf("%s",USART2_RX_BUF);	//发送到串口
		if(mode)USART2_RX_STA=0;
	} 
}




//USR_TCP232发送命令后,检测接收到的应答
//str:期待的应答结果
//返回值:0,没有得到期待的应答结果
//    其他,期待应答结果的位置(str的位置)
u8 *usr_tcp232_check_cmd(u8 *str)
{
	
	char *strx=0;
	if(USART2_RX_STA&0X8000)		//接收到一次数据了
	{ 
		USART2_RX_BUF[USART2_RX_STA&0X7FFF]=0;//添加结束符
		strx=strstr((const char*)USART2_RX_BUF,(const char*)str);
	} 
	return (u8*)strx;
}



//向usr_tcp232发送命令
//cmd:发送的命令字符串(不需要添加回车了)
//ack:期待的应答结果,如果为空,则表示不需要等待应答
//waittime:等待时间(单位:10ms)
//返回值:0,发送成功(得到了期待的应答结果)
//       1,发送失败
u8 usr_tcp232_send_cmd1(u8 *cmd,u8 *ack,u16 waittime)
{
	u8 res=0; 
	USART2_RX_STA=0;
	u2_printf("%s\r",cmd);	//发送命令
	if(ack&&waittime)		//需要等待应答
	{
		while(--waittime)	//等待倒计时
		{
			DELAY_MS(10);
			if(USART2_RX_STA&0X8000)//接收到期待的应答结果
			{
				if(usr_tcp232_check_cmd(ack))break;//得到有效数据 
				USART2_RX_STA=0;
			} 
		}
		if(waittime==0)res=1; 
	}
	return res;
} 



////获得第一次发送回的实验编号
////参数：等待时间和第一次发送的命令
////waittime :等待时间
//u8 usr_tcp232_getnumber(u8 *a,u16 waittime)
//{
//	 u8  number[6];
//	 u8  act[7];
//	 u8 res;
//	 u8 i=0,j=0;
//	u2_printf("%s\r",a);
//	while(--waittime)	//等待倒计时
//		{
//			DELAY_MS(10);
//			if(USART2_RX_STA&0X8000)//接收到期待的应答结果
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


//得到实验编号
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




//usr_tcp232向服务器发送验证请求
//参数 学生ID 时间 桌号
//返回值，成功回0，失败回1，但是目前还没有进行核验
//函数保留
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
	
//向服务器发送成绩
//实验参数是 学生ID，时间 实验编号 桌号 成绩
	//目前的实验编号是强制设定的，到后面会通过服务器来返回
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

	
	//向服务器发送txt文件
	//参数 ID号 文件名 文件内容
	//目前只能发送文件，后期需要加工
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




















