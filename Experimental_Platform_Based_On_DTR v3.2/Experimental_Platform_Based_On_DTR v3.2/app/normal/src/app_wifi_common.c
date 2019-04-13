#include "ep_app.h"

const u8* http_wifista_ip = "dev.walkclass.com"; //���ӵķ�����IP��ַ
const u8* http_portnum = "80";
const u8* mqtt_wifista_ip = "47.96.188.208"; //���ӵķ�����IP��ַ
const u8* mqtt_portnum = "6883";

void usr_c322_at_response(u8 mode)
{
	if(uart.uart_x->rx_status & 0X8000) {	//���յ�һ��������
		uart.uart_x->pRx_buffer[uart.uart_x->rx_status & 0X3FFF] = 0; //��ӽ�����
		//printf("%s",uart.uart_x->pRx_buffer);	//���͵�����
		//uart.oop(uart.uart_1).write("%s",uart.uart_x->pRx_buffer);
		if(mode)uart.uart_x->rx_status = 0;
	}
}

//str:�ڴ���Ӧ����
//����ֵ:0,û�еõ��ڴ���Ӧ����
//    ����,�ڴ�Ӧ������λ��(str��λ��)
u8* usr_c322_check_cmd(u8 *str)
{
	char *strx = NULL;
	if(uart.uart_x->rx_status & 0X8000) {	//���յ�һ��������
		uart.uart_x->pRx_buffer[uart.uart_x->rx_status & 0X3FFF] = 0; //��ӽ�����
		strx = strstr((const char*)uart.uart_x->pRx_buffer, (const char*)str);
	}
	return (u8*)strx;
}

//cmd:���͵������ַ���
//ack:�ڴ���Ӧ����,���Ϊ��,���ʾ����Ҫ�ȴ�Ӧ��
//waittime:�ȴ�ʱ��(��λ:10ms)
//����ֵ:0,���ͳɹ�(�õ����ڴ���Ӧ����)
//       1,����ʧ��
wifiStatus usr_c322_send_cmd(u8 *cmd, u8 *ack, u16 waittime)
{
	uart.uart_x->rx_status = 0;
	uart.oop(uart.uart_x).write("%s", cmd);			//��������
	if(ack && waittime) {					//��Ҫ�ȴ�Ӧ��
		while(--waittime) {				//�ȴ�����ʱ
			bsp_delay_ms(10);
			if(uart.uart_x->rx_status & 0X8000) { 	//���յ��ڴ���Ӧ����
				usr_c322_at_response(0);   	//��ӡATָ�����Ϣ
				if(usr_c322_check_cmd(ack)) 
					return WIFI_OK;		//�õ���Ч����
				else
					uart.uart_x->rx_status = 0;
			}
		}
		if(waittime == 0)
			return WIFI_ERR;
	} else;
	return WIFI_OK;
}

//�˳�͸��ģʽ
//����ֵ:1,�˳��ɹ�;
//       0,�˳�ʧ��
wifiStatus usr_c322_quit_trans(void)
{
	u8 i;
	if(usr_c322_send_cmd("+++", "a", 20) == WIFI_OK) {
		if(usr_c322_send_cmd("a", "+OK", 20) == WIFI_OK)
			return WIFI_OK;
		else
			return WIFI_ERR;
	} else {
		i = strcmp((const char*)uart.uart_x->pRx_buffer, "+++");
		if(i)
			return WIFI_ERR;
		else {
			usr_c322_send_cmd("\r\n", "", 20);
			return WIFI_OK;
		}
	}
}

void usr_c322_led_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12; //nready,bit_wifi_status��Ӧ����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4

	GPIO_SetBits(GPIOA, GPIO_Pin_11 | GPIO_Pin_12);
}

void usr_c322_wifista_wsta_parse()
{
	u8 i;
	u8 *str = NULL;
	str = usr_c322_check_cmd("+OK") + 4;
	memset(wifi_data.name, 0, sizeof(wifi_data.name));
	for(i = 0; *str != '('; i++, str++)
		wifi_data.name[i] = *str;
}

wifiStatus usr_c322_check_ping(void)
{
	u8 i;
	u8 p[50];
	usr_c322_quit_trans();
	sprintf((char *)p, "AT+PING=%s\r\n", http_wifista_ip);
	if(usr_c322_send_cmd(p, "SUCCESS", 500) == WIFI_OK) {
		usr_c322_send_cmd("AT+ENTM\r\n", "+OK", 20);
		return WIFI_OK;
	}
	else {
		usr_c322_send_cmd("AT+ENTM\r\n", "+OK", 20);
		return WIFI_SERVER_ERR;
	}
	return WIFI_OK;
}

