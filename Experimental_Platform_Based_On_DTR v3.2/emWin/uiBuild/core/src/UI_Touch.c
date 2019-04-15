#include "bsp.h"
#include "uiBuild.h"
#include "app_exp_routine.h"

coord_t coordAtLastDetect;
coord_t coordAtPresent;
coord_t coordAtRelease;

const area_t touch_validated_area[9] = {
	{0, 123, 0 + 126, 123 + 85},
	{0, 208, 0 + 126, 208 + 50},
	{0, 258, 0 + 126, 258 + 50},
	{0, 308, 0 + 126, 308 + 50},
	{159, 124, 159 + 203, 124 + 80},
	{159, 206, 159 + 203, 206 + 80},
	{159, 292, 159 + 203, 292 + 80},
	{510, 310, 510 + 144, 310 + 50},
	{363, 385, 363 + 432, 385 + 84}
};
int present_touch_area = 1;
int ex_touch_area = 1;


void trigger_virtual_touch_process(int x, int y, int trigger_time)
{
	touch.status = TP_PRESSED;
	touch.touch_number = 1;
	touch.coordXY[0].x = x;
	touch.coordXY[0].y = y;
	GUI_Delay(trigger_time);
	touch.status = TP_NOT_PRESSED;
}

static int get_touch_area()
{
	int i;
	for(i = 0; i < 9; i++) {
		if(coordAtLastDetect.x > touch_validated_area[i].x0 && coordAtLastDetect.x < touch_validated_area[i].x1 && coordAtLastDetect.y > touch_validated_area[i].y0 && coordAtLastDetect.y < touch_validated_area[i].y1)
			return i + 1;
	}
	return 0;
}

gesture_t get_gesture()
{
	gesture_t gestureAtPresent;
	static uint8_t ex_touch_status;

	touch.scan();
	if(TP_PRESSED == touch.status) {
		coordAtLastDetect.x = touch.coordXY[0].x;
		coordAtLastDetect.y = touch.coordXY[0].y;
	}
	while(TP_PRESSED == touch.status) {
		ex_touch_status = touch.status;
		touch.scan();
		coordAtPresent.x = touch.coordXY[0].x;
		coordAtPresent.y = touch.coordXY[0].y;

		coordAtLastDetect.x = coordAtPresent.x;
		coordAtLastDetect.y = coordAtPresent.y;
		vTaskDelay(5);
	}

	if(TP_NOT_PRESSED == touch.status) {
		if(TP_PRESSED == ex_touch_status && gestureAtPresent != slide)
			gestureAtPresent = release;
		coordAtPresent.x = 0;
		coordAtPresent.y = 0;
		ex_touch_status = TP_NOT_PRESSED;
	}

	return gestureAtPresent;
}

void ui_action()
{
	if(get_gesture() == release) {
		if(WM_IsVisible(keyboard.hWin))
			return;
		else {
			present_touch_area = get_touch_area();
			if(present_touch_area >= 1 && present_touch_area <= 4) {
				present_bar_status = present_touch_area;
				bar_highlight_slide(ex_bar_status, present_bar_status);
				if(present_bar_status != ex_bar_status) {
					if(ex_bar_status == ACTION_EXP_SCORE)
						routine.flags.flagTeacherLogin = flag_reset;
					if(!((present_bar_status == ACTION_EXP_DETAIL && ex_bar_status == ACTION_EXP_SCORE) || (present_bar_status == ACTION_EXP_SCORE && ex_bar_status == ACTION_EXP_DETAIL)))
						menu_reconstruct_bar_content(present_bar_status);
					menu_reconstruct_list_content(present_bar_status, present_list_status);
                                        if(!((present_bar_status == ACTION_EXP_DETAIL && ex_bar_status == ACTION_EXP_SCORE) || (present_bar_status == ACTION_EXP_SCORE && ex_bar_status == ACTION_EXP_DETAIL)))
                                                ex_list_status = 1;
				}

				ex_bar_status = present_bar_status;

			} else if(present_touch_area >= 5 && present_touch_area <= 7) {
				present_list_status = present_touch_area - 4;
				list_highlight_slide(ex_list_status, present_list_status);
				if(present_list_status != ex_list_status)
					menu_reconstruct_list_content(present_bar_status, present_list_status);
				ex_list_status = present_list_status;
			}
			ex_touch_area = present_touch_area;
		}
	}
}















