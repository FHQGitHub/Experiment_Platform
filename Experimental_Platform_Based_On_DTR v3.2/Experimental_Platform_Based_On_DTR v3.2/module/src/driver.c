#include "driver.h"

int chr_dev_register(chr_dev_t *dev, f_ops_t *file_operation, int buffer_len)
{
        if(NULL == file_operation)
                return -1;
        dev->ops = file_operation;
        dev->buffer = calloc(1, buffer_len);
        
        if(NULL == dev->buffer)
                return -1;
        
        return 0;
}

