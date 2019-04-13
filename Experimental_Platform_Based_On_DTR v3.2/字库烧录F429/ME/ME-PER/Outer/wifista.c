#include "common.h"
#include "stdlib.h"
#include "malloc.h"  
#include "string.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//ATK-ESP8266 WIFI模块 WIFI STA驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2015/4/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 

//ATK-ESP8266 WIFI STA测试
//用于测试TCP/UDP连接
//返回值:0,正常
//    其他,错误代码

extern u8 Wifi_List[10][20];

void atk_8266_wifista_connect(void)
{
	u8 p[50];
	atk_8266_quit_trans();
	atk_8266_send_cmd("AT+CWMODE=1","OK",80);		//设置WIFI STA模式
	atk_8266_send_cmd("AT+RST","ready",80);		//DHCP服务器关闭(仅AP模式有效) 
	//设置连接到的WIFI网络名称/加密方式/密码,这几个参数需要根据您自己的路由器设置进行修改!! 
	sprintf((char*)p,"AT+CWJAP_CUR=\"%s\",\"%s\"",wifista_ssid,wifista_password);//设置无线参数:ssid,密码
	while(atk_8266_send_cmd(p,"OK",2000));					//连接2.2.2.2服务器，以发送HTTP登录请求
	delay_xms(1000);
	atk_8266_send_cmd("AT+CIPMUX=0","OK",20);   //0：单连接，1：多连接
}

void atk_8266_wifista_login(void)                 //登录函数
{
	atk_8266_send_cmd("AT+CIPSTART=\"TCP\",\"2.2.2.2\",80","OK",200);
	atk_8266_send_cmd("AT+CIPMODE=1","OK",200);      //传输模式为：透传			
	USART3_RX_STA=0;													 
	atk_8266_quit_trans();
	atk_8266_send_cmd("AT+CIPSEND","OK",20);         //开始透传       
	atk_8266_send_cmd("POST /ac_portal/login.php HTTP/1.1","",0);        //开始发送HTTP请求
	atk_8266_send_cmd("Host:2.2.2.2","",0);
	atk_8266_send_cmd("Connection:keep-alive","",0);
	atk_8266_send_cmd("Content-Length:57","",0);
	atk_8266_send_cmd("Accept:*/*","",0);
	atk_8266_send_cmd("User-Agent:Mozilla/5.0(Linux;Android 7.1.1;OD103 Build/NMF26F;wv)","",0);
	atk_8266_send_cmd("Content-Type:application/x-www-form-urlencoded;charset=UTF-8","",0);
	atk_8266_send_cmd("Accept-Encodeing:gzip,deflate","",0);
	atk_8266_send_cmd("Accept-Language:zh-CN,en-US;q=0.8","",0);
	atk_8266_send_cmd("X-Requested-With:XMLHttpRequest","",0);
	atk_8266_send_cmd("","",0);                   //区分请求头和请求主体
	atk_8266_send_cmd("opr=pwdLogin&userName=16041538&pwd=990404GZXWAN&rememberpwd=0","success",20);   //发送学号和密码登陆
	atk_8266_quit_trans();	//退出透传
	atk_8266_send_cmd("AT+CIPCLOSE","OK",20);      //关闭与2.2.2.2服务器连接
}

//发送HTTP请求函数
//返回值：0或1：没通过或通过；2：发送失败
u8 atk_8266_wifista_HTTP_request(u8* request,u8* parameter)               
{
	u8 *strx=0;
	u8 status=0;
	u8 a[75];
	sprintf((char*)a,"AT+CIPSTART=\"TCP\",\"%s\",%s",(u8*)wifista_ip,(u8*)portnum);    //配置目标TCP服务器
	atk_8266_send_cmd(a,"OK",200);
	memset(a,0,sizeof(a));
	delay_xms(10);	
	atk_8266_quit_trans();
	atk_8266_send_cmd("AT+CIPSEND","OK",20);         //开始透传     
	sprintf((char*)a,"GET /api/%s/?%s HTTP/1.1",request,parameter);    //配置目标TCP服务器
	atk_8266_send_cmd(a,"",0);   
	atk_8266_send_cmd("Host: zx.mcfhq.com","",0);
	atk_8266_send_cmd("Connection: keep-alive","",0);
	atk_8266_send_cmd("User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:57.0) Gecko/20100101 Firefox/57.0","",0);
	atk_8266_send_cmd("Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8","",0);
	atk_8266_send_cmd("Accept-Encoding: gzip, deflate","",0);
	atk_8266_send_cmd("Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2","",0);
	atk_8266_send_cmd("","status",50);                  //区分请求头和请求主体
	strx=atk_8266_check_cmd("status");  //在定位到指定字符串之前都不能清零串口接收标志寄存器，否则无法定位
	if(strx)
	{
		status=*(strx+7)-'0';                 //确定返回值位置 取得返回值
		USART3_RX_STA=0;
		atk_8266_quit_trans();	//退出透传
		atk_8266_send_cmd("AT+CIPCLOSE","OK",50);      //关闭与目标服务器连接
	}
	else
	{
		USART3_RX_STA=0;
		status=2;
		atk_8266_quit_trans();	//退出透传
		atk_8266_send_cmd("AT+CIPCLOSE","OK",50);      //关闭与目标服务器连接
	}
	return status;
}

