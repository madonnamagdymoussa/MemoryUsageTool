
#ifndef UART_REG_H_
#define UART_REG_H_

#include "lstd.h"



/************************************ Base Address **********************************************/
#define UART0_BASE    0x4000C000
#define UART1_BASE    0x4000D000
#define UART2_BASE    0x4000E000
#define UART3_BASE    0x4000F000
#define UART4_BASE    0x40010000
#define UART5_BASE    0x40011000
#define UART6_BASE    0x40012000
#define UART7_BASE    0x40013000
/************************************ Base Address **********************************************/


/*************************************** offset **********************************************/
#define DATA_OFFSET      0x00
#define FLAG_OFFSET      0x018
#define ICR_OFFSET       0x044
#define RCGCUART_OFFSET  0x618
#define UARTCTL_OFFSET   0x030
#define UARTLCRH_OFFSET  0x02C
#define UARTIM_OFFSET    0x038
#define UARTRIS_OFFSET   0x03C
#define UARTMIS_OFFSET   0x040
#define UARTDMACTL_OFFSET  0x048
#define UARTIFLS_OFFSET   0x034
/*************************************** offset **********************************************/



typedef union {
    struct {

      u32_t   ReceiveDMAEnable:1;
      u32_t   TransmitDMAEnable :1;
      u32_t   DMAonError:1;
      u32_t   reserved: 29;

    }bits;
    u32_t Register;
}UARTDMACTL_Reg;

//typedef union {

//    struct {
//        u32_t BaudClockSource:4;
//        u32_t reserved :28;

//    }bits;

//    u32_t Register;

//};

typedef union {

     struct {
         u32_t IntegerBaudRateDivisor:16;
         u32_t reserved :16;

    }bits;

    u32_t Register;
}UARTIBRD_Reg;

typedef union {

    struct {

      u32_t  FractionalBaudRateDivisor:6;
      u32_t reserved :26;

    }bits;

    u32_t Register;
}UARTFBRD_Reg;


typedef union {

    struct {

        u32_t BaudClockSource:4;
        u32_t reserved:28;

    }bits;

    u32_t Register;

}UARTCC_Reg;


typedef union {

    struct {
        u32_t UARTModule_RunModeClockGatingControl:8;
        u32_t reserved :24;

    }bits;

    u32_t Register;

}RCGCUART_Reg;

typedef union {

    struct{
        u32_t Data:8;
        u32_t FramingError:1;
        u32_t ParityError:1;
        u32_t BreakError:1;
        u32_t OverrunError:1;
        u32_t :20;
    }bits;

    u32_t Register;

}UARTDR_Reg;


typedef union {

    struct{
        u32_t CTS:1;
        u32_t :2;
        u32_t Busy:1;
        u32_t ReceiveFIFOEmpty:1;
        u32_t TransmitFIFOFull:1;
        u32_t ReceiveFIFOFull:1;
        u32_t TransmitFIFOEmpty:1;
        u32_t   :24;
    }bits;

    u32_t Register;

}UARTFR_Reg;


typedef union {

    struct {
        u32_t :1;
        u32_t CTSMIC:1;
        u32_t :2;
        u32_t ReceiveInterruptClear :1;
        u32_t TransmitInterruptClear :1;
        u32_t ReceiveTimeOutInterruptClear:1;
        u32_t FramingErrorInterruptClear:1;
        u32_t ParityErrorInterruptClear:1;
        u32_t BreakErrorInterruptClear:1;
        u32_t OverrunErrorInterrupClear:1;
        u32_t :1;
        u32_t NineBITIC:1;
        u32_t :19;

    }bits;

    u32_t Register;

}UARTICR_Reg;


//typedef union {

//    struct{


//     u32_t ModuleNum :8;
//     u32_t           :24;

//    }bits;

//    u32_t Register;

//}RCGCUART_Reg;

