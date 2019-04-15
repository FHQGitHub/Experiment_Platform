#include "ep_app.h"

epoch_dev_t new_dev;
epoch_dev_list_t dev_list;

epoch_return_t epochMatchDevice()
{
	int i;
        int action_status;
	rc522_get_serial_number(card_serial_num);
        if(0 == card_serial_num[0] && 0 == card_serial_num[1] && 0 == card_serial_num[2] && 0 == card_serial_num[3])
                rc522_get_serial_number(card_serial_num);

	if(card_serial_num[0] || card_serial_num[1] || card_serial_num[2] || card_serial_num[3]) {
		memset(card_serial_num, 0, 16);
		action_status = rc522_read_sector(15, 0, new_key_A, card_read_buf);
		if(action_status)
			action_status = rc522_read_sector(15, 0, new_key_A, card_read_buf);

		if(0 == action_status) {
                        new_dev.id_sector = card_read_buf[0];
                        new_dev.name_sector = card_read_buf[1];
                        new_dev.type = card_read_buf[2];
                        
                        action_status = rc522_read_sector(new_dev.id_sector, 0, new_key_A, card_read_buf);
                        if(action_status)
                                action_status = rc522_read_sector(new_dev.id_sector, 0, new_key_A, card_read_buf);
                        if(0 == action_status) {
                                strncpy(new_dev.id, card_read_buf, 16);
				for(i = 0; i < 16; i++) 
					if((card_read_buf[i] < 'a' || card_read_buf[i] > 'z') && (card_read_buf[i] < 'A' || card_read_buf[i] > 'Z') && (card_read_buf[i] < '0' || card_read_buf[i] > '9'))
						return epoch_rfid_err;
			}
                        else 
                                return epoch_rfid_err;
                        
                        action_status = rc522_read_sector(new_dev.name_sector, 0, new_key_A, card_read_buf);
                        if(action_status)
                                action_status = rc522_read_sector(new_dev.name_sector, 0, new_key_A, card_read_buf);
                        if(0 == action_status)
                                strncpy(new_dev.name, card_read_buf, 16);
                        else 
                                return epoch_rfid_err;
                        
                        return epoch_rfid_ok;
                }
                

			
		else if(action_status == PASSWD_ERR)
			return epoch_rfid_err;
                else 
                        return epoch_rfid_none;
	}
        else 
                return epoch_rfid_none;
}



