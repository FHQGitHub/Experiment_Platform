#ifndef __DRIVER_H
#define __DRIVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

#include "stm32f4xx.h"

typedef struct {
        void    (*init)(void);
        int     (*open)(char *);
        int     (*read)(char *s, int n); 
        int     (*write)(char *s, int n);
        void    (*close)(void);
}f_ops_t;

typedef struct {
        char            *buffer;
        f_ops_t         *ops;
}chr_dev_t;

extern f_ops_t usart1_operation;
extern f_ops_t usart2_operation;
extern f_ops_t usart3_operation;

extern f_ops_t spi1_operation;

int chr_dev_register(chr_dev_t *dev, f_ops_t *file_operation, int buffer_len);


#endif
