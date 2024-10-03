/*************************************************************************************************************************************/
/* Name:   DMA.c                                                                                                                    */
/* Author: Madonna Magdy                                                                                                             */
/* Version: V1                                                                                                                       */
/* Usage: This module contains the implementation for the DMA functions                                                             */
/*************************************************************************************************************************************/

#include "DMA_reg.h"
#include "lstd.h"
#include "DMA.h"
#include "UART_config.h"
#include "UART.h"
#include "NVIC.h"
#include "GPIO.h"
#include<math.h>
#include "UART_reg.h"
extern u8_t SourceBuffer_DMA[1024];
extern u8_t DestBuffer_DMA[1024];
extern unsigned char volatile UARTDMA_TxFlag;
extern unsigned char volatile UARTDMA_RxFlag;
u8_t static DMA_InterruptFlag=0;

extern u8_t DestBufferA[1];
extern u8_t DestBufferB[1];

u8_t volatile ScatterGatherFlag=0;
extern s32_t SourceIndexCounterDMA;
extern s32_t SourceIndexCounterDMA356;
extern volatile  UARTFR_Reg  *const UART_FlagRegisters[8];
extern volatile  UARTICR_Reg  *const UART_InterruptClearRegisters[8];

//extern u8_t SourceBufferUART_380Byte[380];
/******************************************* ID Description of the Unit *********************************************************/
// first number of ID signifies the module used (the DMA driver takes number 2)

  //The Second number signifies that whether you are using a function or an array or a variable
 //(The variable takes number1 ,The array takes number 2, The function takes number 3  )

 //The Third number signifies the number of a function or an array or a variable

/******************************************* ID Description of the Unit ********************************************************/


/******************************  ID Description For Testing *********************************************************/

 //First part is the ID description of the Unit

 //The second part signifies how many number of tests you use on a certain variable or function (on a certain unit)

/******************************  ID Description For Testing *********************************************************/

/************************  UNIT ID: 2.2.1 *******************************************************/
/* UNIT ID: 2.2.1
 *
 * UNIT NAME: ui8ControlTable
 *
 * UNIT LOCATION: .bss section because it is uninitialized
 *
 * UNIT DESCRIPTION: the content of the array stores the Source pointer , destination pointer,
 * the control word and unused entry of EACH channel Control Structure.
 *
 *Source pointer for channelX--> 4 bytes
 *destination pointer for channelX--> 4 bytes
 *control word for channelX--> 4 bytes
 *unused entry for channelX--> 4 bytes
 *ThereFore, the total bytes for EACH channel will be 16 bytes
 *
 *UNIT NOTE: 1-the array is aligned on 1024-byte boundary according to the specification for tiva c document
 *           2-the array is NOT static because the address of the first location in the array will be the base address
 *           of control structure for each channel.Will be used in DMA_reg.h file
 *
 * */
unsigned char ui8ControlTable[1024] __attribute__ ((aligned(1024)));/*******************************/



/************************  UNIT ID: 2.2.2 *************************************************************/
/* UNIT ID: 6.2.2
 *
 * UNIT NAME: DMA_SoftwareTransfer_Callback
 *
 * UNIT LOCATION: The array is stored in .data section
 * At Runtime it will be copied to Ram memory as the content of the array might be changed
 *
 * UNIT DESCRIPTION:
 * Array of pointers to functions
 * the index of the array represents the the channel number
 * the content of the array represents pointer variable to function
 * static keyword is added because the function can not be called by the software the hardware will call it
 * volatile keyword is added because the value can be changed by hardware (disable optimization)
 * the pointer is of type CallbackFunc_t --> points to a function that returns void and takes void as an argument because
 * the call back function is not called by software so by logic no one will insert an argument
 * and the return type will be void because the user can not call it
 *
 * UNIT NOTE:
 * If you don't initialize DMA_SoftwareTransfer_Callback[] with a null pointer
 * and you forgot to register the call back function there will
 * be segmentation fault because you are trying to access a wild pointer

 * The advantage of the if condition ---> (if(DMA_SoftwareTransfer_Callback[] != NULL_PTR) )
 * you can't check on a garbage value but you can check on the null value
 * to see if the pointer to function (DMA_SoftwareTransfer_Callback[]) doesn't hold the
 * address of a function or doesn't hold a value
 *
 */
