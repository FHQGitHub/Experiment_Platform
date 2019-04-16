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

	result = f_open(&f, DB_FILE_VOICE, FA_CREATE_NEW | FA_READ);
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
	
	result = f_open(&f, DB_FILE_MUX, FA_CREATE_NEW | FA_READ);
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
	
	result = f_open(&f, DB_FILE_VOLUME, FA_CREATE_NEW | FA_READ);
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
	
	result = f_open(&f, DB_FILE_DEVID, FA_CREATE_NEW | FA_READ);
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
	
	result = f_open(&f, DB_FILE_GATEWAYID, FA_CREATE_NEW | FA_READ);
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
	
	vTaskSuspendAll();
	
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
	xTaskResumeAll();
	return br;

}


static int db_write(const char * filename, const char *p)
{
	FIL f;
	FRESULT result;
	UINT wr;
	
	vTaskSuspendAll();
	
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
	xTaskResumeAll();
	
	return wr;
}

int dbSettingParamInit()
{
	
	int res = 0;
	char db_write_buf[30];
	char db_read_buf[30];
	char *index_head = NULL;
	char *index_tail = NULL;
	char pattern[30];
	
	memset(db_read_buf, 0, 30);
	res = local_db.read(DB_FILE_VOICE, db_read_buf);
	if(0 == res) {
		memset(db_write_buf, 0, 30);
		sprintf(db_write_buf, "voice:on");
		local_db.write(DB_FILE_VOICE, db_write_buf);
		res = local_db.read(DB_FILE_VOICE, db_read_buf);
		if(res < 0) 
			return -1;
		
	}
	else {
		if(!strcmp(db_read_buf, "voice:on"))
			sys_config.voice = on;
		else if(!strcmp(db_read_buf, "voice:off"))
			sys_config.voice = off;
		else {
			memset(db_write_buf, 0, 30);
			sprintf(db_write_buf, "voice:on");
			local_db.write(DB_FILE_VOICE, db_write_buf);
		}
			
	}
	
	memset(db_read_buf, 0, 30);
	res = local_db.read(DB_FILE_MUX, db_read_buf);
	if(0 == res) {
		memset(db_write_buf, 0, 30);
		sprintf(db_write_buf, "mux:on");
		local_db.write(DB_FILE_MUX, db_write_buf);
		res = local_db.read(DB_FILE_MUX, db_read_buf);
		if(res < 0) 
			return -1;
		
	}
	else {
		if(!strcmp(db_read_buf, "mux:on"))
			sys_config.mux = on;
		else if(!strcmp(db_read_buf, "mux:off"))
			sys_config.mux = off;
		else {
			memset(db_write_buf, 0, 30);
			sprintf(db_write_buf, "mux:off");
			local_db.write(DB_FILE_MUX, db_write_buf);
		}
			
	}
	
	memset(db_read_buf, 0, 30);
	res = local_db.read(DB_FILE_VOLUME, db_read_buf);
	if(0 == res) {
		memset(db_write_buf, 0, 30);
		sprintf(db_write_buf, "volume:1");
		local_db.write(DB_FILE_VOLUME, db_write_buf);
		res = local_db.read(DB_FILE_VOLUME, db_read_buf);
		if(res < 0) 
			return -1;
		
	}
	else {
		if(strstr(db_read_buf, "volume"))
			sys_config.volume = db_read_buf[7] - '0';
		else {
			sys_config.volume = 1;
			memset(db_write_buf, 0, 30);
			sprintf(db_write_buf, "volume:1");
			local_db.write(DB_FILE_VOLUME, db_write_buf);
		}
	}
		
	
	memset(db_read_buf, 0, 30);
	res = local_db.read(DB_FILE_DEVID, db_read_buf);
	if(0 != res)
		strcpy(sys_config.dev_id, db_read_buf);
	else;
	
	memset(db_read_buf, 0, 30);
	res = local_db.read(DB_FILE_GATEWAYID, db_read_buf);
	if(0 != res)
		strcpy(sys_config.gateway_id, db_read_buf);
	else;
	
	
	return 0;
}
	
	

