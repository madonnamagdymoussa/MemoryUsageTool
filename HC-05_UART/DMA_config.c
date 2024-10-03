#include "DMA_config.h"
#include "UART_reg.h"

/*
 * typedef struct{
    DMAChannelNum_t ChannelNum;
    DMA_DestAddressIncrement_t DestAddressIncrement;
    DMA_SrcAddressIncrement_t SrcAddressIncrement;
    DMA_DestDataSize_t DestDataSize;
    DMA_SrcDataSize_t SrcDataSize;
}DMA_ChannelControlWordConfig_t;
 *
 */

extern u32_t ListA[1];
extern u32_t ListB[1];
extern u32_t ListDest[6];
extern u32_t ListC[1];
//u32_t ListTransferSize= DMA_ListSize*4-1;

extern u8_t ListA1[1];
extern u8_t ListB1[1];

extern u32_t ListD[2];
extern u32_t ListE[2];
extern u32_t ListF[2];


DMA_ConfigurationChannel_t  DMAChannel8_UARTChannel0RX={
     DMAChannel_8,
     Byte_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode,
     SetDefaultPriorityChannel
};

DMA_ConfigurationChannel_t DMAChannel9_UARTChannel0TX={
     DMAChannel_9,
     NoIncrement_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode,
     SetDefaultPriorityChannel
};

/****************************************************************************************************/
DMA_ConfigurationChannel_t  DMAChannel22_UARTChannel1RX={
     DMAChannel_22,
     Byte_DestInc,
     NoIncrement_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode,
     SetHighPriorityChannel,
     EncodingNum_0,
     _8_Transfers ,
     DMA_BurstRequest,
     7
};


DMA_ConfigurationChannel_t  DMAChannel23_UARTChannel1TX={
     DMAChannel_23,
     NoIncrement_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode,
     SetHighPriorityChannel,
     EncodingNum_0,
     _16_Transfers ,
     DMA_BurstRequest,
     15
};

/*DMA_ConfigurationChannel_t  DMAChannel23_UARTChannel1TX={
     DMAChannel_23,
     NoIncrement_DestInc,
     NoIncrement_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode,
     SetDefaultPriorityChannel,
     EncodingNum_0,
     _1_Transfer,
     DMA_SingleRequest,
     0
};*/

/****************************************************************************************************/
DMA_ConfigurationChannel_t DMAChannel0_UARTChannel2RX={
     DMAChannel_0,
     Byte_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode,
     SetDefaultPriorityChannel
};

DMA_ConfigurationChannel_t DMAChannel23_UARTChannel2TX={
     DMAChannel_1,
     NoIncrement_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode,
     SetDefaultPriorityChannel
};
/****************************************************************************************************/

DMA_ConfigurationChannel_t DMAChannel16_UARTChannel3RX={
     DMAChannel_16,
     Byte_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode,
     SetDefaultPriorityChannel
};

DMA_ConfigurationChannel_t DMAChannel17_UARTChannel3TX={
     DMAChannel_17,
     NoIncrement_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode,
     SetDefaultPriorityChannel
};
/****************************************************************************************************/
DMA_ConfigurationChannel_t  DMAChannel18_UARTChannel4RX={
     DMAChannel_18,
     Byte_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode,
     SetDefaultPriorityChannel
};

DMA_ConfigurationChannel_t DMAChannel19_UARTChannel4TX={
     DMAChannel_19,
     NoIncrement_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode,
     SetDefaultPriorityChannel
};
/****************************************************************************************************/


DMA_ConfigurationChannel_t DMAChannel6_UARTChannel5RX={
     DMAChannel_6,
     Byte_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode,
     SetDefaultPriorityChannel
};

DMA_ConfigurationChannel_t DMAChannel7_UARTChannel5TX={
     DMAChannel_7,
     NoIncrement_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode,
     SetDefaultPriorityChannel
};
/****************************************************************************************************/
DMA_ConfigurationChannel_t DMAChannel10_UARTChannel6RX={
     DMAChannel_10,
     Byte_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode,
     SetDefaultPriorityChannel
};

DMA_ConfigurationChannel_t DMAChannel11_UARTChannel6TX={
     DMAChannel_11,
     NoIncrement_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode,
     SetDefaultPriorityChannel
};
/****************************************************************************************************/
DMA_ConfigurationChannel_t DMAChannel20_UARTChannel7RX={
     DMAChannel_20,
     NoIncrement_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode,
     SetDefaultPriorityChannel
};

DMA_ConfigurationChannel_t DMAChannel21_UARTChannel7TX={
     DMAChannel_21,
     NoIncrement_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode,
     SetDefaultPriorityChannel
};
/****************************************************************************************************/

DMA_ConfigurationChannel_t  *   DMA_ChannelsConfigTX[8]={

  &DMAChannel9_UARTChannel0TX,
  &DMAChannel23_UARTChannel1TX,
  &DMAChannel23_UARTChannel2TX,
  &DMAChannel17_UARTChannel3TX,
  &DMAChannel19_UARTChannel4TX,
  &DMAChannel7_UARTChannel5TX,
  &DMAChannel11_UARTChannel6TX,
  &DMAChannel21_UARTChannel7TX
};