typedef union {

    struct{
    u32_t UARTEnable :1;
    u32_t SIRnable :1;
    u32_t SIRLP :1;
    u32_t SMART:1;
    u32_t EndofTransmission:1;
    u32_t HighSpeedEnable:1;
    u32_t :1;
    u32_t LoopBackEnable :1;
    u32_t TransmitEnable :1;
    u32_t ReceiveEnable :1;
    u32_t :1;
    u32_t RequestToSend:1;
    u32_t :2;
    u32_t EnableRequestToSend :1;
    u32_t EnableClearToSend:1;
    u32_t :16;

    }bits;

    u32_t Register;

}UARTCTL_Reg;


typedef union {

    struct{
    u32_t   SendBreak:1;
    u32_t   ParityEnable:1;
    u32_t   EvenParitySelect:1;
    u32_t   TwoStopBitsSelect:1;
    u32_t   EnableFIFOs:1;
    u32_t   WordLength:2;
    u32_t   StickParitySelect:1;
    u32_t  :24;

    }bits;

    u32_t Register;

}UARTLCRH_Reg;


typedef union {

    struct{
        u32_t :1;
        u32_t CTSIM:1;
        u32_t :2;
        u32_t ReceiveInterruptMask:1;
        u32_t TransmitInterruptMask:1;
        u32_t ReceiveTimeOutInterruptMask:1;
        u32_t FramingErrorInterruptMask:1;
        u32_t ParityErrorInterruptMask:1;
        u32_t BreakErrorInterruptMask:1;
        u32_t OverrunErrorInterruptMask:1;
        u32_t :1;
        u32_t _9BitInterruptMask:1;
        u32_t :19;

    }bits;

    u32_t Register;

}UARTIM_Reg;


typedef union {

    struct{

    u32_t :1;
    u32_t CTSMIS:1;
    u32_t  :2;
    u32_t  ReceiveMaskedInterruptStatus:1;
    u32_t TransmitMaskedInterruptStatus:1;
    u32_t ReceiveTimeOutMaskedInterruptStatus:1;
    u32_t FramingErrorMaskedInterruptStatus:1;
    u32_t ParityErrorMaskedInterruptStatus:1;
    u32_t BreakErrorMaskedInterruptStatus:1;
    u32_t  OverrunErrorMaskedInterruptStatus:1;
    u32_t _9BitModeMaskedInterruptStatus:1;
    u32_t    :19;
    }bits;

    u32_t Register;

}UARTMIS_Reg;


typedef union {

    struct{

       u32_t  DMAOnError:1;
       u32_t TransmitDMAEnable:1;
       u32_t ReceiveDMAEnable:1;
       u32_t :29;
    }bits;

    u32_t Register;

}UARTDMACTL;

typedef union{

    struct{
        u32_t TXIFLSEL:3;
        u32_t RXIFLSEL:3;
        u32_t :26;
    }bits;

    u32_t Register;

}UARTIFLS_Reg;

#define UART0_Data_Reg         (( volatile UARTDR_Reg*)(UART0_BASE+DATA_OFFSET))
#define UART1_Data_Reg         (( volatile UARTDR_Reg*)(UART1_BASE+DATA_OFFSET))
#define UART2_Data_Reg         (( volatile UARTDR_Reg*)(UART2_BASE+DATA_OFFSET))
#define UART3_Data_Reg         (( volatile UARTDR_Reg*)(UART3_BASE+DATA_OFFSET))
#define UART4_Data_Reg         (( volatile UARTDR_Reg*)(UART4_BASE+DATA_OFFSET))
#define UART5_Data_Reg         (( volatile UARTDR_Reg*)(UART5_BASE+DATA_OFFSET))
#define UART6_Data_Reg         (( volatile UARTDR_Reg*)(UART6_BASE+DATA_OFFSET))
#define UART7_Data_Reg         (( volatile UARTDR_Reg*)(UART7_BASE+DATA_OFFSET))

