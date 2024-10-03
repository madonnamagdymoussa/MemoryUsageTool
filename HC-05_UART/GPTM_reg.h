
#ifndef GPTM_REG_H_
#define GPTM_REG_H_

#include "lstd.h"

#define GPTM_32BitTimer0BaseAdd   0x40030000
#define GPTM_32BitTimer1BaseAdd   0x40031000
#define GPTM_32BitTimer2BaseAdd   0x40032000
#define GPTM_32BitTimer3BaseAdd   0x40033000
#define GPTM_32BitTimer4BaseAdd   0x40034000
#define GPTM_32BitTimer5BaseAdd   0x40035000

#define GPTM_64BitTimer0BaseAdd   0x40036000
#define GPTM_64BitTimer1BaseAdd   0x40037000
#define GPTM_64BitTimer2BaseAdd   0x4004C000
#define GPTM_64BitTimer3BaseAdd   0x4004D000
#define GPTM_64BitTimer4BaseAdd   0x4004E000
#define GPTM_64BitTimer5BaseAdd   0x4004F000

#define GPTMTAILR_Offset          0x028
#define GPTMTBILR_Offset          0x02C
#define GPTMTAMR_Offset           0x004
#define GPTMTBMR_Offset           0x008
#define GPTMCTL_Offset            0x00C
#define GPTMTAMATCHR_Offset       0x030
#define GPTMTBMATCHR_Offset       0x034
#define GPTMICR_Offset            0x024
#define GPTMRIS_Offset            0x01C

typedef union {

    struct{

     u32_t  TimerA_Enable:1;
     u32_t  TimerA_StallEnable:1;
     u32_t  TimerA_EventMode:1;
     u32_t  RTC_StallEnable:1;
     u32_t  TimerA_OutputTriggerEnable:1;
     u32_t  TimerA_PWMOutputLevel:1;
     u32_t  TimerB_Enable:1;
     u32_t  TimerB_StallEnable:1;
     u32_t  TimerB_EventMode:1;
     u32_t  TimerB_OutputTriggerEnable:1;
     u32_t  TimerB_PWMOutputLevel:1;

    }bits;

    u32_t Register;
}GPTMCTL_reg;


typedef union {

    struct{

        u32_t Configuration:3;
        u32_t :29;

    }bits;

    u32_t Register;
}GPTMCFG_Reg;


typedef union {

    struct{

        u32_t TimerMode :2;
        u32_t TimerCaptureMode:1;
        u32_t TimerAlternateModeSelect:1;
        u32_t TimerCountDirection:1;
        u32_t TimerMatchInterruptEnable:1;
        u32_t TimerWaitOnTrigger:1;
        u32_t TimerSnapShotMode:1;
        u32_t TimerIntervalLoadWrite:1;
        u32_t TimerPWMInterruptEnable:1;
        u32_t TimerMatchRegisterUpdate:1;
        u32_t TimerPWMLegacyOperation:1;
        u32_t  :20;

    }bits;

    u32_t Register;

}GPTMTMR_Reg;

typedef union {

    struct{

        u32_t TATORIS:1;
        u32_t CAMRIS:1;
        u32_t CAERIS:1;
        u32_t RTCRIS:1;
        u32_t TAMRIS:1;
        u32_t :3;
        u32_t TBTORIS:1;
        u32_t CBMRIS:1;
        u32_t CBERIS:1;
        u32_t TBMRIS:1;
        u32_t :4;
        u32_t WUERIS:1;
        u32_t :15;
    }bits;

    u32_t Register;
}GPTMRIS_t;


typedef union {
    struct{
        u32_t TATOCINT:1;
        u32_t CAMCINT:1;
        u32_t CAECINT:1;
        u32_t RTCCINT:1;
        u32_t TAMCINT:1;
        u32_t :3;
        u32_t TBTOCINT:1;
        u32_t CBMCINT:1;
        u32_t CBECINT:1;
        u32_t TBMCINT:1;
        u32_t :4;
        u32_t WUECINT:1;
        u32_t :15;

    }bits;
 u32_t Register;
}GPTMICR_Reg;

typedef union{
    struct{

        u32_t TATORIS:1;
        u32_t CAMRIS:1;
        u32_t CAERIS:1;
        u32_t RTCRIS:1;
        u32_t TAMRIS:1;
        u32_t :3;
        u32_t TBTORIS:1;
        u32_t CBMRIS:1;
        u32_t CBERIS:1;
        u32_t TBMRIS:1;
        u32_t :4;
        u32_t WUERIS:1;
        u32_t :15;
    }bits;
    u32_t Register;
}GPTMRIS_Reg;

