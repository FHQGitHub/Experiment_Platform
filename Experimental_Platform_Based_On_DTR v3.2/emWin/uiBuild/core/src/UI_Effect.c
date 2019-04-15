#include "uiBuild.h"

ui_effect_t ui_effect;

static long rgb_to_RGB565(int r, int g, int b)
{
	return (long)((r >> 3 << 3 << 16) + (g >> 2 << 2 << 8) + (b >> 3 << 3));
}

static void switch_bar_higlight_area(dir_t dir)
{
	int i;

	if(dir_up == dir) {
		for(i = 0; i < 9; i++) {
			WM_MoveWindow(hBarWin, 0, -6);
			GUI_Delay(10);
		}
	} else {
		for(i = 0; i < 9; i++) {
			WM_MoveWindow(hBarWin, 0, 6);
			GUI_Delay(10);
		}
	}
}

static void switch_list_higlight_area(dir_t dir)
{
	int i;

	if(dir_up == dir) {
		for(i = 0; i < 10; i++) {
			WM_MoveWindow(hListWin, 0, -8);
			GUI_Delay(10);
		}
		WM_MoveWindow(hListWin, 0, -2);
	} else {
		for(i = 0; i < 10; i++) {
			WM_MoveWindow(hListWin, 0, 8);
			GUI_Delay(10);
		}
		WM_MoveWindow(hListWin, 0, 2);
	}
}

void list_content_slide(dir_t dir)
{
	int i;
	int partial_r_highlight = (212 - 143) / 10, partial_g_highlight = (242 - 145) / 10, partial_b_highlight = (249 - 147) / 10;
	int partial_r_normal = (249 - 143) / 10, partial_g_normal = (252 - 145) / 10, partial_b_normal = (255 - 147) / 10;
	if(dir_shallow == dir) {
		for(i = 0; i < 10; i++) {
			TEXT_SetTextColor(hSubListTitle1, rgb_to_RGB565(143 + partial_r_highlight * i, 145 + partial_g_highlight * i, 147 + partial_b_highlight * i));
			TEXT_SetTextColor(hSubListContent1, rgb_to_RGB565(143 + partial_r_highlight * i, 145 + partial_g_highlight * i, 147 + partial_b_highlight * i));
			TEXT_SetTextColor(hSubListTitle2, rgb_to_RGB565(143 + partial_r_normal * i, 145 + partial_g_normal * i, 147 + partial_b_normal * i));
			TEXT_SetTextColor(hSubListContent2, rgb_to_RGB565(143 + partial_r_normal * i, 145 + partial_g_normal * i, 147 + partial_b_normal * i));
			TEXT_SetTextColor(hSubListTitle3, rgb_to_RGB565(143 + partial_r_normal * i, 145 + partial_g_normal * i, 147 + partial_b_normal * i));
			TEXT_SetTextColor(hSubListContent3, rgb_to_RGB565(143 + partial_r_normal * i, 145 + partial_g_normal * i, 147 + partial_b_normal * i));
			GUI_Delay(10 + i * 2);

		}
		TEXT_SetTextColor(hSubListTitle1, 0x00F9F2D4);
		TEXT_SetTextColor(hSubListContent1, 0x00F9F2D4);
		TEXT_SetTextColor(hSubListTitle2, 0x00FFFCF9);
		TEXT_SetTextColor(hSubListContent2, 0x00FFFCF9);
		TEXT_SetTextColor(hSubListTitle3, 0x00FFFCF9);
		TEXT_SetTextColor(hSubListContent3, 0x00FFFCF9);

	} else {
		for(i = 0; i < 9; i++) {
			TEXT_SetTextColor(hSubListTitle1, rgb_to_RGB565(212 - partial_r_highlight * i, 242 - partial_g_highlight * i, 249 - partial_b_highlight * i));
			TEXT_SetTextColor(hSubListContent1, rgb_to_RGB565(212 - partial_r_highlight * i, 242 - partial_g_highlight * i, 249 - partial_b_highlight * i));
			TEXT_SetTextColor(hSubListTitle2, rgb_to_RGB565(249 - partial_r_normal * i, 252 - partial_g_normal * i, 255 - partial_b_normal * i));
			TEXT_SetTextColor(hSubListContent2, rgb_to_RGB565(249 - partial_r_normal * i, 252 - partial_g_normal * i, 255 - partial_b_normal * i));
			TEXT_SetTextColor(hSubListTitle3, rgb_to_RGB565(249 - partial_r_normal * i, 252 - partial_g_normal * i, 255 - partial_b_normal * i));
			TEXT_SetTextColor(hSubListContent3, rgb_to_RGB565(249 - partial_r_normal * i, 252 - partial_g_normal * i, 255 - partial_b_normal * i));
			GUI_Delay(10 + i * 2);
		}
		TEXT_SetTextColor(hSubListTitle1, 0x00868380);
		TEXT_SetTextColor(hSubListContent1, 0x00868380);
		TEXT_SetTextColor(hSubListTitle2, 0x00868380);
		TEXT_SetTextColor(hSubListContent2, 0x00868380);
		TEXT_SetTextColor(hSubListTitle3, 0x00868380);
		TEXT_SetTextColor(hSubListContent3, 0x00868380);
	}
}