#define UART0_Flag_Reg         (( volatile UARTFR_Reg*)(UART0_BASE+FLAG_OFFSET))
#define UART1_Flag_Reg         (( volatile UARTFR_Reg*)(UART1_BASE+FLAG_OFFSET))
#define UART2_Flag_Reg         (( volatile UARTFR_Reg*)(UART2_BASE+FLAG_OFFSET))
#define UART3_Flag_Reg         (( volatile UARTFR_Reg*)(UART3_BASE+FLAG_OFFSET))
#define UART4_Flag_Reg         (( volatile UARTFR_Reg*)(UART4_BASE+FLAG_OFFSET))
#define UART5_Flag_Reg         (( volatile UARTFR_Reg*)(UART5_BASE+FLAG_OFFSET))
#define UART6_Flag_Reg         (( volatile UARTFR_Reg*)(UART6_BASE+FLAG_OFFSET))
#define UART7_Flag_Reg         (( volatile UARTFR_Reg*)(UART7_BASE+FLAG_OFFSET))

#define UART0_InterruptClear_Reg         (( volatile UARTICR_Reg*)(UART0_BASE+ICR_OFFSET))
#define UART1_InterruptClear_Reg         (( volatile UARTICR_Reg*)(UART1_BASE+ICR_OFFSET))
#define UART2_InterruptClear_Reg         (( volatile UARTICR_Reg*)(UART2_BASE+ICR_OFFSET))
#define UART3_InterruptClear_Reg         (( volatile UARTICR_Reg*)(UART3_BASE+ICR_OFFSET))
#define UART4_InterruptClear_Reg         (( volatile UARTICR_Reg*)(UART4_BASE+ICR_OFFSET))
#define UART5_InterruptClear_Reg         (( volatile UARTICR_Reg*)(UART5_BASE+ICR_OFFSET))
#define UART6_InterruptClear_Reg         (( volatile UARTICR_Reg*)(UART6_BASE+ICR_OFFSET))
#define UART7_InterruptClear_Reg         (( volatile UARTICR_Reg*)(UART7_BASE+ICR_OFFSET))



#define UART0_InterruptMask_Reg         (( volatile UARTIM_Reg*)(UART0_BASE+UARTIM_OFFSET))
#define UART1_InterruptMask_Reg         (( volatile UARTIM_Reg*)(UART1_BASE+UARTIM_OFFSET))
#define UART2_InterruptMask_Reg         (( volatile UARTIM_Reg*)(UART2_BASE+UARTIM_OFFSET))
#define UART3_InterruptMask_Reg         (( volatile UARTIM_Reg*)(UART3_BASE+UARTIM_OFFSET))
#define UART4_InterruptMask_Reg         (( volatile UARTIM_Reg*)(UART4_BASE+UARTIM_OFFSET))
#define UART5_InterruptMask_Reg         (( volatile UARTIM_Reg*)(UART5_BASE+UARTIM_OFFSET))
#define UART6_InterruptMask_Reg         (( volatile UARTIM_Reg*)(UART6_BASE+UARTIM_OFFSET))
#define UART7_InterruptMask_Reg         (( volatile UARTIM_Reg*)(UART7_BASE+UARTIM_OFFSET))

#define UART0_MaskedInterruptStatus_Reg         (( volatile UARTMIS_Reg*)(UART0_BASE+UARTMIS_OFFSET))
#define UART1_MaskedInterruptStatus_Reg         (( volatile UARTMIS_Reg*)(UART1_BASE+UARTMIS_OFFSET))
#define UART2_MaskedInterruptStatus_Reg         (( volatile UARTMIS_Reg*)(UART2_BASE+UARTMIS_OFFSET))
#define UART3_MaskedInterruptStatus_Reg         (( volatile UARTMIS_Reg*)(UART3_BASE+UARTMIS_OFFSET))
#define UART4_MaskedInterruptStatus_Reg         (( volatile UARTMIS_Reg*)(UART4_BASE+UARTMIS_OFFSET))
#define UART5_MaskedInterruptStatus_Reg         (( volatile UARTMIS_Reg*)(UART5_BASE+UARTMIS_OFFSET))
#define UART6_MaskedInterruptStatus_Reg         (( volatile UARTMIS_Reg*)(UART6_BASE+UARTMIS_OFFSET))
#define UART7_MaskedInterruptStatus_Reg         (( volatile UARTMIS_Reg*)(UART7_BASE+UARTMIS_OFFSET))



