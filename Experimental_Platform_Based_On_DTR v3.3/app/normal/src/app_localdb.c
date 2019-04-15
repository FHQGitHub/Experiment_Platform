#include "ep_app.h"

static int db_init(void);
static int db_read(const char * filename, char *p);
static int db_write(const char * filename, const char *p);


dbInfoTypedef local_db = {
	db_init,
	db_read,
	db_write
};

static FATFS dbfs;
char *FL = NULL;

static int db_init()
{
	static FRESULT result;
	FIL f;

	result = f_mount(&dbfs, LOCALDB_ROOT, 1);
	
	if (FR_NO_FILESYSTEM == result)	{

		f_mkfs(LOCALDB_ROOT, 0, 0);
		f_mount(NULL, LOCALDB_ROOT, 0);
		result = f_mount(&dbfs, LOCALDB_ROOT, 1);
		if (FR_OK != result) {
			local_db.info = fs_not_exist;
			return 0;
		}

		f_mkdir(LOCALDB_LOCAL_PATH);
		f_mkdir(LOCALDB_INFO_PATH);
		f_mkdir(LOCALDB_SETTING_PATH);
		f_mkdir(LOCALDB_RECORD_PATH);
		f_mkdir(LOCALDB_USER_PATH);
	}

	else if(FR_OK == result)
		local_db.info = fs_exist;

	else {
		local_db.info = fs_not_exist;
		f_mount(&dbfs, LOCALDB_ROOT, NULL);
		return 0;
	}

	
	result = f_open(&f, DB_FILE_INFO, FA_CREATE_NEW | FA_READ);
	if(FR_OK == result) {
		local_db.info = fs_new;
		f_close(&f);
	} else if(FR_EXIST == result) {
		f_close(&f);
		local_db.info = fs_exist;
	} else {
		local_db.info = fs_crashed;
		f_mount(&dbfs, LOCALDB_ROOT, NULL);
		return 0;
	}

	result = f_open(&f, DB_FILE_SETTING, FA_CREATE_NEW | FA_READ);
	if(FR_OK == result) {
		local_db.info = fs_new;
		f_close(&f);
	} else if(FR_EXIST == result) {
		f_close(&f);
		local_db.info = fs_exist;
	} else {
		local_db.info = fs_crashed;
		f_mount(&dbfs, LOCALDB_ROOT, NULL);
		return 0;
	}

	result = f_open(&f, DB_FILE_RECORD, FA_CREATE_NEW | FA_READ);
	if(FR_OK == result) {
		local_db.info = fs_new;
		f_close(&f);
	} else if(FR_EXIST == result) {
		f_close(&f);
		local_db.info = fs_exist;
	} else {
		local_db.info = fs_crashed;
		f_mount(&dbfs, LOCALDB_ROOT, NULL);
		return 0;
	}

	result = f_open(&f, DB_FILE_LOG, FA_CREATE_NEW | FA_READ);
	if(FR_OK == result) {
		local_db.info = fs_new;
		f_close(&f);
	} else if(FR_EXIST == result) {
		f_close(&f);
		local_db.info = fs_exist;
	} else {
		local_db.info = fs_crashed;
		f_mount(&dbfs, LOCALDB_ROOT, NULL);
		return 0;
	}

	f_mount(&dbfs, LOCALDB_ROOT, NULL);

	return 1;

}

static int db_read(const char * filename, char *p)
{
	FIL f;
	FRESULT result;
	UINT br;
	
	if(NULL == p)
		return -1;
	result = f_open(&f, filename, FA_OPEN_ALWAYS | FA_READ);

	if (result != FR_OK) {
		return -1;
	}

	f_rewind(&f);

	if (f_read(&f, p, f.fsize, &br) < 1) {
		if (f_error(&f)) {
			f_close(&f);
			return -1;
		}
	}

	f_close(&f);
	return br;

}


static int db_write(const char * filename, const char *p)
{
	FIL f;
	FRESULT result;
	UINT wr;
	
	if(NULL == p)
		return -1;
	result = f_open(&f, filename, FA_OPEN_ALWAYS | FA_WRITE);

	if (result != FR_OK) {
		return -1;
	}

	f_rewind(&f);

	if (f_write(&f, p, strlen(p), &wr) < 1) {
		if (f_error(&f)) {
			f_close(&f);
			return -1;
		}
	}

	f_close(&f);
	return wr;
}