static volatile  CallbackFunc_t DMA_SoftwareTransfer_Callback[32]={NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,
                                                                   NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,
                                                                   NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,
                                                                   NULL_PTR,NULL_PTR};/***************************/



/************************  UNIT ID: 2.2.3 *************************************************************/
/* UNIT ID: 2.2.3
 *
 * UNIT NAME: DMA_ErrorHandler_Callback
 *
 * UNIT LOCATION: The array is stored in .data section
 * At Runtime it will be copied to Ram memory as the content of the array might be changed
 *
 * UNIT DESCRIPTION:
 * Array of pointers to functions
 * the index of the array represents the the channel number
 * the content of the array represents pointer variable to function
 * static keyword is added because the function can not be called by the software the hardware will call it
 * volatile keyword is added because the value can be changed by hardware (disable optimization)
 * the pointer is of type CallbackFunc_t --> points to a function that returns void and takes void as an argument because
 * the call back function is not called by software so by logic no one will insert an argument
 * and the return type will be void because the user can not call it
 *
 * UNIT NOTE:
 * If you don't initialize DMA_ErrorHandler_Callback[] with a null pointer
 * and you forgot to register the call back function there will
 * be segmentation fault because you are trying to access a wild pointer

 * The advantage of the if condition ---> (if(DMA_ErrorHandler_Callback[] != NULL_PTR) )
 * you can't check on a garbage value but you can check on the null value
 * to see if the pointer to function (DMA_ErrorHandler_Callback[]) doesn't hold the
 * address of a function or doesn't hold a value
 *
 */
static volatile  CallbackFunc_t DMA_ErrorHandler_Callback[32]={NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,
                                                               NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,
                                                               NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,
                                                               NULL_PTR,NULL_PTR};/***************************/

/*
int FindChannelNum_InterruptSource(){

    u32_t InterruptSourceFlag=0xFF;

    u32_t ChannelInterruptSources_bitNumbers= DMAChannelInterruptStatus & InterruptSourceFlag;

    if ( (ChannelInterruptSources_bitNumbers & 0) != 0 ){

        if (ChannelInterruptSources_bitNumbers == 2 || ChannelInterruptSources_bitNumbers == 3 ){

            return ChannelInterruptSources_bitNumbers;
        }
        else{
       u32_t Sqrt_ChannelInterruptSourcesVar= (u32_t) sqrt(ChannelInterruptSources_bitNumbers);

       return Sqrt_ChannelInterruptSourcesVar;
       //NOTE: if for example bit 3 and bit 4 is set (sqrt(12)) the lower number (HIGHER PRIORITY) will be returned
       //in our example number 3 will be returned due to the the casting performed  -->(u32_t) sqrt

        }


    }

    return 55555;

}*/

/*========================================Mem To Mem Mode====================================================*/
   /*DMAChannelInterruptStatus->Bits.ChannelInterruptStatus_9 =1; //clear the interrupt

   DMA_PeripheralInitialization();
   DMA_ChannelControlStructureSet(Pt_DMAChannel30_MemToMem, &SourceBuffer_DMA[2] , &DestBuffer_DMA[2] );
   DMA_EnableChannel(DMAChannel_30);
   DMA_ConfigureChannelSoftwareRequest(EnableSoftwareRequest , DMAChannel_30);*/


/*========================================Ping Pong Mode====================================================*/
      /* if(1==DMA_InterruptFlag){

           UART_DMA_Reload_PrimaryControlStructure(UART_Channel1, &DestBufferA[0]);
           DMA_ConfigureChannelSoftwareRequest(EnableSoftwareRequest , DMAChannel_22);

       }
       else if(0 == DMA_InterruptFlag){

           UART_DMA_Reload_AlternateControlStructure(UART_Channel1, &DestBufferB[0]);
           DMA_ConfigureChannelSoftwareRequest(EnableSoftwareRequest , DMAChannel_22);

       }

       DMA_InterruptFlag ^=1;
       DMAChannelInterruptStatus->Bits.ChannelInterruptStatus_22 =1; //clear the interrupt*/


