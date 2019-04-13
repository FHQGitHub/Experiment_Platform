#ifndef __APP_HTTP_H__
#define __APP_HTTP_H__

#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ff.h"
#include "app_localdb.h"

typedef enum {
	HTTP_OK = 1,
	HTTP_ERR,
	HTTP_NO_DATA
} httpStatus;

typedef enum {
	http_submit_dev_id = 1,
	http_get_appointment,
	http_student_login_check,
	http_teacher_login_check,
	http_student_start_exp,
	http_exp_score,
	http_logout_check,
	http_record_update,
	http_record_download,
	http_sync_time
} httpEvent;

typedef struct {
	httpEvent event;
	httpStatus status;
	char *param;
} http_notify_t;

httpStatus httpSubmitDevId(char *httpDataBuffer);
httpStatus httpGetAppointment(char *httpDataBuffer);
httpStatus httpStudentLoginCheck(char *httpDataBuffer);
httpStatus httpTeacherLoginCheck(char *httpDataBuffer);
httpStatus httpStudentStartExp(char *httpDataBuffer);
httpStatus httpExpScore(char *httpDataBuffer);
httpStatus httpLogoutCheck(char *httpDataBuffer);
httpStatus httpRecordUpdate(char *httpDataBuffer);
httpStatus httpRecordDownload(char *httpDataBuffer);
httpStatus httpSyncTime(char *httpDataBuffer);

#endif
