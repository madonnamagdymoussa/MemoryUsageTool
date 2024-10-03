#include "SystickTimer_reg.h"
#include "SystickTimer.h"
#include "SystemControl.h"
#include "SystemControl_config.h"
#include "lstd.h"
#include "NVIC.h"
#include "NVIC_config.h"


static volatile  CallbackFunc_t Systick_Callback =NULL_PTR;

 SystickHandler(){

     if (Systick_Callback != NULL_PTR){

     (*Systick_Callback)();

     }

 }
/***************************************************************************************/
/*                        STATIC INLINE FUNCTIONS                                      */
/***************************************************************************************/
static inline void SysTickEnable(void){
    SystickControlStatus_R->bits.ENABLE=1;
}


static inline void SysTickDisable(void){
    SystickControlStatus_R->bits.ENABLE=0;
}



static inline u64_t SysTickFrequencyGet(void){


  if(PIOSC_Div4 == SystickControlStatus_R->bits.CLK_SRC){

      return PIOSC_Div4_FrequencyVal;
  }

  u64_t SystemClkFreq;
  SystemClkFreq  = SC_GetSystemClock();
  return SystemClkFreq;

}


/***************************************************************************************/
/*                        INTERFACING FUNCTIONS                                        */
/***************************************************************************************/

void SysTickConfigureClockSource(Systick_ClkSource ClkSource){

    SystickControlStatus_R->bits.CLK_SRC=ClkSource;
}

void SysTickGenerateDelay_Polling(u32_t NumDelayUnit, GPTM_DelayUnit_t DelayUnit){

    SysTickDisable();

    u64_t SystickClkSource_FreqVal;
    u64_t TimerOnTickNum;

    //SystickClkSource_FreqVal=SysTickFrequencyGet();

    //TimerOnTickNum=(SystickClkSource_FreqVal/DelayUnit);
      SystickClkSource_FreqVal=0;
      TimerOnTickNum=0;
    SysTickReloadValue_R->bits.RELOAD=Systick_CounterSize-(Systick_CounterSize-TimerOnTickNum);

    SysTickEnable();

    u32_t NumDelayUnit_Counter;

    for(NumDelayUnit_Counter=0; NumDelayUnit_Counter<=NumDelayUnit; NumDelayUnit_Counter++){
     while(SystickControlStatus_R->bits.COUNT==0);
    }

    SysTickDisable();

}

void Systick_RegisterCallbackFunction(CallbackFunc_t pt_callback){

    Systick_Callback=pt_callback;
}


void SysTickGenerateDelay_Interrupt(u32_t NumDelayUnit, GPTM_DelayUnit_t DelayUnit){

    SysTickDisable();

    u64_t SystickClkSource_FreqVal;
    u64_t TimerOnTickNum;

    SystickClkSource_FreqVal=SysTickFrequencyGet();

    //TimerOnTickNum=(SystickClkSource_FreqVal/DelayUnit);
     TimerOnTickNum=0;
    SysTickReloadValue_R->bits.RELOAD=Systick_CounterSize-(Systick_CounterSize-TimerOnTickNum);

    SystickControlStatus_R->bits.INTEN=1;
     NVIC_Enable_Interrupt(15);
    SysTickEnable();

}

void Systick_ClearFlag(void){

    u32_t ReadFlag;
    ReadFlag=SystickControlStatus_R->Register;
}
