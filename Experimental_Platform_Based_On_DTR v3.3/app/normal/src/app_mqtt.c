#include "ep_app.h"

u8 subscribeResponse[5];
const u8 connectResponse[] = {0x20, 0x02, 0x00, 0x00};    	 		
const u8 pingResponse[] = {0xd0, 0x00};

u8 GetDataFixedHead(unsigned char MesType, unsigned char DupFlag, unsigned char QosLevel, unsigned char Retain)
{
	unsigned char dat = 0;
	dat = (MesType & 0x0f) << 4;
	dat |= (DupFlag & 0x01) << 3;
	dat |= (QosLevel & 0x03) << 1;
	dat |= (Retain & 0x01);
	return dat;
}

/*
	获取连接的数据包正确连接的返回20 02 00 00
*/
u8 GetDataConnet(unsigned char *buff)
{
	unsigned int i, len, lennum = 0;
	unsigned char *msg;
	buff[0] = GetDataFixedHead(MQTT_TypeCONNECT, 0, 0, 0);
	buff[2] = 0x00;
	buff[3] = 0x04;
	buff[4] = 'M';
	buff[5] = 'Q';
	buff[6] = 'T';
	buff[7] = 'T';
	buff[8] = 0x04;// Protocol Level
	buff[9] = 0 | (MQTT_StaCleanSession << 1) | (MQTT_StaWillFlag << 1)
	          | (MQTT_StaWillQoS << 3) | (MQTT_StaWillRetain << 5)
	          |	(MQTT_StaPasswordFlag << 6) | (MQTT_StaUserNameFlag << 7);
	buff[10] = MQTT_KeepAlive >> 8;
	buff[11] = MQTT_KeepAlive;
	len = strlen(MQTT_ClientIdentifier);
	buff[12] = len >> 8;
	buff[13] = len;
	msg = MQTT_ClientIdentifier;
	for(i = 0; i < len; i++) {
		buff[14 + i] =  msg[i];
	}
	lennum += len;
	if(MQTT_StaWillFlag) {
		len = strlen(MQTT_WillTopic);
		buff[13 + lennum + 1] = len >> 8;
		buff[13 + lennum + 2] = len;
		lennum += 2;
		msg = MQTT_WillTopic;
		for(i = 0; i < len; i++) {
			buff[14 + lennum + i] =  msg[i];
		}
		lennum += len;
		len = strlen(MQTT_WillMessage);
		buff[12] = len >> 8;
		buff[13] = len;
		lennum += 2;
		msg = MQTT_WillMessage;
		for(i = 0; i < len; i++) {
			buff[14 + lennum + i] =  msg[i];
		}
		lennum += len;
	}
	if(MQTT_StaUserNameFlag) {
		len = strlen(MQTT_UserName);
		buff[13 + lennum + 1] = len >> 8;
		buff[13 + lennum + 2] = len;
		lennum += 2;
		msg = MQTT_UserName;
		for(i = 0; i < len; i++) {
			buff[14 + lennum + i] =  msg[i];
		}
		lennum += len;

	}
	if(MQTT_StaPasswordFlag) {
		len = strlen(MQTT_Password);
		buff[13 + lennum + 1] = len >> 8;
		buff[13 + lennum + 2] = len;
		lennum += 2;
		msg = MQTT_Password;
		for(i = 0; i < len; i++) {
			buff[14 + lennum + i] =  msg[i];
		}
		lennum += len;
	}
	buff[1] = 13 + lennum - 1;

	return buff[1] + 2;
}

/*
	获取断开连接的数据包
*/
void GetDataDisConnet(unsigned char *buff)
{
	buff[0] = 0xe0;
	buff[1] = 0;
}

/*
	心跳请求的数据包成功返回d0 00
*/
void GetDataPINGREQ(unsigned char *buff)
{
	buff[0] = 0xc0;
	buff[1] = 0;
}

/*
	订阅主题的数据包 Num:主题序号 RequestedQoS:服务质量要求0,1或2
*/
u8 GetDataSUBSCRIBE(unsigned char *buff, unsigned char *dat, unsigned int Num, unsigned char RequestedQoS)
{
	unsigned int i, len = 0, lennum = 0;
	buff[0] = 0x82;
	len = strlen(dat);
	buff[2] = Num >> 8;
	buff[3] = Num;
	buff[4] = len >> 8;
	buff[5] = len;
	for(i = 0; i < len; i++) {
		buff[6 + i] = dat[i];
	}
	lennum = len;
	buff[6 + lennum ] = RequestedQoS;
	buff[1] = lennum + 5;

	return buff[1] + 2;
}