wifiStatus usr_c322_check_tcp_connect(void)
{
	usr_c322_quit_trans();
	if(usr_c322_send_cmd("AT+SOCKLKA\r\n", "DISCONNECTED", 20) == WIFI_ERR) {
		if(usr_c322_send_cmd("AT+SOCKLKA1\r\n", "DISCONNECTED", 20) == WIFI_ERR) {
			usr_c322_socket_operation(socketB, socketOFF);
			usr_c322_send_cmd("AT+ENTM\r\n", "+OK", 20);
			return WIFI_OK;
		}
		else {
			usr_c322_send_cmd("AT+ENTM\r\n", "+OK", 20);
			return WIFI_TCP_ERR;
		}
	} 
	else {
		usr_c322_send_cmd("AT+ENTM\r\n", "+OK", 20);
		return WIFI_TCP_ERR;
	}
}

wifiStatus usr_c322_socket_operation(enum socketName name, enum socketOperation operation)
{
	u8 i;
	wifiStatus wifiRetVal;
	switch(name) {
		case socketA:
			switch(operation) {
				case socketON:
					usr_c322_send_cmd("AT+SOCKDISA=ON\r\n", "+OK", 20);
					for(i = 0; i < 5; i ++) {
						wifiRetVal = usr_c322_send_cmd("AT+SOCKLKA\r\n", "CONNECTED", 20);
						if(WIFI_OK == wifiRetVal) {
							if(usr_c322_check_cmd("DISCONNECTED"))
								bsp_delay_ms(1000);
							else
								return WIFI_OK;
						}	
						else
							return WIFI_ERR;
					}
				break;
				case socketOFF:
					usr_c322_send_cmd("AT+SOCKDISA=OFF\r\n", "+OK", 20);
					for(i = 0; i < 5; i ++) {
						wifiRetVal = usr_c322_send_cmd("AT+SOCKLKA\r\n", "CONNECTED", 20);
						if(WIFI_OK == wifiRetVal) {
							if(usr_c322_check_cmd("DISCONNECTED"))
								return WIFI_OK;
							else
								bsp_delay_ms(1000);
						}	
						else
							return WIFI_ERR;
					}
				break;
				default:
					
				break;
			}
		break;
		case socketB:
			switch(operation) {
				case socketON:
					usr_c322_send_cmd("AT+SOCKDISB=ON\r\n", "+OK", 20);
					for(i = 0; i < 5; i ++) {
						wifiRetVal = usr_c322_send_cmd("AT+SOCKLKB\r\n", "CONNECTED", 20);
						if(WIFI_OK == wifiRetVal) {
							if(usr_c322_check_cmd("DISCONNECTED"))
								bsp_delay_ms(1000);
							else
								return WIFI_OK;
						}	
						else
							return WIFI_ERR;
					}
				break;
				case socketOFF:
					usr_c322_send_cmd("AT+SOCKDISB=OFF\r\n", "+OK", 20);
					for(i = 0; i < 5; i ++) {
						wifiRetVal = usr_c322_send_cmd("AT+SOCKLKB\r\n", "CONNECTED", 20);
						if(WIFI_OK == wifiRetVal) {
							if(usr_c322_check_cmd("DISCONNECTED"))
								return WIFI_OK;
							else
								bsp_delay_ms(1000);
						}	
						else
							return WIFI_ERR;
					}
				break;
				default:
					
				break;
			}
		break;
		case socketA1:
			switch(operation) {
				case socketON:
					usr_c322_send_cmd("AT+SOCKDISA1=ON\r\n", "+OK", 20);
					for(i = 0; i < 5; i ++) {
						wifiRetVal = usr_c322_send_cmd("AT+SOCKLKA1\r\n", "CONNECTED", 20);
						if(WIFI_OK == wifiRetVal) {
							if(usr_c322_check_cmd("DISCONNECTED"))
								bsp_delay_ms(1000);
							else
								return WIFI_OK;
						}	
						else
							return WIFI_ERR;
					}
				break;
				case socketOFF:
					usr_c322_send_cmd("AT+SOCKDISA1=OFF\r\n", "+OK", 20);
					for(i = 0; i < 5; i ++) {
						wifiRetVal = usr_c322_send_cmd("AT+SOCKLKA1\r\n", "CONNECTED", 20);
						if(WIFI_OK == wifiRetVal) {
							if(usr_c322_check_cmd("DISCONNECTED"))
								return WIFI_OK;
							else
								bsp_delay_ms(1000);
						}	
						else
							return WIFI_ERR;
					}
				break;
				default:
					
				break;
			}
		break;
		default:
			
		break;
	}
	return WIFI_TCP_ERR;
}
