
#ifndef GPIO_H_
#define GPIO_H_
/* =====================================================================================*/
/*                                  INCLUDES                                            */
/* =====================================================================================*/
#include "gpio_config.h"

void GPIO_SetData(GPIO_PortNumIndexArr_t PortNumIndexArr , GPIO_ConfigureChannelNum_t ConfigureChannelNum, GPIO_OutputValue_t OutputValue);

void GPIO_SetPinStatus(GPIO_PortNumIndexArr_t PortNumIndexArr, GPIO_ConfigureChannelNum_t ConfigureChannelNum, GPIO_PinState_t PinState );

void GPIO_TogglePinValue(GPIO_PortNumIndexArr_t PortNumIndexArr, GPIO_ConfigureChannelNum_t ConfigureChannelNum);

void GPIO_ConfigureCommit(GPIO_PortNumIndexArr_t PortNumIndexArr, GPIO_ConfigureChannelNum_t ConfigureChannelNum, GPIO_LockMode_t LockMode);

void GPIO_ConfigureAlternateFunctionSelect(GPIO_PortNumIndexArr_t PortNumIndexArr, GPIO_ConfigureChannelNum_t ConfigureChannelNum , GPIO_AFSELMode_t AFSELMode);

void GPIO_ConfigureAnalogModeSelect(GPIO_PortNumIndexArr_t PortNumIndexArr, GPIO_ConfigureChannelNum_t ConfigureChannelNum, GPIO_AMSELMode_t AMSELMode);

void GPIO_ConfigureDigitalEnable(GPIO_PortNumIndexArr_t PortNumIndexArr, GPIO_ConfigureChannelNum_t ConfigureChannelNum, GPIO_DigitalMode_t DigitalMode);

void GPIO_ConfigurePortControl(GPIO_PortNumIndexArr_t PortNumIndexArr, GPIO_ConfigureChannelNum_t ConfigureChannelNum, GPIO_ConfigureMuxValue_t ConfigureMuxValue );

void GPIO_ConfigureInterruptMask(GPIO_PortNumIndexArr_t PortNumIndexArr, GPIO_ConfigureChannelNum_t ConfigureChannelNum, GPIO_InterruptMaskMode_t InterruptMaskMode);

void GPIO_EXTIClearInterrupt(GPIO_PortNumIndexArr_t PortNumIndexArr, GPIO_ConfigureChannelNum_t ConfigureChannelNum);

void GPIO_EnableAFSEL_UART(GPIO_UARTConfigChannel_t* pt_UARTConfigChannel);

void GPIO_EnableAFSEL_GPTM(GPIO_TimerConfigChannel_t * pt_TimerConfigChannel);

void RegisterCallbackFunction(GPIO_PortNumIndexArr_t PortNumIndexArr,CallbackFunc_t pt_callback);

void GPIO_ConfigureOutputPin(GPIO_ConfigurePin_t* pt_ConfigurePin);
void GPIO_ConfigureInputPin(GPIO_ConfigurePin_t* pt_ConfigurePin);

u32_t GPIO_ReadBitBandBits(GPIO_ConfigureChannelNum_t ChannelNum, GPIO_PortNumIndexArr_t PortNumIndexArr);
void GPIO_WriteBitBandBits(GPIO_ConfigureChannelNum_t ChannelNum, GPIO_PortNumIndexArr_t PortNumIndexArr, GPIO_OutputValue_t  OutputValue);
void GPIO_ToggleBitBandBits(GPIO_ConfigureChannelNum_t ChannelNum, GPIO_PortNumIndexArr_t PortNumIndexArr);

void GPIO_SetPinDirection(GPIO_PortNumIndexArr_t PortNumIndexArr, GPIO_ConfigureChannelNum_t ConfigureChannelNum, GPIO_PinState_t PinState );

#endif /* GPIO_H_ */



