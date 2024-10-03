
#ifndef GPIO_REG_H_
#define GPIO_REG_H_

#include "lstd.h"

/******************************************** Base address using ---> APB  ****************************************/
#define PORTA_BASE  0x40004000
#define PORTB_BASE  0x40005000
#define PORTC_BASE  0x40006000
#define PORTD_BASE  0x40007000
#define PORTE_BASE  0x40024000
#define PORTF_BASE  0x40025000
/******************************************** Base address using ---> APB  ****************************************/


/***********************************************GPIOIS**************************************************/
typedef union {

    struct {

    u32_t Interrupt_Sence :8;
    u32_t reserved:24;

}Bits;

 u32_t Register;

}GPIO_InterruptSense_Reg;
/************************************* Description of GPIOIS***********************************************/
/* If a bit is set     (from 0 -> 7 ) it will be configured to detect levels
 * If a bit is cleared (from 0 -> 7 ) it will be configured to detect edges
 *
 *  Access of the bits:
 *   1- Atomic access through struct
 *   2- Read-modify-write operation on the whole register --> u32_t Register
 */
/*********************************************GPIOIS*****************************************************/


/*********************************************GPIOIBE*****************************************************/
typedef union {

    struct {

    u32_t InterruptBothEdges:8;
    u32_t reserved :24;

}Bits;

 u32_t Register;

}GPIO_InterruptBothEdges_Reg;
/************************************* Description of GPIOIBE***********************************************/
/* If a bit is set AND interrupt sense register is configured to detect edges --> the pin will detect both rising and falling edges
 *                                                                            --> the value of the interrupt event register will be ignored
 *
 * If a bit is cleared --> it will be controlled by GPIO interrupt event
 *
 *  Access of the bits:
 *   1- Atomic access through struct
 *   2- Read-modify-write operation on the whole register --> u32_t Register
 */
/**********************************************GPIOIBE******************************************************/


/********************************************* GPIOIEV *****************************************************/
typedef union {
struct {

 u32_t InterruptEvent :8;
 u32_t reserved:24;

}Bits;

 u32_t Register;

}GPIO_InterruptEvent_Reg;
/************************************* Description of GPIOIEV***********************************************/
/* If a bit is set     --> a rising edge or high level triggers an interrupt
 * If a bit is cleared --> a falling edge or a low level triggers an interrupt
 *
 *  Access of the bits:
 *   1- Atomic access through struct
 *   2- Read-modify-write operation on the whole register--> u32_t Register
 */
/********************************************** GPIOIEV *************************************************************/


/********************************************* GPIOIM *****************************************************/
typedef union {
struct {

 u32_t InterruptMaskEnable :8;
 u32_t reserved:24;

}Bits;

 u32_t Register;

}GPIO_InterruptMask_Reg;
/************************************* Description of GPIOIM***********************************************/
/* If a bit is set     --> allows the interrupt signal to be sent to the interrupt control
 * If a bit is cleared --> prevents the interrupt signal to be sent to the interrupt control
 *
 *  Access of the bits:
 *   1- Atomic access through struct
 *   2- Read-modify-write operation on the whole register--> u32_t Register
 */
/********************************************** GPIOIM*************************************************************/


typedef union {

    struct {
        u32_t Data :8;
        u32_t reserved :24;

    }bits;

    u32_t Register;

}GPIO_Data_Reg;

typedef union {

    struct {
        u32_t Direction :8;
        u32_t reserved :24;

    }bits;

    u32_t Register;

}GPIO_Direction_Reg;


typedef union {

    struct {
        u32_t DigitalEnable:8;
        u32_t reserved :24;

    }bits;

 u32_t Register;

}GPIO_DigitalEnable_Reg;

typedef union{

    struct{
        u32_t AlternateFunctionSelect :8;
        u32_t reserved :24;

    }bits;

  u32_t Register;

}GPIO_AFSEL_Reg;

typedef union {

    struct{
        u32_t AnalogModeSelect :8;
        u32_t reserved :24;
    }bits;

    u32_t Register;

}GPIO_AMSEL_Reg;


typedef union {

    struct {
        u32_t commit :8;
        u32_t reserved :24;
    }bits;

    u32_t Register;

}GPIO_CR_Reg;


typedef union {

    struct {

        u32_t  InterruptClear :8;
        u32_t reserved :24;

    }bits;

    u32_t Register;

}GPIO_ICR_Reg;

