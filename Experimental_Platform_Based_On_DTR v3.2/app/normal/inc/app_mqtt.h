#ifndef __MQTT_H
#define __MQTT_H

#include "app_wifi_common.h"

#define		MQTT_TypeCONNECT				1						//��������
#define		MQTT_TypeCONNACK				2						//����Ӧ��  
#define		MQTT_TypePUBLISH				3						//������Ϣ 
#define		MQTT_TypePUBACK					4						//����Ӧ��  
#define		MQTT_TypePUBREC					5						//�����ѽ��գ���֤����1  
#define		MQTT_TypePUBREL					6						//�����ͷ�,��֤����2  
#define		MQTT_TypePUBCOMP				7						//�������,��֤����3  
#define		MQTT_TypeSUBSCRIBE				8						//�������� 
#define		MQTT_TypeSUBACK					9						//����Ӧ��  
#define		MQTT_TypeUNSUBSCRIBE				10						//ȡ������  
#define		MQTT_TypeUNSUBACK				11						//ȡ������Ӧ��  
#define		MQTT_TypePINGREQ				12						//ping����  
#define		MQTT_TypePINGRESP				13						//pingӦ��  
#define		MQTT_TypeDISCONNECT 				14						//�Ͽ�����  

#define		MQTT_StaCleanSession				1						// ����Ự
#define		MQTT_StaWillFlag				0						// ������־
#define		MQTT_StaWillQoS					0						// ����QoS���ӱ�־�ĵ�4λ�͵�3λ
#define		MQTT_StaWillRetain				0						// ��������
#define		MQTT_StaUserNameFlag				1						// User Name Flag
#define		MQTT_StaPasswordFlag				1						// Password Flag
#define		MQTT_KeepAlive					60
#define		MQTT_ClientIdentifier  				"10022541"					// Client Identifier
#define		MQTT_WillTopic					""						// Will Topic
#define		MQTT_WillMessage				""						// Will Message
#define		MQTT_UserName					"hduuser"					// User Name
#define		MQTT_Password					"aEyyX2oF"					// Password

#define		MQTT_MaxQoS					2
#define		MQTT_PUBLISHWithRetain				0x31
#define		MQTT_PUBLISHWithoutRetain			0x30

typedef enum {
	MQTT_ERR = 1,
	MQTT_OK,
	MQTT_TIMEOUT
} mqttStatus;

typedef enum {
	mqtt_init = 1,
	mqtt_pingque,
	mqtt_restart,
	mqtt_subscribe
} mqttEvent;

typedef struct {
	mqttEvent event;
	mqttStatus status;
} mqtt_notify_t;

typedef struct {
	char moduleId;
	char rank;
} mqtt_rcv_info_t;

extern mqtt_rcv_info_t mqtt_rcv_info;

u8 GetDataFixedHead(unsigned char MesType, unsigned char DupFlag, unsigned char QosLevel, unsigned char Retain);
u8 GetDataPUBLISH(unsigned char *buff, unsigned char dup, unsigned char qos, unsigned char retain, const char *topic , const char *msg); //��ȡ������Ϣ�����ݰ�
u8 GetDataSUBSCRIBE(unsigned char *buff, unsigned char *dat, unsigned int Num, unsigned char RequestedQoS); //������������ݰ� Num:������� RequestedQoS:��������Ҫ��0,1��2
u8 GetDataConnet(unsigned char *buff);//��ȡ���ӵ����ݰ���ȷ���ӵķ���20 02 00 00
void GetDataDisConnet(unsigned char *buff);//��ȡ�Ͽ����ӵ����ݰ�
void GetDataPINGREQ(unsigned char *buff);//������������ݰ��ɹ�����d0 00

mqttStatus usr_c322_wifista_mqtt_init(void);
mqttStatus usr_c322_wifista_mqtt_connect(void);
mqttStatus usr_c322_wifista_mqtt_subscribe(u8 *topic);
mqttStatus usr_c322_wifista_mqtt_check(unsigned char *rcv_buff);
mqttStatus usr_c322_wifista_mqtt_ping(void);
mqttStatus mqttParsePublish(unsigned char *mqttDataBuff);
void usr_c322_wifista_mqtt_puback(unsigned int Num);
wifiStatus usr_c322_wifista_mqtt_restart(void);

#endif