//通过HTTP请求获取预约信息函数
//返回值：NULL,未收到学号响应;否则返回学号首位地址
u8* atk_8266_wifista_HTTP_appointment(u8* room,u8* table)                 
{
	u8* appointID;
	u8 a[70];
	sprintf((char*)a,"AT+CIPSTART=\"TCP\",\"%s\",%s",(u8*)wifista_ip,(u8*)portnum);    //配置目标TCP服务器
	atk_8266_send_cmd(a,"OK",200);
	memset(a,0,sizeof(a));
	delay_xms(10);	
	atk_8266_quit_trans();
	atk_8266_send_cmd("AT+CIPSEND","OK",20);         //开始透传             
	sprintf((char*)a,"GET /api/appointment/?room=%s&table=%s HTTP/1.1",room,table);    //配置目标TCP服务器
	atk_8266_send_cmd(a,"",20);                      //开始发送HTTP请求
	atk_8266_send_cmd("Host: zx.mcfhq.com","",0);
	atk_8266_send_cmd("Connection: keep-alive","",0);
	atk_8266_send_cmd("User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:57.0) Gecko/20100101 Firefox/57.0","",0);
	atk_8266_send_cmd("Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8","",0);
	atk_8266_send_cmd("Accept-Encoding: gzip, deflate","",0);
	atk_8266_send_cmd("Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2","",0);
	atk_8266_send_cmd("","sid",50);                  //区分请求头和请求主体
	appointID=atk_8266_check_cmd("sid"); //在定位到指定字符串之前都不能清零串口接收标志寄存器，否则无法定位
	if(appointID)
	{
		appointID+=4;      //定位到预约人学号
		USART3_RX_STA=0;
		atk_8266_quit_trans();	//退出透传   
		atk_8266_send_cmd("AT+CIPCLOSE","OK",20);      //关闭与目标服务器连接
	}
	else
	{
		appointID=NULL;
		USART3_RX_STA=0;
		atk_8266_quit_trans();	//退出透传
		atk_8266_send_cmd("AT+CIPCLOSE","OK",20);      //关闭与目标服务器连接
	}
	return appointID;
}

void atk_8266_wifista_parse()
{
	u8* strx=USART3_RX_BUF;
	u16 i = 0;
	u16 j = 0;
	u16 k = 0;
	u8 WifiNameIndex = 1;
	u8 WifiNumber = 0;
	
	while(USART3_RX_BUF[k])
	{
		strx=USART3_RX_BUF+j;
		i = 0;
		if(strstr(strx,"+CWLAP"))
		{
			for(;strx[i]!='(';i++)
			{
				if(strx[i] == 0)
					return;
				else if(strx[i] == '\n')
					continue;
			}
			
			i ++;		
			Wifi_List[WifiNumber][0] = strx[i];
			
			while(strx[i]!='\"')
			{
				if(strx[i] == 0)
					return;
				else if(strx[i] == '\n')
					continue;
				else
					i ++;
			}
			
			i ++;
			while(strx[i] != '\"')
			{
				if(strx[i] == 0)
					return;
				else if(strx[i] == '\n')
					continue;
				else
					Wifi_List[WifiNumber][WifiNameIndex++] = strx[i++];
			}
			
			while(strx[i] != '\n')
			{
				if(strx[i] == 0)
					return;
				else if(strx[i] == '\n')
					continue;
				else
					i ++;
			}
			
			WifiNumber ++;
			if(WifiNumber >= 9)
				return;
			WifiNameIndex = 1;
			
			j += i;
		}
		k = j;
		k ++;
	}
}