/*
	订阅主题的响应数据包 Num:主题序号 RequestedQoS:服务质量要求0,1或2
*/
u8 GetDataSUBACK(unsigned char *buff, unsigned int Num, unsigned char RequestedQoS)
{
	buff[0] = GetDataFixedHead(MQTT_TypeSUBACK, 0, 0, 0);
	buff[1] = 3;
	buff[2] = Num >> 8;
	buff[3] = Num;
	buff[4] = RequestedQoS;
	
	return buff[1] + 2;
}

/*
	获取发布消息的数据包
*/
u8 GetDataPUBLISH(unsigned char *buff, unsigned char dup, unsigned char qos, unsigned char retain, const char *topic , const char *msg)
{
	unsigned int i, len = 0, lennum = 0;
	buff[0] = GetDataFixedHead(MQTT_TypePUBLISH, dup, qos, retain);
	len = strlen(topic);
	buff[2] = len >> 8;
	buff[3] = len;
	for(i = 0; i < len; i++) 
		buff[4 + i] = topic[i];
	lennum = len;
	len = strlen(msg);
	for(i = 0; i < len; i++) 
		buff[4 + i + lennum] = msg[i];
	lennum += len;
	buff[1] = lennum;

	return buff[1] + 2;
}
/*
	PUBLISH的响应数据包 Num:主题序号
*/
void usr_c322_wifista_mqtt_puback(unsigned int Num)
{
	u8 buff[4];
	buff[0] = GetDataFixedHead(MQTT_TypePUBACK, 0, 0, 0);
	buff[1] = 2;
	buff[2] = Num >> 8;
	buff[3] = Num;
	
	uart.oop(uart.uart_2).write_raw(buff, 4);
}

mqttStatus usr_c322_wifista_mqtt_connect()
{
	u8 len = 0;
	mqttStatus res;
	u8 waittime = 20;
	u8 mqttBuff[50];
	int strx;
	uart.uart_2->rx_status = 0;
	len = GetDataConnet(mqttBuff);
	uart.oop(uart.uart_2).write_raw(mqttBuff, len);
	while(--waittime) {
		bsp_delay_ms(100);
		if(uart.uart_2->rx_status & 0x8000) {
			strx = memcmp(uart.uart_2->pRx_buffer, connectResponse, 4);
			if(strx != 0) {
				res = MQTT_ERR;        //连接失败
				uart.uart_2->rx_status = 0;
			}
			else {
				res = MQTT_OK;		//连接成功
				uart.uart_2->rx_status = 0;
				break;
			}
		}
	}
	if(waittime == 0)
		res = MQTT_TIMEOUT;         //接收超时
	return res;
}

mqttStatus usr_c322_wifista_mqtt_subscribe(u8 *topic)
{
	u8 len = 0;
	mqttStatus res;
	u8 waittime = 20;
	u8 mqttBuff[100];
	int strx;
	uart.uart_2->rx_status = 0;
	len = GetDataSUBSCRIBE(mqttBuff, topic, 11, MQTT_MaxQoS);
	GetDataSUBACK(subscribeResponse, 11, MQTT_MaxQoS);
	uart.oop(uart.uart_2).write_raw(mqttBuff, len);
	while(--waittime) {
		bsp_delay_ms(100);
		if(uart.uart_2->rx_status & 0x8000) {
			strx = memcmp(uart.uart_2->pRx_buffer, subscribeResponse, 5);
			if(strx != 0) {
				res = MQTT_ERR;        //连接失败
				uart.uart_2->rx_status = 0;
			}
			else {
				res = MQTT_OK;		//连接成功
				if((uart.uart_2->rx_status & 0x0fff) <= 5)
					uart.uart_2->rx_status = 0;
				else;
				break;
			}
		}
	}
	if(waittime == 0)
		res = MQTT_TIMEOUT;         //接收超时
	return res;
}

