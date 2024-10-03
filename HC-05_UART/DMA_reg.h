
#ifndef DMA_REG_H_
#define DMA_REG_H_

#include "lstd.h"

/***********************************Base Address DMA****************************************/
#define DMA_BASE  0x400FF000
/***********************************Base Address DMA****************************************/
extern unsigned char ui8ControlTable[1024];
/**********************************OFFSET*************************************/
#define DMACFG_OFFSET     0x004
#define DMACTLBASE_OFFSET 0x008
#define DMADSTENDP_OFFSET 0x004
#define DMACHCTL_OFFSET   0x008
#define DMASWREQ_OFFSET   0x014
#define DMACHMAP0_OFFSET  0x510
#define DMACHMAP1_OFFSET  0x514
#define DMACHMAP2_OFFSET  0x518
#define DMACHMAP3_OFFSET  0x51C

#define AlternateControlTable_BaseAddress  (ui8ControlTable + 0x200)
/**********************************OFFSET*************************************/

/***************************************Base Address of each channel control structure **************************************************/
#define ChannelControl0_BaseAddress  (ui8ControlTable)
#define ChannelControl1_BaseAddress  (ui8ControlTable + 0x10)
#define ChannelControl2_BaseAddress  (ui8ControlTable + 0x20)
#define ChannelControl3_BaseAddress  (ui8ControlTable + 0x30)
#define ChannelControl4_BaseAddress  (ui8ControlTable + 0x40)
#define ChannelControl5_BaseAddress  (ui8ControlTable + 0x50)
#define ChannelControl6_BaseAddress  (ui8ControlTable + 0x60)
#define ChannelControl7_BaseAddress  (ui8ControlTable + 0x70)
#define ChannelControl8_BaseAddress  (ui8ControlTable + 0x80)
#define ChannelControl9_BaseAddress  (ui8ControlTable + 0x90)
#define ChannelControl10_BaseAddress (ui8ControlTable + 0xA0)
#define ChannelControl11_BaseAddress (ui8ControlTable + 0xB0)
#define ChannelControl12_BaseAddress (ui8ControlTable + 0xC0)
#define ChannelControl13_BaseAddress (ui8ControlTable + 0xD0)
#define ChannelControl14_BaseAddress (ui8ControlTable + 0xE0)
#define ChannelControl15_BaseAddress (ui8ControlTable + 0xF0)
#define ChannelControl16_BaseAddress (ui8ControlTable + 0x100)
#define ChannelControl17_BaseAddress (ui8ControlTable + 0x110)
#define ChannelControl18_BaseAddress (ui8ControlTable + 0x120)
#define ChannelControl19_BaseAddress (ui8ControlTable + 0x130)
#define ChannelControl20_BaseAddress (ui8ControlTable + 0x140)
#define ChannelControl21_BaseAddress (ui8ControlTable + 0x150)
#define ChannelControl22_BaseAddress (ui8ControlTable + 0x160)
#define ChannelControl23_BaseAddress (ui8ControlTable + 0x170)
#define ChannelControl24_BaseAddress (ui8ControlTable + 0x180)
#define ChannelControl25_BaseAddress (ui8ControlTable + 0x190)
#define ChannelControl26_BaseAddress (ui8ControlTable + 0x1A0)
#define ChannelControl27_BaseAddress (ui8ControlTable + 0x1B0)
#define ChannelControl28_BaseAddress (ui8ControlTable + 0x1C0)
#define ChannelControl29_BaseAddress (ui8ControlTable + 0x1D0)
#define ChannelControl30_BaseAddress (ui8ControlTable + 0x1E0)
#define ChannelControl31_BaseAddress (ui8ControlTable + 0x1F0)

