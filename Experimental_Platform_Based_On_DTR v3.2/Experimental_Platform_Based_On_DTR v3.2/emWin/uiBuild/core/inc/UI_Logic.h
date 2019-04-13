#ifndef __UI_LOGIC_H
#define __UI_LOGIC_H

#include "GUI.h"
#include "DIALOG.h"
#include "WM.h"

#define menu_list_element_for_each(pos, head)                           for (pos = (head->next); pos != NULL; pos = pos->next)
#define element_list_of(bar_index, list_index)                          (&(menu.bar[bar_index - 1].subList[list_index - 1].elements))


typedef enum{
        element_visible,
        element_invisible,
}element_state_t;

typedef enum{
        element_win,
        element_text,
        element_button,
        element_image,
        element_edit
}element_type_t;

typedef struct list_element {
        WM_HWIN                 hAttachWin;
        element_state_t         state;
        element_type_t          type;
        void                    *element_data;
        int                     data_size;
        struct list_element     *next;
}list_element_t;

typedef struct {
        WM_HWIN hContentWin;
        list_element_t elements;
}list_content_t;
       
typedef struct {
        char pStrBarName[10];
        list_content_t  subList[3];
}side_bar_t;

typedef struct {
        side_bar_t bar[4];
}menu_t;

extern menu_t menu;
extern int present_bar_status;
extern int ex_bar_status;
extern int present_list_status;
extern int ex_list_status;

void menu_list_element_set_visible(int bar_index, int list_index, WM_HWIN hWin, int state);
void menu_list_element_set_data(int bar_index, int list_index, WM_HWIN hWin, void *edata);
void menu_list_element_roleplay(void);
void menu_reconstruct_bar_content(int bar_index);
void menu_reconstruct_list_content(int bar_index, int list_index);
void menu_init(void);

        
#endif
