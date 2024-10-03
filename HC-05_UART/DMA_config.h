
#ifndef DMA_CONFIG_H_
#define DMA_CONFIG_H_

#include "lstd.h"

#define DMASoftwareChannelTransfer_InterruptNum (46)
#define DMAError_InterruptNum (47)
#define DMA_EnableDMAControllerBit   (0)

#define DMA_ListSize   (3)

/*************************** Madonna Naming Convention in config.h file ***************************/

/* 1-If the enum constants is used for storing the Indices of an Array then the enum name must end with IndexArr_t
 * Example of the enum name: PeripheralName_xxxxIndexArr_t
 *
 * 1.1- If the enum constants is used for storing the Indices of the array the Last constant must store the total
 * number of the indices and that constant name must end with _Indices
 *
 * 2-If the enum constants is used for storing values that will be inserted inside the hardware registers(configurations) then
 * the enum name must begin with Configure keyword
 * Example of the enum name: PeripheralName_Configurexxxxxxx_t
 *
 * 2.1- IF the configuration is related to turning on or off or even controlling a Specific feature
 * then the enum name must end with Mode_t
 * Example of the enum name: PeripheralName_ConfigurexxxxxMode_t
 *
 *
 * 3-If the struct is used to store the information of specific channel such as the channel number
 * and the instance of the typedef enum related to configurations then
 * the name of the struct must end with ConfigurationChannel_t
 * Example of the struct name: PeripheralName_xxxxxConfigurationChannel_t
 *
 * 4-The Name of the Array of pointer to struct must end with  _ArrPtrStruct
 *
 *
 * */
/*************************** Madonna Naming Convention in config.h file ***************************/

/* =====================================================================================*/
/*                                    ENUM                                              */
/* =====================================================================================*/


typedef enum{
    DMAChannel_0,
    DMAChannel_1,
    DMAChannel_2,
    DMAChannel_3,
    DMAChannel_4,
    DMAChannel_5,
    DMAChannel_6,
    DMAChannel_7,
    DMAChannel_8,
    DMAChannel_9,
    DMAChannel_10,
    DMAChannel_11,
    DMAChannel_12,
    DMAChannel_13,
    DMAChannel_14,
    DMAChannel_15,
    DMAChannel_16,
    DMAChannel_17,
    DMAChannel_18,
    DMAChannel_19,
    DMAChannel_20,
    DMAChannel_21,
    DMAChannel_22,
    DMAChannel_23,
    DMAChannel_24,
    DMAChannel_25,
    DMAChannel_26,
    DMAChannel_27,
    DMAChannel_28,
    DMAChannel_29,
    DMAChannel_30,
    DMAChannel_31,

}DMAChannelNum_t;

typedef enum{
    Byte_DestInc=0x0,
    HalfWord_DestInc=0x1,
    Word_DestInc=0x2,
    NoIncrement_DestInc=0x3
}DMA_DestAddressIncrement_t;


typedef enum{
    Byte_srcInc=0x0,
    HalfWord_srcInc=0x1,
    Word_srcInc=0x2,
    NoIncrement_srcInc=0x3
}DMA_SrcAddressIncrement_t;


typedef enum{
    Byte_DestData=0x0,
    HalfWord_DestData=0x1,
    Word_DestData=0x2,
}DMA_DestDataSize_t;


typedef enum{
    Byte_SrcData=0x0,
    HalfWord_SrcData=0x1,
    Word_SrcData=0x2,
}DMA_SrcDataSize_t;

typedef enum{
DisableSoftwareRequest,
EnableSoftwareRequest
}DMA_SoftwareRequestMode_t;

typedef enum{

    EnableInterrupt,
    ClearInterrupt
}DMA_InterruptStatus;

typedef enum{
    EncodingNum_0,
    EncodingNum_1,
    EncodingNum_2,
    EncodingNum_3,
    EncodingNum_4

}DMAEncodingNum_t;

typedef enum{
    SetDefaultPriorityChannel,
    SetHighPriorityChannel
}DMAConfigurePrioChannel_t;

typedef enum{
    StopMode,
    BasicMode,
    AutoRequest,
    PingPong,
    MemoryScatterGather,
    AlternateMemoryScatterGather,
    PeripheralScatterGather,
    AlternatePeripheralScatterGather
}DMA_ConfigTransferMode_t;

typedef enum{
    _1_Transfer,
    _2_Transfers,
    _4_Transfers,
    _8_Transfers,
    _16_Transfers,
    _32_Transfers,
    _64_Transfers,
    _128_Transfers,
    _256_Transfers,
    _512_Transfers,
    _1024_Transfers
}DMA_ConfigArbitSize_t;

typedef enum{
    DMA_SingleRequest,
    DMA_BurstRequest
}DMA_ConfigRequestType_t;


typedef struct{
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


typedef struct{
    u32_t * Pointer_SrcEndAddr;
    u32_t * Pointer_DstEndAddr;
    u32_t ControlWord;
    u32_t Unused;
}DMA_ListTable_t;

//Array of pointers to structures
extern DMA_ConfigurationChannel_t *DMA_ChannelsConfigTX[8];
extern DMA_ConfigurationChannel_t *DMA_ChannelsConfigRX[8];
extern DMA_ConfigurationChannel_t *Pt_DMAChannel30_MemToMem;
extern DMA_ConfigurationChannel_t *Pt_DMAChannel28_MemToMem;
extern DMA_ConfigurationChannel_t *Pt_DMAChannel29_MemToMem;
extern DMA_ConfigurationChannel_t *Pt_DMAChannel0_MemToMem;
extern DMA_ConfigurationChannel_t *Pt_DMAChannel1_MemToMem;




extern DMA_ListTable_t DMA_ControlTable_Arr[3];
extern DMA_ListTable_t DMA_ControlTable_PeripheralScatterGatherArr[DMA_ListSize];

#endif /* DMA_CONFIG_H_ */
