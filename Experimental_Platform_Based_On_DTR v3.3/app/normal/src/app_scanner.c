#include "ep_app.h"

u8 QR_On_key[9] = {0x7E, 0x00, 0x08, 0x01, 0x00, 0x02, 0x01, 0xAB, 0xCD}; //����ɨ��ָ��
u8 QR_On_res[7] = {0x02, 0x00, 0x00, 0x01, 0x00, 0x33, 0x31};    //ģ�鷵����Ϣ

u8 u4_buf[200];


u8 QR_On(void)
{
	u8 res = 0;
	u8 waittime = 30;
	u8 strx = 0;
	uart.uart_4->rx_status = 0;
	uart.oop(uart.uart_4).write_raw(QR_On_key, 9);

	while(--waittime) {
		bsp_delay_ms(10);
		if(uart.uart_4->rx_status & 0x8000) { //�ȴ�ɨ��ģ�鷵����Ϣ
			strx = memcmp(uart.uart_4->pRx_buffer, QR_On_res, 7);
			if(strx != 0) {
				res = 1;      //����ʧ��
				//printf("����ʧ��\r\n");
			} else {
				//printf("�����ɹ�\r\n");
			}
			uart.uart_4->rx_status = 0;
			break;
		}
	}
	if(waittime == 0) {
		res = 2;         
	}
	return res;
}



u8 QR_RX_Data(u8 rxDat[], const u8 * check)
{
	u8 res = 0;
	u8 count = 0;
	char *strx = 0;
	while(!(uart.uart_4->rx_status & 0x8000) && count <= 5) { 
		bsp_delay_ms(1000);
		count ++;
	}
	if(count >= 5) {
		count = 0;
		return 0xff;
	}
	if(uart.uart_4->rx_status & 0x8000) {
		memset(u4_buf, 0, 200);
		memcpy(u4_buf, uart.uart_4->pRx_buffer, 200);
		uart.uart_4->pRx_buffer[(uart.uart_4->rx_status & 0X3FFF) - 1] = 0; 
		uart.uart_4->rx_status = 0;
		strx = strstr((const char*)uart.uart_4->pRx_buffer, (const char *)check);
		if(strx) {
			strcpy((char *)rxDat, (const char*)uart.uart_4->pRx_buffer);
			res = 1;
		}
	}
	return res;
}