#define AlternateChannelControl0_BaseAddress  (AlternateControlTable_BaseAddress)
#define AlternateChannelControl1_BaseAddress  (ui8ControlTable + 0x200 + 0x10)
#define AlternateChannelControl2_BaseAddress  (ui8ControlTable + 0x200 + 0x20)
#define AlternateChannelControl3_BaseAddress  (AlternateControlTable_BaseAddress + 0x30)
#define AlternateChannelControl4_BaseAddress  (AlternateControlTable_BaseAddress + 0x40)
#define AlternateChannelControl5_BaseAddress  (AlternateControlTable_BaseAddress + 0x50)
#define AlternateChannelControl6_BaseAddress  (AlternateControlTable_BaseAddress + 0x60)
#define AlternateChannelControl7_BaseAddress  (AlternateControlTable_BaseAddress + 0x70)
#define AlternateChannelControl8_BaseAddress  (AlternateControlTable_BaseAddress + 0x80)
#define AlternateChannelControl9_BaseAddress  (AlternateControlTable_BaseAddress + 0x90)
#define AlternateChannelControl10_BaseAddress (AlternateControlTable_BaseAddress + 0xA0)
#define AlternateChannelControl11_BaseAddress (AlternateControlTable_BaseAddress + 0xB0)
#define AlternateChannelControl12_BaseAddress (AlternateControlTable_BaseAddress + 0xC0)
#define AlternateChannelControl13_BaseAddress (AlternateControlTable_BaseAddress + 0xD0)
#define AlternateChannelControl14_BaseAddress (AlternateControlTable_BaseAddress + 0xE0)
#define AlternateChannelControl15_BaseAddress (AlternateControlTable_BaseAddress + 0xF0)
#define AlternateChannelControl16_BaseAddress (AlternateControlTable_BaseAddress + 0x100)
#define AlternateChannelControl17_BaseAddress (AlternateControlTable_BaseAddress + 0x110)
#define AlternateChannelControl18_BaseAddress (AlternateControlTable_BaseAddress + 0x120)
#define AlternateChannelControl19_BaseAddress (AlternateControlTable_BaseAddress + 0x130)
#define AlternateChannelControl20_BaseAddress (AlternateControlTable_BaseAddress + 0x140)
#define AlternateChannelControl21_BaseAddress (AlternateControlTable_BaseAddress + 0x150)
#define AlternateChannelControl22_BaseAddress (AlternateControlTable_BaseAddress + 0x160)
#define AlternateChannelControl23_BaseAddress (AlternateControlTable_BaseAddress + 0x170)
#define AlternateChannelControl24_BaseAddress (AlternateControlTable_BaseAddress + 0x180)
#define AlternateChannelControl25_BaseAddress (AlternateControlTable_BaseAddress + 0x190)
#define AlternateChannelControl26_BaseAddress (AlternateControlTable_BaseAddress + 0x1A0)
#define AlternateChannelControl27_BaseAddress (AlternateControlTable_BaseAddress + 0x1B0)
#define AlternateChannelControl28_BaseAddress (AlternateControlTable_BaseAddress + 0x1C0)
#define AlternateChannelControl29_BaseAddress (AlternateControlTable_BaseAddress + 0x1D0)
#define AlternateChannelControl30_BaseAddress (AlternateControlTable_BaseAddress + 0x1E0)
#define AlternateChannelControl31_BaseAddress (AlternateControlTable_BaseAddress + 0x1F0)


/***************************************Base Address of each channel control structure **************************************************/

typedef union {

    struct{

      u32_t  MasterEnableStatus:1;
      u32_t                    :3;
      u32_t ControlStateMachineStatus :4;
      u32_t :8;
      u32_t AvailableDMAChannelsMinus1:5;
      u32_t :11;

    }Bits;

    u32_t Register;
}DMASTAT_Reg;


typedef union {

    struct {

    u32_t  ControllerMasterEnable:1;
    u32_t :31;

    }Bits;

    u32_t Register;

}DMACFG_Reg;


typedef union{

    struct{

        u32_t :10;
        u32_t ChannelControlBaseAddress :22;

    }Bits;

 u32_t Register;

}DMACTLBASE_Reg;


typedef union {

    struct{

     u32_t DMAModuleRunModeClockGatingControl:1;
     u32_t :31;
    }Bits;

    u32_t Register;

}RCGCDMA_Reg;


