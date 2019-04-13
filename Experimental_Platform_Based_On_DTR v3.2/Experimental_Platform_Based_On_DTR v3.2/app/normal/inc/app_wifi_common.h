#ifndef __COMMON_H__
#define __COMMON_H__	 

#include "bsp.h"

#define Nready 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11) //PA11
#define Nlink		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12) //PA12

enum socketName
{
	socketA = 1,
	socketB,
	socketA1
};

enum socketOperation
{
	socketON = 1,
	socketOFF
};

typedef enum
{
	wifi_scan = 1,
	wifi_connect,
	wifi_ping_check,
	wifi_tcp_check
} wifiEvent;

typedef enum
{
	WIFI_OK = 1,
	WIFI_ERR,
	WIFI_SERVER_ERR,
	WIFI_TCP_ERR
} wifiStatus;

typedef struct
{
	wifiEvent event;
	wifiStatus status;
} wifi_setting_t;

typedef struct
{
	u8 name[20];
	u8 password[20];
} wifi_data_t;

extern wifiStatus bit_wifi_status;
extern u8 wifi_list[20][40];
extern wifi_data_t wifi_data;
//用户配置参数
extern const u8* http_portnum;			//连接端口
extern const u8* http_wifista_ip;        //连接的服务器IP地址
extern const u8* mqtt_portnum;		//mqtt连接端口
extern const u8* mqtt_wifista_ip;   //mqtt连接的服务器IP地址

void usr_c322_led_init(void);
void usr_c322_at_response(u8 mode);
u8* usr_c322_check_cmd(u8 *str);
wifiStatus usr_c322_send_cmd(u8 *cmd,u8 *ack,u16 waittime);
wifiStatus usr_c322_quit_trans(void);

wifiStatus usr_c322_init(void);	        									 //初始化WIFI模块函数
wifiStatus usr_c322_hdu_login(u8 *userName, u8 *pwd);                                     
wifiStatus usr_c322_wifista_connect(u8* wifista_ssid,u8* wifista_password);  //更改WIFI函数
wifiStatus usr_c322_wifista_HTTP_request(u8* request);         			
void usr_c322_wifista_scan_parse(void);                                      
wifiStatus usr_c322_change_ip(const u8* wifista_ip,const u8* portnum);
wifiStatus usr_c322_wifista_scan(void);
wifiStatus usr_c322_waiting_restart(void);
wifiStatus usr_c322_check_ping(void);
wifiStatus usr_c322_check_tcp_connect(void);
wifiStatus usr_c322_socket_operation(enum socketName name, enum socketOperation operation);
#endif





