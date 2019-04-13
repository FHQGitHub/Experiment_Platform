#include "ep_app.h"

static int DAYS = 24 * 3600 * 1000;
static int FOURYEARS = 365 * 3 + 366;
static int norMoth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static int leapMoth[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static void getHourMinSecMSec(int nMSecond)
{
	int nSecond = nMSecond / 1000;

	system_time.msec =  nMSecond % 1000;
	/*注意UNIX时间戳与北京时区的时差8h*/
	system_time.hour = nSecond / 3600 + 8;
	system_time.min = (nSecond % 3600) / 60;
	system_time.sec = (nSecond % 3600) % 60;
}


static void getMonthAndDay(bool bLeapYear, int nDays, int *nMoth, int *nDay)
{
	int i = 0;
	int nTmp = 0;
	int *pMoth = bLeapYear ? leapMoth : norMoth;


	for (i = 0; i < 12; i++) {
		nTmp = nDays - pMoth[i];
		if (nTmp <= 0) {
			*nMoth = i + 1;
			if (nTmp == 0) {
				*nDay = pMoth[i];
			} else {
				*nDay = nDays;
			}
			break;
		}
		nDays = nTmp;
	}


	return;
}


static void getStampTime(long long timestamp)
{
	long long nTime = timestamp;
	int nDays = nTime / DAYS + ((nTime % DAYS) ? 1 : 0);
	int nYear4 = nDays / FOURYEARS;
	int nRemain = nDays % FOURYEARS;

	system_time.year = 1970 + nYear4 * 4;
	system_time.month = 0;
	system_time.day = 0;
	bool bLeapyear = false;


	if (nRemain < 365) {
		;
	} else if (nRemain < 365 * 2) {
		system_time.year += 1;
		nRemain -= 365;
	} else if (nRemain < 365 * 3) {
		system_time.year += 2;
		nRemain -= 365 * 2;
	} else {
		system_time.year += 3;
		nRemain -= 365 * 3;
		bLeapyear = true;
	}
	getMonthAndDay(bLeapyear, nRemain, &system_time.month, &system_time.day);
	getHourMinSecMSec(nTime % DAYS);
	return;
}

httpStatus httpSubmitDevId(char *httpDataBuffer)
{
	JSON_Value *content;
	const char *success_flg = NULL;
	httpStatus httpRetVal = HTTP_ERR;

	content = json_parse_string(httpDataBuffer);

	if (content != NULL) {
		success_flg = json_object_get_string(json_object(content), "successFlg");
		if(strcmp(success_flg, "true")) {
			json_value_free(content);
			httpRetVal = HTTP_NO_DATA;
		} else
			httpRetVal = HTTP_OK;
	}

	json_value_free(content);
	return httpRetVal;


}

httpStatus httpGetAppointment(char *httpDataBuffer)
{
	JSON_Value *content;
	const char *success_flg = NULL;
	const char *exp_name = NULL;
	const char *exp_end_time = NULL;
	const char *exp_class_id = NULL;
	int exp_id = NULL;
	int exp_appointed_id = NULL;
	

	JSON_Object *exp_student = NULL;
	const char *exp_student_uid = NULL;
	const char *exp_student_name = NULL;
	const char *exp_student_eid = NULL;

	JSON_Array *modules;
	int *exp_module_id = NULL;
	char *exp_module_content = NULL;

	JSON_Object *exp_module_1 = NULL;
	int exp_module_1_id;
	const char *exp_module_1_name = NULL;
	const char *exp_module_1_content = NULL;

	JSON_Object *exp_module_2 = NULL;
	int exp_module_2_id;
	const char *exp_module_2_name = NULL;
	const char *exp_module_2_content = NULL;

	JSON_Object *exp_module_3 = NULL;
	int exp_module_3_id;
	const char *exp_module_3_name = NULL;
	const char *exp_module_3_content = NULL;

	httpStatus httpRetVal = HTTP_OK;

	content = json_parse_string(httpDataBuffer);

	if (content != NULL) {

		success_flg = json_object_get_string(json_object(content), "successFlg");
		if(strcmp(success_flg, "true")) {
			json_value_free(content);
			return HTTP_ERR;
		}
		strcpy(routine.main_exp.mainExpName, json_object_get_string(json_object(content), "experimentName"));
		exp_id = (int)json_object_get_number(json_object(content), "experimentId");

		exp_student = json_object_get_object(json_object(content), "student");
		if(NULL != exp_student) {
			strcpy(routine.appointed_uid, json_object_get_string(exp_student, "userId"));
			strcpy(routine.appointed_eid, json_object_get_string(exp_student, "employeeId"));
		}
		
		routine.main_exp.subExpNumber = (int)json_object_get_number(json_object(content), "moduleCount");
		modules = json_object_get_array(json_object(content), "modules");
		if(NULL != modules) {
			exp_module_1 = json_array_get_object(modules, 0);
			if(exp_module_1 != NULL) {
				exp_module_1_name = json_object_get_string(exp_module_1, "moduleName");
				if(exp_module_1_name!= NULL)
					strcpy(routine.main_exp.sub_exp[0].subExpName, exp_module_1_name);
				
				exp_module_1_content = json_object_get_string(exp_module_1, "content");
				if(exp_module_1_content!= NULL)
					strcpy(routine.main_exp.sub_exp[0].subExpDetail, exp_module_1_name);
			}

			exp_module_2 = json_array_get_object(modules, 1);
			if(exp_module_2 != NULL) {
				exp_module_2_name = json_object_get_string(exp_module_2, "moduleName");
				if(exp_module_2_name!= NULL)
					strcpy(routine.main_exp.sub_exp[1].subExpName, exp_module_2_name);
				
				exp_module_2_content = json_object_get_string(exp_module_2, "content");
				if(exp_module_2_content!= NULL)
					strcpy(routine.main_exp.sub_exp[1].subExpDetail, exp_module_2_name);
			}

			exp_module_3 = json_array_get_object(modules, 2);
			if(exp_module_3 != NULL) {
				exp_module_3_name = json_object_get_string(exp_module_3, "moduleName");
				if(exp_module_3_name!= NULL)
					strcpy(routine.main_exp.sub_exp[2].subExpName, exp_module_3_name);
				
				exp_module_3_content = json_object_get_string(exp_module_3, "content");
				if(exp_module_3_content!= NULL)
					strcpy(routine.main_exp.sub_exp[2].subExpDetail, exp_module_3_name);
			}
		}
		
		exp_end_time = json_object_get_string(json_object(content), "endTime");
		if(NULL != exp_end_time)
			strcpy(routine.end_time, exp_end_time);
		
		exp_appointed_id = (int)json_object_get_number(json_object(content), "expeArrangementId");
		if(NULL != exp_appointed_id)
			routine.appointed_expid = exp_appointed_id;
		else
			routine.appointed_expid = -1;
		
		exp_class_id = json_object_get_string(json_object(content), "tClzId");
		if(NULL != exp_class_id)
			strcpy(routine.class_id, exp_class_id);
		else
			strcpy(routine.class_id, "NULL");
	}
	json_value_free(content);
	return httpRetVal;
}

httpStatus httpStudentLoginCheck(char *httpDataBuffer)
{
	JSON_Value *content;
	const char *success_flg = NULL;
	int result = NULL;

	JSON_Value *user = NULL;
	const char *user_id = NULL;
	const char *user_name = NULL;
	const char *user_eid = NULL;

	httpStatus httpRetVal = HTTP_OK;

	content = json_parse_string(httpDataBuffer);

	if (content != NULL) {

		success_flg = json_object_get_string(json_object(content), "successFlg");
		if(strcmp(success_flg, "true")) {
			json_value_free(content);
			httpRetVal = HTTP_ERR;
		}
		result = (int)json_object_get_number(json_object(content), "result");
		if(0 == result) {
			httpRetVal = HTTP_NO_DATA;
		}

		user = json_object_get_value(json_object(content), "user");
		if(user != NULL) {
			strcpy(routine.online_uid_list[routine.online_number], json_object_get_string(json_object(user), "userId"));
			strcpy(routine.online_eid_list[routine.online_number], json_object_get_string(json_object(user), "employeeId"));
		}
	} else {
		json_value_free(content);
		httpRetVal = HTTP_ERR;
	}
	json_value_free(user);
	json_value_free(content);
	return httpRetVal;

}

httpStatus httpTeacherLoginCheck(char *httpDataBuffer)
{
	JSON_Value *content;
	const char *success_flg = NULL;
	int result = NULL;
	
	JSON_Value *user = NULL;

	httpStatus httpRetVal = HTTP_OK;

	content = json_parse_string(httpDataBuffer);

	if (content != NULL) {

		success_flg = json_object_get_string(json_object(content), "successFlg");
		if(strcmp(success_flg, "true")) {
			json_value_free(content);
			httpRetVal = HTTP_ERR;
		}
		result = (int)json_object_get_number(json_object(content), "result");
		if(0 == result) {
			httpRetVal = HTTP_NO_DATA;
		}
		user = json_object_get_value(json_object(content), "user");
		if(user != NULL)
			strcpy(routine.online_tid, json_object_get_string(json_object(user), "userId"));
	} 
	else
		httpRetVal = HTTP_ERR;
	json_value_free(user);
	json_value_free(content);
	return httpRetVal;
}

httpStatus httpStudentStartExp(char *httpDataBuffer)
{
	JSON_Value *content;
	const char *success_flg = NULL;
	httpStatus httpRetVal = HTTP_ERR;

	content = json_parse_string(httpDataBuffer);

	if (content != NULL) {
		success_flg = json_object_get_string(json_object(content), "successFlg");
		if(strcmp(success_flg, "true")) {
			json_value_free(content);
			httpRetVal = HTTP_NO_DATA;
		} else
			httpRetVal = HTTP_OK;
	}
	json_value_free(content);
	return httpRetVal;
}

httpStatus httpExpScore(char *httpDataBuffer)
{
	JSON_Value *content;
	const char *success_flg = NULL;
	httpStatus httpRetVal = HTTP_ERR;

	content = json_parse_string(httpDataBuffer);

	if (content != NULL) {
		success_flg = json_object_get_string(json_object(content), "successFlg");
		if(strcmp(success_flg, "true")) {
			json_value_free(content);
			httpRetVal = HTTP_NO_DATA;
		} else
			httpRetVal = HTTP_OK;
	}
	json_value_free(content);
	return httpRetVal;


}

httpStatus httpLogoutCheck(char *httpDataBuffer)
{
	JSON_Value *content;
	const char *success_flg = NULL;
	httpStatus httpRetVal = HTTP_ERR;

	content = json_parse_string(httpDataBuffer);

	if (content != NULL) {
		success_flg = json_object_get_string(json_object(content), "successFlg");
		if(strcmp(success_flg, "true")) {
			json_value_free(content);
			httpRetVal = HTTP_NO_DATA;
		} else
			httpRetVal = HTTP_OK;
	}

	json_value_free(content);
	return httpRetVal;


}

httpStatus httpRecordUpdate(char *httpDataBuffer)
{
	JSON_Value *content;
	const char *success_flg = NULL;
	const char *log = NULL;
	httpStatus httpRetVal = HTTP_OK;

	content = json_parse_string(httpDataBuffer);

	if (content != NULL) {
		success_flg = json_object_get_string(json_object(content), "successFlg");
		if(strcmp(success_flg, "true")) {
			json_value_free(content);
			httpRetVal = HTTP_ERR;
		}

		log = json_object_get_string(json_object(content), "log");

		if(strcmp(log, "newest"))
			httpRetVal = HTTP_NO_DATA;
		else;
	}
	json_value_free(content);
	return httpRetVal;
}

httpStatus httpRecordDownload(char *httpDataBuffer)
{
	JSON_Value *content;
	const char *success_flg = NULL;
	const char *log = NULL;
	httpStatus httpRetVal = HTTP_OK;

	content = json_parse_string(httpDataBuffer);

	if (content != NULL) {

		success_flg = json_object_get_string(json_object(content), "successFlg");
		if(strcmp(success_flg, "true")) {
			json_value_free(content);
			httpRetVal = HTTP_ERR;
		}

		log = json_object_get_string(json_object(content), "log");

		if(strcmp(log, "all done"))
			httpRetVal = HTTP_NO_DATA;
		else;
	}
	json_value_free(content);
	return httpRetVal;
}

httpStatus httpSyncTime(char *httpDataBuffer)
{
	JSON_Value *content;
	const char *success_flg = NULL;
	long long time_ms;
	httpStatus httpRetVal = HTTP_OK;

	content = json_parse_string(httpDataBuffer);

	if (content != NULL) {
		success_flg = json_object_get_string(json_object(content), "successFlg");
		if(strcmp(success_flg, "true")) {
			json_value_free(content);
			httpRetVal = HTTP_ERR;
		}
		time_ms = (long long)json_object_get_number(json_object(content), "timestamp");
		if (time_ms != 0) {
			getStampTime(time_ms);
			httpRetVal = HTTP_OK;
		}
	}
	json_value_free(content);
	return httpRetVal;
}