DMA_ErrorHandler(){

  /*  u32_t ChannelNum_InterruptSource = FindChannelNum_InterruptSource();

     if (ChannelNum_InterruptSource != 0){

       if( DMA_ErrorHandler_Callback[ChannelNum_InterruptSource ] != NULL_PTR){

           DMA_ErrorHandler_Callback[ChannelNum_InterruptSource ]();//executing the call back function in the app layer

           DMAChannelInterruptStatus |= (1<<ChannelNum_InterruptSource); //clear the interrupt
       }
     }*/

    //DMAChannelInterruptStatus |= (1<<DMAChannel_9); //clear the interrupt
    DMABusErrorClear_Reg |=(1<<0);

}



volatile  u8_t** const SourceAddressPointerRegisters[32]={

   SourceAddressPointer_0,
   SourceAddressPointer_1,
   SourceAddressPointer_2,
   SourceAddressPointer_3,
   SourceAddressPointer_4,
   SourceAddressPointer_5,
   SourceAddressPointer_6,
   SourceAddressPointer_7,
   SourceAddressPointer_8,
   SourceAddressPointer_9,
   SourceAddressPointer_10,
   SourceAddressPointer_11,
   SourceAddressPointer_12,
   SourceAddressPointer_13,
   SourceAddressPointer_14,
   SourceAddressPointer_15,
   SourceAddressPointer_16,
   SourceAddressPointer_17,
   SourceAddressPointer_18,
   SourceAddressPointer_19,
   SourceAddressPointer_20,
   SourceAddressPointer_21,
   SourceAddressPointer_22,
   SourceAddressPointer_23,
   SourceAddressPointer_24,
   SourceAddressPointer_25,
   SourceAddressPointer_26,
   SourceAddressPointer_27,
   SourceAddressPointer_28,
   SourceAddressPointer_29,
   SourceAddressPointer_30,
   SourceAddressPointer_31
};


volatile  u8_t** const AlternateSourceAddressPointerRegisters[32]={

   AlternateSourceAddressPointer_0,
   AlternateSourceAddressPointer_1,
   AlternateSourceAddressPointer_2,
   AlternateSourceAddressPointer_3,
   AlternateSourceAddressPointer_4,
   AlternateSourceAddressPointer_5,
   AlternateSourceAddressPointer_6,
   AlternateSourceAddressPointer_7,
   AlternateSourceAddressPointer_8,
   AlternateSourceAddressPointer_9,
   AlternateSourceAddressPointer_10,
   AlternateSourceAddressPointer_11,
   AlternateSourceAddressPointer_12,
   AlternateSourceAddressPointer_13,
   AlternateSourceAddressPointer_14,
   AlternateSourceAddressPointer_15,
   AlternateSourceAddressPointer_16,
   AlternateSourceAddressPointer_17,
   AlternateSourceAddressPointer_18,
   AlternateSourceAddressPointer_19,
   AlternateSourceAddressPointer_20,
   AlternateSourceAddressPointer_21,
   AlternateSourceAddressPointer_22,
   AlternateSourceAddressPointer_23,
   AlternateSourceAddressPointer_24,
   AlternateSourceAddressPointer_25,
   AlternateSourceAddressPointer_26,
   AlternateSourceAddressPointer_27,
   AlternateSourceAddressPointer_28,
   AlternateSourceAddressPointer_29,
   AlternateSourceAddressPointer_30,
   AlternateSourceAddressPointer_31
};


volatile  u8_t ** const DestinationAddressPointerRegisters[32]={
    DestinationAddressPointer_0,
    DestinationAddressPointer_1,
    DestinationAddressPointer_2,
    DestinationAddressPointer_3,
    DestinationAddressPointer_4,
    DestinationAddressPointer_5,
    DestinationAddressPointer_6,
    DestinationAddressPointer_7,
    DestinationAddressPointer_8,
    DestinationAddressPointer_9,
    DestinationAddressPointer_10,
    DestinationAddressPointer_11,
    DestinationAddressPointer_12,
    DestinationAddressPointer_13,
    DestinationAddressPointer_14,
    DestinationAddressPointer_15,
    DestinationAddressPointer_16,
    DestinationAddressPointer_17,
    DestinationAddressPointer_18,
    DestinationAddressPointer_19,
    DestinationAddressPointer_20,
    DestinationAddressPointer_21,
    DestinationAddressPointer_22,
    DestinationAddressPointer_23,
    DestinationAddressPointer_24,
    DestinationAddressPointer_25,
    DestinationAddressPointer_26,
    DestinationAddressPointer_27,
    DestinationAddressPointer_28,
    DestinationAddressPointer_29,
    DestinationAddressPointer_30,
    DestinationAddressPointer_31
};


