#include "bsp.h"

#if	(__USE_DRIVER_TOUCH)

coord_struct_type coordXY_raw[6];

static GUI_PID_STATE State = {0};

static uint8_t init(void);
static uint8_t scan(void);

bsp_touch_struct touch = {
	TP_NOT_PRESSED,
	0,
	{ {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0} },

	init,
	scan

};

static uint8_t init()
{
	switch(lcd.id) {
	case 0x5510 :
		return GT9147_Init();

	default:
		return 0;
	}
}

static uint8_t scan()
{
	uint8_t	i;
	uint16_t temp;
	static uint8_t	touch_sta_old = 0;

	switch(lcd.id) {
	case 0x5510 :
		GT9147_Scan();
		break;

	default:
		break;
	}

	for (i = 0; i < touch.touch_number; i++) {

		touch.coordXY[i].x = LCD_HOR_RESOLUTION - coordXY_raw[i].x;
		touch.coordXY[i].y = coordXY_raw[i].y;

	}

	State.x = touch.coordXY[0].x;
	State.y = touch.coordXY[0].y;

	State.Pressed = touch.status;
	GUI_PID_StoreState(&State);
	touch_sta_old = touch.status;

	return touch.status;

}

#endif