typedef union{

    struct{
        u32_t XFERMODE    :3;
        u32_t NXTUSEBURST :1;
        u32_t XFERSIZE    :10;
        u32_t ARBSIZE     :4;
        u32_t             :6;
        u32_t SRCSIZE     :2;
        u32_t SRCINC      :2;
        u32_t DSTSIZE     :2;
        u32_t DSTINC      :2;

    }Bits;

    u32_t Register;

}DMACHCTL_Reg;



typedef union{
    struct{

        u32_t CH0SEL:4;
        u32_t CH1SEL:4;
        u32_t CH2SEL:4;
        u32_t CH3SEL:4;
        u32_t CH4SEL:4;
        u32_t CH5SEL:4;
        u32_t CH6SEL:4;
        u32_t CH7SEL:4;
    }Bits;
    u32_t Register;
}DMACHMAP0_Reg;


typedef union{
    struct{

        u32_t CH8SEL:4;
        u32_t CH9SEL:4;
        u32_t CH10SEL:4;
        u32_t CH11SEL:4;
        u32_t CH12SEL:4;
        u32_t CH13SEL:4;
        u32_t CH14SEL:4;
        u32_t CH15SEL:4;
    }Bits;
    u32_t Register;
}DMACHMAP1_Reg;

typedef union{
    struct{

        u32_t CH16SEL:4;
        u32_t CH17SEL:4;
        u32_t CH18SEL:4;
        u32_t CH19SEL:4;
        u32_t CH20SEL:4;
        u32_t CH21SEL:4;
        u32_t CH22SEL:4;
        u32_t CH23SEL:4;
    }Bits;
    u32_t Register;
}DMACHMAP2_Reg;

typedef union{
    struct{

        u32_t CH24SEL:4;
        u32_t CH25SEL:4;
        u32_t CH26SEL:4;
        u32_t CH27SEL:4;
        u32_t CH28SEL:4;
        u32_t CH29SEL:4;
        u32_t CH30SEL:4;
        u32_t CH31SEL:4;
    }Bits;
    u32_t Register;
}DMACHMAP3_Reg;


typedef union{

    struct{

        u32_t ChannelInterruptStatus_0:1;
        u32_t ChannelInterruptStatus_1:1;
        u32_t ChannelInterruptStatus_2:1;
        u32_t ChannelInterruptStatus_3:1;
        u32_t ChannelInterruptStatus_4:1;
        u32_t ChannelInterruptStatus_5:1;
        u32_t ChannelInterruptStatus_6:1;
        u32_t ChannelInterruptStatus_7:1;
        u32_t ChannelInterruptStatus_8:1;
        u32_t ChannelInterruptStatus_9:1;
        u32_t ChannelInterruptStatus_10:1;
        u32_t ChannelInterruptStatus_11:1;
        u32_t ChannelInterruptStatus_12:1;
        u32_t ChannelInterruptStatus_13:1;
        u32_t ChannelInterruptStatus_14:1;
        u32_t ChannelInterruptStatus_15:1;
        u32_t ChannelInterruptStatus_16:1;
        u32_t ChannelInterruptStatus_17:1;
        u32_t ChannelInterruptStatus_18:1;
        u32_t ChannelInterruptStatus_19:1;
        u32_t ChannelInterruptStatus_20:1;
        u32_t ChannelInterruptStatus_21:1;
        u32_t ChannelInterruptStatus_22:1;
        u32_t ChannelInterruptStatus_23:1;
        u32_t ChannelInterruptStatus_24:1;
        u32_t ChannelInterruptStatus_25:1;
        u32_t ChannelInterruptStatus_26:1;
        u32_t ChannelInterruptStatus_27:1;
        u32_t ChannelInterruptStatus_28:1;
        u32_t ChannelInterruptStatus_29:1;
        u32_t ChannelInterruptStatus_30:1;
        u32_t ChannelInterruptStatus_31:1;
    }Bits;
    u32_t Register;
}DMACHIS_Reg;

#define RCGCDMA_REG ((RCGCDMA_Reg volatile*)(0x400FE000 + 0x60C) )
#define DMA_ChannelControlBasePointer   ( (volatile DMACTLBASE_Reg*)(DMA_BASE+DMACTLBASE_OFFSET) )

