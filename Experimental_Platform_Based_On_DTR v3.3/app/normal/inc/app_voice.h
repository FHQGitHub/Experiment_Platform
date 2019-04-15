#ifndef __VOICE_H
#define __VOICE_H

#include "stm32f4xx.h"

//合成指令
#define 	STATE_CHECK             (u8)0x21		//状态检测
#define 	SAVE_POWER              (u8)0x88		//省电模式
#define 	WAKE_UP                 (u8)0xff		//唤醒芯片
#define 	TERMINATE	        (u8)0x02		//停止合成
#define 	PAUSE   	        (u8)0x03		//暂停合成
#define 	RESUME                  (u8)0x04		//恢复合成

//响应
#define		ACK_INIT_OK	        (u8)0x4a		//初始化成功
#define		ACK_CORRECT_CMD         (u8)0x41		//收到正确指令
#define		ACK_WRONG_CMD           (u8)0x45		//收到错误指令
#define		ACK_BUSY	        (u8)0x4e		//当前繁忙
#define		ACK_FREE	        (u8)0x4f		//当前空闲

extern const u8 voiceSetting[];

extern const u8 voiceWelcome[];

extern const u8 voiceShowQrCode[];

extern const u8 voiceSignInSuccess[];

extern const u8 voiceSignInFail[];

extern const u8 voiceSignInOverTime[];

extern const u8 voiceIdentifySuccess[];
	
extern const u8 voiceIdentifyFail[];

extern const u8 voiceIdentifyOverTime[];

extern const u8 voiceMarkLoadSuccess[];

extern const u8 voiceMarkLoadFail[];

extern const u8 voiceMarkLoadOverTime[];
	
extern const u8 voiceEndExp[];

extern const u8 voiceStatrMatch[];

extern const u8 voiceStatrMatch[];

extern const u8 voiceMatchSuccess[];

extern const u8 voiceMatchFail[];

extern const u8 voiceMatchTimeExpired[];

u8 voiceInitCheck(void);
u8 voiceSendCommand(u8 com,u8 res);
u8 voiceSendData(u16 len,const char* data);
u8 voiceDispString(const u8* str);

#endif