volatile  u8_t ** const AlternateDestinationAddressPointerRegisters[32]={
   AlternateDestinationAddressPointer_0,
   AlternateDestinationAddressPointer_1,
   AlternateDestinationAddressPointer_2,
   AlternateDestinationAddressPointer_3,
   AlternateDestinationAddressPointer_4,
   AlternateDestinationAddressPointer_5,
   AlternateDestinationAddressPointer_6,
   AlternateDestinationAddressPointer_7,
   AlternateDestinationAddressPointer_8,
   AlternateDestinationAddressPointer_9,
   AlternateDestinationAddressPointer_10,
   AlternateDestinationAddressPointer_11,
   AlternateDestinationAddressPointer_12,
   AlternateDestinationAddressPointer_13,
   AlternateDestinationAddressPointer_14,
   AlternateDestinationAddressPointer_15,
   AlternateDestinationAddressPointer_16,
   AlternateDestinationAddressPointer_17,
   AlternateDestinationAddressPointer_18,
   AlternateDestinationAddressPointer_19,
   AlternateDestinationAddressPointer_20,
   AlternateDestinationAddressPointer_21,
   AlternateDestinationAddressPointer_22,
   AlternateDestinationAddressPointer_23,
   AlternateDestinationAddressPointer_24,
   AlternateDestinationAddressPointer_25,
   AlternateDestinationAddressPointer_26,
   AlternateDestinationAddressPointer_27,
   AlternateDestinationAddressPointer_28,
   AlternateDestinationAddressPointer_29,
   AlternateDestinationAddressPointer_30,
   AlternateDestinationAddressPointer_31
};


volatile static DMACHCTL_Reg * const AlternateDMA_ChannelControlWordRegisters[32]={
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_0,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_1,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_2,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_3,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_4,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_5,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_6,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_7,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_8,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_9,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_10,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_11,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_12,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_13,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_14,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_15,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_16,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_17,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_18,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_19,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_20,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_21,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_22,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_23,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_24,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_25,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_26,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_27,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_28,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_29,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_30,
   (DMACHCTL_Reg*)AlternateDMA_ChannelControlWord_31
};


volatile static DMACHCTL_Reg * const DMA_ChannelControlWordRegisters[32]={
   (DMACHCTL_Reg*)DMA_ChannelControlWord_0,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_1,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_2,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_3,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_4,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_5,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_6,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_7,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_8,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_9,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_10,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_11,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_12,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_13,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_14,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_15,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_16,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_17,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_18,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_19,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_20,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_21,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_22,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_23,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_24,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_25,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_26,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_27,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_28,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_29,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_30,
   (DMACHCTL_Reg*)DMA_ChannelControlWord_31
};

volatile static u32_t *DMA_ChannelMapSelectRegisters[4]={
      (u32_t *)DMA_ChannelMapSelect0_Reg,
      (u32_t *)DMA_ChannelMapSelect1_Reg,
      (u32_t *)DMA_ChannelMapSelect2_Reg,
      (u32_t *)DMA_ChannelMapSelect3_Reg

};

u32_t handlerCounter=0;