#define SourceAddressPointer_0  ((volatile u8_t**)(ChannelControl0_BaseAddress))
#define SourceAddressPointer_1  ((volatile u8_t**)(ChannelControl1_BaseAddress))
#define SourceAddressPointer_2  ((volatile u8_t**)(ChannelControl2_BaseAddress))
#define SourceAddressPointer_3  ((volatile u8_t**)(ChannelControl3_BaseAddress))
#define SourceAddressPointer_4  ((volatile u8_t**)(ChannelControl4_BaseAddress))
#define SourceAddressPointer_5  ((volatile u8_t**)(ChannelControl5_BaseAddress))
#define SourceAddressPointer_6  ((volatile u8_t**)(ChannelControl6_BaseAddress))
#define SourceAddressPointer_7  ((volatile u8_t**)(ChannelControl7_BaseAddress))
#define SourceAddressPointer_8  ((volatile u8_t**)(ChannelControl8_BaseAddress))
#define SourceAddressPointer_9  ((volatile u8_t**)(ChannelControl9_BaseAddress))
#define SourceAddressPointer_10 ((volatile u8_t**)(ChannelControl10_BaseAddress))
#define SourceAddressPointer_11 ((volatile u8_t**)(ChannelControl11_BaseAddress))
#define SourceAddressPointer_12 ((volatile u8_t**)(ChannelControl12_BaseAddress))
#define SourceAddressPointer_13 ((volatile u8_t**)(ChannelControl13_BaseAddress))
#define SourceAddressPointer_14 ((volatile u8_t**)(ChannelControl14_BaseAddress))
#define SourceAddressPointer_15 ((volatile u8_t**)(ChannelControl15_BaseAddress))
#define SourceAddressPointer_16 ((volatile u8_t**)(ChannelControl16_BaseAddress))
#define SourceAddressPointer_17 ((volatile u8_t**)(ChannelControl17_BaseAddress))
#define SourceAddressPointer_18 ((volatile u8_t**)(ChannelControl18_BaseAddress))
#define SourceAddressPointer_19 ((volatile u8_t**)(ChannelControl19_BaseAddress))
#define SourceAddressPointer_20 ((volatile u8_t**)(ChannelControl20_BaseAddress))
#define SourceAddressPointer_21 ((volatile u8_t**)(ChannelControl21_BaseAddress))
#define SourceAddressPointer_22 ((volatile u8_t**)(ChannelControl22_BaseAddress))
#define SourceAddressPointer_23 ((volatile u8_t**)(ChannelControl23_BaseAddress))
#define SourceAddressPointer_24 ((volatile u8_t**)(ChannelControl24_BaseAddress))
#define SourceAddressPointer_25 ((volatile u8_t**)(ChannelControl25_BaseAddress))
#define SourceAddressPointer_26 ((volatile u8_t**)(ChannelControl26_BaseAddress))
#define SourceAddressPointer_27 ((volatile u8_t**)(ChannelControl27_BaseAddress))
#define SourceAddressPointer_28 ((volatile u8_t**)(ChannelControl28_BaseAddress))
#define SourceAddressPointer_29 ((volatile u8_t**)(ChannelControl29_BaseAddress))
#define SourceAddressPointer_30 ((volatile u8_t**)(ChannelControl30_BaseAddress))
#define SourceAddressPointer_31 ((volatile u8_t**)(ChannelControl31_BaseAddress))