mqttStatus usr_c322_wifista_mqtt_ping()
{
	u8 len = 0;
	mqttStatus res;
	u8 waittime = 20;
	u8 mqttBuff[50];
	int strx;
	uart.uart_2->rx_status = 0;
	GetDataPINGREQ(mqttBuff);
	uart.oop(uart.uart_2).write_raw(mqttBuff, 2);
	while(--waittime) {
		bsp_delay_ms(100);
		if(uart.uart_2->rx_status & 0x8000) {
			strx = memcmp(uart.uart_2->pRx_buffer, pingResponse, 2);
			if(strx != 0) {
				res = MQTT_ERR;        //连接失败
				uart.uart_2->rx_status = 0;
			}
			else {
				res = MQTT_OK;		//连接成功
				uart.uart_2->rx_status = 0;
				break;
			}
		}
	}
	if(waittime == 0)
		res = MQTT_TIMEOUT;         //接收超时
	return res;
}

mqttStatus usr_c322_wifista_mqtt_check(unsigned char *rcv_buff)
{
	u8 *str = rcv_buff;
	u16 topicLength = 0;
	u16 packetIdentifier = 0;
	mqttStatus mqttRetVal = MQTT_TIMEOUT;
	
	if(uart.uart_2->rx_status & 0x8000) {
		if((rcv_buff[0] & (~MQTT_PUBLISHWithoutRetain)) == 0x02) {
			topicLength = (str[2] << 8) | str[3];
			packetIdentifier = (str[topicLength + 4] << 8) | str[topicLength + 5];
			usr_c322_wifista_mqtt_puback(packetIdentifier);
			
			mqttRetVal = mqttParsePublish(&str[topicLength + 6]);
		}
		else if((rcv_buff[5] & (~MQTT_PUBLISHWithRetain)) == 0x02) {
			str = &rcv_buff[5];
			topicLength = (str[2] << 8) | str[3];
			packetIdentifier = (str[topicLength + 4] << 8) | str[topicLength + 5];
			usr_c322_wifista_mqtt_puback(packetIdentifier);
			
			mqttRetVal = mqttParsePublish(&str[topicLength + 6]);
		}
		else if(((rcv_buff[0] & (~MQTT_PUBLISHWithoutRetain)) == 0x00) || ((rcv_buff[5] & (~MQTT_PUBLISHWithRetain)) == 0x00)){
			topicLength = (str[2] << 8) | str[3];
			mqttRetVal = mqttParsePublish(&str[topicLength + 4]);
		}
		else
			mqttRetVal = MQTT_ERR;
		uart.uart_2->rx_status = 0;
	}
	else;
	return mqttRetVal;
}

