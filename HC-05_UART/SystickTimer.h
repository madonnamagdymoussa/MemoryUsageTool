/*
 * SystickTimer.h
 *
 *  Created on: Nov 30, 2022
 *      Author: future
 */

#ifndef SYSTICKTIMER_H_
#define SYSTICKTIMER_H_

#include "lstd.h"
#include "GPTM_config.h"
#define PIOSC_Div4_FrequencyVal  (4000000)
#define Systick_CounterSize      (16777216)

typedef enum{

    PIOSC_Div4,
    SysClk
}Systick_ClkSource;

/*
typedef enum{
    milli_Sec=1000,
    micro_Sec=1000000,
    Sec=1,
}GPTM_DelayUnit_t;*/


void SysTickConfigureClockSource(Systick_ClkSource ClkSource);
void SysTickGenerateDelay_Polling(u32_t NumDelayUnit, GPTM_DelayUnit_t DelayUnit);
void Systick_RegisterCallbackFunction(CallbackFunc_t pt_callback);
void SysTickGenerateDelay_Interrupt(u32_t NumDelayUnit, GPTM_DelayUnit_t DelayUnit);
void Systick_ClearFlag(void);
#endif /* SYSTICKTIMER_H_ */