void display_board_slide(WM_HWIN hWin, int position)
{
	int i;
	int raw_axis_x =  WM_GetWindowOrgX(hWin);
	int diff_x = (position - raw_axis_x) / 10;

	for(i = 0; i < 10; i ++) {
		WM_MoveWindow(hWin, diff_x, 0);
		GUI_Delay(5);
	}



}


void bar_highlight_slide(int from, int to)
{
	int diff = to - from;
	int i;

	if(diff < 0) {
		for(i = 0; i < -diff; i++)
			switch_bar_higlight_area(dir_up);
	}

	else  {
		for(i = 0; i < diff; i++)
			switch_bar_higlight_area(dir_down);
	}

}

void list_highlight_slide(int from, int to)
{
	int diff = to - from;
	int i;

	if(diff < 0) {
		for(i = 0; i < -diff; i++)
			switch_list_higlight_area(dir_up);
	}

	else  {
		for(i = 0; i < diff; i++)
			switch_list_higlight_area(dir_down);
	}

}

void common_win_slide(WM_HWIN hWin, dir_t dir, int pixels)
{
	int diff = pixels / 10;
	int i;

	if(dir == dir_left) {
		for(i = 0; i < 10; i++) {
			WM_MoveWindow(hWin, -diff, 0);
			GUI_Exec();
		}
	} else if(dir == dir_right) {
		for(i = 0; i < 10; i++) {
			WM_MoveWindow(hWin, -diff, 0);
			GUI_Exec();
		}
	} else if(dir == dir_up) {
		for(i = 0; i < 10; i++) {
			WM_MoveWindow(hWin, 0, -diff);
			GUI_Exec();
		}
	} else if(dir == dir_down) {
		for(i = 0; i < 10; i++) {
			WM_MoveWindow(hWin, 0, diff);
			GUI_Exec();
		}
	} else;
}

void element_bounce(WM_HWIN hElement, int times)
{
	int i, j;
	int scale_y = WM_GetWindowSizeY(hElement);
	int bounce_distance = scale_y / 8;

	for(i = 0; i < times; i++) {
		for(j = 0; j < bounce_distance; j++) {
			WM_MoveWindow(hElement, 0, -1);
			GUI_Delay(20 + j * 3);
		}
		GUI_Delay(50);
		for(j = 0; j < bounce_distance; j++) {
			WM_MoveWindow(hElement, 0, 1);
			GUI_Delay(20 + j * 3);
		}
	}
}

void notify_show(char *notify_text1, char *notify_text2)
{
	TEXT_SetText(hNotifyText1, notify_text1);
	TEXT_SetText(hNotifyText2, notify_text2);
	WM_ShowWindow(hNotifyWindow);
	WM_BringToTop(hNotifyWindow);
	GUI_Delay(2000);
	WM_HideWindow(hNotifyWindow);
}










