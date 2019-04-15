#include "ep_app.h"

u8 wifi_list[20][40];
wifiStatus bit_wifi_status = WIFI_ERR;
wifi_data_t wifi_data;

wifiStatus usr_c322_hdu_login(u8 *userName, u8 *pwd)
{
	u8 p[100];
	wifiStatus tem = 0;
	wifiStatus wifiRetVal;
	memset(p, 0, sizeof(p));
	usr_c322_quit_trans();
	wifiRetVal = usr_c322_socket_operation(socketA, socketOFF);
	if(wifiRetVal == WIFI_OK) {
		wifiRetVal = usr_c322_socket_operation(socketB, socketON);
		if(wifiRetVal == WIFI_OK) {
			usr_c322_send_cmd("AT+ENTM\r\n", "+OK", 20);
			usr_c322_send_cmd("POST /ac_portal/login.php HTTP/1.1\r\n", "", 20);
			usr_c322_send_cmd("Host: 2.2.2.2\r\n", "", 20);
			usr_c322_send_cmd("Connection: keep-alive\r\n", "", 20);
			usr_c322_send_cmd("Content-Length: 61\r\n", "", 20);
			usr_c322_send_cmd("Content-Type: application/x-www-form-urlencoded; charset=UTF-8\r\n", "", 20);
			usr_c322_send_cmd("\r\n", "", 20);
			sprintf((char *)p, "opr=pwdLogin&userName=%s&pwd=%s&rememberPwd=0\r\n", userName, pwd);
			wifiRetVal = usr_c322_send_cmd(p, "success", 20);
			usr_c322_quit_trans();
			if(usr_c322_socket_operation(socketB, socketOFF) == WIFI_OK)
				usr_c322_socket_operation(socketA, socketON);
		} 
		else;
	}
	else;
	return wifiRetVal;
}

wifiStatus usr_c322_init(void)
{
	u8 res, i = 0;
	u8 p[75];
	while(Nready && i < 3) { 		//等待Nready引脚拉低
		bsp_delay_ms(1000);
		i ++;
	}
	usr_c322_quit_trans();

	usr_c322_send_cmd("AT+WMODE=STA\r\n", "+OK", 20);
	usr_c322_send_cmd("AT+WKMOD=TRANS\r\n","+OK",20);
	usr_c322_send_cmd("AT+WKMOD1=TRANS\r\n","+OK",20);
	memset(p, 0, sizeof(p));
	sprintf((char*)p, "AT+SOCKA=TCPC,%s,%s\r\n", http_wifista_ip, http_portnum);
	usr_c322_send_cmd(p, "+OK", 20);
	usr_c322_send_cmd("AT+SOCKB=TCPC,2.2.2.2,80\r\n", "+OK", 20);
	memset(p, 0, sizeof(p));
	sprintf((char*)p, "AT+SOCKA1=TCPC,%s,%s\r\n", mqtt_wifista_ip, mqtt_portnum);
	usr_c322_send_cmd(p, "+OK", 20);
	usr_c322_send_cmd("AT+Z\r\n", "+OK", 20);
	return usr_c322_waiting_restart();
}

wifiStatus usr_c322_change_ip(const u8* wifista_ip, const u8* portnum)
{
	u8 p[75];
	usr_c322_quit_trans();
	sprintf((char*)p, "AT+SOCKA=TCPC,%s,%s\r\n", wifista_ip, portnum);
	usr_c322_send_cmd(p, "+OK", 20);
	usr_c322_send_cmd("AT+Z\r\n", "+OK", 20);
	return usr_c322_waiting_restart();
}

wifiStatus usr_c322_wifista_connect(u8* wifista_ssid, u8* wifista_password)
{
	u8 p[75];
	usr_c322_quit_trans();
	memset(p, 0, sizeof(p));

	sprintf((char*)p, "AT+WSTA=%s,%s\r\n", wifista_ssid, wifista_password);
	usr_c322_send_cmd(p, "+OK", 20);
	usr_c322_send_cmd("AT+Z\r\n", "+OK", 20);
	return usr_c322_waiting_restart();
}

wifiStatus usr_c322_wifista_HTTP_request(u8* request)
{
	u8 p[200];
	memset(p, 0, sizeof(p));
	sprintf((char*)p, "GET %s\r\n", request);   
	if(usr_c322_send_cmd(p, "successFlg", 200) == WIFI_OK)
		return WIFI_OK;
	else if(usr_c322_send_cmd(p, "+ERR", 50) == WIFI_OK) {
		usr_c322_send_cmd("AT+ENTM\r\n", "+OK", 20);
		if(usr_c322_send_cmd(p, "successFlg", 100) == WIFI_OK)
			return WIFI_OK;
		else
			return WIFI_ERR;
	} else;
}

wifiStatus usr_c322_wifista_scan()
{
	u8 i, j;
	wifiStatus res;
	for(i = 0; i < 13; i++) {
		for(j = 0; j < 20; j++)
			wifi_list[i][j] = 0;
	}
	usr_c322_quit_trans();
	res = usr_c322_send_cmd("AT+WSCAN\r\n", "+OK", 500);
	usr_c322_wifista_scan_parse();
	usr_c322_send_cmd("AT+ENTM\r\n", "+OK", 50);
	return res;
}

void usr_c322_wifista_scan_parse()
{
	u8 times;
	u8 *str = NULL;
	u8 WifiNameChineseFlag = 0;
	u8 WifiNameIndex = 1;
	u8 WifiNumber = 0;
	str = usr_c322_check_cmd("INDICATOR") + 9;
	
	while('\r' != *str)
	{
		if('\n' == *str)
		{
			str += 2;
			while(',' != *str && WifiNameIndex <20)
			{
				if(WifiNameChineseFlag == 0) {
					if((*str >= ' ') && (*str <= '~')) {
						wifi_list[WifiNumber][WifiNameIndex] = *str;
						WifiNameIndex ++;
					} else
						WifiNameChineseFlag = 1;
				}
				str ++;
			}
			str ++;
			while(',' != *str)
				str ++;
			str ++;
			if('O' != *str)							//??????
				wifi_list[WifiNumber][0] = '1';     //??
			else
				wifi_list[WifiNumber][0] = '0';     //OPEN,???
			
			if((WifiNameChineseFlag == 1) || (0 == strcmp((const char *)&wifi_list[WifiNumber][1], ""))) {  //剔除中文WiFi和无名WiFi
				memset(wifi_list[WifiNumber], 0, sizeof(wifi_list[WifiNumber]));
				WifiNumber --;
			}
			for(times = 0; times < WifiNumber; times++)	{					//剔除相同的WIFI
				if(0 == strcmp((const char *)&wifi_list[WifiNumber][1], (const char *)&wifi_list[times][1])) {
					memset(wifi_list[WifiNumber], 0, sizeof(wifi_list[WifiNumber]));
					WifiNumber --;
					break;
				}
			}
			
			WifiNumber ++;
			WifiNameIndex = 1;
			WifiNameChineseFlag = 0;
		}
		if(WifiNumber > 20)
			return;
		str ++;
	}
}