DMA_ConfigurationChannel_t *DMA_ChannelsConfigRX[8]={

   &DMAChannel8_UARTChannel0RX,
   &DMAChannel22_UARTChannel1RX,
   &DMAChannel0_UARTChannel2RX,
   &DMAChannel16_UARTChannel3RX,
   &DMAChannel18_UARTChannel4RX,
   &DMAChannel6_UARTChannel5RX,
   &DMAChannel10_UARTChannel6RX,
   &DMAChannel20_UARTChannel7RX

 };

/*
 * typedef struct{
    DMAChannelNum_t ChannelNum;
    DMA_DestAddressIncrement_t DestAddressIncrement;
    DMA_SrcAddressIncrement_t SrcAddressIncrement;
    DMA_DestDataSize_t DestDataSize;
    DMA_SrcDataSize_t SrcDataSize;
    DMA_ConfigTransferMode_t TransferMode;
    DMAConfigurePrioChannel_t PrioChannel;
    DMAEncodingNum_t EncodingNum;
    DMA_ConfigArbitSize_t ArbitSize;

    DMA_ConfigRequestType_t RequestType;
    u32_t TransferSize;

}DMA_ConfigurationChannel_t;
 *
 *
 * */
/****************************************************************************************************/
DMA_ConfigurationChannel_t  DMAChannel0_MemToMem={
     DMAChannel_0,
     Byte_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode,
     SetDefaultPriorityChannel,
     EncodingNum_4,
     _1024_Transfers,
     DMA_BurstRequest,
     1023
};

DMA_ConfigurationChannel_t  DMAChannel1_MemToMem={
     DMAChannel_1,
     Byte_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     BasicMode,
     SetHighPriorityChannel,
     EncodingNum_4,
     _512_Transfers,
     DMA_BurstRequest,
     511
};


DMA_ConfigurationChannel_t  DMAChannel30_MemToMem={
     DMAChannel_30,
     Byte_DestInc,
     Byte_srcInc,
     Byte_DestData,
     Byte_SrcData,
     AutoRequest,
     SetHighPriorityChannel,
     EncodingNum_0,
     _1024_Transfers,
     DMA_BurstRequest,
     1023
};

DMA_ConfigurationChannel_t  DMAChannel28_MemToMem={
     DMAChannel_28,
     Word_DestInc,
     Word_srcInc,
     Word_DestData,
     Word_SrcData,
     MemoryScatterGather,
     SetHighPriorityChannel,
     EncodingNum_0,
     _4_Transfers,
     DMA_SingleRequest,
     11 //DMA_ListSize*4-1
};

DMA_ConfigurationChannel_t  DMAChannel29_MemToMem={
     DMAChannel_29,
     Word_DestInc,
     Word_srcInc,
     Word_DestData,
     Word_SrcData,
     PeripheralScatterGather,
     SetHighPriorityChannel,
     EncodingNum_0,
     _4_Transfers,
     DMA_SingleRequest,
     11 //DMA_ListSize*4-1
};

DMA_ConfigurationChannel_t  DMAChannel26_MemToMem={
     DMAChannel_26,
     Word_DestInc,
     Word_srcInc,
     Word_DestData,
     Word_SrcData,
     AutoRequest,
     SetHighPriorityChannel,
     EncodingNum_0,
     _1024_Transfers,
     DMA_SingleRequest,
     0x3FF
};


DMA_ConfigurationChannel_t *Pt_DMAChannel30_MemToMem=&DMAChannel30_MemToMem;
DMA_ConfigurationChannel_t *Pt_DMAChannel28_MemToMem=&DMAChannel28_MemToMem;
DMA_ConfigurationChannel_t *Pt_DMAChannel29_MemToMem=&DMAChannel29_MemToMem;
DMA_ConfigurationChannel_t *Pt_DMAChannel0_MemToMem=&DMAChannel0_MemToMem;
DMA_ConfigurationChannel_t *Pt_DMAChannel1_MemToMem=&DMAChannel1_MemToMem;

/****************************************************************************************************/

/*typedef struct{
    u8_t * Pointer_SrcEndAddr;
    u8_t * Pointer_DstEndAddr;
    u32_t Items;
    u32_t Unused;
}DMA_ControlTable_t;*/

/*extern u32_t ListD[2];
extern u32_t ListE[1];
extern u32_t ListF[4];
 * */
DMA_ListTable_t DMA_ControlTable_Arr[3]={

   {
    &ListD[1],
    &ListDest[1],
      0xAA000015
   },
   {
    &ListE[1],
    &ListDest[3],
    0xAA000015
   },

   {
    &ListF[1],
    &ListDest[5],
    0xAA000015
   }


};

DMA_ListTable_t DMA_ControlTable_PeripheralScatterGatherArr[DMA_ListSize]={

   {
    &ListA[0],
    (u32_t*)0x4000D000,
      0x22000007
   },
   {
    &ListB[0],
    (u32_t*)0x4000D000,
    0x22000007
   },

   {
    &ListC[0],
    (u32_t*)0x4000D000,
    0x22000007
   }

};