#define UART0_IntegerBaudRateDivisor    (( volatile UARTIBRD_Reg*)(UART0_BASE+0x024))
#define UART1_IntegerBaudRateDivisor    (( volatile UARTIBRD_Reg*)(UART1_BASE+0x024))
#define UART2_IntegerBaudRateDivisor    (( volatile UARTIBRD_Reg*)(UART2_BASE+0x024))
#define UART3_IntegerBaudRateDivisor    (( volatile UARTIBRD_Reg*)(UART3_BASE+0x024))
#define UART4_IntegerBaudRateDivisor    (( volatile UARTIBRD_Reg*)(UART4_BASE+0x024))
#define UART5_IntegerBaudRateDivisor    (( volatile UARTIBRD_Reg*)(UART5_BASE+0x024))
#define UART6_IntegerBaudRateDivisor    (( volatile UARTIBRD_Reg*)(UART6_BASE+0x024))
#define UART7_IntegerBaudRateDivisor    (( volatile UARTIBRD_Reg*)(UART7_BASE+0x024))

#define UART0_FractionalBaudRateDivisor  (( volatile UARTFBRD_Reg*)(UART0_BASE+0x028))
#define UART1_FractionalBaudRateDivisor  (( volatile UARTFBRD_Reg*)(UART1_BASE+0x028))
#define UART2_FractionalBaudRateDivisor  (( volatile UARTFBRD_Reg*)(UART2_BASE+0x028))
#define UART3_FractionalBaudRateDivisor  (( volatile UARTFBRD_Reg*)(UART3_BASE+0x028))
#define UART4_FractionalBaudRateDivisor  (( volatile UARTFBRD_Reg*)(UART4_BASE+0x028))
#define UART5_FractionalBaudRateDivisor  (( volatile UARTFBRD_Reg*)(UART5_BASE+0x028))
#define UART6_FractionalBaudRateDivisor  (( volatile UARTFBRD_Reg*)(UART6_BASE+0x028))
#define UART7_FractionalBaudRateDivisor  (( volatile UARTFBRD_Reg*)(UART7_BASE+0x028))

#define UART0_ClockConfiguration         (( volatile UARTCC_Reg*)(UART0_BASE+0xFC8))
#define UART1_ClockConfiguration         (( volatile UARTCC_Reg*)(UART1_BASE+0xFC8))
#define UART2_ClockConfiguration         (( volatile UARTCC_Reg*)(UART2_BASE+0xFC8))
#define UART3_ClockConfiguration         (( volatile UARTCC_Reg*)(UART3_BASE+0xFC8))
#define UART4_ClockConfiguration         (( volatile UARTCC_Reg*)(UART4_BASE+0xFC8))
#define UART5_ClockConfiguration         (( volatile UARTCC_Reg*)(UART5_BASE+0xFC8))
#define UART6_ClockConfiguration         (( volatile UARTCC_Reg*)(UART6_BASE+0xFC8))
#define UART7_ClockConfiguration         (( volatile UARTCC_Reg*)(UART7_BASE+0xFC8))

#define SYSCTL_UARTRunModeClockGatingControl_Reg  *(( volatile RCGCUART_Reg* )(0x400FE000+RCGCUART_OFFSET ))

#define UART0_Control_Reg      (( volatile UARTCTL_Reg*)(UART0_BASE+UARTCTL_OFFSET))
#define UART1_Control_Reg      (( volatile UARTCTL_Reg*)(UART1_BASE+UARTCTL_OFFSET))
#define UART2_Control_Reg      (( volatile UARTCTL_Reg*)(UART2_BASE+UARTCTL_OFFSET))
#define UART3_Control_Reg      (( volatile UARTCTL_Reg*)(UART3_BASE+UARTCTL_OFFSET))
#define UART4_Control_Reg      (( volatile UARTCTL_Reg*)(UART4_BASE+UARTCTL_OFFSET))
#define UART5_Control_Reg      (( volatile UARTCTL_Reg*)(UART5_BASE+UARTCTL_OFFSET))
#define UART6_Control_Reg      (( volatile UARTCTL_Reg*)(UART6_BASE+UARTCTL_OFFSET))
#define UART7_Control_Reg      (( volatile UARTCTL_Reg*)(UART7_BASE+UARTCTL_OFFSET))

