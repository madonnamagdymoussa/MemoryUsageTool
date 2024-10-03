//#include <stdio.h>
#include "HC-05.h"
#include "GPIO.h"
#include "GPIO_config.h"
#include "GPTM_config.h"
#include "GPTM.h"
#include "DMA.h"
#include "UART.h"
#include "NVIC.h"
#include "SystemControl.h"
#include "SystemControl_config.h"
#include "SystickTimer.h"

#include <stdio.h>
#include <stdlib.h>

u8_t charater1=0xAB;
u8_t *ptr_charater1=&charater1;

u8_t SourceBuffer_DMA[1024] ;
u8_t DestBufferA[1];
u8_t DestBufferB[1];
u8_t DestBuffer_DMA[1024];


u32_t ListA[1]={0xAB};
u32_t ListB[1]={0xCD};
u32_t ListC[1]={0xEF};


u32_t ListD[2]={0xAAABCBDD,0XFF223344};
u32_t ListE[2]={0x34567891,0x11778899};
u32_t ListF[2]={0x66557799,0xEE77AAD3};

u32_t ListDest[6];
u32_t IndexCounter=0;

u8_t SourceBufferUART[8]={0xAA,0xBB,0xCC,0xDD,0xEE,0xFF,0x99,0x88};
u32_t indexCounter=0;
s32_t SourceIndexCounterDMA=1023;
s32_t SourceIndexCounterDMA356=356;
u32_t MySystemClock;
u32_t static volatile unused_var1=1;
u32_t static volatile unused_var2=2;
u32_t static unused_var3=3;
u32_t static unused_var4=4;


u8_t SourceArray512[512];
u8_t DestArray512[512];
//u8_t SourceBufferUART_350Byte[350];
u32_t volatile IdleLoopCounter=0;

void UnusedFunc1(void){
    u32_t Indexcounter;
    u32_t counter;

    for(Indexcounter=0;Indexcounter<100;Indexcounter++){
        counter++;
    }
}

