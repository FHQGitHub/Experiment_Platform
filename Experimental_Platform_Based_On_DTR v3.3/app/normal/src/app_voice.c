#include "ep_app.h"

u8 k;
u8 voice_Com[4] = {0xFD, 0x00, 0x01};  	     			//模块指令头
char voice_Dat[100];            					//语音数据 最多25个中文字符

const u8 voiceWelcome[] = "欢迎使用、智能物联电工电子实验台";

const u8 voiceShowQrCode[] = "请扫描您的二维码";

const u8 voiceSignInSuccess[] = "签到成功";

const u8 voiceSignInFail[] = "签到失败";

const u8 voiceSignInOverTime[] = "签到上传超时";

const u8 voiceIdentifySuccess[] = "身份验证成功";

const u8 voiceIdentifyFail[] = "身份验证失败";

const u8 voiceIdentifyOverTime[] = "身份验证超时";

const u8 voiceMarkLoadSuccess[] = "成绩上传成功";

const u8 voiceMarkLoadFail[] = "成绩上传失败";

const u8 voiceMarkLoadOverTime[] = "成绩上传超时";

const u8 voiceEndExp[] = "本次实验到此结束";

const u8 voiceStatrMatch[] = "开始匹配设备，请将、待匹配设备贴近感应区";

const u8 voiceMatchSuccess[] = "成功匹配到设备";

const u8 voiceMatchFail[] = "设备匹配失败";

const u8 voiceMatchTimeExpired[] = "设备匹配超时";

/******************************************
判断上电初始化是否成功函数
返回值：0：失败
		1：成功
********************************************/
u8 voiceInitCheck()
{
	u8 i = 0;
	u8 waittime = 10;
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOA时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //nready,bit_wifi_status对应引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化GPIOE2,3,4

	GPIO_ResetBits(GPIOF, GPIO_Pin_1);
	bsp_delay_ms(50);
	GPIO_SetBits(GPIOF, GPIO_Pin_1);

	while(--waittime) { //等待语音模块返回信息
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
发送命令函数
输入：	com:命令
		res:响应
返回值：0:响应超时;
		1:响应正确;
		其他:响应不符的其他响应
**********************************************/
u8 voiceSendCommand(u8 com, u8 res)
{
	u8 j = 0;
	u8 i = 0;
	u8 waittime = 30;
	uart.uart_5->rx_status = 0;
	voice_Com[3] = com;		//合并命令
	for(j = 0; j < 4; j++) {	//循环发送数据
		while(USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET); //循环发送,直到发送完毕
		USART_SendData(UART5, voice_Com[j]);
	}
	while(--waittime) {
		bsp_delay_ms(10);
		if(uart.uart_5->rx_status & 0x8000) { //等待语音模块返回信息
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
发送数据函数
输入：	len:字符串长度（转化为字节）
		data:数据
返回值：0:合成超时
		1:合成成功
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
	while(voiceSendCommand(STATE_CHECK, ACK_FREE) != 1 && waittime > 0) {	//等待模块空闲
		bsp_delay_ms(10);
		waittime --;
	}
	waittime = 100;
	sprintf(&voice_Dat[5], data);	                               //将中文编码连接在数值其后
	uart.oop(uart.uart_5).write_raw((u8 *)voice_Dat, len + 5);
	while(--waittime) {
		bsp_delay_ms(10);
		if(uart.uart_5->rx_status & 0x8000) {                   //等待语音模块返回信息
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