#define UART0_LineControl_Reg      (( volatile UARTLCRH_Reg*)(UART0_BASE+UARTLCRH_OFFSET))
#define UART1_LineControl_Reg      (( volatile UARTLCRH_Reg*)(UART1_BASE+UARTLCRH_OFFSET))
#define UART2_LineControl_Reg      (( volatile UARTLCRH_Reg*)(UART2_BASE+UARTLCRH_OFFSET))
#define UART3_LineControl_Reg      (( volatile UARTLCRH_Reg*)(UART3_BASE+UARTLCRH_OFFSET))
#define UART4_LineControl_Reg      (( volatile UARTLCRH_Reg*)(UART4_BASE+UARTLCRH_OFFSET))
#define UART5_LineControl_Reg      (( volatile UARTLCRH_Reg*)(UART5_BASE+UARTLCRH_OFFSET))
#define UART6_LineControl_Reg      (( volatile UARTLCRH_Reg*)(UART6_BASE+UARTLCRH_OFFSET))
#define UART7_LineControl_Reg      (( volatile UARTLCRH_Reg*)(UART7_BASE+UARTLCRH_OFFSET))

#define UART0_DMAControl_Reg       ((volatile UARTDMACTL*)(UART0_BASE+UARTDMACTL_OFFSET))
#define UART1_DMAControl_Reg       ((volatile UARTDMACTL*)(UART1_BASE+UARTDMACTL_OFFSET))
#define UART2_DMAControl_Reg       ((volatile UARTDMACTL*)(UART2_BASE+UARTDMACTL_OFFSET))
#define UART3_DMAControl_Reg       ((volatile UARTDMACTL*)(UART3_BASE+UARTDMACTL_OFFSET))
#define UART4_DMAControl_Reg       ((volatile UARTDMACTL*)(UART4_BASE+UARTDMACTL_OFFSET))
#define UART5_DMAControl_Reg       ((volatile UARTDMACTL*)(UART5_BASE+UARTDMACTL_OFFSET))
#define UART6_DMAControl_Reg       ((volatile UARTDMACTL*)(UART6_BASE+UARTDMACTL_OFFSET))
#define UART7_DMAControl_Reg       ((volatile UARTDMACTL*)(UART7_BASE+UARTDMACTL_OFFSET))


#define UART0_UARTIFLS_Reg        ((volatile UARTIFLS_Reg*)(UART0_BASE+UARTIFLS_OFFSET) )
#define UART1_UARTIFLS_Reg        ((volatile UARTIFLS_Reg*)(UART1_BASE+UARTIFLS_OFFSET) )
#define UART2_UARTIFLS_Reg        ((volatile UARTIFLS_Reg*)(UART2_BASE+UARTIFLS_OFFSET) )
#define UART3_UARTIFLS_Reg        ((volatile UARTIFLS_Reg*)(UART3_BASE+UARTIFLS_OFFSET) )
#define UART4_UARTIFLS_Reg        ((volatile UARTIFLS_Reg*)(UART4_BASE+UARTIFLS_OFFSET) )
#define UART5_UARTIFLS_Reg        ((volatile UARTIFLS_Reg*)(UART5_BASE+UARTIFLS_OFFSET) )
#define UART6_UARTIFLS_Reg        ((volatile UARTIFLS_Reg*)(UART6_BASE+UARTIFLS_OFFSET) )
#define UART7_UARTIFLS_Reg        ((volatile UARTIFLS_Reg*)(UART7_BASE+UARTIFLS_OFFSET) )

#endif /* UART_REG_H_ */
