
#ifndef GPIO_CONFIG_H_
#define GPIO_CONFIG_H_

/* =====================================================================================*/
/*                                    INCLUDES                                          */
/* =====================================================================================*/
#include "lstd.h"
//#include "DMA_reg.h"

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
 * 4-The Name of the Array of pointer to struct must end with  _ArrPtrStruct
 *
 *
 * */
/*************************** Madonna Naming Convention in config.h file ***************************/

/* =====================================================================================*/
/*                                    ENUM                                              */
/* =====================================================================================*/
 typedef enum{

    Channel_0 =0,
    Channel_1 =1,
    Channel_2 =2,
    Channel_3 =3,
    Channel_4 =4,
    Channel_5 =5,
    Channel_6 =6,
    Channel_7 =7

}GPIO_ConfigureChannelNum_t;
/***********************************/

typedef enum{
    PortA =0,
    PortB =1,
    PortC =2,
    PortD =3,
    PortE =4,
    PortF =5,

    Port_Indices=6
}GPIO_PortNumIndexArr_t;
/***********************************/

typedef enum{
    InputFloat =0,
    Output =1,

    MinNumState=0,
    MaxNumState=1
}GPIO_PinState_t;
/***********************************/

typedef enum {
    OutputLow,
    OutputHigh
}GPIO_OutputValue_t;
/***********************************/

typedef enum{
    Disable_AFSEL,
    Enable_AFSEL
}GPIO_AFSELMode_t;
/***********************************/
typedef enum{
    Disable_AMSEL,
    Enable_AMSEL
}GPIO_AMSELMode_t;
/***********************************/

typedef enum{
    MuxValue_0,
    MuxValue_1,
    MuxValue_2,
    MuxValue_3,
    MuxValue_4,
    MuxValue_5,
    MuxValue_6,
    MuxValue_7,
    MuxValue_8,
    MuxValue_9,
    MuxValue_10,
    MuxValue_11,
    MuxValue_12,
    MuxValue_13,
    MuxValue_14,
    MuxValue_15,
}GPIO_ConfigureMuxValue_t;
/***********************************/

typedef enum{
  DisableDigitalFunction,
  EnableDigitalFunction
}GPIO_DigitalMode_t;
/***********************************/

typedef enum{
   DisableOpenDrain,
   EnableOpenDrain
}GPIO_OpenDrainMode_t;
/***********************************/

typedef enum{
    EnableLock,
    DisableLock
}GPIO_LockMode_t;
/***********************************/

typedef enum{
    Enable_InterruptMask,
    Disable_InterruptMask
}GPIO_InterruptMaskMode_t;
/***********************************/

/******************************END OF ENUM*******************************/

/* =====================================================================================*/
/*                                    MACRO                                             */
/* =====================================================================================*/

#define PWM_32_64BitTimer0A_IndexArr (0)
#define PWM_32_64BitTimer0B_IndexArr (1)
#define PWM_32_64BitTimer1A_IndexArr (2)
#define PWM_32_64BitTimer1B_IndexArr (3)
#define PWM_32_64BitTimer2A_IndexArr (4)
#define PWM_32_64BitTimer2B_IndexArr (5)
#define PWM_32_64BitTimer3A_IndexArr (6)
#define PWM_32_64BitTimer3B_IndexArr (7)
#define PWM_32_64BitTimer4A_IndexArr (8)
#define PWM_32_64BitTimer4B_IndexArr (9)
#define PWM_32_64BitTimer5A_IndexArr (10)
#define PWM_32_64BitTimer5B_IndexArr (11)
/******************************END OF MACRO*******************************/

/* =====================================================================================*/
/*                                    STRUCT                                             */
/* =====================================================================================*/
typedef struct{
    GPIO_PortNumIndexArr_t PortNumIndexArr;
    GPIO_ConfigureChannelNum_t ConfigureChannelNum;
    u8_t PWM_Timer_IndexArr;
}const GPIO_TimerConfigChannel_t;

/* =================================================*/
/*NOTE: Due to padding it PREFERABLE to place the struct member with type u8_t
 *at the END of the of the struct in order to reserve two bytes only
 *
 * IF you placed  u8_t PWM_Timer_IndexArr at the start of the struct
 * or even in the middle then it will reserve 4 bytes
 * */
/* =================================================*/

typedef struct{
    GPIO_PortNumIndexArr_t PortNumIndexArr;
    GPIO_ConfigureChannelNum_t ChannelNumRx;
    GPIO_ConfigureChannelNum_t ChannelNumTx;
}const GPIO_UARTConfigChannel_t;

/******************************END OF STRUCT*******************************/

typedef struct{

    GPIO_PortNumIndexArr_t PortNumIndexArr;
    GPIO_ConfigureChannelNum_t ConfigureChannelNum;
 }GPIO_ConfigurePin_t;


extern GPIO_TimerConfigChannel_t * const GPIO_TimerAFSELConfig_ArrPtrStruct[12];
extern GPIO_UARTConfigChannel_t * const GPIO_AFSELUARTConfig_ArrPtrStruct[8];

extern GPIO_ConfigurePin_t GPIO_ConfigurePin_PF4;
extern GPIO_ConfigurePin_t GPIO_ConfigurePin_PF2;
extern GPIO_ConfigurePin_t GPIO_ConfigurePin_PF1;
extern GPIO_ConfigurePin_t GPIO_ConfigurePin_PF3;
extern GPIO_ConfigurePin_t GPIO_ConfigurePin_PF0;

#endif /* GPIO_CONFIG_H_ */
