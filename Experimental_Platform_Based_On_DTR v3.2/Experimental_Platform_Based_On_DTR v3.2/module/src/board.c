#include "board.h"
        
#if (_BOARD_USE_USART1)        
usart_hw_t usart1_hw = {
        .Baud_Rate = 115200,
        .Preetmption = 1,
        .Sub_Preemption = 1,
        .USARTx = USART1,
        .USART_CLK = RCC_APB2Periph_USART1,
        .USART_APBxClock_FUN = RCC_APB2PeriphClockCmd,
        .USART_GPIO_CLK = RCC_AHB1Periph_GPIOA,
        .USART_GPIO_APBxClock_FUN = RCC_AHB1PeriphClockCmd,
        .GPIO_AF = GPIO_AF_USART1,
        .USART_TX_PORT = GPIOA,
        .USART_RX_PORT = GPIOA,
        .USART_TX_PIN = GPIO_Pin_9,
        .USART_RX_PIN = GPIO_Pin_10,
        .USART_TX_PinSource = GPIO_PinSource9,
        .USART_RX_PinSource = GPIO_PinSource10,
        .USART_IRQx = USART1_IRQn,
        .USART_RX_BUF = NULL,
        .USART_RX_LEN = 200,
        .USART_RX_STA = 0
};
#endif 

#if (_BOARD_USE_USART2)    
usart_hw_t usart2_hw = {
        .Baud_Rate = 115200,
        .Preetmption = 1,
        .Sub_Preemption = 1,
        .USARTx = USART2,
        .USART_CLK = RCC_APB1Periph_USART2,
        .USART_APBxClock_FUN = RCC_APB1PeriphClockCmd,
        .USART_GPIO_CLK = RCC_AHB1Periph_GPIOA,
        .USART_GPIO_APBxClock_FUN = RCC_AHB1PeriphClockCmd,
        .GPIO_AF = GPIO_AF_USART2,
        .USART_TX_PORT = GPIOA,
        .USART_RX_PORT = GPIOA,
        .USART_TX_PIN = GPIO_Pin_9,
        .USART_RX_PIN = GPIO_Pin_10,
        .USART_TX_PinSource = GPIO_PinSource9,
        .USART_RX_PinSource = GPIO_PinSource10,
        .USART_IRQx = USART2_IRQn,
        .USART_RX_BUF = NULL,
        .USART_RX_LEN = 200,
        .USART_RX_STA = 0
};
#endif

#if (_BOARD_USE_USART3)
usart_hw_t usart3_hw = {
        .Baud_Rate = 115200,
        .Preetmption = 1,
        .Sub_Preemption = 1,
        .USARTx = USART3,
        .USART_CLK = RCC_APB1Periph_USART3,
        .USART_APBxClock_FUN = RCC_APB1PeriphClockCmd,
        .USART_GPIO_CLK = RCC_AHB1Periph_GPIOA,
        .USART_GPIO_APBxClock_FUN = RCC_AHB1PeriphClockCmd,
        .GPIO_AF = GPIO_AF_USART3,
        .USART_TX_PORT = GPIOA,
        .USART_RX_PORT = GPIOA,
        .USART_TX_PIN = GPIO_Pin_9,
        .USART_RX_PIN = GPIO_Pin_10,
        .USART_TX_PinSource = GPIO_PinSource9,
        .USART_RX_PinSource = GPIO_PinSource10,
        .USART_IRQx = USART3_IRQn,
        .USART_RX_BUF = NULL,
        .USART_RX_LEN = 200,
        .USART_RX_STA = 0
};
#endif

#if (_BOARD_USE_SPI1)
spi_hw_t spi1_hw = {
        .SPI_MISO_CLK = RCC_APB2Periph_GPIOA,
        .SPI_MOSI_CLK = RCC_APB2Periph_GPIOA,
        .SPI_SCLK_CLK = RCC_APB2Periph_GPIOA,
        .SPI_SS_CLK = RCC_APB2Periph_GPIOA,
        .SPI_GPIO_APBxClock_FUN = RCC_APB1PeriphClockCmd,
        .SPI_MISO_PORT = GPIOA,
        .SPI_MOSI_PORT = GPIOA,
        .SPI_SCLK_PORT = GPIOA,
        .SPI_SS_PORT = GPIOA,
        .SPI_MISO_PIN = GPIO_Pin_6,
        .SPI_MOSI_PIN = GPIO_Pin_7,
        .SPI_SCLK_PIN = GPIO_Pin_5,
        .SPI_SS_PIN = GPIO_Pin_4,
        .SPI_RX_BUF = NULL,
        .SPI_RX_LEN = 100,
        .SPI_RX_STA = 0
};
#endif
