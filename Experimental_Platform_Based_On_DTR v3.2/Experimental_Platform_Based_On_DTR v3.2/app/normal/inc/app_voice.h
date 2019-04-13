#ifndef __VOICE_H
#define __VOICE_H

#include "stm32f4xx.h"

//�ϳ�ָ��
#define 	STATE_CHECK             (u8)0x21		//״̬���
#define 	SAVE_POWER              (u8)0x88		//ʡ��ģʽ
#define 	WAKE_UP                 (u8)0xff		//����оƬ
#define 	TERMINATE	        (u8)0x02		//ֹͣ�ϳ�
#define 	PAUSE   	        (u8)0x03		//��ͣ�ϳ�
#define 	RESUME                  (u8)0x04		//�ָ��ϳ�

//��Ӧ
#define		ACK_INIT_OK	        (u8)0x4a		//��ʼ���ɹ�
#define		ACK_CORRECT_CMD         (u8)0x41		//�յ���ȷָ��
#define		ACK_WRONG_CMD           (u8)0x45		//�յ�����ָ��
#define		ACK_BUSY	        (u8)0x4e		//��ǰ��æ
#define		ACK_FREE	        (u8)0x4f		//��ǰ����

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

