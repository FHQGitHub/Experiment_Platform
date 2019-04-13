#ifndef __EP_APP_H
#define __EP_APP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "bsp.h"
#include "driver.h"
#include "shell.h"

#include "uiBuild.h"

#include "app_voice.h"
#include "app_wifi_common.h"
#include "app_exp_routine.h"
#include "app_http.h"
#include "app_epoch_match.h"
#include "app_scanner.h"
#include "app_mqtt.h"

enum switch_t{
        on,
        off
};

typedef struct {
        char dev_id[20];
        enum switch_t voice;
        enum switch_t doze;
        enum switch_t mux;
}sys_config_t;

typedef struct
{
	wifi_setting_t setting;
	http_notify_t http_notify;
	mqtt_notify_t mqtt_notify;
}wifi_config_t;

extern sys_config_t sys_config;

#endif