mqttStatus mqttParsePublish(unsigned char *mqttDataBuff)
{
	JSON_Value *content;
	const char *event_type = NULL;
	
	char i;
	mqtt_rcv_info_t mqtt_rcv_info;
	wifi_config_t wifi_config;
	mqttStatus mqttRetVal;
	
	memset(&wifi_config, 0, sizeof(wifi_config));
	content = json_parse_string((char *)mqttDataBuff);
	
	if (content != NULL) {
		event_type = json_object_get_string(json_object(content), "type");
		if(0 == strcmp(event_type, "ExpStart")) {
			wifi_config.http_notify.event = http_get_appointment;
			if(errQUEUE_FULL == xQueueSend(xQueueWifi, (const void *)(&wifi_config), 50))
				notify_show("操作无效", "请稍后");
			
                        expRoutineFlagSet(FLAG_EXP_START, 1);
			mqttRetVal = MQTT_OK;
		}
		else if(0 == strcmp(event_type, "StudentLogin")) {
			routine.flags.flagStudentLogin = flag_set;
			menu_reconstruct_list_content(present_bar_status, present_list_status, 1);
			mqttRetVal = MQTT_OK;
		}
		else if(0 == strcmp(event_type, "SubExpStart")) {
			mqtt_rcv_info.moduleId = (int)json_object_get_number(json_object(content), "moduleId");
			for(i = 0; i < routine.main_exp.subExpNumber; i++) {
				if(mqtt_rcv_info.moduleId == routine.main_exp.sub_exp[i].moduleId) {
					routine.main_exp.sub_exp[i].status = exp_lasting;
					break;
				}
			}
			mqttRetVal = MQTT_OK;
		}
		else if(0 == strcmp(event_type, "SubExpSubmit")) {
			mqtt_rcv_info.moduleId = (int)json_object_get_number(json_object(content), "moduleId");
			mqtt_rcv_info.rank = (char)json_object_get_number(json_object(content), "rank");
			for(i = 0; i < routine.main_exp.subExpNumber; i++) {
				if(mqtt_rcv_info.moduleId == routine.main_exp.sub_exp[i].moduleId) {
					routine.main_exp.sub_exp[i].submitRank = mqtt_rcv_info.rank;
					routine.main_exp.sub_exp[i].status = exp_submitted;
					break;
				}
			}
			mqttRetVal = MQTT_OK;
		}
		else if(0 == strcmp(event_type, "SubExpFinish")) {
			mqtt_rcv_info.moduleId = (int)json_object_get_number(json_object(content), "moduleId");
			for(i = 0; i < routine.main_exp.subExpNumber; i++) {
				if(mqtt_rcv_info.moduleId == routine.main_exp.sub_exp[i].moduleId) {
					routine.main_exp.sub_exp[i].status = exp_finished;
					break;
				}
			}
			mqttRetVal = MQTT_OK;
		}
		else if(0 == strcmp(event_type, "QusetionSet")) {
			mqtt_rcv_info.moduleId = (int)json_object_get_number(json_object(content), "moduleId");
			mqtt_rcv_info.rank = (char)json_object_get_number(json_object(content), "rank");
			for(i = 0; i < routine.main_exp.subExpNumber; i++) {
				if(mqtt_rcv_info.moduleId == routine.main_exp.sub_exp[i].moduleId) {
					routine.main_exp.sub_exp[i].questionRank = mqtt_rcv_info.rank;
					break;
				}
			}
			routine.flags.flagQuestionSet = flag_set;
			mqttRetVal = MQTT_OK;
		}
		else if(0 == strcmp(event_type, "QusetionSolved")) {
			mqttRetVal = MQTT_OK;
		}
		else if(0 == strcmp(event_type, "AnswerRanking")) {
			mqtt_rcv_info.moduleId = (int)json_object_get_number(json_object(content), "moduleId");
			mqtt_rcv_info.rank = (char)json_object_get_number(json_object(content), "rank");
			for(i = 0; i < routine.main_exp.subExpNumber; i++) {
				if(mqtt_rcv_info.moduleId == routine.main_exp.sub_exp[i].moduleId) {
					routine.main_exp.sub_exp[i].questionRank = mqtt_rcv_info.rank;
					break;
				}
			}
			mqttRetVal = MQTT_OK;
		}
		else if(0 == strcmp(event_type, "MarkRanking")) {
			mqtt_rcv_info.moduleId = (int)json_object_get_number(json_object(content), "moduleId");
			mqtt_rcv_info.rank = (char)json_object_get_number(json_object(content), "rank");
			for(i = 0; i < routine.main_exp.subExpNumber; i++) {
				if(mqtt_rcv_info.moduleId == routine.main_exp.sub_exp[i].moduleId) {
					routine.main_exp.sub_exp[i].submitRank = mqtt_rcv_info.rank;
					break;
				}
			}
			mqttRetVal = MQTT_OK;
		}
		else if(0 == strcmp(event_type, "ExpEnd")) {
			mqttRetVal = MQTT_OK;
		}
		else
			mqttRetVal = MQTT_ERR;
	}
	else
		mqttRetVal = MQTT_ERR;
	json_value_free(content);
	return mqttRetVal;
}

mqttStatus usr_c322_wifista_mqtt_init()
{
	mqttStatus mqttRetVal;
	mqttRetVal = usr_c322_wifista_mqtt_connect();
	if(MQTT_OK == mqttRetVal)
		mqttRetVal = usr_c322_wifista_mqtt_ping();
	else;
	return mqttRetVal;
}

wifiStatus usr_c322_wifista_mqtt_restart()
{
	u8 i;
	wifiStatus wifiRetVal;
	usr_c322_quit_trans();
	wifiRetVal = usr_c322_socket_operation(socketA1, socketOFF);
	if(WIFI_OK == wifiRetVal)
		wifiRetVal = usr_c322_socket_operation(socketA1, socketON);
	else;
	usr_c322_send_cmd("AT+ENTM\r\n", "+OK", 20);
	return wifiRetVal;
}


