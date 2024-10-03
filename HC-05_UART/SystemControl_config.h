#ifndef SYSTEMCONTROL_CONFIG_H_
#define SYSTEMCONTROL_CONFIG_H_
//#include "GPTM_config.h"

/*************************** Madonna Naming Convention in config.h file ***************************/

/* 1-If the enum constants is used for storing the Indices of an Array then the enum name must end with IndexArr_t
 * Example of the enum name: PeripheralName_xxxxIndexArr_t
 *
 * 1.1- If the enum constants is used for storing the Indices of the array the Last constant must store the total
 * number of the indices and that constant name must end with _Indices
 *
 * 2-If the enum constants is used for storing values that will be inserted inside the hardware registers(configurations) then
 * the enum name must begin with Configure keyword
 * Example of the enum name: PeripheralName_Configurexxxxxxx_t
 *
 * 2.1- IF the configuration is related to turning on or off or even controlling a Specific feature
 * then the enum name must end with Mode_t
 * Example of the enum name: PeripheralName_ConfigurexxxxxMode_t
 *
 *
 * 3-If the struct is used to store the information of specific channel such as the channel number
 * and the instance of the typedef enum related to configurations then
 * the name of the struct must end with ConfigurationChannel_t
 * Example of the struct name: PeripheralName_xxxxxConfigurationChannel_t
 *
 *4-The name of the instance created from typedef union must in _unionInst
 *Example of the union name: PeripheralName_xxxxx_unionInst
 *
 * */
/*************************** Madonna Naming Convention in config.h file ***************************/

/* =====================================================================================*/
/*                                    ENUM                                              */
/* =====================================================================================*/
typedef enum{

    MainOscillator,
    PrecisionInterOscillator,
    PrecisionInterOscillatorDIV4,
    LowFreqInterOscillator
} SC_ConfigureOscSource_t;
/*********************************/

typedef enum {
    _5MHz_USB =0x09,
    _6MHz_USB=0x0B,
    _7_3728MHz=0x0D,
    _8MHz_USB=0x0E,
    _10MHz_USB=0x10

} SC_ConfigureCrystalValue_t;
/*********************************/

typedef enum {
    DisableSysDiv,
    EnableSysDiv
}SC_ConfigureSysDivMode_t;
/*********************************/

typedef enum{
    DisablePWMClkDiv,
    EnablePWMClkDiv
} SC_ConfigurePWMDivMode_t;
/*********************************/

typedef enum{
    PLL_Output,
    OSC_Output
}BypassValue_OutputSource_t;
/*********************************/

typedef enum{
    SYS_DIV1,
    SYS_DIV2,
    SYS_DIV3,
    SYS_DIV4,
    SYS_DIV5,
    SYS_DIV6,
    SYS_DIV7,
    SYS_DIV8,
    SYS_DIV9,
    SYS_DIV10,
    SYS_DIV11,
    SYS_DIV12,
    SYS_DIV13,
    SYS_DIV14,
    SYS_DIV15,
    SYS_DIV16
}SC_ConfigureSysDiv_t;
/*********************************/

typedef enum{
    PWM_Div2,
    PWM_Div4,
    PWM_Div8,
    PWM_Div16,
    PWM_Div32,
    PWM_Div64=7
}SC_ConfigurePWMDiv_t;
/***********************************/

typedef enum{
 Module0PWM,
 Module1PWM
}SC_ConfigPWMmoduleNum_t;
/***********************************/

typedef enum{
	Module0ADC,
	Module1ADC
}SC_ConfigADCmoduleNum_t;
/***********************************/



/* =====================================================================================*/
/*                                    STRUCT                                            */
/* =====================================================================================*/

typedef struct{
    SC_ConfigureOscSource_t ConfigOscSource;
    BypassValue_OutputSource_t OutputSource;
    SC_ConfigureSysDiv_t ConfigureSysDiv;
    SC_ConfigureSysDivMode_t ConfigureSysDivMode;
    SC_ConfigureCrystalValue_t ConfigCrystalValue;

}SystemControlConfig_t;


typedef struct{

    SC_ConfigurePWMDiv_t ConfigurePWMDiv;
    SC_ConfigurePWMDivMode_t ConfigurePWMDivMode;
    SC_ConfigPWMmoduleNum_t ConfigPWMmoduleUsed;

}SC_PWMConfiguration_t;


/************************************** Creating instances of typedef Structure *****************************************************************************************/
extern SystemControlConfig_t ConfigSystemSrc_PLL;
extern SystemControlConfig_t ConfigSystemSrc_PrecisionInternalOSC;
extern SC_PWMConfiguration_t PWM_Module0;
extern SystemControlConfig_t ConfigSystemSrc_PrecisionInternalOSC_DIV4;




#endif /* SYSTEMCONTROL_CONFIG_H_ */
