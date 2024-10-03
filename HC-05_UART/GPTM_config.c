/* =====================================================================================*/
/*                                    INCLUDES                                          */
/* =====================================================================================*/
#include"GPTM_config.h"


/*************************************TIMER 0**************************************/
GPTM_ConfigurationChannel_t GPTM_Config_32BitTimer0A ={
    _32_64BitTimer_IndiOrConcat,
    TimerA,
    _32_64BitTimerA,
    Timer0,
 };

GPTM_ConfigurationChannel_t GPTM_Config_32BitTimer0B ={
    _32_64BitTimer_IndiOrConcat,
    TimerB,
    _32_64BitTimerB,
    Timer0,
};

/*************************************TIMER 1**************************************/
GPTM_ConfigurationChannel_t GPTM_Config_32BitTimer1A ={
   _32_64BitTimer_IndiOrConcat,
   TimerA,
   _32_64BitTimerA,
   Timer1,
};

GPTM_ConfigurationChannel_t GPTM_Config_32BitTimer1B ={
    _32_64BitTimer_IndiOrConcat,
    TimerB,
    _32_64BitTimerB,
    Timer1,
 };

/*************************************TIMER 2**************************************/
GPTM_ConfigurationChannel_t GPTM_Config_32BitTimer2A ={
    _32_64BitTimer_IndiOrConcat,
    TimerA,
    _32_64BitTimerA,
    Timer2,
};

GPTM_ConfigurationChannel_t GPTM_Config_32BitTimer2B ={
    _32_64BitTimer_IndiOrConcat,
    TimerB,
    _32_64BitTimerB,
    Timer2,
};

/*************************************TIMER 3**************************************/
GPTM_ConfigurationChannel_t GPTM_Config_32BitTimer3A ={
    _32_64BitTimer_IndiOrConcat,
    TimerA,
    _32_64BitTimerA,
    Timer3,
};

GPTM_ConfigurationChannel_t GPTM_Config_32BitTimer3B ={
    _32_64BitTimer_IndiOrConcat,
    TimerB,
    _32_64BitTimerB,
    Timer3,
};

/*************************************TIMER 4**************************************/
GPTM_ConfigurationChannel_t GPTM_Config_32BitTimer4A ={
    _32_64BitTimer_IndiOrConcat,
    TimerA,
    _32_64BitTimerA,
    Timer4,
};

GPTM_ConfigurationChannel_t GPTM_Config_32BitTimer4B ={
    _32_64BitTimer_IndiOrConcat,
    TimerB,
    _32_64BitTimerB,
    Timer4,
};

/*************************************TIMER 5**************************************/
GPTM_ConfigurationChannel_t GPTM_Config_32BitTimer5A ={
    _32_64BitTimer_IndiOrConcat,
    TimerA,
    _32_64BitTimerA,
    Timer5,
};

GPTM_ConfigurationChannel_t GPTM_Config_32BitTimer5B ={
    _32_64BitTimer_IndiOrConcat,
    TimerB,
    _32_64BitTimerB,
    Timer5,
};

GPTM_ConfigurationChannel_t*  GPTM_Config_ArrPtrStruct[12]={
    &GPTM_Config_32BitTimer0A,
    &GPTM_Config_32BitTimer0B,
    &GPTM_Config_32BitTimer1A,
    &GPTM_Config_32BitTimer1B,
    &GPTM_Config_32BitTimer2A,
    &GPTM_Config_32BitTimer2B,
    &GPTM_Config_32BitTimer3A,
    &GPTM_Config_32BitTimer3B,
    &GPTM_Config_32BitTimer4A,
    &GPTM_Config_32BitTimer4B,
    &GPTM_Config_32BitTimer5A,
    &GPTM_Config_32BitTimer5B
};