int main(void)
{

    //void SysTickGenerateDelay_Interrupt(u32_t NumDelayUnit, GPTM_DelayUnit_t DelayUnit){

    /*****************************Global Interrupt Enable****************************/
     __asm("  CPSIE  I");
     //SC_Initialization(&ConfigSystemSrc_PrecisionInternalOSC_DIV4);
     SysTickConfigureClockSource(SysClk);
     MySystemClock= SC_GetSystemClock();

     /*****************************Output Pin used for logical Analyzer ****************************/
      GPIO_ConfigureOutputPin(&GPIO_ConfigurePin_PF1);
      GPIO_ConfigureInputPin(&GPIO_ConfigurePin_PF0);
      GPIO_ConfigureInputPin(&GPIO_ConfigurePin_PF4);

     /***************************** Initialize the Source Buffer with Random Number ****************************/
     /*for(IndexCounter=0;IndexCounter<1024;IndexCounter++){
         SourceBuffer_DMA[IndexCounter]=rand();

     }

     for(IndexCounter=0;IndexCounter<512;IndexCounter++){
         SourceArray512[IndexCounter]=rand();
     }*/

     /**************************************GPIO to UART DMA [peripheral to peripheral]****************************************/
     /*UART_Initialization(&UARTChannel1_Config, GPIO_AFSELUARTConfig_ArrPtrStruct[1]);

     DMA_PeripheralInitialization();

     DMA_EnableChannelAttributes(DMA_ChannelsConfigTX[1]);

     DMA_ConfigurePriority(SetHighPriorityChannel, DMAChannel_23);

     DMA_ConfigurePeripheralInterrupt(EnableInterrupt);
     DMA_ConfigureChannelInterrupt(EnableInterrupt, DMAChannel_23);
     UART_Transmit_DMA(UART_Channel1,  ((u8_t*)0x400250FC), DMAChannel_23);

     DMA_EnableChannel(DMAChannel_23);
     GPIO_WriteBitBandBits(Channel_1, PortF, OutputLow);
     //GPIO_WriteBitBandBits(Channel_1, PortF, OutputHigh);
     DMA_ConfigureChannelSoftwareRequest(EnableSoftwareRequest , DMAChannel_23);*/

     /**************************************GPIO to UART Polling [peripheral to peripheral]****************************************/
     /*UART_Initialization(&UARTChannel1_Config, GPIO_AFSELUARTConfig_ArrPtrStruct[1]);

     if( 0 == GPIO_ReadBitBandBits(Channel_4,PortF) ){

          GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 180, milli_Sec);


          if(0 == GPIO_ReadBitBandBits(Channel_4,PortF) ){
              Leds_RedLedOn();
              while( 0 == GPIO_ReadBitBandBits(Channel_4,PortF)  );
              GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 30, milli_Sec);
          }
      }*/


     /**************************************Arbitration Scenario [three channels]***************************************/
     /*DMA_PeripheralInitialization();

     // Channel 0 (highest priority): Arbitration Size 1024
     DMA_ChannelControlStructureSet(Pt_DMAChannel0_MemToMem, &SourceBuffer_DMA[1023] , &DestBuffer_DMA[1023] );
     DMA_EnableChannelAttributes(Pt_DMAChannel0_MemToMem);
     DMA_AssignChannel(DMAChannel_0, EncodingNum_3);
     DMA_EnableChannel(DMAChannel_0);
     DMA_ConfigurePeripheralInterrupt(EnableInterrupt);
     DMA_ConfigureChannelInterrupt(EnableInterrupt, DMAChannel_0);
     //GPIO_WriteBitBandBits(Channel_1, PortF, OutputLow);
     //GPIO_WriteBitBandBits(Channel_1, PortF, OutputHigh);

     // Channel 1 (Mid level priority): Arbitration Size 512
     DMA_ChannelControlStructureSet(Pt_DMAChannel1_MemToMem, &SourceArray512[511] , &DestArray512[511] );
     DMA_EnableChannelAttributes(Pt_DMAChannel1_MemToMem);
     DMA_AssignChannel(DMAChannel_1, EncodingNum_4);
     DMA_EnableChannel(DMAChannel_1);
     DMA_ConfigurePeripheralInterrupt(EnableInterrupt);
     DMA_ConfigureChannelInterrupt(EnableInterrupt, DMAChannel_1);
     GPIO_WriteBitBandBits(Channel_1, PortF, OutputLow);
     GPIO_WriteBitBandBits(Channel_1, PortF, OutputHigh);

       //DMA_ConfigureChannelSoftwareRequest(EnableSoftwareRequest , DMAChannel_0);
       //DMA_ConfigureChannelSoftwareRequest(EnableSoftwareRequest , DMAChannel_1);

     //Channel 23 UART
     UART_Initialization(&UARTChannel1_Config, GPIO_AFSELUARTConfig_ArrPtrStruct[1]);
     DMA_EnableChannelAttributes(DMA_ChannelsConfigTX[1]);
     DMA_ConfigurePriority(SetHighPriorityChannel, DMAChannel_23);
     DMA_ConfigureChannelInterrupt(EnableInterrupt, DMAChannel_23);
     UART_Transmit_DMA(UART_Channel1,  &SourceBuffer_DMA[1023], DMAChannel_23);
     DMA_EnableChannel(DMAChannel_23);

     DMA_ConfigureChannelsRequests(0x00800003);*/

    //*******************Code for Mem To Mem DMA *******************
    DMA_PeripheralInitialization();
    DMA_ChannelControlStructureSet(Pt_DMAChannel30_MemToMem, &SourceBuffer_DMA[1023] , &DestBuffer_DMA[1023] );
    DMA_EnableChannelAttributes(Pt_DMAChannel30_MemToMem);
    DMA_AssignChannel(DMAChannel_30, EncodingNum_0);
    DMA_EnableChannel(DMAChannel_30);
    DMA_ConfigurePeripheralInterrupt(EnableInterrupt);
    DMA_ConfigureChannelInterrupt(EnableInterrupt, DMAChannel_30);
    //GPIO_WriteBitBandBits(Channel_1, PortF, OutputLow);
    //GPIO_WriteBitBandBits(Channel_1, PortF, OutputHigh);
    SysTickGenerateDelay_Interrupt(1, Sec);
    DMA_ConfigureChannelSoftwareRequest(EnableSoftwareRequest , DMAChannel_30);

    /*****************************************Copy data from Source to destination using Software **********************************************/
    /* GPIO_WriteBitBandBits(Channel_1, PortF, OutputLow);
     GPIO_WriteBitBandBits(Channel_1, PortF, OutputHigh);
     for(IndexCounter=0;IndexCounter<1024;IndexCounter++){

         DestBuffer_DMA[IndexCounter] =SourceBuffer_DMA[IndexCounter];
     }
     GPIO_WriteBitBandBits(Channel_1, PortF, OutputLow);*/


 //*******************Code for Mem To peripheral DMA UART Transmit [==Burst Request 1024 Bytes==]*******************

      /*GPIO_WriteBitBandBits(Channel_1, PortF, OutputLow);

      UART_Initialization(&UARTChannel1_Config, GPIO_AFSELUARTConfig_ArrPtrStruct[1]);

      DMA_PeripheralInitialization();

      DMA_EnableChannelAttributes(DMA_ChannelsConfigTX[1]);

      DMA_ConfigurePriority(SetHighPriorityChannel, DMAChannel_23);

      DMA_ConfigurePeripheralInterrupt(EnableInterrupt);
      DMA_ConfigureChannelInterrupt(EnableInterrupt, DMAChannel_23);
      UART_Transmit_DMA(UART_Channel1,  &SourceBuffer_DMA[1023], DMAChannel_23);

      DMA_EnableChannel(DMAChannel_23);
      GPIO_WriteBitBandBits(Channel_1, PortF, OutputHigh);
      SysTickGenerateDelay_Interrupt(1, Sec);
      DMA_ConfigureChannelSoftwareRequest(EnableSoftwareRequest , DMAChannel_23);
      //void DMA_ConfigureChannelsRequests(u8_t ChannelsNum)*/


//*******************Code for Mem To peripheral DMA UART Receive [==Burst Request 1024 Bytes==]*******************

     /*UART_Initialization(&UARTChannel1_Config, GPIO_AFSELUARTConfig_ArrPtrStruct[1]);

     DMA_PeripheralInitialization();

     DMA_EnableChannelAttributes(DMA_ChannelsConfigRX[1]);

     DMA_ConfigurePriority(SetHighPriorityChannel, DMAChannel_22);

     DMA_ConfigurePeripheralInterrupt(EnableInterrupt);
     DMA_ConfigureChannelInterrupt(EnableInterrupt, DMAChannel_22);
     UART_DMA_Reload_PrimaryControlStructure(UART_Channel1, &DestBuffer_DMA[1023]);
     UART_Receive_DMA(UART_Channel1);
     DMA_EnableChannel(DMAChannel_22);
     SysTickGenerateDelay_Interrupt(1, Sec);
     GPIO_WriteBitBandBits(Channel_1, PortF, OutputLow);
     GPIO_WriteBitBandBits(Channel_1, PortF, OutputHigh);
     DMA_ConfigureChannelSoftwareRequest(EnableSoftwareRequest , DMAChannel_22);*/


      //*******************Code for Mem To peripheral Polling UART Transmit [===========20 Bytes================]*******************
        /*UART_Initialization(&UARTChannel1_Config, GPIO_AFSELUARTConfig_ArrPtrStruct[1]);

        GPIO_WriteBitBandBits(Channel_1, PortF, OutputLow);
        GPIO_WriteBitBandBits(Channel_1, PortF, OutputHigh);

        for(indexCounter=0;indexCounter<1023;indexCounter++){
            UART_TransmitChar_Polling(UART_Channel1, &SourceBuffer_DMA[indexCounter]);
        }

        GPIO_WriteBitBandBits(Channel_1, PortF, OutputLow);
        indexCounter++;*/
      //*******************Code for Mem To pheripheral Receive *******************

      /*DMA_EnableChannelAttributes(DMA_ChannelsConfigRX[1]);

       UART_DMA_Reload_PrimaryControlStructure(UART_Channel1, &DestBufferA[0]);
       UART_DMA_Reload_AlternateControlStructure(UART_Channel1, &DestBufferB[0]);

      UART_Receive_DMA(UART_Channel1);
      DMA_EnableChannel(DMAChannel_22);
      DMA_ConfigureChannelSoftwareRequest(EnableSoftwareRequest , DMAChannel_22);
      DMA_ConfigureChannelInterrupt(EnableInterrupt, DMAChannel_22);*/


      //*******************Code for Memory Scatter Gather *******************
      /*DMA_PeripheralInitialization();
      DMA_EnableChannelAttributes(Pt_DMAChannel28_MemToMem);
      DMA_ConfigurePriority(SetHighPriorityChannel, DMAChannel_28);
      DMA_ConfigurePeripheralInterrupt(EnableInterrupt);
      DMA_ChannelScatterGatherSet(Pt_DMAChannel28_MemToMem);
      DMA_ConfigureChannelInterrupt(EnableInterrupt, DMAChannel_28);
      DMA_EnableChannel(DMAChannel_28);
      DMA_ConfigureChannelSoftwareRequest(EnableSoftwareRequest , DMAChannel_28);*/

      //*******************Code for Peripheral Scatter Gather *******************
      /*UART_Initialization(&UARTChannel1_Config, GPIO_AFSELUARTConfig_ArrPtrStruct[1]);
      DMA_PeripheralInitialization();
      UART_Transmit_DMA(UART_Channel1);
      DMA_EnableChannelAttributes(Pt_DMAChannel29_MemToMem);
      DMA_ConfigurePriority(SetHighPriorityChannel, DMAChannel_29);
      DMA_ChannelPeripheralScatterGatherSet(Pt_DMAChannel29_MemToMem);
      DMA_EnableChannel(DMAChannel_29);
      DMA_ConfigureChannelSoftwareRequest(EnableSoftwareRequest , DMAChannel_29);
      DMA_ConfigureChannelSoftwareRequest(EnableSoftwareRequest , DMAChannel_29);
      DMA_ConfigureChannelSoftwareRequest(EnableSoftwareRequest , DMAChannel_29);*/
    //SysTickGenerateDelay_Interrupt(1, Sec);
    /*asm("   nop");
    asm("   nop");
    asm("   nop");
    asm("   nop");
    asm("   nop");
    asm("   nop");
    asm("   nop");
    asm("   nop");
    asm("   nop");
    asm("   nop");
    asm("   nop");
    asm("   nop");
    asm("   nop");
    asm("   nop");
    asm("   nop");
    asm("   nop");
    asm("   nop");
    asm("   nop");
    asm("   nop");
    asm("   nop");
    asm("   nop");
    asm("   nop");
    asm("   nop");
    asm("   nop");
    asm("   nop");
    asm("   nop");
    asm("   nop");
    asm("   nop");
    asm("   nop");*/

    static int static_var = 5;  // This should also go into .data
    int local_var = 0;  // This will be in .text section

    while(1){
        local_var++;  // Simple loop to ensure code isn't optimized out


        //GPIO_WriteBitBandBits(Channel_1, PortF, OutputHigh);
       // IdleLoopCounter++;
        //GPIO_WriteBitBandBits(Channel_1, PortF, OutputLow);
        //IdleLoopCounter++;
        /* UART_DMA_Reload_PrimaryControlStructure(UART_Channel1, &DestBufferA[0]);
        DMA_ConfigureChannelSoftwareRequest(EnableSoftwareRequest , DMAChannel_22);

        UART_DMA_Reload_AlternateControlStructure(UART_Channel1, &DestBufferB[0]);
        DMA_ConfigureChannelSoftwareRequest(EnableSoftwareRequest , DMAChannel_22);*/

     }

}
