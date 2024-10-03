#include "UART.h"
#include "lstd.h"
#include "DMA.h"
#include "DMA_config.h"
#include "UART_config.h"
#include "lstd.h"

void HC05_Initialization(void){
 UART_Initialization(&UARTChannel1_Config, GPIO_AFSELUARTConfig_ArrPtrStruct[1]);

}

void HC05_Initialization_DMA(void){

 UART_Initialization(&UARTChannel1_Config, GPIO_AFSELUARTConfig_ArrPtrStruct[1]);
 DMA_PeripheralInitialization();
// DMA_ChannelInitialization(DMAChannel_9, DMA_ChannelsConfigTX[1]);
 //DMA_ChannelInitialization(DMAChannel_8, DMA_ChannelsConfigRX[1]);

}

void HC05_SendString_DMA(u8_t *pTxBuffer){

    DMA_ConfigurePriority(SetHighPriorityChannel, DMAChannel_9);
    //UART_Transmit_DMA(UART_Channel1, (u32_t*)pTxBuffer, DMAChannel_9);

    /************************Start Transfer********************************/
    DMA_ConfigureChannelSoftwareRequest(EnableSoftwareRequest , DMAChannel_9);
    DMA_EnableChannel(DMAChannel_9);
}


void HC05_ReceiveString_DMA(u8_t *pRxBuffer){

    DMA_ConfigurePriority(SetHighPriorityChannel, DMAChannel_8);
    //UART_Receive_DMA(UART_Channel1, (u32_t*)pRxBuffer, DMAChannel_8);

    /************************Start Transfer********************************/
    DMA_ConfigureChannelSoftwareRequest(EnableSoftwareRequest , DMAChannel_8);
    DMA_EnableChannel(DMAChannel_8);
}

void HC05_ReadChar(u8_t *CharacterRead){

    UART_RecieveChar_Polling(UART_Channel1, CharacterRead);

}


void HC05_WriteChar(u8_t *pTxBuffer){
 UART_TransmitChar_Polling(UART_Channel1, pTxBuffer);

}

void HC05_WriteString(u8_t* String  ){

    while(*String){

        HC05_WriteChar(String++);
    }
}
