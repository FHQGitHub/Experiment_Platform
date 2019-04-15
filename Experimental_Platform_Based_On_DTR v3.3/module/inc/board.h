#ifndef __BOARD_H
#define __BOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

#include "stm32f4xx.h"

#define _BOARD_USE_USART1                       (1)
#define _BOARD_USE_SPI1                         (0)

typedef struct {
        int             Baud_Rate;
        int             Preetmption;
        int             Sub_Preemption;
        USART_TypeDef   *USARTx;
        unsigned long   USART_CLK;
        void            (*USART_APBxClock_FUN)(uint32_t, FunctionalState);
        unsigned long   USART_GPIO_CLK;
        void            (*USART_GPIO_APBxClock_FUN)(uint32_t, FunctionalState);
        int             GPIO_AF;
        GPIO_TypeDef    *USART_TX_PORT;
        GPIO_TypeDef    *USART_RX_PORT;
        unsigned int    USART_TX_PIN;
        unsigned int    USART_RX_PIN;
        unsigned int    USART_TX_PinSource;
        unsigned int    USART_RX_PinSource;
        unsigned int    USART_IRQx;
        char            *USART_RX_BUF;
        unsigned int    USART_RX_LEN;
        unsigned int    USART_RX_STA;
}usart_hw_t;

typedef struct {
        unsigned long   SPI_MISO_CLK;
        unsigned long   SPI_MOSI_CLK;
        unsigned long   SPI_SCLK_CLK;
        unsigned long   SPI_SS_CLK;
        void            (*SPI_GPIO_APBxClock_FUN)(uint32_t, FunctionalState);
        GPIO_TypeDef    *SPI_MISO_PORT;
        GPIO_TypeDef    *SPI_MOSI_PORT;
        GPIO_TypeDef    *SPI_SCLK_PORT;
        GPIO_TypeDef    *SPI_SS_PORT;
        unsigned int    SPI_MISO_PIN;
        unsigned int    SPI_MOSI_PIN;
        unsigned int    SPI_SCLK_PIN;
        unsigned int    SPI_SS_PIN;
        char            *SPI_RX_BUF;
        unsigned int    SPI_RX_LEN;
        unsigned int    SPI_RX_STA;
}spi_hw_t;
        
extern usart_hw_t usart1_hw;
extern usart_hw_t usart2_hw;
extern usart_hw_t usart3_hw;

extern spi_hw_t spi1_hw;

#endif