DMA_SoftwareTransferHandler(){


    DMAChannelInterruptStatus->Bits.ChannelInterruptStatus_30 =1; //clear the interrupt
    GPIO_WriteBitBandBits(Channel_1, PortF, OutputLow);
   // handlerCounter++;
   // if(1==DMAChannelInterruptStatus->Bits.ChannelInterruptStatus_23){
     //UART_InterruptClearRegisters[1]->bits.TransmitInterruptClear=1;
     /*SourceIndexCounterDMA= SourceIndexCounterDMA-16;
     DMAChannelInterruptStatus->Bits.ChannelInterruptStatus_23 =1; //clear the interrupt

    if(SourceIndexCounterDMA>=0){
    UART_Transmit_DMA(UART_Channel1,  &SourceBuffer_DMA[SourceIndexCounterDMA], DMAChannel_23);
    (*DMA_ChannelControlWordRegisters[DMAChannel_23]).Bits.XFERSIZE=15;
    (*DMA_ChannelControlWordRegisters[DMAChannel_23]).Bits.XFERMODE=BasicMode;
    (*DMA_ChannelControlWordRegisters[DMAChannel_23]).Bits.DSTINC= NoIncrement_DestInc;
    DMA_EnableChannel(DMAChannel_23);
    DMA_ConfigureChannelSoftwareRequest(EnableSoftwareRequest , DMAChannel_23);
    }
    else if(SourceIndexCounterDMA<0){
        GPIO_WriteBitBandBits(Channel_1, PortF, OutputLow);
        handlerCounter++;
    }*/



    //}

   /* GPIO_WriteBitBandBits(Channel_1, PortF, OutputLow);
    handlerCounter++;

    if(1==DMAChannelInterruptStatus->Bits.ChannelInterruptStatus_0){
       // GPIO_WriteBitBandBits(Channel_1, PortF, OutputLow);
        DMAChannelInterruptStatus->Register=(1<<0); //clear the interrupt

    }

    if(1==DMAChannelInterruptStatus->Bits.ChannelInterruptStatus_1){
       // GPIO_WriteBitBandBits(Channel_1, PortF, OutputLow);
        DMAChannelInterruptStatus->Register=(1<<1);//clear the interrupt
    }

    if(1==DMAChannelInterruptStatus->Bits.ChannelInterruptStatus_23){
         GPIO_WriteBitBandBits(Channel_1, PortF, OutputHigh);
         UART_InterruptClearRegisters[1]->bits.TransmitInterruptClear=1;
         UART_Transmit_DMA(UART_Channel1,  ((u8_t*)0x400250FC), DMAChannel_23);

        (*DMA_ChannelControlWordRegisters[DMAChannel_23]).Bits.XFERMODE=BasicMode;
        (*DMA_ChannelControlWordRegisters[DMAChannel_23]).Bits.DSTINC= NoIncrement_DestInc;
        (*DMA_ChannelControlWordRegisters[DMAChannel_23]).Bits.SRCINC=NoIncrement_srcInc;
        DMA_EnableChannel(DMAChannel_23);
        DMA_ConfigureChannelSoftwareRequest(EnableSoftwareRequest , DMAChannel_23);

         DMAChannelInterruptStatus->Bits.ChannelInterruptStatus_23 =1; //clear the interrupt

        }*/

    /*if(1==DMAChannelInterruptStatus->Bits.ChannelInterruptStatus_23){

         //DMAChannelInterruptStatus->Bits.ChannelInterruptStatus_23 =1; //clear the interrupt
        DMAChannelInterruptStatus->Register=(1<<23); //clear the interrupt
        }*/


 }

//GPIO_WriteBitBandBits(Channel_1, PortF, OutputHigh);
//GPIO_WriteBitBandBits(Channel_1, PortF, OutputLow);
//handlerCounter++;
/*    GPIO_WriteBitBandBits(Channel_1, PortF, OutputHigh);
UART_InterruptClearRegisters[1]->bits.ReceiveInterruptClear=1;
SourceIndexCounterDMA= SourceIndexCounterDMA-8;

if(SourceIndexCounterDMA>0){

UART_DMA_Reload_PrimaryControlStructure(UART_Channel1, &DestBuffer_DMA[SourceIndexCounterDMA]);
UART_Receive_DMA(UART_Channel1);
//UART_Transmit_DMA(UART_Channel1,  &SourceBuffer_DMA[SourceIndexCounterDMA], DMAChannel_23);
(*DMA_ChannelControlWordRegisters[DMAChannel_22]).Bits.XFERSIZE=7;
(*DMA_ChannelControlWordRegisters[DMAChannel_22]).Bits.XFERMODE=BasicMode;
//(*DMA_ChannelControlWordRegisters[DMAChannel_22]).Bits.DSTINC= NoIncrement_DestInc;
(*DMA_ChannelControlWordRegisters[DMAChannel_22]).Bits.SRCINC=NoIncrement_srcInc;
DMA_EnableChannel(DMAChannel_22);
DMA_ConfigureChannelSoftwareRequest(EnableSoftwareRequest , DMAChannel_22);
}
else if(SourceIndexCounterDMA==0){
  GPIO_WriteBitBandBits(Channel_1, PortF, OutputLow);
}

DMAChannelInterruptStatus->Bits.ChannelInterruptStatus_22 =1; //clear the interrupt*/