/***************************************** IntervalLoadA 64bit or 16bit **************************************************************/
#define GPTM_16_32BitTimer0AIntervalLoad    ( (volatile void*) (GPTM_32BitTimer0BaseAdd + GPTMTAILR_Offset)  )
#define GPTM_16_32BitTimer1AIntervalLoad    ( (volatile void*) (GPTM_32BitTimer1BaseAdd + GPTMTAILR_Offset)  )
#define GPTM_16_32BitTimer2AIntervalLoad    ( (volatile void*) (GPTM_32BitTimer2BaseAdd + GPTMTAILR_Offset)  )
#define GPTM_16_32BitTimer3AIntervalLoad    ( (volatile void*) (GPTM_32BitTimer3BaseAdd + GPTMTAILR_Offset)  )
#define GPTM_16_32BitTimer4AIntervalLoad    ( (volatile void*) (GPTM_32BitTimer4BaseAdd + GPTMTAILR_Offset)  )
#define GPTM_16_32BitTimer5AIntervalLoad    ( (volatile void*) (GPTM_32BitTimer5BaseAdd + GPTMTAILR_Offset)  )

/***************************************** IntervalLoadA 64bit or 16bit **************************************************************/
#define GPTM_32_64BitTimer0AIntervalLoad    ( (volatile void*) (GPTM_64BitTimer0BaseAdd + GPTMTAILR_Offset)  )
#define GPTM_32_64BitTimer1AIntervalLoad    ( (volatile void*) (GPTM_64BitTimer1BaseAdd + GPTMTAILR_Offset)  )
#define GPTM_32_64BitTimer2AIntervalLoad    ( (volatile void*) (GPTM_64BitTimer2BaseAdd + GPTMTAILR_Offset)  )
#define GPTM_32_64BitTimer3AIntervalLoad    ( (volatile void*) (GPTM_64BitTimer3BaseAdd + GPTMTAILR_Offset)  )
#define GPTM_32_64BitTimer4AIntervalLoad    ( (volatile void*) (GPTM_64BitTimer4BaseAdd + GPTMTAILR_Offset)  )
#define GPTM_32_64BitTimer5AIntervalLoad    ( (volatile void*) (GPTM_64BitTimer5BaseAdd + GPTMTAILR_Offset)  )

/***************************************** IntervalLoadB 16bit**************************************************************/
#define GPTM_16BitTimer0BIntervalLoad    ( (volatile u16_t*) (GPTM_32BitTimer0BaseAdd + GPTMTBILR_Offset)  )
#define GPTM_16BitTimer1BIntervalLoad    ( (volatile u16_t*) (GPTM_32BitTimer1BaseAdd + GPTMTBILR_Offset)  )
#define GPTM_16BitTimer2BIntervalLoad    ( (volatile u16_t*) (GPTM_32BitTimer2BaseAdd + GPTMTBILR_Offset)  )
#define GPTM_16BitTimer3BIntervalLoad    ( (volatile u16_t*) (GPTM_32BitTimer3BaseAdd + GPTMTBILR_Offset)  )
#define GPTM_16BitTimer4BIntervalLoad    ( (volatile u16_t*) (GPTM_32BitTimer4BaseAdd + GPTMTBILR_Offset)  )
#define GPTM_16BitTimer5BIntervalLoad    ( (volatile u16_t*) (GPTM_32BitTimer5BaseAdd + GPTMTBILR_Offset)  )

/***************************************** IntervalLoadB 32bit**************************************************************/
#define GPTM_32BitTimer0BIntervalLoad    ( (volatile u32_t*) (GPTM_64BitTimer0BaseAdd + GPTMTBILR_Offset)  )
#define GPTM_32BitTimer1BIntervalLoad    ( (volatile u32_t*) (GPTM_64BitTimer1BaseAdd + GPTMTBILR_Offset)  )
#define GPTM_32BitTimer2BIntervalLoad    ( (volatile u32_t*) (GPTM_64BitTimer2BaseAdd + GPTMTBILR_Offset)  )
#define GPTM_32BitTimer3BIntervalLoad    ( (volatile u32_t*) (GPTM_64BitTimer3BaseAdd + GPTMTBILR_Offset)  )
#define GPTM_32BitTimer4BIntervalLoad    ( (volatile u32_t*) (GPTM_64BitTimer4BaseAdd + GPTMTBILR_Offset)  )
#define GPTM_32BitTimer5BIntervalLoad    ( (volatile u32_t*) (GPTM_64BitTimer5BaseAdd + GPTMTBILR_Offset)  )

