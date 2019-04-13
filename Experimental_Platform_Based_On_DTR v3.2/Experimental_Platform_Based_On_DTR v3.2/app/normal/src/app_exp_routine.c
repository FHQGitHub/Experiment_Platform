#include "ep_app.h"

exp_routine_t routine;

char test_id_list[8][9] = {
        "16041531",
        "16041532",
        "16041533",
        "16041534",
        "16041535",
        "16041536",
        "16041537",
        "16041538",
};

void expGetRoutineContents()
{
        strcpy(routine.main_exp.mainExpName, "实验一");
        
        strcpy(routine.main_exp.sub_exp[0].subExpName, "实验原理");
        strcpy(routine.main_exp.sub_exp[0].subExpDetail, "编码器和译码器都是常用的组合逻辑电路");
        
        strcpy(routine.main_exp.sub_exp[1].subExpName, "病房优先呼叫器");
        strcpy(routine.main_exp.sub_exp[1].subExpDetail, "有3个病房,每一个病房有一个按键");
        
        strcpy(routine.main_exp.sub_exp[2].subExpName, "用译码器实现多输出函数");
        strcpy(routine.main_exp.sub_exp[2].subExpDetail, "用1片74LS138和1片74LS20设计");
}

void expRoutineFlagSet(int routine_flags, int state)
{
        switch(routine_flags) {
        case FLAG_EXP_START :
                if(1 == state)
                        routine.flags.flagExpStart = flag_set;
                else
                        routine.flags.flagExpStart = flag_reset;
        break;
        
        case FLAG_STUDENT_LOGIN :
                if(1 == state)
                        routine.flags.flagStudentLogin = flag_set;
                else
                        routine.flags.flagStudentLogin = flag_reset;
        break;
        
        case FLAG_TEACHER_LOGIN :
                if(1 == state)
                        routine.flags.flagTeacherLogin = flag_set;
                else
                        routine.flags.flagTeacherLogin = flag_reset;
        break;
        
        case FLAG_QUESTION_SET :
                if(1 == state)
                        routine.flags.flagQuestionSet = flag_set;
                else
                        routine.flags.flagQuestionSet = flag_reset;
        break;
        }
        xTaskNotify(MenuTask_Handler, (uint32_t)(&ui_effect), eNoAction);
        
}
        