/************************************************************************************************************************/
/*                                      Initialization Functions                                                        */
/************************************************************************************************************************/

void DMA_PeripheralInitialization(){


      /*Enable the DMA clock*/
     RCGCDMA_REG->Bits.DMAModuleRunModeClockGatingControl=1;

    /*********************************STEP2***************************************/
     /*Enable the μDMA controller by setting the MASTEREN bit*/
     DMAConfiguration_Reg |=(1<<DMA_EnableDMAControllerBit);

     //DMA_ConfigureControlTableBaseAddress(&ui8ControlTable[0]);
     /*********************************STEP3***************************************/
     (DMA_ChannelControlBasePointer)->Register=(u32_t)ui8ControlTable;

     /*********************************STEP4***************************************/
     //DMA_ConfigurePeripheralInterrupt(EnableInterrupt);
}


void DMA_EnableChannelAttributes(DMA_ConfigurationChannel_t* PtrDMAConfig){

    /*********************************STEP1***************************************/
    /*set the channel to High priority or Default priority*/
    DMA_ConfigurePriority(PtrDMAConfig->PrioChannel, PtrDMAConfig->ChannelNum);

    /*********************************STEP2***************************************/
    /*select the primary channel control structure for this transfer*/
    DMAChannelPrimaryAlternateClear_Reg |=(1<<(PtrDMAConfig->ChannelNum));

    /*********************************STEP3***************************************/
    /*allow the μDMA controller to respond to single and burst requests*/
    DMAChannelUseBurstClear_Reg |=(1<<(PtrDMAConfig->ChannelNum));
    //DMAChannelUseBurstSet_Reg |=(1<<(PtrDMAConfig->ChannelNum)); // disable single request

    /*********************************STEP4***************************************/
    /*allow the μDMA controller to recognize requests for this channel*/
    DMAChannelRequestMaskClear |=(1<<(PtrDMAConfig->ChannelNum));

    /*********************************STEP5***************************************/
    DMA_AssignChannel(PtrDMAConfig->ChannelNum, PtrDMAConfig->EncodingNum);

    /*********************************STEP6***************************************/
    DMA_ConfigureChannelInterrupt(EnableInterrupt, PtrDMAConfig->ChannelNum);
}

void DMA_DisableChannelAttributes(DMA_ConfigurationChannel_t* PtrDMAConfig){

    if(SetHighPriorityChannel == PtrDMAConfig->PrioChannel){

        DMAChannelPriorityClear_Reg |= (1<< (PtrDMAConfig->ChannelNum) );
    }

    if(DMA_BurstRequest == PtrDMAConfig->RequestType){

        DMAChannelUseBurstClear_Reg |=(1<< (PtrDMAConfig->ChannelNum) );
    }

    DMAChannelRequestMaskClear |=(1<< (PtrDMAConfig->ChannelNum) );

}

void DMA_ConfigureControlTableBaseAddress(void *ptControlTable){

    DMA_ChannelControlBasePointer->Bits.ChannelControlBaseAddress=(u32_t )ptControlTable;
}

void DMA_EnableChannel(DMAChannelNum_t ChannelNum){
    DMAChannelEnableSet_Reg |=(1<<ChannelNum);
}