/***************************************** Configuration **************************************************************/
#define GPTM_16_32BitTimer0Configuration     ( (volatile GPTMCFG_Reg*)(GPTM_32BitTimer0BaseAdd) )
#define GPTM_16_32BitTimer1Configuration     ( (volatile GPTMCFG_Reg*)(GPTM_32BitTimer1BaseAdd) )
#define GPTM_16_32BitTimer2Configuration     ( (volatile GPTMCFG_Reg*)(GPTM_32BitTimer2BaseAdd) )
#define GPTM_16_32BitTimer3Configuration     ( (volatile GPTMCFG_Reg*)(GPTM_32BitTimer3BaseAdd) )
#define GPTM_16_32BitTimer4Configuration     ( (volatile GPTMCFG_Reg*)(GPTM_32BitTimer4BaseAdd) )
#define GPTM_16_32BitTimer5Configuration     ( (volatile GPTMCFG_Reg*)(GPTM_32BitTimer5BaseAdd) )

#define GPTM_32_64BitTimer0Configuration     ( (volatile GPTMCFG_Reg*)(GPTM_64BitTimer0BaseAdd) )
#define GPTM_32_64BitTimer1Configuration     ( (volatile GPTMCFG_Reg*)(GPTM_64BitTimer1BaseAdd) )
#define GPTM_32_64BitTimer2Configuration     ( (volatile GPTMCFG_Reg*)(GPTM_64BitTimer2BaseAdd) )
#define GPTM_32_64BitTimer3Configuration     ( (volatile GPTMCFG_Reg*)(GPTM_64BitTimer3BaseAdd) )
#define GPTM_32_64BitTimer4Configuration     ( (volatile GPTMCFG_Reg*)(GPTM_64BitTimer4BaseAdd) )
#define GPTM_32_64BitTimer5Configuration     ( (volatile GPTMCFG_Reg*)(GPTM_64BitTimer5BaseAdd) )

/***************************************** Mode A **************************************************************/
#define GPTM_16_32BitTimer0AMode       ((volatile GPTMTMR_Reg*)(GPTM_32BitTimer0BaseAdd + GPTMTAMR_Offset))
#define GPTM_16_32BitTimer1AMode       ((volatile GPTMTMR_Reg*)(GPTM_32BitTimer1BaseAdd + GPTMTAMR_Offset))
#define GPTM_16_32BitTimer2AMode       ((volatile GPTMTMR_Reg*)(GPTM_32BitTimer2BaseAdd + GPTMTAMR_Offset))
#define GPTM_16_32BitTimer3AMode       ((volatile GPTMTMR_Reg*)(GPTM_32BitTimer3BaseAdd + GPTMTAMR_Offset))
#define GPTM_16_32BitTimer4AMode       ((volatile GPTMTMR_Reg*)(GPTM_32BitTimer4BaseAdd + GPTMTAMR_Offset))
#define GPTM_16_32BitTimer5AMode       ((volatile GPTMTMR_Reg*)(GPTM_32BitTimer5BaseAdd + GPTMTAMR_Offset))

#define GPTM_32_64BitTimer0AMode       ((volatile GPTMTMR_Reg*)(GPTM_64BitTimer0BaseAdd + GPTMTAMR_Offset))
#define GPTM_32_64BitTimer1AMode       ((volatile GPTMTMR_Reg*)(GPTM_64BitTimer1BaseAdd + GPTMTAMR_Offset))
#define GPTM_32_64BitTimer2AMode       ((volatile GPTMTMR_Reg*)(GPTM_64BitTimer2BaseAdd + GPTMTAMR_Offset))
#define GPTM_32_64BitTimer3AMode       ((volatile GPTMTMR_Reg*)(GPTM_64BitTimer3BaseAdd + GPTMTAMR_Offset))
#define GPTM_32_64BitTimer4AMode       ((volatile GPTMTMR_Reg*)(GPTM_64BitTimer4BaseAdd + GPTMTAMR_Offset))
#define GPTM_32_64BitTimer5AMode       ((volatile GPTMTMR_Reg*)(GPTM_64BitTimer5BaseAdd + GPTMTAMR_Offset))