typedef union{
    struct{
     u32_t   GPIOPortRunModeClockGatingControl :6;
     u32_t   reserved :26;


    }Bits;

    u32_t Register;

}RCGCGPIO_Reg;

typedef union{
    struct{
        u32_t   GPIOPortRunModeClockGatingControl :6;
        u32_t   reserved :26;
    }Bits;
    u32_t Register;
}RCGC2_Reg;

typedef union{

    struct{

        u32_t PullUpEnable:8;
        u32_t :24;
    }Bits;

    u32_t Register;
}GPIOPUR_Reg;



#define GPIOIS_PortA_R   ( (volatile GPIO_InterruptSense_Reg*)(PORTA_BASE+ 0x404) )
#define GPIOIS_PortB_R   ( (volatile GPIO_InterruptSense_Reg*)(PORTB_BASE+ 0x404) )
#define GPIOIS_PortC_R   ( (volatile GPIO_InterruptSense_Reg*)(PORTC_BASE+ 0x404) )
#define GPIOIS_PortD_R   ( (volatile GPIO_InterruptSense_Reg*)(PORTD_BASE+ 0x404) )
#define GPIOIS_PortE_R   ( (volatile GPIO_InterruptSense_Reg*)(PORTE_BASE+ 0x404) )
#define GPIOIS_PortF_R   ( (volatile GPIO_InterruptSense_Reg*)(PORTF_BASE+ 0x404) )


#define GPIOIBE_PortA_R   ( (volatile GPIO_InterruptBothEdges_Reg*)(PORTA_BASE+ 0x408) )
#define GPIOIBE_PortB_R   ( (volatile GPIO_InterruptBothEdges_Reg*)(PORTB_BASE+ 0x408) )
#define GPIOIBE_PortC_R   ( (volatile GPIO_InterruptBothEdges_Reg*)(PORTC_BASE+ 0x408) )
#define GPIOIBE_PortD_R   ( (volatile GPIO_InterruptBothEdges_Reg*)(PORTD_BASE+ 0x408) )
#define GPIOIBE_PortE_R   ( (volatile GPIO_InterruptBothEdges_Reg*)(PORTE_BASE+ 0x408) )
#define GPIOIBE_PortF_R   ( (volatile GPIO_InterruptBothEdges_Reg*)(PORTF_BASE+ 0x408) )

#define GPIOIEV_PortA_R   ( (volatile GPIO_InterruptEvent_Reg*)(PORTA_BASE+ 0x40C) )
#define GPIOIEV_PortB_R   ( (volatile GPIO_InterruptEvent_Reg*)(PORTB_BASE+ 0x40C) )
#define GPIOIEV_PortC_R   ( (volatile GPIO_InterruptEvent_Reg*)(PORTC_BASE+ 0x40C) )
#define GPIOIEV_PortD_R   ( (volatile GPIO_InterruptEvent_Reg*)(PORTD_BASE+ 0x40C) )
#define GPIOIEV_PortE_R   ( (volatile GPIO_InterruptEvent_Reg*)(PORTE_BASE+ 0x40C) )
#define GPIOIEV_PortF_R   ( (volatile GPIO_InterruptEvent_Reg*)(PORTF_BASE+ 0x40C) )


#define GPIOIM_PortA_R   ( (volatile GPIO_InterruptMask_Reg*)(PORTA_BASE+ 0x410) )
#define GPIOIM_PortB_R   ( (volatile GPIO_InterruptMask_Reg*)(PORTB_BASE+ 0x410) )
#define GPIOIM_PortC_R   ( (volatile GPIO_InterruptMask_Reg*)(PORTC_BASE+ 0x410) )
#define GPIOIM_PortD_R   ( (volatile GPIO_InterruptMask_Reg*)(PORTD_BASE+ 0x410) )
#define GPIOIM_PortE_R   ( (volatile GPIO_InterruptMask_Reg*)(PORTE_BASE+ 0x410) )
#define GPIOIM_PortF_R   ( (volatile GPIO_InterruptMask_Reg*)(PORTF_BASE+ 0x410) )

#define GPIO_PortA_Data  (*( (volatile GPIO_Data_Reg*) PORTA_BASE + 0x3FC ) )
#define GPIO_PortB_Data  (*( (volatile GPIO_Data_Reg*) PORTB_BASE + 0x3FC) )
#define GPIO_PortC_Data  (*( (volatile GPIO_Data_Reg*) 0x400063FC) )
#define GPIO_PortD_Data  (*( (volatile GPIO_Data_Reg*) 0x400073FC) )
#define GPIO_PortE_Data  (*( (volatile GPIO_Data_Reg*) PORTE_BASE + 0x3FC) )
#define GPIO_PortF_Data  (*( (volatile GPIO_Data_Reg*) 0x40025038 ) )

