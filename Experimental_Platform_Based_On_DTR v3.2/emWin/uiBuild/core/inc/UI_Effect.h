#ifndef __UI_SLIDE_H
#define __UI_SLIDE_H

#include "WM.h"

typedef enum {
        dir_up = 0,
        dir_down,
        dir_left,
        dir_right,
        dir_shallow,
        dir_deep
}dir_t;

typedef enum {
        effect_start,
        effect_stop,
}effect_sta_t;

typedef struct {
        WM_HWIN hWin;
        effect_sta_t status;
}ui_effect_t;

extern ui_effect_t ui_effect;
        
void bar_highlight_slide(int from, int to);
void list_highlight_slide(int from, int to);
void list_content_slide(dir_t dir);
void display_board_slide(WM_HWIN hWin, int position);
void common_win_slide(WM_HWIN hWin, dir_t dir, int pixels);
void element_bounce(WM_HWIN hElement, int times);
void notify_show(char *notify_text1, char *notify_text2);

#endif