/***************************************** Mode B **************************************************************/
#define GPTM_16_32BitTimer0BMode       ((volatile GPTMTMR_Reg*)(GPTM_32BitTimer0BaseAdd + GPTMTBMR_Offset))
#define GPTM_16_32BitTimer1BMode        ((volatile GPTMTMR_Reg*)(GPTM_32BitTimer1BaseAdd + GPTMTBMR_Offset))
#define GPTM_16_32BitTimer2BMode       ((volatile GPTMTMR_Reg*)(GPTM_32BitTimer2BaseAdd + GPTMTBMR_Offset))
#define GPTM_16_32BitTimer3BMode       ((volatile GPTMTMR_Reg*)(GPTM_32BitTimer3BaseAdd + GPTMTBMR_Offset))
#define GPTM_16_32BitTimer4BMode       ((volatile GPTMTMR_Reg*)(GPTM_32BitTimer4BaseAdd + GPTMTBMR_Offset))
#define GPTM_16_32BitTimer5BMode       ((volatile GPTMTMR_Reg*)(GPTM_32BitTimer5BaseAdd + GPTMTBMR_Offset))

#define GPTM_32_64BitTimer0BMode       ((volatile GPTMTMR_Reg*)(GPTM_64BitTimer0BaseAdd + GPTMTBMR_Offset))
#define GPTM_32_64BitTimer1BMode       ((volatile GPTMTMR_Reg*)(GPTM_64BitTimer1BaseAdd + GPTMTBMR_Offset))
#define GPTM_32_64BitTimer2BMode       ((volatile GPTMTMR_Reg*)(GPTM_64BitTimer2BaseAdd + GPTMTBMR_Offset))
#define GPTM_32_64BitTimer3BMode       ((volatile GPTMTMR_Reg*)(GPTM_64BitTimer3BaseAdd + GPTMTBMR_Offset))
#define GPTM_32_64BitTimer4BMode       ((volatile GPTMTMR_Reg*)(GPTM_64BitTimer4BaseAdd + GPTMTBMR_Offset))
#define GPTM_32_64BitTimer5BMode       ((volatile GPTMTMR_Reg*)(GPTM_64BitTimer5BaseAdd + GPTMTBMR_Offset))

/***************************************** CTL Register  **************************************************************/
#define GPTM_16_32BitTimer0Control ((volatile GPTMCTL_reg*)(GPTM_32BitTimer0BaseAdd + GPTMCTL_Offset))
#define GPTM_16_32BitTimer1Control ((volatile GPTMCTL_reg*)(GPTM_32BitTimer1BaseAdd + GPTMCTL_Offset))
#define GPTM_16_32BitTimer2Control ((volatile GPTMCTL_reg*)(GPTM_32BitTimer2BaseAdd + GPTMCTL_Offset))
#define GPTM_16_32BitTimer3Control ((volatile GPTMCTL_reg*)(GPTM_32BitTimer3BaseAdd + GPTMCTL_Offset))
#define GPTM_16_32BitTimer4Control ((volatile GPTMCTL_reg*)(GPTM_32BitTimer4BaseAdd + GPTMCTL_Offset))
#define GPTM_16_32BitTimer5Control ((volatile GPTMCTL_reg*)(GPTM_32BitTimer5BaseAdd + GPTMCTL_Offset))

#define GPTM_32_64BitTimer0Control ((volatile GPTMCTL_reg*)(GPTM_64BitTimer0BaseAdd + GPTMCTL_Offset))
#define GPTM_32_64BitTimer1Control ((volatile GPTMCTL_reg*)(GPTM_64BitTimer1BaseAdd + GPTMCTL_Offset))
#define GPTM_32_64BitTimer2Control ((volatile GPTMCTL_reg*)(GPTM_64BitTimer2BaseAdd + GPTMCTL_Offset))
#define GPTM_32_64BitTimer3Control ((volatile GPTMCTL_reg*)(GPTM_64BitTimer3BaseAdd + GPTMCTL_Offset))
#define GPTM_32_64BitTimer4Control ((volatile GPTMCTL_reg*)(GPTM_64BitTimer4BaseAdd + GPTMCTL_Offset))
#define GPTM_32_64BitTimer5Control ((volatile GPTMCTL_reg*)(GPTM_64BitTimer5BaseAdd + GPTMCTL_Offset))

