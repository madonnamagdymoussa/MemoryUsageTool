
#ifndef SYSTEMCONTROL_REG_H_
#define SYSTEMCONTROL_REG_H_

#include "lstd.h"

/*********************************** Base Address ***********************************/
#define SYSTEM_CONTROL_BASE  0x400FE000
/*********************************** Base Address ***********************************/



typedef union {
      struct{

         u32_t MainOscillatorDisable :1;
         u32_t :3;
         u32_t OscillatorSource:2;
         u32_t CrystalValue :5;
         u32_t PLLBypass:1;
         u32_t :1;
         u32_t PLLPowerDown :1;
         u32_t  :3;
         u32_t PWMUnitClockDivisor:3;
         u32_t EnablePWMClockDivisor:1;
         u32_t :1;
         u32_t EnableSystemClockDivider:1;
         u32_t SystemClockDivisor :4;
         u32_t AutoClockGating:1;
         u32_t :4;

    }bits;

 u32_t Register;

}RCC_Reg;

typedef union{

    struct {
        u32_t MINT:10;
        u32_t MFRAC:10;
        u32_t reserved :12;

    }bits;

 u32_t Register;

}PLLFREQ0_Reg;


typedef union {
    struct {

    u32_t N:5;
    u32_t  :3;
    u32_t Q:5;
    u32_t  :19;

    }bits;

    u32_t Register;

}PLLFREQ1_Reg;

typedef union {
    struct{
        u32_t PLLLock  :1;
        u32_t reserved :31;

    }bits;

    u32_t Register;

}PLLSTAT_Reg;

typedef union {

    struct {
   u32_t reserved :1;
   u32_t BOR1RIS :1;
   u32_t  :1;
   u32_t MOFRIS:1;
   u32_t  :2;
   u32_t PLLLockRawInterruptStatus:1;
   u32_t USBPLLLockRawInterruptStatus :1;
   u32_t MOSCPowerUpRawInterruptStatus :1;
   u32_t  :1;
   u32_t VDDARIS :1;
   u32_t BOR0RIS:1;
   u32_t  :20;

    }bits;

    u32_t Register;
}RIS_Reg;



typedef union {
    struct {
          u32_t  :4;
          u32_t OscillatorSource2 :3;
          u32_t  :4;
          u32_t PLLBypass2 : 1;
          u32_t  : 1;
          u32_t PowerDownPLL :1;
          u32_t PowerDownUSBPLL :1;
          u32_t  :7;
          u32_t SYSDIV2LSB:1;
          u32_t SystemClockDivisor2 :6;
          u32_t  :1;
          u32_t DIV400: 1;
          u32_t UseRCC2: 1;

    }bits;

    u32_t Register;
}RCC2_Reg;

typedef union {
    struct{

      u32_t  PWMModule0 :1;
      u32_t  PWMModule1 :1;
      u32_t  :30;

    }bits;

    u32_t Register;
}RCGCPWM_Reg;

#define SC_PLL_FREQUENCY0             ( (volatile PLLFREQ0_Reg*) (SYSTEM_CONTROL_BASE + 0x160) )
#define SC_PLL_FREQUENCY1             ( (volatile PLLFREQ1_Reg*) (SYSTEM_CONTROL_BASE + 0x164) )
#define SC_PLL_STATUS                 ( (volatile PLLSTAT_Reg*) (SYSTEM_CONTROL_BASE + 0x168) )
#define SC_RIS                        ( (volatile RIS_Reg*) (SYSTEM_CONTROL_BASE + 0x050) )
#define SC_RunModeClockConfiguration  ( (volatile RCC_Reg*) (SYSTEM_CONTROL_BASE + 0x060) )
#define SC_RunModeClockConfiguration2 ( (volatile RCC2_Reg*) (SYSTEM_CONTROL_BASE + 0x070) )

/*************************************** RunModeClkConfiguration ******************************************/
#define SC_RunModeClockPWM_Reg        ((volatile RCGCPWM_Reg*)(SYSTEM_CONTROL_BASE + 0x640))
#define SC_RunModeClockADC_Reg        ((volatile u32_t*)(SYSTEM_CONTROL_BASE + 0x638))




#endif /* SYSTEMCONTROL_REG_H_ */
