#include "common.h"
#include "stdlib.h"
#include "malloc.h"  
#include "string.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//ATK-ESP8266 WIFIģ�� WIFI STA��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2015/4/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 

//ATK-ESP8266 WIFI STA����
//���ڲ���TCP/UDP����
//����ֵ:0,����
//    ����,�������

extern u8 Wifi_List[10][20];

void atk_8266_wifista_connect(void)
{
	u8 p[50];
	atk_8266_quit_trans();
	atk_8266_send_cmd("AT+CWMODE=1","OK",80);		//����WIFI STAģʽ
	atk_8266_send_cmd("AT+RST","ready",80);		//DHCP�������ر�(��APģʽ��Ч) 
	//�������ӵ���WIFI��������/���ܷ�ʽ/����,�⼸��������Ҫ�������Լ���·�������ý����޸�!! 
	sprintf((char*)p,"AT+CWJAP_CUR=\"%s\",\"%s\"",wifista_ssid,wifista_password);//�������߲���:ssid,����
	while(atk_8266_send_cmd(p,"OK",2000));					//����2.2.2.2���������Է���HTTP��¼����
	delay_xms(1000);
	atk_8266_send_cmd("AT+CIPMUX=0","OK",20);   //0�������ӣ�1��������
}

void atk_8266_wifista_login(void)                 //��¼����
{
	atk_8266_send_cmd("AT+CIPSTART=\"TCP\",\"2.2.2.2\",80","OK",200);
	atk_8266_send_cmd("AT+CIPMODE=1","OK",200);      //����ģʽΪ��͸��			
	USART3_RX_STA=0;													 
	atk_8266_quit_trans();
	atk_8266_send_cmd("AT+CIPSEND","OK",20);         //��ʼ͸��       
	atk_8266_send_cmd("POST /ac_portal/login.php HTTP/1.1","",0);        //��ʼ����HTTP����
	atk_8266_send_cmd("Host:2.2.2.2","",0);
	atk_8266_send_cmd("Connection:keep-alive","",0);
	atk_8266_send_cmd("Content-Length:57","",0);
	atk_8266_send_cmd("Accept:*/*","",0);
	atk_8266_send_cmd("User-Agent:Mozilla/5.0(Linux;Android 7.1.1;OD103 Build/NMF26F;wv)","",0);
	atk_8266_send_cmd("Content-Type:application/x-www-form-urlencoded;charset=UTF-8","",0);
	atk_8266_send_cmd("Accept-Encodeing:gzip,deflate","",0);
	atk_8266_send_cmd("Accept-Language:zh-CN,en-US;q=0.8","",0);
	atk_8266_send_cmd("X-Requested-With:XMLHttpRequest","",0);
	atk_8266_send_cmd("","",0);                   //��������ͷ����������
	atk_8266_send_cmd("opr=pwdLogin&userName=16041538&pwd=990404GZXWAN&rememberpwd=0","success",20);   //����ѧ�ź������½
	atk_8266_quit_trans();	//�˳�͸��
	atk_8266_send_cmd("AT+CIPCLOSE","OK",20);      //�ر���2.2.2.2����������
}

//����HTTP������
//����ֵ��0��1��ûͨ����ͨ����2������ʧ��
u8 atk_8266_wifista_HTTP_request(u8* request,u8* parameter)               
{
	u8 *strx=0;
	u8 status=0;
	u8 a[75];
	sprintf((char*)a,"AT+CIPSTART=\"TCP\",\"%s\",%s",(u8*)wifista_ip,(u8*)portnum);    //����Ŀ��TCP������
	atk_8266_send_cmd(a,"OK",200);
	memset(a,0,sizeof(a));
	delay_xms(10);	
	atk_8266_quit_trans();
	atk_8266_send_cmd("AT+CIPSEND","OK",20);         //��ʼ͸��     
	sprintf((char*)a,"GET /api/%s/?%s HTTP/1.1",request,parameter);    //����Ŀ��TCP������
	atk_8266_send_cmd(a,"",0);   
	atk_8266_send_cmd("Host: zx.mcfhq.com","",0);
	atk_8266_send_cmd("Connection: keep-alive","",0);
	atk_8266_send_cmd("User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:57.0) Gecko/20100101 Firefox/57.0","",0);
	atk_8266_send_cmd("Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8","",0);
	atk_8266_send_cmd("Accept-Encoding: gzip, deflate","",0);
	atk_8266_send_cmd("Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2","",0);
	atk_8266_send_cmd("","status",50);                  //��������ͷ����������
	strx=atk_8266_check_cmd("status");  //�ڶ�λ��ָ���ַ���֮ǰ���������㴮�ڽ��ձ�־�Ĵ����������޷���λ
	if(strx)
	{
		status=*(strx+7)-'0';                 //ȷ������ֵλ�� ȡ�÷���ֵ
		USART3_RX_STA=0;
		atk_8266_quit_trans();	//�˳�͸��
		atk_8266_send_cmd("AT+CIPCLOSE","OK",50);      //�ر���Ŀ�����������
	}
	else
	{
		USART3_RX_STA=0;
		status=2;
		atk_8266_quit_trans();	//�˳�͸��
		atk_8266_send_cmd("AT+CIPCLOSE","OK",50);      //�ر���Ŀ�����������
	}
	return status;
}

//ͨ��HTTP�����ȡԤԼ��Ϣ����
//����ֵ��NULL,δ�յ�ѧ����Ӧ;���򷵻�ѧ����λ��ַ
u8* atk_8266_wifista_HTTP_appointment(u8* room,u8* table)                 
{
	u8* appointID;
	u8 a[70];
	sprintf((char*)a,"AT+CIPSTART=\"TCP\",\"%s\",%s",(u8*)wifista_ip,(u8*)portnum);    //����Ŀ��TCP������
	atk_8266_send_cmd(a,"OK",200);
	memset(a,0,sizeof(a));
	delay_xms(10);	
	atk_8266_quit_trans();
	atk_8266_send_cmd("AT+CIPSEND","OK",20);         //��ʼ͸��             
	sprintf((char*)a,"GET /api/appointment/?room=%s&table=%s HTTP/1.1",room,table);    //����Ŀ��TCP������
	atk_8266_send_cmd(a,"",20);                      //��ʼ����HTTP����
	atk_8266_send_cmd("Host: zx.mcfhq.com","",0);
	atk_8266_send_cmd("Connection: keep-alive","",0);
	atk_8266_send_cmd("User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:57.0) Gecko/20100101 Firefox/57.0","",0);
	atk_8266_send_cmd("Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8","",0);
	atk_8266_send_cmd("Accept-Encoding: gzip, deflate","",0);
	atk_8266_send_cmd("Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2","",0);
	atk_8266_send_cmd("","sid",50);                  //��������ͷ����������
	appointID=atk_8266_check_cmd("sid"); //�ڶ�λ��ָ���ַ���֮ǰ���������㴮�ڽ��ձ�־�Ĵ����������޷���λ
	if(appointID)
	{
		appointID+=4;      //��λ��ԤԼ��ѧ��
		USART3_RX_STA=0;
		atk_8266_quit_trans();	//�˳�͸��   
		atk_8266_send_cmd("AT+CIPCLOSE","OK",20);      //�ر���Ŀ�����������
	}
	else
	{
		appointID=NULL;
		USART3_RX_STA=0;
		atk_8266_quit_trans();	//�˳�͸��
		atk_8266_send_cmd("AT+CIPCLOSE","OK",20);      //�ر���Ŀ�����������
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