#define AlternateSourceAddressPointer_0  ((volatile u8_t**)(AlternateChannelControl0_BaseAddress))
#define AlternateSourceAddressPointer_1  ((volatile u8_t**)(AlternateChannelControl1_BaseAddress))
#define AlternateSourceAddressPointer_2  ((volatile u8_t**)(AlternateChannelControl2_BaseAddress))
#define AlternateSourceAddressPointer_3  ((volatile u8_t**)(AlternateChannelControl3_BaseAddress))
#define AlternateSourceAddressPointer_4  ((volatile u8_t**)(AlternateChannelControl4_BaseAddress))
#define AlternateSourceAddressPointer_5  ((volatile u8_t**)(AlternateChannelControl5_BaseAddress))
#define AlternateSourceAddressPointer_6  ((volatile u8_t**)(AlternateChannelControl6_BaseAddress))
#define AlternateSourceAddressPointer_7  ((volatile u8_t**)(AlternateChannelControl7_BaseAddress))
#define AlternateSourceAddressPointer_8  ((volatile u8_t**)(AlternateChannelControl8_BaseAddress))
#define AlternateSourceAddressPointer_9  ((volatile u8_t**)(AlternateChannelControl9_BaseAddress))
#define AlternateSourceAddressPointer_10 ((volatile u8_t**)(AlternateChannelControl10_BaseAddress))
#define AlternateSourceAddressPointer_11 ((volatile u8_t**)(AlternateChannelControl11_BaseAddress))
#define AlternateSourceAddressPointer_12 ((volatile u8_t**)(AlternateChannelControl12_BaseAddress))
#define AlternateSourceAddressPointer_13 ((volatile u8_t**)(AlternateChannelControl13_BaseAddress))
#define AlternateSourceAddressPointer_14 ((volatile u8_t**)(AlternateChannelControl14_BaseAddress))
#define AlternateSourceAddressPointer_15 ((volatile u8_t**)(AlternateChannelControl15_BaseAddress))
#define AlternateSourceAddressPointer_16 ((volatile u8_t**)(AlternateChannelControl16_BaseAddress))
#define AlternateSourceAddressPointer_17 ((volatile u8_t**)(AlternateChannelControl17_BaseAddress))
#define AlternateSourceAddressPointer_18 ((volatile u8_t**)(AlternateChannelControl18_BaseAddress))
#define AlternateSourceAddressPointer_19 ((volatile u8_t**)(AlternateChannelControl19_BaseAddress))
#define AlternateSourceAddressPointer_20 ((volatile u8_t**)(AlternateChannelControl20_BaseAddress))
#define AlternateSourceAddressPointer_21 ((volatile u8_t**)(AlternateChannelControl21_BaseAddress))
#define AlternateSourceAddressPointer_22 ((volatile u8_t**)(AlternateChannelControl22_BaseAddress))
#define AlternateSourceAddressPointer_23 ((volatile u8_t**)(AlternateChannelControl23_BaseAddress))
#define AlternateSourceAddressPointer_24 ((volatile u8_t**)(AlternateChannelControl24_BaseAddress))
#define AlternateSourceAddressPointer_25 ((volatile u8_t**)(AlternateChannelControl25_BaseAddress))
#define AlternateSourceAddressPointer_26 ((volatile u8_t**)(AlternateChannelControl26_BaseAddress))
#define AlternateSourceAddressPointer_27 ((volatile u8_t**)(AlternateChannelControl27_BaseAddress))
#define AlternateSourceAddressPointer_28 ((volatile u8_t**)(AlternateChannelControl28_BaseAddress))
#define AlternateSourceAddressPointer_29 ((volatile u8_t**)(AlternateChannelControl29_BaseAddress))
#define AlternateSourceAddressPointer_30 ((volatile u8_t**)(AlternateChannelControl30_BaseAddress))
#define AlternateSourceAddressPointer_31 ((volatile u8_t**)(AlternateChannelControl31_BaseAddress))




#define DestinationAddressPointer_0  ((volatile u8_t**)(ChannelControl0_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_1  ((volatile u8_t**)(ChannelControl1_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_2  ((volatile u8_t**)(ChannelControl2_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_3  ((volatile u8_t**)(ChannelControl3_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_4  ((volatile u8_t**)(ChannelControl4_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_5  ((volatile u8_t**)(ChannelControl5_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_6  ((volatile u8_t**)(ChannelControl6_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_7  ((volatile u8_t**)(ChannelControl7_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_8  ((volatile u8_t**)(ChannelControl8_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_9  ((volatile u8_t**)(ChannelControl9_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_10 ((volatile u8_t**)(ChannelControl10_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_11 ((volatile u8_t**)(ChannelControl11_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_12 ((volatile u8_t**)(ChannelControl12_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_13 ((volatile u8_t**)(ChannelControl13_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_14 ((volatile u8_t**)(ChannelControl14_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_15 ((volatile u8_t**)(ChannelControl15_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_16 ((volatile u8_t**)(ChannelControl16_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_17 ((volatile u8_t**)(ChannelControl17_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_18 ((volatile u8_t**)(ChannelControl18_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_19 ((volatile u8_t**)(ChannelControl19_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_20 ((volatile u8_t**)(ChannelControl20_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_21 ((volatile u8_t**)(ChannelControl21_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_22 ((volatile u8_t**)(ChannelControl22_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_23 ((volatile u8_t**)(ChannelControl23_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_24 ((volatile u8_t**)(ChannelControl24_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_25 ((volatile u8_t**)(ChannelControl25_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_26 ((volatile u8_t**)(ChannelControl26_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_27 ((volatile u8_t**)(ChannelControl27_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_28 ((volatile u8_t**)(ChannelControl28_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_29 ((volatile u8_t**)(ChannelControl29_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_30 ((volatile u8_t**)(ChannelControl30_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer_31 ((volatile u8_t**)(ChannelControl31_BaseAddress + DMADSTENDP_OFFSET))


