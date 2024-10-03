
#ifndef SYSTICKTIMER_REG_H_
#define SYSTICKTIMER_REG_H_

#include "lstd.h"

#define SYSTICK_BASE_ADDRESS    (0xE000E000)

typedef union {

    struct{

        u32_t ENABLE:1;
        u32_t INTEN:1;
        u32_t CLK_SRC:1;
        u32_t :13;
        u32_t COUNT:1;
        u32_t :15;
    }bits;

    u32_t Register;

}STCTRL_Reg;


typedef union {

    struct{
        u32_t RELOAD:24;
        u32_t :8;
    }bits;

    u32_t Register;
}STRELOAD_Reg;


typedef union {

    struct{
        u32_t CURRENT:24;
        u32_t :8;
    }bits;

    u32_t Register;
}STCURRENT_Reg;



#define SystickControlStatus_R       ((STCTRL_Reg volatile*)(SYSTICK_BASE_ADDRESS + 0x010))
#define SysTickReloadValue_R         ((STRELOAD_Reg volatile*)(SYSTICK_BASE_ADDRESS + 0x014))
#define SysTickCurrentValue_R        ((STCURRENT_Reg volatile*)(SYSTICK_BASE_ADDRESS + 0x018))


#endif /* SYSTICKTIMER_REG_H_ */