void DMA_ChannelControlStructureSet(DMA_ConfigurationChannel_t* ptrConfig, u8_t*SourceAddress , u8_t*DestAddress ){

    if((0==UARTDMA_RxFlag) || (0==ScatterGatherFlag)){
     *(SourceAddressPointerRegisters[ptrConfig->ChannelNum])=(u8_t*)SourceAddress;
    }

    if((0==UARTDMA_TxFlag) || (0==ScatterGatherFlag)){
     *(DestinationAddressPointerRegisters[ptrConfig->ChannelNum])=(u8_t*)DestAddress;
    }

    (*DMA_ChannelControlWordRegisters[ptrConfig->ChannelNum]).Bits.DSTINC=ptrConfig->DestAddressIncrement;
    (*DMA_ChannelControlWordRegisters[ptrConfig->ChannelNum]).Bits.DSTSIZE=ptrConfig->DestDataSize;
    (*DMA_ChannelControlWordRegisters[ptrConfig->ChannelNum]).Bits.SRCINC=ptrConfig->SrcAddressIncrement;
    (*DMA_ChannelControlWordRegisters[ptrConfig->ChannelNum]).Bits.SRCSIZE=ptrConfig->SrcDataSize;
    (*DMA_ChannelControlWordRegisters[ptrConfig->ChannelNum]).Bits.XFERMODE=ptrConfig->TransferMode;
    (*DMA_ChannelControlWordRegisters[ptrConfig->ChannelNum]).Bits.XFERSIZE=ptrConfig->TransferSize;
    (*DMA_ChannelControlWordRegisters[ptrConfig->ChannelNum]).Bits.ARBSIZE=ptrConfig->ArbitSize;

}

void DMA_ChannelAlternateControlStructureSet(DMA_ConfigurationChannel_t* ptrConfig, u8_t*SourceAddress , u8_t*DestAddress){

    if((0==UARTDMA_RxFlag) || (0==ScatterGatherFlag)){
    *(AlternateSourceAddressPointerRegisters[ptrConfig->ChannelNum])=(u8_t*)SourceAddress;
    }

    if((0==UARTDMA_TxFlag) || (0==ScatterGatherFlag)){
    *(AlternateDestinationAddressPointerRegisters[ptrConfig->ChannelNum])=(u8_t*)DestAddress;
    }

    (*AlternateDMA_ChannelControlWordRegisters[ptrConfig->ChannelNum]).Bits.DSTINC=ptrConfig->DestAddressIncrement;
    (*AlternateDMA_ChannelControlWordRegisters[ptrConfig->ChannelNum]).Bits.DSTSIZE=ptrConfig->DestDataSize;
    (*AlternateDMA_ChannelControlWordRegisters[ptrConfig->ChannelNum]).Bits.SRCINC=ptrConfig->SrcAddressIncrement;
    (*AlternateDMA_ChannelControlWordRegisters[ptrConfig->ChannelNum]).Bits.SRCSIZE=ptrConfig->SrcDataSize;
    (*AlternateDMA_ChannelControlWordRegisters[ptrConfig->ChannelNum]).Bits.XFERMODE=ptrConfig->TransferMode;
    (*AlternateDMA_ChannelControlWordRegisters[ptrConfig->ChannelNum]).Bits.XFERSIZE=ptrConfig->TransferSize;
    (*AlternateDMA_ChannelControlWordRegisters[ptrConfig->ChannelNum]).Bits.ARBSIZE=ptrConfig->ArbitSize;

}


void DMA_ConfigureChannelSoftwareRequest(DMA_SoftwareRequestMode_t RequestMode,DMAChannelNum_t ChannelNum){

    switch(RequestMode){

    case DisableSoftwareRequest:
        DMAChannelSoftwareRequest_Register &= ~(1<<ChannelNum);
   break;

    case EnableSoftwareRequest:
        DMAChannelSoftwareRequest_Register |= (1<<ChannelNum);
    break;

    }

}

void DMA_ConfigureChannelsRequests(u32_t ChannelsNum){

    DMAChannelSoftwareRequest_Register |=(ChannelsNum);
}

void DMA_ConfigurePeripheralInterrupt(DMA_InterruptStatus Status){

        if(EnableInterrupt == Status){
        NVIC_Enable_Interrupt(DMASoftwareChannelTransfer_InterruptNum);
        NVIC_Enable_Interrupt(DMAError_InterruptNum);
    }

    else if(ClearInterrupt == Status){
        NVIC_Clear_Interrupt(DMASoftwareChannelTransfer_InterruptNum);
        NVIC_Clear_Interrupt(DMAError_InterruptNum);
    }

}



void DMA_ConfigureChannelInterrupt(DMA_InterruptStatus Status, DMAChannelNum_t ChannelNum){

    switch(Status){
      case EnableInterrupt:
         DMAChannelInterruptStatus->Register |=(1<<ChannelNum);

      case ClearInterrupt:
        DMAChannelInterruptStatus->Register &= ~(1<<ChannelNum);
    }

}

