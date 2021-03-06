#ifndef __MQTT_H
#define __MQTT_H

#include "app_wifi_common.h"

#define		MQTT_TypeCONNECT				1						//请求连接
#define		MQTT_TypeCONNACK				2						//请求应答  
#define		MQTT_TypePUBLISH				3						//发布消息 
#define		MQTT_TypePUBACK					4						//发布应答  
#define		MQTT_TypePUBREC					5						//发布已接收，保证传递1  
#define		MQTT_TypePUBREL					6						//发布释放,保证传递2  
#define		MQTT_TypePUBCOMP				7						//发布完成,保证传递3  
#define		MQTT_TypeSUBSCRIBE				8						//订阅请求 
#define		MQTT_TypeSUBACK					9						//订阅应答  
#define		MQTT_TypeUNSUBSCRIBE				10						//取消订阅  
#define		MQTT_TypeUNSUBACK				11						//取消订阅应答  
#define		MQTT_TypePINGREQ				12						//ping请求  
#define		MQTT_TypePINGRESP				13						//ping应答  
#define		MQTT_TypeDISCONNECT 				14						//断开连接  

#define		MQTT_StaCleanSession				1						// 清理会话
#define		MQTT_StaWillFlag				0						// 遗嘱标志
#define		MQTT_StaWillQoS					0						// 遗嘱QoS连接标志的第4位和第3位
#define		MQTT_StaWillRetain				0						// 遗嘱保留
#define		MQTT_StaUserNameFlag				1						// User Name Flag
#define		MQTT_StaPasswordFlag				1						// Password Flag
#define		MQTT_KeepAlive					60
#define		MQTT_ClientIdentifier  				"10022542"					// Client Identifier
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
	int  moduleId;
	char rank;
} mqtt_rcv_info_t;

u8 GetDataFixedHead(unsigned char MesType, unsigned char DupFlag, unsigned char QosLevel, unsigned char Retain);
u8 GetDataPUBLISH(unsigned char *buff, unsigned char dup, unsigned char qos, unsigned char retain, const char *topic , const char *msg); 
u8 GetDataSUBSCRIBE(unsigned char *buff, unsigned char *dat, unsigned int Num, unsigned char RequestedQoS); 
u8 GetDataConnet(unsigned char *buff);
void GetDataDisConnet(unsigned char *buff);
void GetDataPINGREQ(unsigned char *buff);

mqttStatus usr_c322_wifista_mqtt_init(void);
mqttStatus usr_c322_wifista_mqtt_connect(void);
mqttStatus usr_c322_wifista_mqtt_subscribe(u8 *topic);
mqttStatus usr_c322_wifista_mqtt_check(unsigned char *rcv_buff);
mqttStatus usr_c322_wifista_mqtt_ping(void);
mqttStatus mqttParsePublish(unsigned char *mqttDataBuff);
void usr_c322_wifista_mqtt_puback(unsigned int Num);
wifiStatus usr_c322_wifista_mqtt_restart(void);

#endif
