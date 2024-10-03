
#ifndef UART_H_
#define UART_H_

#include "UART_config.h"
#include "lstd.h"
#include "GPIO_config.h"
#include "DMA.h"
#define UARTRecTimeOut 600 //time in ms after which UART_RcCharwTimeOut function returns. A null is returned if nothing is received.

void UART_Initialization(UART_Config_t* pt_Config, GPIO_UARTConfigChannel_t* pt_UARTConfigChannel);
void UART_ConfigureInterruptSource(enum UART_IRQ_Event InterruptFlag, UART_InterruptMaskConfig_t InterruptMaskConfig, UART_Channel_t Channel);



void UART_TransmitChar_Polling(UART_Channel_t channel, u8_t *pTxBuffer);
void UART_RecieveChar_Polling(UART_Channel_t channel, u8_t *pRxBuffer);


void UART_TransmitChar_Interrupt(UART_Channel_t channel, u8_t *pRxBuffer);
void UART_RecieveChar_Interrupt(UART_Channel_t channel, u8_t *pRxBuffer);
void UART_RecCharwTimeOut (char* data,UART_Channel_t channel );


void UART_Transmit_DMA(UART_Channel_t Channel, u8_t *SourceAddressBuffer, DMAChannelNum_t DMAChannelNum);
void UART_Receive_DMA(UART_Channel_t Channel);
void UART_DMA_Reload_PrimaryControlStructure(UART_Channel_t Channel, u8_t *destAddressBuffer);
void UART_DMA_Reload_AlternateControlStructure(UART_Channel_t Channel, u8_t *destAddressBuffer);


void UART0_RegisterCallbackFunction(enum UART_IRQ_Event Flag, CallbackFunc_t pt_callback);
void UART1_RegisterCallbackFunction(enum UART_IRQ_Event Flag, CallbackFunc_t pt_callback);
void UART2_RegisterCallbackFunction(enum UART_IRQ_Event Flag, CallbackFunc_t pt_callback);
void UART3_RegisterCallbackFunction(enum UART_IRQ_Event Flag, CallbackFunc_t pt_callback);
void UART4_RegisterCallbackFunction(enum UART_IRQ_Event Flag, CallbackFunc_t pt_callback);
void UART5_RegisterCallbackFunction(enum UART_IRQ_Event Flag, CallbackFunc_t pt_callback);
void UART6_RegisterCallbackFunction(enum UART_IRQ_Event Flag, CallbackFunc_t pt_callback);
void UART7_RegisterCallbackFunction(enum UART_IRQ_Event Flag, CallbackFunc_t pt_callback);






#endif /* UART_H_ */
