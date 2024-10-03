/* =====================================================================================*/
/*                                  INCLUDES                                            */
/* =====================================================================================*/
  #include "GPIO_config.h"

/* =====================================================================================*/
/*                                   INSTANCE OF STRUCT                                 */
/* =====================================================================================*/


/*==================================================*/
/*     Config for  AFSEL_PWM                        */
/*==================================================*/
GPIO_TimerConfigChannel_t Timer0A_32_64Bit ={
     PortC,
     Channel_4,
     PWM_32_64BitTimer0A_IndexArr
};/*************************************************/

GPIO_TimerConfigChannel_t Timer0B_32_64Bit={
     PortC,
     Channel_5,
     PWM_32_64BitTimer0B_IndexArr
};/*************************************************/

GPIO_TimerConfigChannel_t Timer1A_32_64Bit={
     PortC,
     Channel_6,
     PWM_32_64BitTimer1A_IndexArr
};/*************************************************/

GPIO_TimerConfigChannel_t Timer1B_32_64Bit={
    PortC,
    Channel_7,
    PWM_32_64BitTimer1B_IndexArr
};/*************************************************/

GPIO_TimerConfigChannel_t Timer2A_32_64Bit={
   PortD,
   Channel_0,
  PWM_32_64BitTimer2A_IndexArr
};/*************************************************/

GPIO_TimerConfigChannel_t Timer2B_32_64Bit={
   PortD,
   Channel_1,
   PWM_32_64BitTimer2B_IndexArr
};/*************************************************/

GPIO_TimerConfigChannel_t Timer3A_32_64Bit={
   PortD,
   Channel_2,
   PWM_32_64BitTimer3A_IndexArr
};/*************************************************/

GPIO_TimerConfigChannel_t Timer3B_32_64Bit={
   PortD,
   Channel_3,
   PWM_32_64BitTimer3B_IndexArr
};/*************************************************/

GPIO_TimerConfigChannel_t Timer4A_32_64Bit={
   PortD,
   Channel_4,
   PWM_32_64BitTimer4A_IndexArr
};/*************************************************/

GPIO_TimerConfigChannel_t Timer4B_32_64Bit={
  PortD,
  Channel_5,
  PWM_32_64BitTimer4B_IndexArr
};/*************************************************/

GPIO_TimerConfigChannel_t Timer5A_32_64Bit ={
   PortD,
   Channel_6,
   PWM_32_64BitTimer5A_IndexArr
};/*************************************************/

GPIO_TimerConfigChannel_t Timer5B_32_64Bit={
   PortD,
   Channel_7,
   PWM_32_64BitTimer5B_IndexArr
};/*************************************************/


/*==================================================*/
/*     Config for  AFSEL_UART                       */
/*==================================================*/
GPIO_UARTConfigChannel_t UART0_AFSELConfig={
PortA,
Channel_0,
Channel_1
};

GPIO_UARTConfigChannel_t UART1_AFSELConfig={
PortB,
Channel_0,
Channel_1
};


GPIO_UARTConfigChannel_t UART2_AFSELConfig={
PortD,
Channel_6,
Channel_7
};


GPIO_UARTConfigChannel_t UART3_AFSELConfig={
PortC,
Channel_6,
Channel_7
};


GPIO_UARTConfigChannel_t UART4_AFSELConfig={
PortC,
Channel_4,
Channel_5
};


GPIO_UARTConfigChannel_t UART5_AFSELConfig={
PortE,
Channel_4,
Channel_5
};


GPIO_UARTConfigChannel_t UART6_AFSELConfig={
PortD,
Channel_4,
Channel_5
};


GPIO_UARTConfigChannel_t UART7_AFSELConfig={
PortE,
Channel_0,
Channel_1
};

/********************GPIO*********************/

GPIO_ConfigurePin_t GPIO_ConfigurePin_PF4={
      PortF,
      Channel_4,
 };

 GPIO_ConfigurePin_t GPIO_ConfigurePin_PF2={
      PortF,
      Channel_2,
 };


 GPIO_ConfigurePin_t GPIO_ConfigurePin_PF1={
      PortF,
      Channel_1,
 };


 GPIO_ConfigurePin_t GPIO_ConfigurePin_PF0={
      PortF,
      Channel_0,
 };

 GPIO_ConfigurePin_t GPIO_ConfigurePin_PF3={
      PortF,
      Channel_3,
 };

/* =====================================================================================*/
/*                         ARRAY OF POINTERS TO STRUCT                                  */
/* =====================================================================================*/

GPIO_TimerConfigChannel_t * const GPIO_TimerAFSELConfig_ArrPtrStruct[12]={
      &Timer0A_32_64Bit,
      &Timer0B_32_64Bit,
      &Timer1A_32_64Bit,
      &Timer1B_32_64Bit,
      &Timer2A_32_64Bit,
      &Timer2B_32_64Bit,
      &Timer3A_32_64Bit,
      &Timer3B_32_64Bit,
      &Timer4A_32_64Bit,
      &Timer4B_32_64Bit,
      &Timer5A_32_64Bit,
      &Timer5B_32_64Bit,
};

GPIO_UARTConfigChannel_t * const GPIO_AFSELUARTConfig_ArrPtrStruct[8]={

 &UART0_AFSELConfig,
 &UART1_AFSELConfig,
 &UART2_AFSELConfig,
 &UART3_AFSELConfig,
 &UART4_AFSELConfig,
 &UART5_AFSELConfig,
 &UART6_AFSELConfig,
 &UART7_AFSELConfig
};
