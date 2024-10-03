#ifndef GPTM_CONFIG_H_
#define GPTM_CONFIG_H_

#include "lstd.h"
//#include "SystemControl_config.h"
#include "GPIO_config.h"
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
 *
 * */
/*************************** Madonna Naming Convention in config.h file ***************************/

 /* =====================================================================================*/
 /*                                    MACRO                                             */
 /* =====================================================================================*/
#define _32Bit_TotalTickNum  (4294967296)

/* =====================================================================================*/
/*                                    ENUM                                              */
/* =====================================================================================*/

typedef enum{
   Timer0,
   Timer1,
   Timer2,
   Timer3,
   Timer4,
   Timer5,
   TimerChannel_Indices
}GPTM_ChannelIndexArr_t;
/***********************************/

typedef enum{
    _16_32BitTimer_IndiOrConcat,
    _32_64BitTimer_IndiOrConcat,
    TimerSize_Indices
}GPTM_TimerSizeIndexArr_t;
/***********************************/

typedef enum{
   TimerA = 0,
   TimerB = 8
}GPTM_ConfigureTimerName_t;
/***********************************/

typedef enum{
    _16_32BitTimerA,
    _32_64BitTimerA,
    _16_32BitTimerB,
    _32_64BitTimerB,
    TimerSizeName_Indices
}GPTM_TimerSizeNameIndexArr_t;
/***********************************/

typedef enum{
    ConcatenatedMode=0x0,
    _32_64BitRTC=0x1,
    IndividualMode=0x4
 }GPTM_ConfigureTimerSize_t;
 /***********************************/

typedef enum{
    CountDownDirection,
    CountUpDirection
 }GPTM_ConfigureCountDirection_t;
 /***********************************/

 typedef enum{
     OneShotMode=0x1,
     PeriodicMode=0x2,
     CaptureMode=0x3
 }GPTM_ConfigureTimerMode_t;
 /***********************************/

 typedef enum{
     MatchInterruptsDisable,
     MatchInterruptEnable
 }GPTM_ConfigureMatchInterruptMode_t;
 /***********************************/

 typedef enum{
     CaptureMode_EdgeCountMode,
     CaptureMode_EdgeTimeMode,
 }GPTM_ConfigureCaptureMode_t;
 /***********************************/

 typedef enum{
     PWM_OutputNotInverted,
     PWM_OutputInverted
 }GPTM_ConfigurePWMOutputLevel_t;
 /***********************************/

  typedef enum{
     milli_Sec=1000,
     micro_Sec=1000000,
     Sec=1,
 }GPTM_DelayUnit_t;

  /* =====================================================================================*/
 /*                                    STRUCT                                             */
 /* =====================================================================================*/
 typedef struct {
    GPTM_TimerSizeIndexArr_t TimerSizeIndexArr;
    GPTM_ConfigureTimerName_t ConfigureTimerName;
    GPTM_TimerSizeNameIndexArr_t TimerSizeNameIndexArr;
    GPTM_ChannelIndexArr_t ChannelIndexArr;

 }const GPTM_ConfigurationChannel_t;

 extern GPTM_ConfigurationChannel_t*  GPTM_Config_ArrPtrStruct[12];

 #endif /* GPTM_CONFIG_H_ */
