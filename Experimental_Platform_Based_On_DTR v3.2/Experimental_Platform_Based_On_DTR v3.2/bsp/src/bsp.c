#include "bsp.h"

notify_type_struct timer6_notify = {0, 0, 0};
system_time_type_struct system_time = {
	.msec = 0,
	.sec = 0,
	.min = 0,
	.hour = 0,
	.day = 1,
	.month = 1,
	.year = 1970
};

void timer6CallBack()
{
	timer6_notify.count_down_per_sec ++;
	timer6_notify.standby_per_min ++;
	timer6_notify.touch_resume_per_sec ++;

	system_time.msec += 50;
	if(system_time.msec >= 1000) {
		system_time.msec = 0;
		system_time.sec ++;
		if(60 == system_time.sec) {
			system_time.sec = 0;
			system_time.min ++;
			if(60 == system_time.min) {
				system_time.min = 0;
				system_time.hour ++;
				if(24 == system_time.hour) {
					system_time.hour = 0;
					system_time.day ++;
					if(30 == system_time.day) {
						system_time.day = 0;
						system_time.month ++;
						if(12 == system_time.month) {
							system_time.month = 0;
							system_time.year ++;
						}
					}
				}
			}
		}
	}
}

void bsp_Init()
{
	bsp_systick_init();
	oop_init();
	hbl_init();

	EXTIX_Init();
	SPI_FLASH_Init();

	uart.init(UART_1 | UART_5, 9600);
	uart.init(UART_2 | UART_3 | UART_4, 115200);
	timer.oop(timer.timer_6).install_handler(timer6CallBack);
	timer.init(TIMER_6 | TIMER_7, MS(50));
	lcd.init();
	touch.init();
	InitRc522();
}

void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
	//uart.oop(uart.uart_1).write_line("Stack Overflow @ %s", pcTaskName);
}