#define DestinationAddressPointer9_UART  ((volatile u32_t**)(ChannelControl9_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer23_UART ((volatile u32_t**)(ChannelControl23_BaseAddress + DMADSTENDP_OFFSET))
#define SourceAddressPointer22_UART ((volatile u32_t**)(ChannelControl22_BaseAddress))
#define AlternateSourceAddressPointer22_UART ((volatile u32_t**)(AlternateChannelControl22_BaseAddress))


/*
 * #define SourceAddressPointer_28 ((volatile u8_t**)(ChannelControl28_BaseAddress))
   #define SourceAddressPointer_29 ((volatile u8_t**)(ChannelControl29_BaseAddress))
 *
 * */

#define SourceAddressPointer28_SW  ((volatile u32_t**)(ChannelControl28_BaseAddress))
#define SourceAddressPointer29_SW  ((volatile u32_t**)(ChannelControl29_BaseAddress))

#define DestinationAddressPointer28_SW ((volatile u32_t**)(ChannelControl28_BaseAddress + DMADSTENDP_OFFSET))
#define DestinationAddressPointer29_SW ((volatile u32_t**)(ChannelControl29_BaseAddress + DMADSTENDP_OFFSET))


#define AlternateEndAddressPointer28_SW  ( (volatile u32_t**)((AlternateChannelControl28_BaseAddress+0x00C)) )
#define AlternateEndAddressPointer29_SW  ( (volatile u32_t**)((AlternateChannelControl29_BaseAddress+0x00C)) )



#define AlternateDestinationAddressPointer_0  ((volatile u8_t**)(AlternateChannelControl0_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_1  ((volatile u8_t**)(AlternateChannelControl1_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_2  ((volatile u8_t**)(AlternateChannelControl2_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_3  ((volatile u8_t**)(AlternateChannelControl3_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_4  ((volatile u8_t**)(AlternateChannelControl4_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_5  ((volatile u8_t**)(AlternateChannelControl5_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_6  ((volatile u8_t**)(AlternateChannelControl6_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_7  ((volatile u8_t**)(AlternateChannelControl7_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_8  ((volatile u8_t**)(AlternateChannelControl8_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_9  ((volatile u8_t**)(AlternateChannelControl9_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_10 ((volatile u8_t**)(AlternateChannelControl10_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_11 ((volatile u8_t**)(AlternateChannelControl11_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_12 ((volatile u8_t**)(AlternateChannelControl12_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_13 ((volatile u8_t**)(AlternateChannelControl13_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_14 ((volatile u8_t**)(AlternateChannelControl14_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_15 ((volatile u8_t**)(AlternateChannelControl15_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_16 ((volatile u8_t**)(AlternateChannelControl16_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_17 ((volatile u8_t**)(AlternateChannelControl17_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_18 ((volatile u8_t**)(AlternateChannelControl18_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_19 ((volatile u8_t**)(AlternateChannelControl19_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_20 ((volatile u8_t**)(AlternateChannelControl20_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_21 ((volatile u8_t**)(AlternateChannelControl21_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_22 ((volatile u8_t**)(AlternateChannelControl22_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_23 ((volatile u8_t**)(AlternateChannelControl23_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_24 ((volatile u8_t**)(AlternateChannelControl24_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_25 ((volatile u8_t**)(AlternateChannelControl25_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_26 ((volatile u8_t**)(AlternateChannelControl26_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_27 ((volatile u8_t**)(AlternateChannelControl27_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_28 ((volatile u8_t**)(AlternateChannelControl28_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_29 ((volatile u8_t**)(AlternateChannelControl29_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_30 ((volatile u8_t**)(AlternateChannelControl30_BaseAddress + DMADSTENDP_OFFSET))
#define AlternateDestinationAddressPointer_31 ((volatile u8_t**)(AlternateChannelControl31_BaseAddress + DMADSTENDP_OFFSET))




