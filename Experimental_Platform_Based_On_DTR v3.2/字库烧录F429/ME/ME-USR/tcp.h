#ifndef __TCP_H
#define __TCP_H
#include "stm32f4xx.h"
#include "redirprintf.h"
#include "delay.h"	
#include "string.h"    
#include "usart2.h" 
 
#define verification 0x01
#define  sendgrade   0x02
#define  sendfile    0x03



void usr_tcp232_at_response(u8 mode);
u8 *usr_tcp232_check_cmd(u8 *str);
u8 usr_tcp232_send_cmd1(u8 *cmd,u8 *ack,u16 waittime);
u8 usr_tcp232_send_Gradedata(u8* id,u8* table,u8 *grade);
u8 usr_tcp232_send_Verdata(u8* id,u8* table);
u8 usr_tcp232_send_file(u8* id,u8* filename,u8* content);
u8 usr_tcp232_getdata(u8 *p);

#endif
