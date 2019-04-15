#ifndef __APP_EPOCH_H
#define __APP_EPOCH_H

/*Epoch型智能物联实验管理机*/
#define EPOCH_IIEES     0x10

/*Epoch型智能电源控制器*/
#define EPOCH_IIPCD     0x11
        
/*Epoch型其他设备*/
#define EPOCH_OTHERS    0x80


typedef enum {
        epoch_rfid_none,
        epoch_rfid_ok,
        epoch_rfid_err
}epoch_return_t ;
        
typedef struct {
        char type;
        char id_sector;
        char name_sector;
        char id[17];
        char name[17];
        char area_rank;
}epoch_dev_t;

typedef struct {
	char number;
	epoch_dev_t connected_dev[20];
}epoch_dev_list_t;
        
extern epoch_dev_t new_dev;
extern epoch_dev_list_t dev_list;

epoch_return_t epochMatchDevice(void);



#endif