#define DMA_ChannelControlWord_0   ((volatile DMACHCTL_Reg*)(ChannelControl0_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_1   ((volatile DMACHCTL_Reg*)(ChannelControl1_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_2   ((volatile DMACHCTL_Reg*)(ChannelControl2_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_3   ((volatile DMACHCTL_Reg*)(ChannelControl3_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_4   ((volatile DMACHCTL_Reg*)(ChannelControl4_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_5   ((volatile DMACHCTL_Reg*)(ChannelControl5_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_6   ((volatile DMACHCTL_Reg*)(ChannelControl6_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_7   ((volatile DMACHCTL_Reg*)(ChannelControl7_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_8   ((volatile DMACHCTL_Reg*)(ChannelControl8_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_9   ((volatile DMACHCTL_Reg*)(ChannelControl9_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_10  ((volatile DMACHCTL_Reg*)(ChannelControl10_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_11  ((volatile DMACHCTL_Reg*)(ChannelControl11_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_12  ((volatile DMACHCTL_Reg*)(ChannelControl12_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_13  ((volatile DMACHCTL_Reg*)(ChannelControl13_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_14  ((volatile DMACHCTL_Reg*)(ChannelControl14_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_15  ((volatile DMACHCTL_Reg*)(ChannelControl15_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_16  ((volatile DMACHCTL_Reg*)(ChannelControl16_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_17  ((volatile DMACHCTL_Reg*)(ChannelControl17_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_18  ((volatile DMACHCTL_Reg*)(ChannelControl18_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_19  ((volatile DMACHCTL_Reg*)(ChannelControl19_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_20  ((volatile DMACHCTL_Reg*)(ChannelControl20_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_21  ((volatile DMACHCTL_Reg*)(ChannelControl21_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_22  ((volatile DMACHCTL_Reg*)(ChannelControl22_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_23  ((volatile DMACHCTL_Reg*)(ChannelControl23_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_24  ((volatile DMACHCTL_Reg*)(ChannelControl24_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_25  ((volatile DMACHCTL_Reg*)(ChannelControl25_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_26  ((volatile DMACHCTL_Reg*)(ChannelControl26_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_27  ((volatile DMACHCTL_Reg*)(ChannelControl27_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_28  ((volatile DMACHCTL_Reg*)(ChannelControl28_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_29  ((volatile DMACHCTL_Reg*)(ChannelControl29_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_30  ((volatile DMACHCTL_Reg*)(ChannelControl30_BaseAddress + DMACHCTL_OFFSET))
#define DMA_ChannelControlWord_31  ((volatile DMACHCTL_Reg*)(ChannelControl31_BaseAddress + DMACHCTL_OFFSET))