//#define GPIO_PORTF_DATA_R (*(( volatile unsigned long *)0x40025038 ) )
//GPIO_Data_Reg
//0x40025038
//0x40025000
//#define GPIO_PortA_Data  (  PORTA_BASE )
//#define GPIO_PortB_Data  (  PORTB_BASE )
//#define GPIO_PortC_Data  (  PORTC_BASE )
//#define GPIO_PortD_Data  (  PORTD_BASE )
//#define GPIO_PortE_Data  (  PORTE_BASE )
//#define GPIO_PortF_Data  (  PORTF_BASE )


#define GPIO_PortA_Direction  (* ( (volatile GPIO_Direction_Reg*)(PORTA_BASE + 0x400) ) )
#define GPIO_PortB_Direction  (* ( (volatile GPIO_Direction_Reg*)(PORTB_BASE + 0x400) ) )
#define GPIO_PortC_Direction  (* ( (volatile GPIO_Direction_Reg*)(PORTC_BASE + 0x400) ) )
#define GPIO_PortD_Direction  (* ( (volatile GPIO_Direction_Reg*)(PORTD_BASE + 0x400) ) )
#define GPIO_PortE_Direction  (* ( (volatile GPIO_Direction_Reg*)(PORTE_BASE + 0x400) ) )
#define GPIO_PortF_Direction  (* ( (volatile GPIO_Direction_Reg*)(PORTF_BASE + 0x400) ) )

#define GPIO_PortA_DigitalEnable ( (volatile GPIO_DigitalEnable_Reg*)(PORTA_BASE + 0x51C) )
#define GPIO_PortB_DigitalEnable ( (volatile GPIO_DigitalEnable_Reg*)(PORTB_BASE + 0x51C) )
#define GPIO_PortC_DigitalEnable ( (volatile GPIO_DigitalEnable_Reg*)(PORTC_BASE + 0x51C) )
#define GPIO_PortD_DigitalEnable ( (volatile GPIO_DigitalEnable_Reg*)(PORTD_BASE + 0x51C) )
#define GPIO_PortE_DigitalEnable ( (volatile GPIO_DigitalEnable_Reg*)(PORTE_BASE + 0x51C) )
#define GPIO_PortF_DigitalEnable ( (volatile GPIO_DigitalEnable_Reg*)(PORTF_BASE + 0x51C) )

#define GPIO_PortA_AlternateFunctionSelect ((volatile GPIO_AFSEL_Reg*)(PORTA_BASE +  0x420))
#define GPIO_PortB_AlternateFunctionSelect ((volatile GPIO_AFSEL_Reg*)(PORTB_BASE +  0x420))
#define GPIO_PortC_AlternateFunctionSelect ((volatile GPIO_AFSEL_Reg*)(PORTC_BASE +  0x420))
#define GPIO_PortD_AlternateFunctionSelect ((volatile GPIO_AFSEL_Reg*)(PORTD_BASE +  0x420))
#define GPIO_PortE_AlternateFunctionSelect ((volatile GPIO_AFSEL_Reg*)(PORTE_BASE +  0x420))
#define GPIO_PortF_AlternateFunctionSelect ((volatile GPIO_AFSEL_Reg*)(PORTF_BASE +  0x420))

#define GPIO_PortA_AnalogModeSelect  ((volatile GPIO_AMSEL_Reg*)(PORTA_BASE +  0x528))
#define GPIO_PortB_AnalogModeSelect  ((volatile GPIO_AMSEL_Reg*)(PORTB_BASE +  0x528))
#define GPIO_PortC_AnalogModeSelect  ((volatile GPIO_AMSEL_Reg*)(PORTC_BASE +  0x528))
#define GPIO_PortD_AnalogModeSelect  ((volatile GPIO_AMSEL_Reg*)(PORTD_BASE +  0x528))
#define GPIO_PortE_AnalogModeSelect  ((volatile GPIO_AMSEL_Reg*)(PORTE_BASE +  0x528))
#define GPIO_PortF_AnalogModeSelect  ((volatile GPIO_AMSEL_Reg*)(PORTF_BASE +  0x528))

