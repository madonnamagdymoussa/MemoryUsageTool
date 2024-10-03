/*************************************************************************************************************************************/
/* Name:   SystemControl.c                                                                                                                    */
/* Author: Madonna Magdy                                                                                                             */
/* Version: V1                                                                                                                       */
/* Usage: This module contains the implementation for the SystemControl functions                                                    */
/*************************************************************************************************************************************/

/************************************ Includes ************************************/
#include "SystemControl_reg.h"
#include "SystemControl.h"

/************************************ Includes ************************************/

/******************************************* ID Description of the Unit *********************************************************/
// first number of ID signifies the module used (the SystemControl  module takes number1)

  //The Second number signifies that whether you are using a function or an array or a variable
 //(The variable takes number1 ,The array takes number 2, The function takes number 3  )

 //The Third number signifies the number of a function or an array or a variable

/******************************************* ID Description of the Unit ********************************************************/


/******************************  ID Description For Testing *********************************************************/

 //First part is the ID description of the Unit

 //The second part signifies how many number of tests you use on a certain variable or function (on a certain unit)

/******************************  ID Description For Testing *********************************************************/


/**************** Unit ID = 1.2.1 **********************************/
/* UNIT ID = 1.2.1
 * UNIT NAME: SYSDIV
 * UNIT DESCRIPTION:
 * the index of the array represents the bits value in the RCC register
 * the content of the array represents the value that will divide the frequency value
 *  */
