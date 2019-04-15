#ifndef __MODULE_shell
#define __MODULE_shell

#include "driver.h"

#define CMD_MAX_SIZE            50
#define CMD_MAX_LINE            10

typedef struct actions_type{
        
        /*ָ�����ƣ�����ָ��ʶ���ƥ��*/
        char                    *action_name;
        /*ָ�����*/
        void                    (*handle)(char *content);
        struct actions_type     *next;
}actions_t;

typedef struct {
        /*��ǰָ��*/
        char            *this_cmd;
        /*��һ��ָ��(δ�õ�)*/
        char            *next_cmd;
        /*�ַ��豸����*/
        chr_dev_t       dev;
        /*ָ�����*/
        actions_t       *actions;
}shell_t;
        
int shell_init(void);
int require_actions(char * act_name, void (*action)(char *content));
int shell_main(void);

#endif
