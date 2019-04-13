#include "testBox.h"	


//获得实验数据函数
//res：期望的响应
//返回值：0：没有得到期望的响应
//        否则返回匹配字符串首地址
u8* GetTestData(u8 *res)
{
    char* strx=0;
	u8 waittime=50;
	u5_printf("send\r\n");
	while(--waittime)	//等待倒计时
	{
		delay_xms(10);
		if(UART5_RX_STA&0X8000)//接收到期待的应答结果
		{
			strx=strstr((const char*)UART5_RX_BUF,(const char*)res);
			UART5_RX_STA=0;
			break;
		}
	}
	return (u8*)strx;
}










