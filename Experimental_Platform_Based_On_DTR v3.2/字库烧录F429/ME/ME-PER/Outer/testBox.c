#include "testBox.h"	


//���ʵ�����ݺ���
//res����������Ӧ
//����ֵ��0��û�еõ���������Ӧ
//        ���򷵻�ƥ���ַ����׵�ַ
u8* GetTestData(u8 *res)
{
    char* strx=0;
	u8 waittime=50;
	u5_printf("send\r\n");
	while(--waittime)	//�ȴ�����ʱ
	{
		delay_xms(10);
		if(UART5_RX_STA&0X8000)//���յ��ڴ���Ӧ����
		{
			strx=strstr((const char*)UART5_RX_BUF,(const char*)res);
			UART5_RX_STA=0;
			break;
		}
	}
	return (u8*)strx;
}










