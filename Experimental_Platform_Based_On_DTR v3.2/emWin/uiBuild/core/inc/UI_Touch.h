#ifndef __UI_TOUCH_H
#define __UI_TOUCH_H

#define AREA_EXP_DETAIL         1
#define AREA_EXP_SOCRE          2
#define AREA_MAC_SETTINGS       3
#define AREA_MAC_INFO           4
#define AREA_SUBLIST_1          1
#define AREA_SUBLIST_2          2
#define AREA_SUBLIST_3          3
#define AREA_KNOWLEDGE          8


typedef enum {
        none = 0,
        press,
        release,
        slide
}gesture_t;

typedef enum {
        exp_detail = 1,
        exp_score,
        mac_settings,
        mac_info
}bar_status_t;

typedef enum {
        sublist_1 = 5,
        sublist_2,
        sublist_3,
}list_status_t;

typedef struct {
        int x;
        int y;
}coord_t;

typedef struct {
        int x0;
        int y0;
        int x1;
        int y1;
}area_t;

extern const area_t touch_validated_area[9];

void trigger_virtual_touch_process(int x, int y, int trigger_time);
gesture_t get_gesture(void);
void ui_action(void);


#endif
