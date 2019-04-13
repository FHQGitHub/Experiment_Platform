#ifndef __MODULE_shell
#define __MODULE_shell

#include "driver.h"

#define CMD_MAX_SIZE            50
#define CMD_MAX_LINE            10

typedef struct actions_type{
        
        /*指令名称，用于指令识别和匹配*/
        char                    *action_name;
        /*指令处理函数*/
        void                    (*handle)(char *content);
        struct actions_type     *next;
}actions_t;

typedef struct {
        /*当前指令*/
        char            *this_cmd;
        /*下一条指令(未用到)*/
        char            *next_cmd;
        /*字符设备类型*/
        chr_dev_t       dev;
        /*指令操作*/
        actions_t       *actions;
}shell_t;
        
int shell_init(void);
int require_actions(char * act_name, void (*action)(char *content));
int shell_main(void);

#endif
