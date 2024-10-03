
#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

#include "lstd.h"

typedef enum{
    UART_Channel0,
    UART_Channel1,
    UART_Channel2,
    UART_Channel3,
    UART_Channel4,
    UART_Channel5,
    UART_Channel6,
    UART_Channel7,

}UART_Channel_t;

typedef enum{

    SystemClock =0x0,
    PIOC=0X5

}
UART_ClockSource_t;


typedef enum{
    _5bits=0x0,
    _6bits=0x1,
   _7bits=0x2,
   _8bits=0x3

}UART_WordLenght_t;

 enum UART_IRQ_Event{

     UART_IRQ_TXNF, //transmit data register empty
     UART_IRQ_RXNE, //recieve not empty
     UART_IRQ_ORE,
     UART_IRQ_PE,
     UART_IRQ_FE
};

typedef enum{
    DisableInterruptMask,
    EnableInterruptMask
}UART_InterruptMaskConfig_t;

typedef struct{

    UART_Channel_t Channel;
    UART_WordLenght_t  WordLenght;
    UART_ClockSource_t Clocksource;
    u32_t baud;
    u32_t pclk;

}UART_Config_t;

/*
 * Value Description
  0x0 TX FIFO ≤ ⅞ empty
  0x1 TX FIFO ≤ ¾ empty
  0x2 TX FIFO ≤ ½ empty (default)
  0x3 TX FIFO ≤ ¼ empty
  0x4 TX FIFO ≤ ⅛ empty
 * */

typedef enum{

    _7_DIV_8_Empty,
    _3_DIV_4_Empty,
    _1_DIV_2_Empty,
    _1_DIV_4_Empty,
    _1_DIV_8_Empty

}UART_InterruptFIFOLevel_t;



extern UART_Config_t UARTChannel1_Config;

#endif /* UART_CONFIG_H_ */
