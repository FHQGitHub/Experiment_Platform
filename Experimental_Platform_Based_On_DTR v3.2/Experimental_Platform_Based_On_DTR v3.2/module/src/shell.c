#include "shell.h"

char *cmd = "* receive {result:1,userId:XXXXXXXXX} 2019.1.13 15:45:46";
char *cmd2 = "@ start {result:1,userId:XXXXXXXXX} 2019.1.13 15:45:46";
shell_t cmd_shell;


/**
* @函数名：	shell_hw_init
* @函数功能：	初始化解释器相关内存
* @参数：       %NUL
* @返回值：	
*               (int) 初始化状态
**/
static int shell_hw_init()
{
        if(NULL == cmd_shell.dev.buffer)
                return -1;
        cmd_shell.this_cmd = calloc(sizeof(char), CMD_MAX_SIZE);
        if(NULL == cmd_shell.this_cmd)
                return -1;
        cmd_shell.next_cmd = calloc(sizeof(char), CMD_MAX_SIZE);
        if(NULL == cmd_shell.next_cmd)
                return -1;
        return 0;
}

/**
* @函数名：	shell_read
* @函数功能：	读取
* @参数：       
*               s -读出数据存放地址
*               n -读取长度
* @返回值：	
*               (int)实际读取长度
**/
static int shell_read(char *s, int n)
{
        /*实现读取函数*/
        /*下面是一个测试用例*/
        strcpy(s, cmd2);
        return strlen(cmd);
}

/**
* @函数名：	shell_write
* @函数功能：	写入
* @参数：       
*               s -写入数据存放地址
*               n -写入长度
* @返回值：	
*               (int)实际写入长度
**/
static int shell_write(char *s, int n)
{
        /*实现写入函数*/
        /*未用到可作空函数处理*/
        return 0;
}

/*file_opreation注册*/
f_ops_t shell_operatons = {
        .read = shell_read,
        .write = shell_write
};

/**
* @函数名：	shell_init
* @函数功能：	初始化解释器
* @参数：       %NUL
* @返回值：	
*               (int)初始化状态
**/
int shell_init()
{
        /*注册解释器设备*/
        chr_dev_register(&cmd_shell.dev, &shell_operatons, CMD_MAX_SIZE * CMD_MAX_LINE);
        return shell_hw_init();
}

/**
* @函数名：	require_actions
* @函数功能：	新增命令
* @参数：
*               act_name -命令名称
*               action(char *content) - 命令处理句柄
* @返回值：	
*               (int)新增状态
**/
int require_actions(char * act_name, void (*action)(char *content))
{
        actions_t *action_node = NULL;
        actions_t *list_index = NULL;
        
        if(NULL == action || NULL == act_name)
                return -1;
        if(NULL == cmd_shell.actions) {
                cmd_shell.actions = calloc(sizeof(actions_t), 1);
                if(NULL == cmd_shell.actions)
                        return -1;
                cmd_shell.actions->action_name = calloc(sizeof(char), strlen(act_name));
                if(NULL == cmd_shell.actions->action_name)
                        return -1;
                strncpy(cmd_shell.actions->action_name , act_name, strlen(act_name));
                cmd_shell.actions->handle = action;
        }
        else {
                
                for(list_index = cmd_shell.actions; list_index->next != NULL; list_index = list_index->next);
                
                action_node = calloc(sizeof(actions_t), 1);
                if(NULL == action_node)
                        return -1;
                action_node->action_name = calloc(sizeof(char), strlen(act_name));
                if(NULL == action_node->action_name)
                        return -1;
                strncpy(action_node->action_name , act_name, strlen(act_name));
                action_node->handle = action;
                list_index->next = action_node;
        }
        
        return 0;
}

/**
* @函数名：	shell_main
* @函数功能：	解释器主循环
* @参数：       %NUL
* @返回值：	
*               (int)当前处理状态
**/
int shell_main()
{
        char sign = 0;
        char *index_head = NULL;
        char *index_tail = NULL;
        char head[CMD_MAX_SIZE];
        char content[CMD_MAX_SIZE];
        int i = 1;
        actions_t *action_index = cmd_shell.actions;
        
        if(NULL == cmd_shell.actions)
                return -1;
        if(cmd_shell.dev.ops->read(cmd_shell.dev.buffer, CMD_MAX_SIZE) > 0) {
                memset(head, 0, sizeof(head));
                memset(content, 0, sizeof(content));
                if(NULL == cmd_shell.this_cmd)
                        return -1;
                strncpy(cmd_shell.this_cmd, cmd_shell.dev.buffer, strlen(cmd_shell.dev.buffer));
                sign = *cmd_shell.this_cmd;
                switch(sign) {
                case '#' :
                        break;
                case '@' :
                        break;
                case '*' :
                        break;
                default :
                        break;
                }
                index_head = cmd_shell.this_cmd + 2;
                index_tail = strstr(index_head, " ");
                strncpy(head, index_head, index_tail - index_head);
                while(NULL != action_index) {
                       if(!strcmp(head, action_index->action_name))
                               break;
                        action_index = action_index->next;
                        ++i;
                }
                if(NULL == action_index)
                        return 0;
                index_head = index_tail + 1;
                strncpy(content, index_head, strlen(index_head));
                cmd_shell.actions->handle(content);
                return i;
        }
        
        return 0;
}
                
                