#define AlternateDMA_ChannelControlWord_0   ((volatile DMACHCTL_Reg*)(AlternateChannelControl0_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_1   ((volatile DMACHCTL_Reg*)(AlternateChannelControl1_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_2   ((volatile DMACHCTL_Reg*)(AlternateChannelControl2_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_3   ((volatile DMACHCTL_Reg*)(AlternateChannelControl3_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_4   ((volatile DMACHCTL_Reg*)(AlternateChannelControl4_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_5   ((volatile DMACHCTL_Reg*)(AlternateChannelControl5_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_6   ((volatile DMACHCTL_Reg*)(AlternateChannelControl6_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_7   ((volatile DMACHCTL_Reg*)(AlternateChannelControl7_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_8   ((volatile DMACHCTL_Reg*)(AlternateChannelControl8_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_9   ((volatile DMACHCTL_Reg*)(AlternateChannelControl9_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_10  ((volatile DMACHCTL_Reg*)(AlternateChannelControl10_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_11  ((volatile DMACHCTL_Reg*)(AlternateChannelControl11_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_12  ((volatile DMACHCTL_Reg*)(AlternateChannelControl12_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_13  ((volatile DMACHCTL_Reg*)(AlternateChannelControl13_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_14  ((volatile DMACHCTL_Reg*)(AlternateChannelControl14_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_15  ((volatile DMACHCTL_Reg*)(AlternateChannelControl15_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_16  ((volatile DMACHCTL_Reg*)(AlternateChannelControl16_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_17  ((volatile DMACHCTL_Reg*)(AlternateChannelControl17_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_18  ((volatile DMACHCTL_Reg*)(AlternateChannelControl18_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_19  ((volatile DMACHCTL_Reg*)(AlternateChannelControl19_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_20  ((volatile DMACHCTL_Reg*)(AlternateChannelControl20_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_21  ((volatile DMACHCTL_Reg*)(AlternateChannelControl21_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_22  ((volatile DMACHCTL_Reg*)(AlternateChannelControl22_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_23  ((volatile DMACHCTL_Reg*)(AlternateChannelControl23_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_24  ((volatile DMACHCTL_Reg*)(AlternateChannelControl24_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_25  ((volatile DMACHCTL_Reg*)(AlternateChannelControl25_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_26  ((volatile DMACHCTL_Reg*)(AlternateChannelControl26_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_27  ((volatile DMACHCTL_Reg*)(AlternateChannelControl27_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_28  ((volatile DMACHCTL_Reg*)(AlternateChannelControl28_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_29  ((volatile DMACHCTL_Reg*)(AlternateChannelControl29_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_30  ((volatile DMACHCTL_Reg*)(AlternateChannelControl30_BaseAddress + DMACHCTL_OFFSET))
#define AlternateDMA_ChannelControlWord_31  ((volatile DMACHCTL_Reg*)(AlternateChannelControl31_BaseAddress + DMACHCTL_OFFSET))




#define DMAChannelSoftwareRequest_Register   *((volatile u32_t*)(DMA_BASE+DMASWREQ_OFFSET))
#define DMAChannelInterruptStatus            ((volatile DMACHIS_Reg*)(DMA_BASE + 0x504))
#define DMAChannelPrioritySet_Reg            *((volatile u32_t*)(DMA_BASE+ 0x038))
#define DMAChannelPriorityClear_Reg          *((volatile u32_t *)(DMA_BASE + 0x03C))
#define DMAConfiguration_Reg                 *((volatile u32_t *)(DMA_BASE + 0x004))
#define DMAChannelEnableSet_Reg              *((volatile u32_t *)(DMA_BASE + 0x028))
#define DMABusErrorClear_Reg                 *((volatile u32_t *)(DMA_BASE + 0x04C))
#define DMAChannelRequestMaskClear           *((volatile u32_t *)(DMA_BASE + 0x024))
#define DMAChannelUseBurstClear_Reg          *((volatile u32_t *)(DMA_BASE + 0x01C))
#define DMAChannelPrimaryAlternateClear_Reg  *((volatile u32_t *)(DMA_BASE + 0x034))
#define DMAChannelUseBurstSet_Reg            *((volatile u32_t *)(DMA_BASE + 0x018))


#define DMA_ChannelMapSelect0_Reg                ((volatile u32_t*)(DMA_BASE + DMACHMAP0_OFFSET))
#define DMA_ChannelMapSelect1_Reg                ((volatile u32_t*)(DMA_BASE + DMACHMAP1_OFFSET))
#define DMA_ChannelMapSelect2_Reg                ((volatile u32_t*)(DMA_BASE + DMACHMAP2_OFFSET))
#define DMA_ChannelMapSelect3_Reg                ((volatile u32_t*)(DMA_BASE + DMACHMAP3_OFFSET))



#endif /* DMA_REG_H_ */
