#include "ep_app.h"

u8 k;
u8 voice_Com[4] = {0xFD, 0x00, 0x01};  	     			//ģ��ָ��ͷ
char voice_Dat[100];            					//�������� ���25�������ַ�

const u8 voiceWelcome[] = "��ӭʹ�á����������繤����ʵ��̨";

const u8 voiceShowQrCode[] = "��ɨ�����Ķ�ά��";

const u8 voiceSignInSuccess[] = "ǩ���ɹ�";

const u8 voiceSignInFail[] = "ǩ��ʧ��";

const u8 voiceSignInOverTime[] = "ǩ���ϴ���ʱ";

const u8 voiceIdentifySuccess[] = "������֤�ɹ�";

const u8 voiceIdentifyFail[] = "������֤ʧ��";

const u8 voiceIdentifyOverTime[] = "������֤��ʱ";

const u8 voiceMarkLoadSuccess[] = "�ɼ��ϴ��ɹ�";

const u8 voiceMarkLoadFail[] = "�ɼ��ϴ�ʧ��";

const u8 voiceMarkLoadOverTime[] = "�ɼ��ϴ���ʱ";

const u8 voiceEndExp[] = "����ʵ�鵽�˽���";

const u8 voiceStatrMatch[] = "��ʼƥ���豸���뽫����ƥ���豸������Ӧ��";

const u8 voiceMatchSuccess[] = "�ɹ�ƥ�䵽�豸";

const u8 voiceMatchFail[] = "�豸ƥ��ʧ��";

const u8 voiceMatchTimeExpired[] = "�豸ƥ�䳬ʱ";

/******************************************
�ж��ϵ��ʼ���Ƿ�ɹ�����
����ֵ��0��ʧ��
		1���ɹ�
********************************************/
u8 voiceInitCheck()
{
	u8 i = 0;
	u8 waittime = 10;
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOAʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //nready,bit_wifi_status��Ӧ����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4

	GPIO_ResetBits(GPIOF, GPIO_Pin_1);
	bsp_delay_ms(50);
	GPIO_SetBits(GPIOF, GPIO_Pin_1);

	while(--waittime) { //�ȴ�����ģ�鷵����Ϣ
		if(uart.uart_5->rx_status & 0x8000) {
			if(uart.uart_5->pRx_buffer[0] == ACK_INIT_OK) {
				i = 1;
				uart.uart_5->rx_status = 0;
				break;
			}
			uart.uart_5->rx_status = 0;
		}
	}
	bsp_delay_ms(100);
	return i;
}

/*********************************************
���������
���룺	com:����
		res:��Ӧ
����ֵ��0:��Ӧ��ʱ;
		1:��Ӧ��ȷ;
		����:��Ӧ������������Ӧ
**********************************************/
u8 voiceSendCommand(u8 com, u8 res)
{
	u8 j = 0;
	u8 i = 0;
	u8 waittime = 30;
	uart.uart_5->rx_status = 0;
	voice_Com[3] = com;		//�ϲ�����
	for(j = 0; j < 4; j++) {	//ѭ����������
		while(USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET); //ѭ������,ֱ���������
		USART_SendData(UART5, voice_Com[j]);
	}
	while(--waittime) {
		bsp_delay_ms(10);
		if(uart.uart_5->rx_status & 0x8000) { //�ȴ�����ģ�鷵����Ϣ
			if(uart.uart_5->pRx_buffer[0] != res) {
				i = uart.uart_5->pRx_buffer[0];
			} else {
				i = 1;
			}
			uart.uart_5->rx_status = 0;
			break;
		}
	}
	return i;
}

/****************************************
�������ݺ���
���룺	len:�ַ������ȣ�ת��Ϊ�ֽڣ�
		data:����
����ֵ��0:�ϳɳ�ʱ
		1:�ϳɳɹ�
*****************************************/
u8 voiceSendData(u16 len, const char* data)
{
	u8 i = 0;
	u8 waittime = 10;
	voice_Dat[0] = 0xfd;
	voice_Dat[1] = len >> 8;
	voice_Dat[2] = len;
	voice_Dat[3] = 0x01;
	voice_Dat[4] = 0x00;
	while(voiceSendCommand(STATE_CHECK, ACK_FREE) != 1 && waittime > 0) {	//�ȴ�ģ�����
		bsp_delay_ms(10);
		waittime --;
	}
	waittime = 100;
	sprintf(&voice_Dat[5], data);	                               //�����ı�����������ֵ���
	uart.oop(uart.uart_5).write_raw((u8 *)voice_Dat, len + 5);
	while(--waittime) {
		bsp_delay_ms(10);
		if(uart.uart_5->rx_status & 0x8000) {                   //�ȴ�����ģ�鷵����Ϣ
			if(uart.uart_5->pRx_buffer[0] == ACK_CORRECT_CMD) {
				i = 1;
			}
			uart.uart_5->rx_status = 0;
			break;
		}
	}
	return i;
}

u8 voiceDispString(const u8* str)
{
	if(sys_config.voice == on) {
		if(voiceSendData(strlen((const char *)str) + 2, (const char *)str))
			return 1;
		else
			return 0;
	} else
		return 1;
}