void DMA_ConfigurePriority(DMAConfigurePrioChannel_t ConfigurePrioChannel, DMAChannelNum_t ChannelNum){

    switch(ConfigurePrioChannel){

    case SetDefaultPriorityChannel:
        DMAChannelPrioritySet_Reg &= ~(1<<ChannelNum);
    break;

    case SetHighPriorityChannel:
        DMAChannelPrioritySet_Reg |= (1<<ChannelNum);
    break;

    }
}

void DMA_AssignChannel(u8_t DMA_ChannelNum, DMAEncodingNum_t EncodingNum){

    u8_t RegisterNum=(u8_t)(DMA_ChannelNum/8);
    u8_t BitNum =((DMA_ChannelNum-(RegisterNum*8))*4) + EncodingNum;
    *DMA_ChannelMapSelectRegisters[RegisterNum]|=(1<<BitNum);
}

void DMA_DeAssignChannel(u8_t DMA_ChannelNum, DMAEncodingNum_t EncodingNum){

    u8_t RegisterNum=(u8_t)(DMA_ChannelNum/8);
    u8_t BitNum =((DMA_ChannelNum-(RegisterNum*8))*4) + EncodingNum;
    *DMA_ChannelMapSelectRegisters[RegisterNum]&=~(1<<BitNum);
}


void DMA_MemoryToMemory_Transfer(u8_t*SourceAddress , u8_t*DestAddress){

    DMA_ChannelControlStructureSet(Pt_DMAChannel30_MemToMem,(u8_t*)SourceAddress, (u8_t*)DestAddress );

    /************************Start Transfer********************************/
    DMA_ConfigureChannelSoftwareRequest(EnableSoftwareRequest , DMAChannel_30);
    DMA_EnableChannel(DMAChannel_30);


}


void DMA_ChannelScatterGatherSet(DMA_ConfigurationChannel_t* ptrConfig){

    *(SourceAddressPointer28_SW)=&DMA_ControlTable_Arr[2].Unused;
    *(DestinationAddressPointer28_SW)=AlternateEndAddressPointer28_SW;
     ScatterGatherFlag=1;
    DMA_ChannelControlStructureSet(ptrConfig, 0x00 , 0x00 );
    ScatterGatherFlag=0;

    //
    // Scatter-gather operations can leave the alt bit set.  So if doing
    // back to back scatter-gather transfers, the second attempt may not
    // work correctly because the alt bit is set.  Therefore, clear the
    // alt bit here to ensure that it is always cleared before a new SG
    // transfer is started.
    //

    DMAChannelPrimaryAlternateClear_Reg |=(1<<(ptrConfig->ChannelNum));

}


void DMA_ChannelPeripheralScatterGatherSet(DMA_ConfigurationChannel_t* ptrConfig){

     *(SourceAddressPointer29_SW)=&DMA_ControlTable_PeripheralScatterGatherArr[DMA_ListSize-1].Unused;
     *(DestinationAddressPointer29_SW)=AlternateEndAddressPointer29_SW;
     ScatterGatherFlag=1;
    DMA_ChannelControlStructureSet(ptrConfig, 0x00 , 0x00 );
    ScatterGatherFlag=0;

    //
    // Scatter-gather operations can leave the alt bit set.  So if doing
    // back to back scatter-gather transfers, the second attempt may not
    // work correctly because the alt bit is set.  Therefore, clear the
    // alt bit here to ensure that it is always cleared before a new SG
    // transfer is started.
    //

    DMAChannelPrimaryAlternateClear_Reg |=(1<<(ptrConfig->ChannelNum));

}

 void DMA_RegisterCallbackFunction_SoftwareTransfer(DMAChannelNum_t ChannelNum, CallbackFunc_t pt_callback){

     DMA_SoftwareTransfer_Callback[ChannelNum]=pt_callback;

 }

 void DMA_RegisterCallbackFunction_ErrorHandler(DMAChannelNum_t ChannelNum, CallbackFunc_t pt_callback){

     DMA_ErrorHandler_Callback[ChannelNum]=pt_callback;

 }