int dbSettingParamInit()
{
	
	int res = 0;
	char db_write_buf[100];
	char db_read_buf[100];
	char *index_head = NULL;
	char *index_tail = NULL;
	char pattern[30];
	
	memset(db_read_buf, 0, 100);
	res = local_db.read(DB_FILE_SETTING, db_read_buf);
	if(0 == res) {
		memset(db_write_buf, 0, 100);
		sprintf(db_write_buf, "voice:on;mux:off;volume:1;id:NULL;");
		local_db.write(DB_FILE_SETTING, db_write_buf);
		res = local_db.read(DB_FILE_SETTING, db_read_buf);
		if(res < 0) 
			return -1;
		
	}
	else if(!(strstr(db_read_buf, "voice") && strstr(db_read_buf, "mux") && strstr(db_read_buf, "volume") && strstr(db_read_buf, "id"))) {
		memset(db_write_buf, 0, 100);
		sprintf(db_write_buf, "voice:on;mux:off;volume:1;id:NULL;");
		local_db.write(DB_FILE_SETTING, db_write_buf);
		res = local_db.read(DB_FILE_SETTING, db_read_buf);
		if(res < 0) 
			return -1;
	}
	
	index_head = strstr(db_read_buf, "voice");
	index_tail = strstr(index_head, ";");
	if(NULL == index_head || NULL == index_tail)
		return -1;
	
	memset(pattern, 30, 0);
	strncpy(pattern, index_head, index_tail - index_head);
	
	if(strstr(pattern, "on")) {
		sys_config.voice = on;
	}
	else if(strstr(pattern, "off")) {
		sys_config.voice = off;
	}
	
	index_head = strstr(db_read_buf, "mux");
	index_tail = strstr(index_head, ";");
	if(NULL == index_head || NULL == index_tail) 
		return -1;
	
	memset(pattern, 30, 0);
	strncpy(pattern, index_head, index_tail - index_head);
	
	if(strstr(pattern, "on")) {
		sys_config.mux = on;
	}
	else if(strstr(pattern, "off")) {
		sys_config.mux = off;
	}
	
	index_head = strstr(db_read_buf, "volume");
	index_tail = strstr(index_head, ";");
	if(NULL == index_head || NULL == index_tail) 
		return -1;
	
	memset(pattern, 30, 0);
	strncpy(pattern, index_head, index_tail - index_head);
	
	index_head = strstr(db_read_buf, "id");
	index_tail = strstr(index_head, ";");
	if(NULL == index_head || NULL == index_tail) 
		return -1;
	
	memset(pattern, 30, 0);
	strncpy(pattern, index_head, index_tail - index_head);
	
	return 0;
}
	
int dbParamSetVoice(int state)
{
	char *index_head = NULL;
	char db_read_buf[100];
	static FRESULT result;
	FIL f;
	int res = 0;
	int wr = 0;
	
	memset(db_read_buf, 0, 100);
	res = local_db.read(DB_FILE_SETTING, db_read_buf);
	if(res < 1)
		return -1;
	
	index_head = strstr(db_read_buf, "voice");
	if(NULL == index_head)
		return -1;
	
	result = f_open(&f, DB_FILE_SETTING, FA_OPEN_EXISTING | FA_READ | FA_WRITE);
	
	if (result != FR_OK) {
		return -1;
	}
	f_rewind(&f);
	result = f_lseek(&f, index_head - db_read_buf + 6);
	if (result != FR_OK) {
		f_close(&f);
		return -1;
	}
	if(state) {
		if (f_write(&f, "on", strlen("on"), &wr) < 1) {
			if (f_error(&f)) {
				f_close(&f);
				return -1;
			}
		}
	}
	else {
		if (f_write(&f, "off", strlen("off"), &wr) < 1) {
			if (f_error(&f)) {
				f_close(&f);
				return -1;
			}
		}
	}
	
	f_close(&f);
	return wr;
		
}

int dbParamSetVolume(int volume)
{
	char *index_head = NULL;
	char db_read_buf[100];
	static FRESULT result;
	FIL f;
	int res = 0;
	int wr = 0;
	
	memset(db_read_buf, 0, 100);
	res = local_db.read(DB_FILE_SETTING, db_read_buf);
	if(res < 1)
		return -1;
	
	index_head = strstr(db_read_buf, "volume");
	
	
	result = f_open(&f, DB_FILE_SETTING, FA_OPEN_EXISTING | FA_READ | FA_WRITE);
	
	if (result != FR_OK) {
		return -1;
	}
	f_rewind(&f);
	result = f_lseek(&f, index_head - db_read_buf + 7);
	if (result != FR_OK) {
		f_close(&f);
		return -1;
	}
	
	f_close(&f);
	return wr;
}

int dbParamSetMux(int state)
{
	static FRESULT result;
	FIL f;
	int wr = 0;
	
	result = f_open(&f, DB_FILE_SETTING, FA_OPEN_EXISTING | FA_READ | FA_WRITE);
	
	if (result != FR_OK) {
		return -1;
	}
	f_rewind(&f);
	result = f_lseek(&f, 13);
	if (result != FR_OK) {
		f_close(&f);
		return -1;
	}
	if(state) {
		if (f_write(&f, "on", strlen("on"), &wr) < 1) {
			if (f_error(&f)) {
				f_close(&f);
				return -1;
			}
		}
	}
	else {
		if (f_write(&f, "off", strlen("off"), &wr) < 1) {
			if (f_error(&f)) {
				f_close(&f);
				return -1;
			}
		}
	}
	
	f_close(&f);
	return wr;
}

int dbParamSetId(char *id)
{
	
}


		
	
	
	

