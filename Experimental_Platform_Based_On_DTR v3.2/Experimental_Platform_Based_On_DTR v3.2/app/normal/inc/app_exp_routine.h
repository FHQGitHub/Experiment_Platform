#ifndef __EXP_ROUTINE_H
#define __EXP_ROUTINE_H

#define EXP_NOT_SCORED         (routine.main_exp.sub_exp[0].status == exp_submitted || \
                                routine.main_exp.sub_exp[1].status == exp_submitted || \
                                routine.main_exp.sub_exp[2].status == exp_submitted || \
                                routine.main_exp.sub_exp[0].status == exp_grading   || \
                                routine.main_exp.sub_exp[1].status == exp_grading   || \
                                routine.main_exp.sub_exp[2].status == exp_grading)
                                
#define EXP_NOT_FINISHED       ((routine.main_exp.sub_exp[0].status != exp_waiting && routine.main_exp.sub_exp[0].status != exp_finished) || \
                                (routine.main_exp.sub_exp[1].status != exp_waiting && routine.main_exp.sub_exp[1].status != exp_finished) || \
                                (routine.main_exp.sub_exp[2].status != exp_waiting && routine.main_exp.sub_exp[2].status != exp_finished))

#define FLAG_EXP_START                          1
#define FLAG_STUDENT_LOGIN                      2
#define FLAG_TEACHER_LOGIN                      3
#define FLAG_QUESTION_SET                       4

enum flag_t {
        flag_reset,
        flag_set
};

enum sub_exp_sta_t{
        exp_waiting,
        exp_lasting,
        exp_submitted,
        exp_grading,
        exp_finished
};

typedef struct {
        enum flag_t flagExpStart;
        enum flag_t flagStudentLogin;
        enum flag_t flagTeacherLogin;
        enum flag_t flagQuestionSet;
}exp_flag_t;

typedef struct {
        enum sub_exp_sta_t status;
        char subExpName[100];
        char subExpDetail[200];
        int  subExpScore;
}sub_exp_content_t;

typedef struct {
        char mainExpName[100];
        sub_exp_content_t sub_exp[10];
        int subExpNumber;
}exp_content_t;

typedef struct {
        exp_flag_t flags;
        exp_content_t main_exp;
	char end_time[20];
	char class_id[33];
        char appointed_uid[33];
        char appointed_eid[20];
	char online_tid[33];
        char online_eid_list[8][20];
        char offline_eid_list[8][20];
        char online_uid_list[8][33];
        int online_number;
        int offline_number;
	int appointed_expid;
}exp_routine_t;

extern exp_routine_t routine;
extern char test_id_list[8][9];

void expGetRoutineContents(void);
void expRoutineFlagSet(int routine_flags, int state);


#endif