/***************************************** Match Register  **************************************************************/
#define GPTM_16_32BitTimer0AMatch   ((volatile void*)(GPTM_32BitTimer0BaseAdd + GPTMTAMATCHR_Offset))
#define GPTM_16_32BitTimer1AMatch   ((volatile void*)(GPTM_32BitTimer1BaseAdd + GPTMTAMATCHR_Offset))
#define GPTM_16_32BitTimer2AMatch   ((volatile void*)(GPTM_32BitTimer2BaseAdd + GPTMTAMATCHR_Offset))
#define GPTM_16_32BitTimer3AMatch   ((volatile void*)(GPTM_32BitTimer3BaseAdd + GPTMTAMATCHR_Offset))
#define GPTM_16_32BitTimer4AMatch   ((volatile void*)(GPTM_32BitTimer4BaseAdd + GPTMTAMATCHR_Offset))
#define GPTM_16_32BitTimer5AMatch   ((volatile void*)(GPTM_32BitTimer5BaseAdd + GPTMTAMATCHR_Offset))

#define GPTM_16_32BitTimer0BMatch   ((volatile u32_t*)(GPTM_32BitTimer0BaseAdd + GPTMTBMATCHR_Offset))
#define GPTM_16_32BitTimer1BMatch   ((volatile u32_t*)(GPTM_32BitTimer1BaseAdd + GPTMTBMATCHR_Offset))
#define GPTM_16_32BitTimer2BMatch   ((volatile u32_t*)(GPTM_32BitTimer2BaseAdd + GPTMTBMATCHR_Offset))
#define GPTM_16_32BitTimer3BMatch   ((volatile u32_t*)(GPTM_32BitTimer3BaseAdd + GPTMTBMATCHR_Offset))
#define GPTM_16_32BitTimer4BMatch   ((volatile u32_t*)(GPTM_32BitTimer4BaseAdd + GPTMTBMATCHR_Offset))
#define GPTM_16_32BitTimer5BMatch   ((volatile u32_t*)(GPTM_32BitTimer5BaseAdd + GPTMTBMATCHR_Offset))

#define GPTM_32_64BitTimer0AMatch   ((volatile void*)(GPTM_64BitTimer0BaseAdd + GPTMTAMATCHR_Offset))
#define GPTM_32_64BitTimer1AMatch   ((volatile void*)(GPTM_64BitTimer1BaseAdd + GPTMTAMATCHR_Offset))
#define GPTM_32_64BitTimer2AMatch   ((volatile void*)(GPTM_64BitTimer2BaseAdd + GPTMTAMATCHR_Offset))
#define GPTM_32_64BitTimer3AMatch   ((volatile void*)(GPTM_64BitTimer3BaseAdd + GPTMTAMATCHR_Offset))
#define GPTM_32_64BitTimer4AMatch   ((volatile void*)(GPTM_64BitTimer4BaseAdd + GPTMTAMATCHR_Offset))
#define GPTM_32_64BitTimer5AMatch   ((volatile void*)(GPTM_64BitTimer5BaseAdd + GPTMTAMATCHR_Offset))

#define GPTM_32_64BitTimer0BMatch   ((volatile u32_t*)(GPTM_64BitTimer0BaseAdd + GPTMTBMATCHR_Offset))
#define GPTM_32_64BitTimer1BMatch   ((volatile u32_t*)(GPTM_64BitTimer1BaseAdd + GPTMTBMATCHR_Offset))
#define GPTM_32_64BitTimer2BMatch   ((volatile u32_t*)(GPTM_64BitTimer2BaseAdd + GPTMTBMATCHR_Offset))
#define GPTM_32_64BitTimer3BMatch   ((volatile u32_t*)(GPTM_64BitTimer3BaseAdd + GPTMTBMATCHR_Offset))
#define GPTM_32_64BitTimer4BMatch   ((volatile u32_t*)(GPTM_64BitTimer4BaseAdd + GPTMTBMATCHR_Offset))
#define GPTM_32_64BitTimer5BMatch   ((volatile u32_t*)(GPTM_64BitTimer5BaseAdd + GPTMTBMATCHR_Offset))