#define GPIO_PortA_PortControl       ((volatile u32_t*)(PORTA_BASE + 0x52C))
#define GPIO_PortB_PortControl       ((volatile u32_t*)(PORTB_BASE + 0x52C))
#define GPIO_PortC_PortControl       ((volatile u32_t*)(PORTC_BASE + 0x52C))
#define GPIO_PortD_PortControl       ((volatile u32_t*)(PORTD_BASE + 0x52C))
#define GPIO_PortE_PortControl       ((volatile u32_t*)(PORTE_BASE + 0x52C))
#define GPIO_PortF_PortControl       ((volatile u32_t*)(PORTF_BASE + 0x52C))

#define GPIO_PortA_LOCK              ((volatile u32_t*)(PORTA_BASE + 0x520))
#define GPIO_PortB_LOCK              ((volatile u32_t*)(PORTB_BASE + 0x520))
#define GPIO_PortC_LOCK              ((volatile u32_t*)(PORTC_BASE + 0x520))
#define GPIO_PortD_LOCK              ((volatile u32_t*)(PORTD_BASE + 0x520))
#define GPIO_PortE_LOCK              ((volatile u32_t*)(PORTE_BASE + 0x520))
#define GPIO_PortF_LOCK              ((volatile u32_t*)(PORTF_BASE + 0x520))


#define GPIO_PortA_Commit            ((volatile GPIO_CR_Reg *)(PORTA_BASE + 0x524))
#define GPIO_PortB_Commit            ((volatile GPIO_CR_Reg *)(PORTB_BASE + 0x524))
#define GPIO_PortC_Commit            ((volatile GPIO_CR_Reg *)(PORTC_BASE + 0x524))
#define GPIO_PortD_Commit            ((volatile GPIO_CR_Reg *)(PORTD_BASE + 0x524))
#define GPIO_PortE_Commit            ((volatile GPIO_CR_Reg *)(PORTE_BASE + 0x524))
#define GPIO_PortF_Commit            ((volatile GPIO_CR_Reg *)(PORTF_BASE + 0x524))

#define GPIO_PortA_PullUp_R          ((volatile GPIOPUR_Reg*)(PORTA_BASE + 0x510))
#define GPIO_PortB_PullUp_R          ((volatile GPIOPUR_Reg*)(PORTB_BASE + 0x510))
#define GPIO_PortC_PullUp_R          ((volatile GPIOPUR_Reg*)(PORTC_BASE + 0x510))
#define GPIO_PortD_PullUp_R          ((volatile GPIOPUR_Reg*)(PORTD_BASE + 0x510))
#define GPIO_PortE_PullUp_R          ((volatile GPIOPUR_Reg*)(PORTE_BASE + 0x510))
#define GPIO_PortF_PullUp_R          ((volatile GPIOPUR_Reg*)(PORTF_BASE + 0x510))


#define GPIO_PortA_InterruptClear   (* ( (volatile GPIO_ICR_Reg*)(PORTA_BASE + 0x41C) ) )
#define GPIO_PortB_InterruptClear   (* ( (volatile GPIO_ICR_Reg*)(PORTB_BASE + 0x41C) ) )
#define GPIO_PortC_InterruptClear   (* ( (volatile GPIO_ICR_Reg*)(PORTC_BASE + 0x41C) ) )
#define GPIO_PortD_InterruptClear   (* ( (volatile GPIO_ICR_Reg*)(PORTD_BASE + 0x41C) ) )
#define GPIO_PortE_InterruptClear   (* ( (volatile GPIO_ICR_Reg*)(PORTE_BASE + 0x41C) ) )
#define GPIO_PortF_InterruptClear   (* ( (volatile GPIO_ICR_Reg*)(PORTF_BASE + 0x41C) ) )


#define GPIO_RunModeClockGatingControl  ((volatile RCGCGPIO_Reg*)(0x400FE000+ 0x608))
#define RunModeClockGatingControlRegister2 ((volatile RCGC2_Reg*)(0x400FE000 + 0x108))

#define GPIO_PORTA_BIT_BAND_R  (0x40004000)
#define GPIO_PORTB_BIT_BAND_R  (0x40005000)
#define GPIO_PORTC_BIT_BAND_R  (0x40006000)
#define GPIO_PORTD_BIT_BAND_R  (0x40007000)
#define GPIO_PORTE_BIT_BAND_R  (0x40024000)
#define GPIO_PORTF_BIT_BAND_R  (0x40025000)


#endif /* GPIO_REG_H_ */

