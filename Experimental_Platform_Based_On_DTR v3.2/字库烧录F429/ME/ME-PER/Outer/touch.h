#ifndef _TOUCH_H
#define _TOUCH_H
#include "stm32f4xx.h"
#include "ott2001a.h"
#include "gt9147.h"
#include "ft5206.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//触摸屏驱动（支持ADS7843/7846/UH7843/7846/XPT2046/TSC2046/OTT2001A等） 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/7
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									   
//////////////////////////////////////////////////////////////////////////////////
#define TP_PRES_DOWN	0X80  //触屏被按下
#define TP_CATH_PRES	0X40  //有按键按下了

typedef struct
{
	u8 (*init)(void);  //初始化触摸屏
	u8 (*scan)(u8);		 //扫描触摸屏0,屏幕扫描;1,物理坐标
	void (*adjust)(void); //触摸屏校准
	u16 x[OTT_MAX_TOUCH];  //当前坐标
	u16 y[OTT_MAX_TOUCH];  //电容屏有最多5组坐标,电阻屏则为x[0],y[0]代表:此次扫描时,触摸屏的坐标用
												 //x[4],y[4]存储第一次按下时的坐标
	u8 sta;  	//笔的状态
						//b7:按下1/松开0; 
						//b6:0,没有按键按下;1,有按键按下. 
						//b5:保留
						//b4~b0:电容触摸屏按下的点数(0,表示未按下,1表示按下)
/////////////////////触摸屏校准参数(电容屏不需要校准)//////////////////////			
	float xfac;
	float yfac;
	float xoff;
	float yoff;
//新增的参数,当触摸屏的左右上下完全颠倒时需要用到.
//b0:0,竖屏(适合左右为X坐标,上下为Y坐标的TP)
//   1,横屏(适合左右为Y坐标,上下为X坐标的TP) 
//b1~6:保留.
//b7:0,电阻屏
//   1,电容屏 
	u8 touchtype;
}_m_tp_dev;

extern _m_tp_dev tp_dev; //触屏控制器在touch.c里面定义

//电阻屏芯片连接引脚
#define PEN		PFin(10)  	//T_PEN
#define DOUT	PFin(8) 	//T_MISO
#define TDIN	PFout(9) 	//T_MOSI
#define TCLK	PBout(1) 	//T_SCK
#define TCS		PBout(2) 	//T_CS

//电阻屏函数
void TP_Write_Byte(u8 num);						//向控制芯片写入一个数据
u16 TP_Read_AD(u8 CMD);							//读取AD转换值
u16 TP_Read_XOY(u8 xy);							//带滤波的坐标读取(X/Y)
u8 TP_Read_XY(u16 *x,u16 *y);					//双方向读取(X+Y)
u8 TP_Read_XY2(u16 *x,u16 *y);					//带加强滤波的双方向坐标读取
void TP_Drow_Touch_Point(u16 x,u16 y,u16 color);//画一个坐标校准点
void TP_Draw_Big_Point(u16 x,u16 y,u16 color);	//画一个大点
void TP_Save_Adjdata(void);						//保存校准参数
u8 TP_Get_Adjdata(void);						//读取校准参数
void TP_Adjust(void);							//触摸屏校准
void TP_Adj_Info_Show(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2,u16 x3,u16 y3,u16 fac);//显示校准信息
//电阻屏/电容屏 共用函数
u8 TP_Scan(u8 tp);								//扫描
u8 TP_Init(void);								//初始化
#endif