/***************************************** Interrupt clear Register  **************************************************************/
#define GPTM_16_32BitTimer0ICR   ((volatile GPTMICR_Reg*)(GPTM_32BitTimer0BaseAdd + GPTMICR_Offset))
#define GPTM_16_32BitTimer1ICR   ((volatile GPTMICR_Reg*)(GPTM_32BitTimer1BaseAdd + GPTMICR_Offset))
#define GPTM_16_32BitTimer2ICR   ((volatile GPTMICR_Reg*)(GPTM_32BitTimer2BaseAdd + GPTMICR_Offset))
#define GPTM_16_32BitTimer3ICR   ((volatile GPTMICR_Reg*)(GPTM_32BitTimer3BaseAdd + GPTMICR_Offset))
#define GPTM_16_32BitTimer4ICR   ((volatile GPTMICR_Reg*)(GPTM_32BitTimer4BaseAdd + GPTMICR_Offset))
#define GPTM_16_32BitTimer5ICR   ((volatile GPTMICR_Reg*)(GPTM_32BitTimer5BaseAdd + GPTMICR_Offset))

#define GPTM_32_64BitTimer0ICR   ((volatile GPTMICR_Reg*)(GPTM_64BitTimer0BaseAdd + GPTMICR_Offset))
#define GPTM_32_64BitTimer1ICR   ((volatile GPTMICR_Reg*)(GPTM_64BitTimer1BaseAdd + GPTMICR_Offset))
#define GPTM_32_64BitTimer2ICR   ((volatile GPTMICR_Reg*)(GPTM_64BitTimer2BaseAdd + GPTMICR_Offset))
#define GPTM_32_64BitTimer3ICR   ((volatile GPTMICR_Reg*)(GPTM_64BitTimer3BaseAdd + GPTMICR_Offset))
#define GPTM_32_64BitTimer4ICR   ((volatile GPTMICR_Reg*)(GPTM_64BitTimer4BaseAdd + GPTMICR_Offset))
#define GPTM_32_64BitTimer5ICR   ((volatile GPTMICR_Reg*)(GPTM_64BitTimer5BaseAdd + GPTMICR_Offset))

/***************************************** Raw Interrupt Register  **************************************************************/
#define GPTM_16_32BitTimer0RIS   ((volatile GPTMRIS_Reg*)(GPTM_32BitTimer0BaseAdd + GPTMRIS_Offset))
#define GPTM_16_32BitTimer1RIS   ((volatile GPTMRIS_Reg*)(GPTM_32BitTimer1BaseAdd + GPTMRIS_Offset))
#define GPTM_16_32BitTimer2RIS   ((volatile GPTMRIS_Reg*)(GPTM_32BitTimer2BaseAdd + GPTMRIS_Offset))
#define GPTM_16_32BitTimer3RIS   ((volatile GPTMRIS_Reg*)(GPTM_32BitTimer3BaseAdd + GPTMRIS_Offset))
#define GPTM_16_32BitTimer4RIS   ((volatile GPTMRIS_Reg*)(GPTM_32BitTimer4BaseAdd + GPTMRIS_Offset))
#define GPTM_16_32BitTimer5RIS   ((volatile GPTMRIS_Reg*)(GPTM_32BitTimer5BaseAdd + GPTMRIS_Offset))

#define GPTM_32_64BitTimer0RIS   ((volatile GPTMRIS_Reg*)(GPTM_64BitTimer0BaseAdd + GPTMRIS_Offset))
#define GPTM_32_64BitTimer1RIS   ((volatile GPTMRIS_Reg*)(GPTM_64BitTimer1BaseAdd + GPTMRIS_Offset))
#define GPTM_32_64BitTimer2RIS   ((volatile GPTMRIS_Reg*)(GPTM_64BitTimer2BaseAdd + GPTMRIS_Offset))
#define GPTM_32_64BitTimer3RIS   ((volatile GPTMRIS_Reg*)(GPTM_64BitTimer3BaseAdd + GPTMRIS_Offset))
#define GPTM_32_64BitTimer4RIS   ((volatile GPTMRIS_Reg*)(GPTM_64BitTimer4BaseAdd + GPTMRIS_Offset))
#define GPTM_32_64BitTimer5RIS   ((volatile GPTMRIS_Reg*)(GPTM_64BitTimer5BaseAdd + GPTMRIS_Offset))



#define SC_RCGCWTIMER_Reg           *((volatile u32_t*)(0x400FE000 + 0x65C))
#define SC_RCGCTIMER_Reg            *((volatile u32_t*)(0x400FE000 +  0x604))

//GPTMICR_Reg

#endif /* GPTM_REG_H_ */