u8_t const SC_SYSDIV[16] ={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
u8_t const SC_PWMDIV[8]  ={2,4,8,16,32,64,64,64};

static inline SC_EnableRunModeClockPWM(SC_PWMConfiguration_t* pt_PWMConfiguration ){

    (SC_RunModeClockPWM_Reg)->Register |=(1<< (pt_PWMConfiguration->ConfigPWMmoduleUsed) );

}

static inline SC_DisableRunModeClockPWM(SC_PWMConfiguration_t* pt_PWMConfiguration){

    (SC_RunModeClockPWM_Reg)->Register &=~(1<< (pt_PWMConfiguration->ConfigPWMmoduleUsed));
}

/*
static inline SC_EnableRunModeClockADC(SC_ConfigADCmoduleUsed_t ConfigADCmoduleUsed){
	(*SC_RunModeClockADC_Reg) |= (1<<ConfigADCmoduleUsed);
}
*/
/**************** Unit ID = 1.3.1 **********************************/
/* UNIT ID = 1.3.1
 * UNIT NAME: SystemControlInitialization_RCC
 * UNIT DESCRIPTION: the function used to initialize the system clock module
 * PARAMETERS : pointer to SystemControlConfig_t struct
 * RETURN TYPE : void
 * PRE-CONDITION : the struct in SystemControl_Config.c must be configured first
 * POST-CONDITION: the RCC will be initialized based on the configuration in the struct of type  SystemControlConfig_t
 */
void SC_Initialization(SystemControlConfig_t* ptConfig){

            /*Use the RCC register*/
    SC_RunModeClockConfiguration2->bits.UseRCC2=0;

    /***********************************Testing ID = 1.3.1.1******************************************************/
    /* test the if condition inside the function if PLL output was configured as an output source
     * Branch testing
     */
  if ( PLL_Output == ptConfig->OutputSource){

   /********************************************STEP1**************************************************/
             SC_RunModeClockConfiguration->bits.PLLBypass=1; /*Disable the use of PLL*/
             SC_RunModeClockConfiguration->bits.EnableSystemClockDivider=DisableSysDiv;
             /*the configuration of the PLL must be validated first before enabling the PLL
              *Therefore,we need to configure the micro controller to run off a "raw" clock source first*/

             /*NOTE:
              *the system clock divider will be disabled at first because
              *there is no reason to open it as we DID NOT choose the clock source or even specify a crystal value
              *So, by logic there is no frequency value to divide
              *So, there is no reason to consume power and enable it at first
              *Enable the clock divider AFTER selecting the clock source and crystal value*/

   /**********************************************STEP2*****************************************************/
             SC_RunModeClockConfiguration->bits.OscillatorSource = ptConfig->ConfigOscSource;
             SC_RunModeClockConfiguration->bits.PLLPowerDown=0;

             if (MainOscillator == ptConfig->ConfigOscSource){
             SC_RunModeClockConfiguration->bits.CrystalValue= ptConfig->ConfigCrystalValue;
             }

              /**************** Testing ID = 1.3.1.2 **********************************/
              /*
              * giving power to the PLL does NOT mean that the PLL will be enabled
              * the PLL must be powered up first before enabling it
              * when the PLL is powered we can lock it up in order to reach the specified frequency
              * AFTER that it can be used
              * Because it is not logic to enable the use of the PLL when it did not reach the specified value (400MHz)
              * Testing -----> At that point we need to test that the PLL is still disabled and it is powered up  */

  /************************************************STEP3***********************************************************/
             SC_RunModeClockConfiguration->bits.SystemClockDivisor = ptConfig->ConfigureSysDiv;
             SC_RunModeClockConfiguration->bits.EnableSystemClockDivider=ptConfig->ConfigureSysDivMode;
             /*
              * system divider used in the struct configuration will be used as an index an the array will access the real value
              * that will be inserted in the register
              */

             /*
              * At that point we can enable the system clock divider because
              * there is an output to the PLL frequency because the PLL circuit is powered up so there is an output frequency
              * Note---> at that point the PLL output frequency did not reach the desired frequency but there is an output
              * so, every thing must be ready before enabling the use of the PLL so we need to enable the system clock divider
              */

  /************************************************STEP4*************************************************************/
             while (0 == SC_RIS->bits.PLLLockRawInterruptStatus);
             /*
              * wait until the PLL timer has reached the ready state
              */

  /************************************************STEP5*************************************************************/
             SC_RunModeClockConfiguration->bits.PLLBypass=0;
             /*Enable the use of the PLL*/

         }


  /*********************************** Testing ID = 1.3.1.1 ******************************************************/
  /* test the if condition inside the function if oscillator source output was configured as an output source
   * Branch testing (second part of the branch testing case ) ---> first part was testing the condition of the PLL output
   *
   */

         else if(OSC_Output == ptConfig->OutputSource){

             SC_RunModeClockConfiguration->bits.PLLBypass=1; /*Disable the use of PLL*/
             SC_RunModeClockConfiguration->bits.OscillatorSource= ptConfig->ConfigOscSource;

             if( MainOscillator == ptConfig->ConfigOscSource){
             SC_RunModeClockConfiguration->bits.CrystalValue= ptConfig->ConfigCrystalValue;
             }

             if( EnableSysDiv == ptConfig->ConfigureSysDivMode){
             SC_RunModeClockConfiguration->bits.SystemClockDivisor = ptConfig->ConfigureSysDiv;
             SC_RunModeClockConfiguration->bits.EnableSystemClockDivider=EnableSysDiv;
             }

         }

}

/**************** Unit ID = 1.3.2 **********************************/
/* UNIT ID = 1.3.2
 * UNIT NAME: SC_GetOscillatorSourceValue_RCC
 * UNIT DESCRIPTION: this function is responsible for getting the oscillator source value based on the RCC register
 * PARAMETERS : void
 * RETURN TYPE : variable of type u32_t that will store the value of the oscillator source
 * PRE-CONDITION : the system clock must be initialized and the RCC register is configured
 * POST-CONDITION: the function will return the value of the oscillator source
 *
 * NOTE :this function is a static function because the user will not use this function in the application layer
 *       instead it will called inside SC_GetSystemClock_RCC function
 */

u32_t static SC_GetOscillatorValue(void){

    switch(SC_RunModeClockConfiguration->bits.OscillatorSource){

        case 0:
            return MAIN_OSC;


        case 1:
            return PRECISION_INTERNAL_OSC;


        case 2:
            return PRECISION_INTERNAL_OSC_DIV4;


        case 3:
            return LOW_FREQUENCY_INTERNAL_OSC;


         /* NOTE:
          *  If you put a return, then the function returns before the break is executed
          *  and therefore the break will never be reached.
          *  So there will be a warning and to solve it remove the break statement
          */


    }

    return 0;
}


/**************** Unit ID = 1.3.3 **********************************/
/* UNIT ID = 1.3.3
 * UNIT NAME: SC_GetSystemClock_RCC
 * UNIT DESCRIPTION: this function is responsible for getting the  value of the system clock
 * PARAMETERS : void
 * RETURN TYPE : variable of type u32_t that will store the value of the system clock
 * PRE-CONDITION : the system clock must be initialized and the RCC register is configured
 * POST-CONDITION: the function will return the value of the oscillator source
 *
 */

u32_t SC_GetSystemClock(void){

    u32_t OS_value;

    /**************** Testing ID = 1.3.3.2 **********************************/
    /* Branch testing (first part)
     * testing the condition when the PLL is used and check the OS_value
     */
    if ( 0 == SC_RunModeClockConfiguration->bits.PLLBypass){

        if ( 1 == SC_RunModeClockConfiguration->bits.EnableSystemClockDivider ){

             OS_value  = 200000000;
             OS_value= (OS_value/SC_SYSDIV[SC_RunModeClockConfiguration->bits.SystemClockDivisor]);
        }

        return OS_value;

    }


    /**************** Testing ID = 1.3.3.2 **********************************/
    /* Branch testing (Second part)
     * testing the condition when the oscillator source is used and check the OS_value
     */
    else if(1 == SC_RunModeClockConfiguration->bits.PLLBypass){

        /**************** Testing ID = 1.3.3.1 **********************************/
        /*
         * Interface testing
         * test that the output of the SC_GetOscillatorSourceValue_RCC() function is equivilant to what was already configured
         */
        OS_value= SC_GetOscillatorValue();

        if ( 1 == SC_RunModeClockConfiguration->bits.EnableSystemClockDivider){
            OS_value= (OS_value/SC_SYSDIV[SC_RunModeClockConfiguration->bits.SystemClockDivisor]);
        }

        return OS_value;

    }

    return 0;
}


void SC_PWMClkIntialization(SC_PWMConfiguration_t* PWMConfiguration){

    SC_EnableRunModeClockPWM(PWMConfiguration);

    SC_RunModeClockConfiguration->bits.EnablePWMClockDivisor = PWMConfiguration->ConfigurePWMDivMode;

    if ( EnablePWMClkDiv == PWMConfiguration->ConfigurePWMDivMode){

    SC_RunModeClockConfiguration->bits.PWMUnitClockDivisor = PWMConfiguration->ConfigurePWMDiv;

    }
}



u32_t SC_GetPWMFrequency(SC_PWMConfiguration_t * pt_PWMConfiguration){

    u32_t PWMFreq;
    u32_t SysClkFreq;

   SysClkFreq = SC_GetSystemClock();

  // if ( 1 == SC_RunModeClockConfiguration->bits.EnableSystemClockDivider){

   if ( 1 == pt_PWMConfiguration->ConfigurePWMDivMode){

       PWMFreq = SysClkFreq/SC_PWMDIV[SC_RunModeClockConfiguration->bits.PWMUnitClockDivisor];
       return PWMFreq;
   }

  return SysClkFreq;

}


void SC_ADC_ClkIntialization(SC_ConfigPWMmoduleNum_t  ConfigPWMmoduleNum){

    *SC_RunModeClockADC_Reg  |= (1<< ConfigPWMmoduleNum );
}
