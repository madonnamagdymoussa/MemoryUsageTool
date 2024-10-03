
#include "SystemControl_config.h"

SystemControlConfig_t ConfigSystemSrc_PLL={
   PrecisionInterOscillator,
   PLL_Output,
   SYS_DIV2,
   EnableSysDiv
  };


SystemControlConfig_t ConfigSystemSrc_PrecisionInternalOSC={
   PrecisionInterOscillator,
   OSC_Output,
   SYS_DIV16,
   EnableSysDiv
  };


SystemControlConfig_t ConfigSystemSrc_PrecisionInternalOSC_DIV4={
   PrecisionInterOscillatorDIV4,
   OSC_Output,
   SYS_DIV2,
   EnableSysDiv
  };

/* Frequency of PWM = (freq of PrecisionInterOscillator) % (PWMDivider)
 * Frequency of PWM = (16*(10^6)) % (64) = 250,000 HZ
 * Tick time = (1/250,000 HZ)
 * */
SC_PWMConfiguration_t PWM_Module0={
      PWM_Div64,
      EnablePWMClkDiv,
      Module0PWM
};
