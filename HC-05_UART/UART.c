/*************************************************************************************************************************************/
/* Name:   UART.c                                                                                                                    */
/* Author: Madonna Magdy                                                                                                             */
/* Version: V1                                                                                                                       */
/* Usage: This module contains the implementation for the UART functions                                                             */
/*************************************************************************************************************************************/

/************************************ Includes ************************************/

  /*************************************************************************************************************************************/
  /* Name:   UART.c                                                                                                                    */
  /* Author: Madonna Magdy                                                                                                             */
  /* Version: V1                                                                                                                       */
  /* Usage: This module contains the implementation for the UART functions                                                             */
  /*************************************************************************************************************************************/

  /************************************ Includes ************************************/
  #include "lstd.h"
  #include "UART.h"
  #include "UART_reg.h"
  #include "SystemControl.h"

  #include "NVIC.h"
  #include "GPIO.h"

  #include "GPTM.h"
  #include "GPTM_config.h"

 #include "DMA_reg.h"
  /************************************ Includes ************************************/
  extern unsigned char ui8ControlTable[1024];
  unsigned char volatile  UARTDMA_TxFlag=0;
  unsigned char volatile UARTDMA_RxFlag=0;

  /******************************************* ID Description of the Unit *********************************************************/
  // first number of ID signifies the module used (the UART  module takes number6, GPIO module takes number 3)

    //The Second number signifies that whether you are using a function or an array or a variable
   //(The variable takes number1 ,The array takes number 2, The function takes number 3  )

   //The Third number signifies the number of a function or an array or a variable

  /******************************************* ID Description of the Unit ********************************************************/


  /******************************  ID Description For Testing *********************************************************/

   //First part is the ID description of the Unit

   //The second part signifies how many number of tests you use on a certain variable or function (on a certain unit)

  /******************************  ID Description For Testing *********************************************************/

   /************************************** Macros for computing the baud rate register ****************************************************/
  /*it is not preferable to use float numbers in embedded systems for that
   *  reason the static inline  function is created  */

  static inline u32_t Get_DivFraction(u32_t ClockSourceValue, u32_t baudValue){

     u32_t SystemClkFreq;
     SystemClkFreq = SC_GetSystemClock();

      /*example --> (u32_t)(19.53) = 19*/
      u32_t UART_DIV =(u32_t)(SystemClkFreq/(16*baudValue));

      /*  (19.53)*(100)  */
      /*  (u32_t)(1953.125) = 1953 */
      u32_t UART_DIVMUL100 =(u32_t)((25*SystemClkFreq)/(4*baudValue));

      /* 19*100 = 1900 */
      u32_t UART_MAINTISSA_MUL100=(u32_t)(UART_DIV*100);

      /*1953-1900=53*/
      u32_t UART_DIVFRACTION=(u32_t)(UART_DIVMUL100-UART_MAINTISSA_MUL100);

      /* 53*64 + 0.5 */
      u32_t UART_FRACTION=   (u32_t)(UART_DIVFRACTION*64*0.001 + 0.5);

      return UART_FRACTION;

  }

  #define UART_DIV(PCLK,BAUD)      (u32_t)(PCLK/(16*BAUD)) /*example --> (u32_t)(19.53) =19 */
   u8_t UART_InterruptNum_Arr[8]={5,6,59,60,61,62,63};



  /************************  UNIT ID: 6.2.1 **********************************/
  /* UNIT ID: 6.2.1
   *
   * UNIT NAME: UART_Callback
   *
   * UNIT LOCATION: The array is stored in .data section
   * At Runtime it will be copied to Ram memory as the content of the array might be changed
   *
   * UNIT DESCRIPTION:
   * Array of pointers to functions
   * the index of the array represents the the port number
   * the content of the array represents pointer variable to function
   * static keyword is added because the function can not be called by the software the hardware will call it
   * volatile keyword is added because the value can be changed by hardware (disable optimization)
   * the pointer is of type CallbackFunc_t --> points to a function that returns void and takes void as an argument because
   * the call back function is not called by software so by logic no one will insert an argument
   * and the return type will be void because the user can not call it
   *
   * UNIT NOTE:
   * If you don't initialize UART_Callback[] with a null pointer
   * and you forgot to register the call back function there will
   * be segmentation fault because you are trying to access a wild pointer

   * The advantage of the if condition ---> (if(UART_Callback[] != NULL_PTR) )
   * you can't check on a garbage value but you can check on the null value
   * to see if the pointer to function (UART_Callback[]) doesn't hold the
   * address of a function or doesn't hold a value
   *
   */
     static volatile  CallbackFunc_t UART0_Callback[5]={NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR};/*******************************************************/
     static volatile  CallbackFunc_t UART1_Callback[5]={NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR};/*******************************************************/
     static volatile  CallbackFunc_t UART2_Callback[5]={NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR};/*******************************************************/
     static volatile  CallbackFunc_t UART3_Callback[5]={NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR};/*******************************************************/
     static volatile  CallbackFunc_t UART4_Callback[5]={NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR};/*******************************************************/
     static volatile  CallbackFunc_t UART5_Callback[5]={NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR};/*******************************************************/
     static volatile  CallbackFunc_t UART6_Callback[5]={NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR};/*******************************************************/
     static volatile  CallbackFunc_t UART7_Callback[5]={NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR};/*******************************************************/


     /**************************************************************************************************************/
    /*UNIT ID : 6.2.2*/

    /*UNIT Name:UART_DataRegisters */

    /*UNIT LOCATION: ro-data section in ROM*/

    /*UNIT DESCRIPTION:*/
    /* creating an array of pointers to registers
     * the user (or the application layer) will not be allowed to have access to the hardware registers
     * because it's not his/her concern
     * he/she will only be allowed to call the interfacing functions in the UART.h file
     * for that reason a keyword static will be added
     *
     * A constant keyword is added because the location of the register never changes
     * so for safety no one can change the location of the pointer the only value that can be changed is the value INSIDE
     * the register ---> the value that the pointer is pointing to
     *
     *A volatile keyword is added to disable the optimization inorder to prevent cashing process
     *as the value may be changed by hardware or by using the DMA
     */
     volatile static UARTDR_Reg  *const UART_DataRegisters[8]={
      (UARTDR_Reg*)UART0_Data_Reg,
      (UARTDR_Reg*)UART1_Data_Reg,
      (UARTDR_Reg*)UART2_Data_Reg,
      (UARTDR_Reg*)UART3_Data_Reg,
      (UARTDR_Reg*)UART4_Data_Reg,
      (UARTDR_Reg*)UART5_Data_Reg,
      (UARTDR_Reg*)UART6_Data_Reg,
      (UARTDR_Reg*)UART7_Data_Reg
   }; /**************************************************************************************************************/




    /**************************************************************************************************************/
     /*UNIT ID : 6.2.3*/

    /*UNIT Name:UART_FlagRegisters */

    /*UNIT LOCATION: ro-data section in ROM*/

    /*UNIT DESCRIPTION:*/
    /* creating an array of pointers to registers
     * the user (or the application layer) will not be allowed to have access to the hardware registers
     * because it's not his/her concern
     * he/she will only be allowed to call the interfacing functions in the UART.h file
     * for that reason a keyword static will be added
     *
     * A constant keyword is added because the location of the register never changes
     * so for safety no one can change the location of the pointer the only value that can be changed is the value INSIDE
     * the register ---> the value that the pointer is pointing to
     *
     *A volatile keyword is added to disable the optimization inorder to prevent cashing process
     *as the value may be changed by hardware or by using the DMA
     */
   volatile  UARTFR_Reg  *const UART_FlagRegisters[8]={
      (UARTFR_Reg*)UART0_Flag_Reg,
      (UARTFR_Reg*)UART1_Flag_Reg,
      (UARTFR_Reg*)UART2_Flag_Reg,
      (UARTFR_Reg*)UART3_Flag_Reg,
      (UARTFR_Reg*)UART4_Flag_Reg,
      (UARTFR_Reg*)UART5_Flag_Reg,
      (UARTFR_Reg*)UART6_Flag_Reg,
      (UARTFR_Reg*)UART7_Flag_Reg
   }; /**************************************************************************************************************/





    /**************************************************************************************************************/
     /*UNIT ID : 6.2.4*/

    /*UNIT Name:UART_InterruptClearRegisters */

    /*UNIT LOCATION: ro-data section in ROM*/

    /*UNIT DESCRIPTION:*/
    /* creating an array of pointers to registers
     * the user (or the application layer) will not be allowed to have access to the hardware registers
     * because it's not his/her concern
     * he/she will only be allowed to call the interfacing functions in the UART.h file
     * for that reason a keyword static will be added
     *
     * A constant keyword is added because the location of the register never changes
     * so for safety no one can change the location of the pointer the only value that can be changed is the value INSIDE
     * the register ---> the value that the pointer is pointing to
     *
     *A volatile keyword is added to disable the optimization inorder to prevent cashing process
     *as the value may be changed by hardware or by using the DMA
     */
   volatile  UARTICR_Reg  *const UART_InterruptClearRegisters[8]={
      (UARTICR_Reg*)UART0_InterruptClear_Reg,
      (UARTICR_Reg*)UART1_InterruptClear_Reg,
      (UARTICR_Reg*)UART2_InterruptClear_Reg,
      (UARTICR_Reg*)UART3_InterruptClear_Reg,
      (UARTICR_Reg*)UART4_InterruptClear_Reg,
      (UARTICR_Reg*)UART5_InterruptClear_Reg,
      (UARTICR_Reg*)UART6_InterruptClear_Reg,
      (UARTICR_Reg*)UART7_InterruptClear_Reg
   }; /**************************************************************************************************************/




    /**************************************************************************************************************/
     /*UNIT ID : 6.2.5*/

    /*UNIT Name:UART_IntegerBaudRateDivisor */

    /*UNIT LOCATION: ro-data section in ROM*/

    /*UNIT DESCRIPTION:*/
    /* creating an array of pointers to registers
     * the user (or the application layer) will not be allowed to have access to the hardware registers
     * because it's not his/her concern
     * he/she will only be allowed to call the interfacing functions in the UART.h file
     * for that reason a keyword static will be added
     *
     * A constant keyword is added because the location of the register never changes
     * so for safety no one can change the location of the pointer the only value that can be changed is the value INSIDE
     * the register ---> the value that the pointer is pointing to
     *
     *A volatile keyword is added to disable the optimization inorder to prevent cashing process
     *as the value may be changed by hardware or by using the DMA
     */
   volatile static UARTIBRD_Reg  *const UART_IntegerBaudRateDivisorRegisters[8]={
      (UARTIBRD_Reg*)UART0_IntegerBaudRateDivisor,
      (UARTIBRD_Reg*)UART1_IntegerBaudRateDivisor,
      (UARTIBRD_Reg*)UART2_IntegerBaudRateDivisor,
      (UARTIBRD_Reg*)UART3_IntegerBaudRateDivisor,
      (UARTIBRD_Reg*)UART4_IntegerBaudRateDivisor,
      (UARTIBRD_Reg*)UART5_IntegerBaudRateDivisor,
      (UARTIBRD_Reg*)UART6_IntegerBaudRateDivisor,
      (UARTIBRD_Reg*)UART7_IntegerBaudRateDivisor
   }; /**************************************************************************************************************/




    /**************************************************************************************************************/
     /*UNIT ID : 6.2.6*/

    /*UNIT Name:UART_FractionalBaudRateDivisor */

    /*UNIT LOCATION: ro-data section in ROM*/

    /*UNIT DESCRIPTION:*/
    /* creating an array of pointers to registers
     * the user (or the application layer) will not be allowed to have access to the hardware registers
     * because it's not his/her concern
     * he/she will only be allowed to call the interfacing functions in the UART.h file
     * for that reason a keyword static will be added
     *
     * A constant keyword is added because the location of the register never changes
     * so for safety no one can change the location of the pointer the only value that can be changed is the value INSIDE
     * the register ---> the value that the pointer is pointing to
     *
     *A volatile keyword is added to disable the optimization inorder to prevent cashing process
     *as the value may be changed by hardware or by using the DMA
     */
   volatile static UARTFBRD_Reg  *const UART_FractionalBaudRateDivisorRegisters[8]={
      (UARTFBRD_Reg*)UART0_FractionalBaudRateDivisor,
      (UARTFBRD_Reg*)UART1_FractionalBaudRateDivisor,
      (UARTFBRD_Reg*)UART2_FractionalBaudRateDivisor,
      (UARTFBRD_Reg*)UART3_FractionalBaudRateDivisor,
      (UARTFBRD_Reg*)UART4_FractionalBaudRateDivisor,
      (UARTFBRD_Reg*)UART5_FractionalBaudRateDivisor,
      (UARTFBRD_Reg*)UART6_FractionalBaudRateDivisor,
      (UARTFBRD_Reg*)UART7_FractionalBaudRateDivisor
   }; /**************************************************************************************************************/




    /**************************************************************************************************************/
     /*UNIT ID : 6.2.7*/

    /*UNIT Name:UART_ClockConfigurationRegisters */

    /*UNIT LOCATION: ro-data section in ROM*/

    /*UNIT DESCRIPTION:*/
    /* creating an array of pointers to registers
     * the user (or the application layer) will not be allowed to have access to the hardware registers
     * because it's not his/her concern
     * he/she will only be allowed to call the interfacing functions in the UART.h file
     * for that reason a keyword static will be added
     *
     * A constant keyword is added because the location of the register never changes
     * so for safety no one can change the location of the pointer the only value that can be changed is the value INSIDE
     * the register ---> the value that the pointer is pointing to
     *
     *A volatile keyword is added to disable the optimization inorder to prevent cashing process
     *as the value may be changed by hardware or by using the DMA
     */
   volatile static UARTCC_Reg  *const UART_ClockConfigurationRegisters[8]={
      (UARTCC_Reg*)UART0_ClockConfiguration,
      (UARTCC_Reg*)UART1_ClockConfiguration,
      (UARTCC_Reg*)UART2_ClockConfiguration,
      (UARTCC_Reg*)UART3_ClockConfiguration,
      (UARTCC_Reg*)UART4_ClockConfiguration,
      (UARTCC_Reg*)UART5_ClockConfiguration,
      (UARTCC_Reg*)UART6_ClockConfiguration,
      (UARTCC_Reg*)UART7_ClockConfiguration
   }; /**************************************************************************************************************/

    /**************************************************************************************************************/
     /*UNIT ID : 6.2.9*/

    /*UNIT Name:UART_ControlRegisters */

    /*UNIT LOCATION: ro-data section in ROM*/

    /*UNIT DESCRIPTION:*/
    /* creating an array of pointers to registers
     * the user (or the application layer) will not be allowed to have access to the hardware registers
     * because it's not his/her concern
     * he/she will only be allowed to call the interfacing functions in the UART.h file
     * for that reason a keyword static will be added
     *
     * A constant keyword is added because the location of the register never changes
     * so for safety no one can change the location of the pointer the only value that can be changed is the value INSIDE
     * the register ---> the value that the pointer is pointing to
     *
     *A volatile keyword is added to disable the optimization inorder to prevent cashing process
     *as the value may be changed by hardware or by using the DMA
     */
   volatile static UARTCTL_Reg  *const UART_ControlRegisters[8]={
      (UARTCTL_Reg*)UART0_Control_Reg,
      (UARTCTL_Reg*)UART1_Control_Reg,
      (UARTCTL_Reg*)UART2_Control_Reg,
      (UARTCTL_Reg*)UART3_Control_Reg,
      (UARTCTL_Reg*)UART4_Control_Reg,
      (UARTCTL_Reg*)UART5_Control_Reg,
      (UARTCTL_Reg*)UART6_Control_Reg,
      (UARTCTL_Reg*)UART7_Control_Reg
   }; /**************************************************************************************************************/


    /**************************************************************************************************************/
     /*UNIT ID : 6.2.10*/

    /*UNIT Name:UART_LineControlRegisters */

    /*UNIT LOCATION: ro-data section in ROM*/

    /*UNIT DESCRIPTION:*/
    /* creating an array of pointers to registers
     * the user (or the application layer) will not be allowed to have access to the hardware registers
     * because it's not his/her concern
     * he/she will only be allowed to call the interfacing functions in the UART.h file
     * for that reason a keyword static will be added
     *
     * A constant keyword is added because the location of the register never changes
     * so for safety no one can change the location of the pointer the only value that can be changed is the value INSIDE
     * the register ---> the value that the pointer is pointing to
     *
     *A volatile keyword is added to disable the optimization inorder to prevent cashing process
     *as the value may be changed by hardware or by using the DMA
     */
   volatile static UARTLCRH_Reg *const UART_LineControlRegisters[8]={
      (UARTLCRH_Reg*)UART0_LineControl_Reg,
      (UARTLCRH_Reg*)UART1_LineControl_Reg,
      (UARTLCRH_Reg*)UART2_LineControl_Reg,
      (UARTLCRH_Reg*)UART3_LineControl_Reg,
      (UARTLCRH_Reg*)UART4_LineControl_Reg,
      (UARTLCRH_Reg*)UART5_LineControl_Reg,
      (UARTLCRH_Reg*)UART6_LineControl_Reg,
      (UARTLCRH_Reg*)UART7_LineControl_Reg
   }; /**************************************************************************************************************/



    /**************************************************************************************************************/
     /*UNIT ID : 6.2.11*/

    /*UNIT Name:UART_InterruptClearRegisters */

    /*UNIT LOCATION: ro-data section in ROM*/

    /*UNIT DESCRIPTION:*/
    /* creating an array of pointers to registers
     * the user (or the application layer) will not be allowed to have access to the hardware registers
     * because it's not his/her concern
     * he/she will only be allowed to call the interfacing functions in the UART.h file
     * for that reason a keyword static will be added
     *
     * A constant keyword is added because the location of the register never changes
     * so for safety no one can change the location of the pointer the only value that can be changed is the value INSIDE
     * the register ---> the value that the pointer is pointing to
     *
     *A volatile keyword is added to disable the optimization inorder to prevent cashing process
     *as the value may be changed by hardware or by using the DMA
     */
   volatile static UARTIM_Reg  *const UART_InterruptMaskRegisters[8]={
      (UARTIM_Reg*)UART0_InterruptMask_Reg,
      (UARTIM_Reg*)UART1_InterruptMask_Reg,
      (UARTIM_Reg*)UART2_InterruptMask_Reg,
      (UARTIM_Reg*)UART3_InterruptMask_Reg,
      (UARTIM_Reg*)UART4_InterruptMask_Reg,
      (UARTIM_Reg*)UART5_InterruptMask_Reg,
      (UARTIM_Reg*)UART6_InterruptMask_Reg,
      (UARTIM_Reg*)UART7_InterruptMask_Reg
   }; /**************************************************************************************************************/


   /**************************************************************************************************************/
    /*UNIT ID : 6.2.12*/

   /*UNIT Name:UART_InterruptClearRegisters */

   /*UNIT LOCATION: ro-data section in ROM*/

   /*UNIT DESCRIPTION:*/
   /* creating an array of pointers to registers
    * the user (or the application layer) will not be allowed to have access to the hardware registers
    * because it's not his/her concern
    * he/she will only be allowed to call the interfacing functions in the UART.h file
    * for that reason a keyword static will be added
    *
    * A constant keyword is added because the location of the register never changes
    * so for safety no one can change the location of the pointer the only value that can be changed is the value INSIDE
    * the register ---> the value that the pointer is pointing to
    *
    *A volatile keyword is added to disable the optimization inorder to prevent cashing process
    *as the value may be changed by hardware or by using the DMA
    */
  volatile static UARTMIS_Reg  *const UART_MaskedInterruptStatusRegisters[8]={
     (UARTMIS_Reg*)UART0_MaskedInterruptStatus_Reg,
     (UARTMIS_Reg*)UART1_MaskedInterruptStatus_Reg,
     (UARTMIS_Reg*)UART2_MaskedInterruptStatus_Reg,
     (UARTMIS_Reg*)UART3_MaskedInterruptStatus_Reg,
     (UARTMIS_Reg*)UART4_MaskedInterruptStatus_Reg,
     (UARTMIS_Reg*)UART5_MaskedInterruptStatus_Reg,
     (UARTMIS_Reg*)UART6_MaskedInterruptStatus_Reg,
     (UARTMIS_Reg*)UART7_MaskedInterruptStatus_Reg
  }; /**************************************************************************************************************/

  volatile static UARTDMACTL* const UART_DMAControlRegisters[8]={

      UART0_DMAControl_Reg,
      UART1_DMAControl_Reg,
      UART2_DMAControl_Reg,
      UART3_DMAControl_Reg,
      UART4_DMAControl_Reg,
      UART5_DMAControl_Reg,
      UART6_DMAControl_Reg,
      UART7_DMAControl_Reg,
  };

volatile static UARTIFLS_Reg* const UART_InterruptFIFOLevelSelect[8]={

     UART0_UARTIFLS_Reg,
     UART1_UARTIFLS_Reg,
     UART2_UARTIFLS_Reg,
     UART3_UARTIFLS_Reg,
     UART4_UARTIFLS_Reg,
     UART5_UARTIFLS_Reg,
     UART6_UARTIFLS_Reg,
     UART7_UARTIFLS_Reg

};

  /************************  UNIT ID: 6.3.1 **********************************/
   /* UNIT ID: 6.3.1
    *
    * UNIT NAME:UART0_IntHandler
    *
    * UNIT LOCATION: FLASH
    * we can not write on the FLASH memory at runtime that's why we add a call back function in the implementation
    * as we CAN NOT change the implementation of the function itself but we can SOLVE that problem by
    * adding a pointer to function. Hence, we can let the pointer point to any function we want in the runtime
    * without changing the implementation of the function itself at the runtime
    *
    * UNIT DESCRIPTION: Interrupt service routine that will be called by hardware under certain conditions
    * These conditions are
    * 1-the interrupt mask of that module is enabled --> Done by the Developer through the UNIT ID
    * 2-the NVIC is enabled for that module --> Done by the Developer through the UNIT ID
    * 3- the global interrupt is enabled --> Done by the Developer
    * 4- Register the callback function pointer ---> Done by the Developer
    * 5- Rising the flag of that module under certain condition --> Done by Hardware
    *
    * That Function related to the UART interrupt of channel0
    * */
    UART0_IntHandler(){

        enum UART_IRQ_Event flag;

     //recieve data register contains data that need to be read
     if ( 1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel0]).bits.ReceiveMaskedInterruptStatus ){

         flag =UART_IRQ_RXNE;
     }

     //transmit data register will be empty
     else if(1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel0]).bits.TransmitMaskedInterruptStatus){
         flag=UART_IRQ_TXNF;
     }


     else if( 1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel0]).bits.OverrunErrorMaskedInterruptStatus ){
         flag=UART_IRQ_ORE;
     }

     else if(1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel0]).bits.ParityErrorMaskedInterruptStatus){
         flag=UART_IRQ_PE;
     }

     else if(1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel0]).bits.FramingErrorMaskedInterruptStatus){
         flag=UART_IRQ_FE;
     }


     if (UART0_Callback[flag] != NULL_PTR){

         (*UART0_Callback[flag])();

     }

  }


  /************************  UNIT ID: 6.3.2 **********************************/
   /* UNIT ID: 6.3.2
    *
    * UNIT NAME:EXTIAIntDefaultHandler
    *
    * UNIT LOCATION: FLASH
    * we can not write on the FLASH memory at runtime that's why we add a call back function in the implementation
    * as we CAN NOT change the implementation of the function itself but we can SOLVE that problem by
    * adding a pointer to function. Hence, we can let the pointer point to any function we want in the runtime
    * without changing the implementation of the function itself at the runtime
    *
    * UNIT DESCRIPTION: Interrupt service routine that will be called by hardware under certain conditions
    * These conditions are
    * 1-the interrupt mask of that module is enabled --> Done by the Developer through the UNIT ID
    * 2-the NVIC is enabled for that module --> Done by the Developer through the UNIT ID
    * 3- the global interrupt is enabled --> Done by the Developer
    * 4- Register the callback function pointer ---> Done by the Developer
    * 5- Rising the flag of that module under certain condition --> Done by Hardware
    *
    * That Function related to the UART interrupt of channel1
    * */
    UART1_IntHandler(){

        enum UART_IRQ_Event flag;

     //recieve data register contains data that need to be read
     if ( 1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel1]).bits.ReceiveMaskedInterruptStatus ){

         flag =UART_IRQ_RXNE;
     }

     //transmit data register will be empty
     else if(1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel1]).bits.TransmitMaskedInterruptStatus){
         flag=UART_IRQ_TXNF;
     }


     else if( 1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel1]).bits.OverrunErrorMaskedInterruptStatus ){
         flag=UART_IRQ_ORE;
     }

     else if(1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel1]).bits.ParityErrorMaskedInterruptStatus){
         flag=UART_IRQ_PE;
     }

     else if(1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel1]).bits.FramingErrorMaskedInterruptStatus){
         flag=UART_IRQ_FE;
     }


     if (UART1_Callback[flag] != NULL_PTR){

         (*UART1_Callback[flag])();

     }



  }

  /************************  UNIT ID: 6.3.3 **********************************/
   /* UNIT ID: 6.3.3
    *
    * UNIT NAME:EXTIAIntDefaultHandler
    *
    * UNIT LOCATION: FLASH
    * we can not write on the FLASH memory at runtime that's why we add a call back function in the implementation
    * as we CAN NOT change the implementation of the function itself but we can SOLVE that problem by
    * adding a pointer to function. Hence, we can let the pointer point to any function we want in the runtime
    * without changing the implementation of the function itself at the runtime
    *
    * UNIT DESCRIPTION: Interrupt service routine that will be called by hardware under certain conditions
    * These conditions are
    * 1-the interrupt mask of that module is enabled --> Done by the Developer through the UNIT ID
    * 2-the NVIC is enabled for that module --> Done by the Developer through the UNIT ID
    * 3- the global interrupt is enabled --> Done by the Developer
    * 4- Register the callback function pointer ---> Done by the Developer
    * 5- Rising the flag of that module under certain condition --> Done by Hardware
    *
    * That Function related to the UART interrupt of channel2
    * */
    UART2_IntHandler(){

        enum UART_IRQ_Event flag;

     //recieve data register contains data that need to be read
     if ( 1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel2]).bits.ReceiveMaskedInterruptStatus ){

         flag =UART_IRQ_RXNE;
     }

     //transmit data register will be empty
     else if(1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel2]).bits.TransmitMaskedInterruptStatus){
         flag=UART_IRQ_TXNF;
     }


     else if( 1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel2]).bits.OverrunErrorMaskedInterruptStatus ){
         flag=UART_IRQ_ORE;
     }

     else if(1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel2]).bits.ParityErrorMaskedInterruptStatus){
         flag=UART_IRQ_PE;
     }

     else if(1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel2]).bits.FramingErrorMaskedInterruptStatus){
         flag=UART_IRQ_FE;
     }


     if (UART2_Callback[flag] != NULL_PTR){

         (*UART2_Callback[flag])();

     }



  }


  /************************  UNIT ID: 6.3.4 **********************************/
   /* UNIT ID: 6.3.4
    *
    * UNIT NAME:EXTIAIntDefaultHandler
    *
    * UNIT LOCATION: FLASH
    * we can not write on the FLASH memory at runtime that's why we add a call back function in the implementation
    * as we CAN NOT change the implementation of the function itself but we can SOLVE that problem by
    * adding a pointer to function. Hence, we can let the pointer point to any function we want in the runtime
    * without changing the implementation of the function itself at the runtime
    *
    * UNIT DESCRIPTION: Interrupt service routine that will be called by hardware under certain conditions
    * These conditions are
    * 1-the interrupt mask of that module is enabled --> Done by the Developer through the UNIT ID
    * 2-the NVIC is enabled for that module --> Done by the Developer through the UNIT ID
    * 3- the global interrupt is enabled --> Done by the Developer
    * 4- Register the callback function pointer ---> Done by the Developer
    * 5- Rising the flag of that module under certain condition --> Done by Hardware
    *
    * That Function related to the UART interrupt of channel3
    * */
    UART3_IntHandler(){

        enum UART_IRQ_Event flag;

     //recieve data register contains data that need to be read
     if ( 1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel3]).bits.ReceiveMaskedInterruptStatus ){

         flag =UART_IRQ_RXNE;
     }

     //transmit data register will be empty
     else if(1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel3]).bits.TransmitMaskedInterruptStatus){
         flag=UART_IRQ_TXNF;
     }


     else if( 1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel3]).bits.OverrunErrorMaskedInterruptStatus ){
         flag=UART_IRQ_ORE;
     }

     else if(1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel3]).bits.ParityErrorMaskedInterruptStatus){
         flag=UART_IRQ_PE;
     }

     else if(1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel3]).bits.FramingErrorMaskedInterruptStatus){
         flag=UART_IRQ_FE;
     }


     if (UART3_Callback[flag] != NULL_PTR){

         (*UART3_Callback[flag])();

     }


  }


  /************************  UNIT ID: 6.3.5 **********************************/
   /* UNIT ID: 6.3.5
    *
    * UNIT NAME:EXTIAIntDefaultHandler
    *
    * UNIT LOCATION: FLASH
    * we can not write on the FLASH memory at runtime that's why we add a call back function in the implementation
    * as we CAN NOT change the implementation of the function itself but we can SOLVE that problem by
    * adding a pointer to function. Hence, we can let the pointer point to any function we want in the runtime
    * without changing the implementation of the function itself at the runtime
    *
    * UNIT DESCRIPTION: Interrupt service routine that will be called by hardware under certain conditions
    * These conditions are
    * 1-the interrupt mask of that module is enabled --> Done by the Developer through the UNIT ID
    * 2-the NVIC is enabled for that module --> Done by the Developer through the UNIT ID
    * 3- the global interrupt is enabled --> Done by the Developer
    * 4- Register the callback function pointer ---> Done by the Developer
    * 5- Rising the flag of that module under certain condition --> Done by Hardware
    *
    * That Function related to the UART interrupt of channel4
    * */
    UART4_IntHandler(){

        enum UART_IRQ_Event flag;

     //recieve data register contains data that need to be read
     if ( 1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel4]).bits.ReceiveMaskedInterruptStatus ){

         flag =UART_IRQ_RXNE;
     }

     //transmit data register will be empty
     else if(1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel4]).bits.TransmitMaskedInterruptStatus){
         flag=UART_IRQ_TXNF;
     }


     else if( 1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel4]).bits.OverrunErrorMaskedInterruptStatus ){
         flag=UART_IRQ_ORE;
     }

     else if(1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel4]).bits.ParityErrorMaskedInterruptStatus){
         flag=UART_IRQ_PE;
     }

     else if(1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel4]).bits.FramingErrorMaskedInterruptStatus){
         flag=UART_IRQ_FE;
     }


     if (UART4_Callback[flag] != NULL_PTR){

         (*UART4_Callback[flag])();

     }



  }


  /************************  UNIT ID: 6.3.6 **********************************/
   /* UNIT ID: 6.3.6
    *
    * UNIT NAME:EXTIAIntDefaultHandler
    *
    * UNIT LOCATION: FLASH
    * we can not write on the FLASH memory at runtime that's why we add a call back function in the implementation
    * as we CAN NOT change the implementation of the function itself but we can SOLVE that problem by
    * adding a pointer to function. Hence, we can let the pointer point to any function we want in the runtime
    * without changing the implementation of the function itself at the runtime
    *
    * UNIT DESCRIPTION: Interrupt service routine that will be called by hardware under certain conditions
    * These conditions are
    * 1-the interrupt mask of that module is enabled --> Done by the Developer through the UNIT ID
    * 2-the NVIC is enabled for that module --> Done by the Developer through the UNIT ID
    * 3- the global interrupt is enabled --> Done by the Developer
    * 4- Register the callback function pointer ---> Done by the Developer
    * 5- Rising the flag of that module under certain condition --> Done by Hardware
    *
    * That Function related to the UART interrupt of channel5
    * */
    UART5_IntHandler(){

        enum UART_IRQ_Event flag;

     //recieve data register contains data that need to be read
     if ( 1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel5]).bits.ReceiveMaskedInterruptStatus ){

         flag =UART_IRQ_RXNE;
     }

     //transmit data register will be empty
     else if(1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel5]).bits.TransmitMaskedInterruptStatus){
         flag=UART_IRQ_TXNF;
     }


     else if( 1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel5]).bits.OverrunErrorMaskedInterruptStatus ){
         flag=UART_IRQ_ORE;
     }

     else if(1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel5]).bits.ParityErrorMaskedInterruptStatus){
         flag=UART_IRQ_PE;
     }

     else if(1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel5]).bits.FramingErrorMaskedInterruptStatus){
         flag=UART_IRQ_FE;
     }

    ///static volatile  CallbackFunc_t UART1_Callback[5]={NULL_PTR};

     if (UART5_Callback[flag] != NULL_PTR){

         (*UART5_Callback[flag])();

     }

  }


  /************************  UNIT ID: 6.3.7 **********************************/
   /* UNIT ID: 6.3.7
    *
    * UNIT NAME:EXTIAIntDefaultHandler
    *
    * UNIT LOCATION: FLASH
    * we can not write on the FLASH memory at runtime that's why we add a call back function in the implementation
    * as we CAN NOT change the implementation of the function itself but we can SOLVE that problem by
    * adding a pointer to function. Hence, we can let the pointer point to any function we want in the runtime
    * without changing the implementation of the function itself at the runtime
    *
    * UNIT DESCRIPTION: Interrupt service routine that will be called by hardware under certain conditions
    * These conditions are
    * 1-the interrupt mask of that module is enabled --> Done by the Developer through the UNIT ID
    * 2-the NVIC is enabled for that module --> Done by the Developer through the UNIT ID
    * 3- the global interrupt is enabled --> Done by the Developer
    * 4- Register the callback function pointer ---> Done by the Developer
    * 5- Rising the flag of that module under certain condition --> Done by Hardware
    *
    * That Function related to the UART interrupt of channel6
    * */
    UART6_IntHandler(){
        enum UART_IRQ_Event flag;

     //recieve data register contains data that need to be read
     if ( 1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel6]).bits.ReceiveMaskedInterruptStatus ){

         flag =UART_IRQ_RXNE;
     }

     //transmit data register will be empty
     else if(1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel6]).bits.TransmitMaskedInterruptStatus){
         flag=UART_IRQ_TXNF;
     }


     else if( 1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel6]).bits.OverrunErrorMaskedInterruptStatus ){
         flag=UART_IRQ_ORE;
     }

     else if(1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel6]).bits.ParityErrorMaskedInterruptStatus){
         flag=UART_IRQ_PE;
     }

     else if(1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel6]).bits.FramingErrorMaskedInterruptStatus){
         flag=UART_IRQ_FE;
     }

    ///static volatile  CallbackFunc_t UART1_Callback[5]={NULL_PTR};

     if (UART6_Callback[flag] != NULL_PTR){

         (*UART6_Callback[flag])();

     }


  }


    /************************  UNIT ID: 6.3.7 **********************************/
     /* UNIT ID: 6.3.7
      *
      * UNIT NAME:EXTIAIntDefaultHandler
      *
      * UNIT LOCATION: FLASH
      * we can not write on the FLASH memory at runtime that's why we add a call back function in the implementation
      * as we CAN NOT change the implementation of the function itself but we can SOLVE that problem by
      * adding a pointer to function. Hence, we can let the pointer point to any function we want in the runtime
      * without changing the implementation of the function itself at the runtime
      *
      * UNIT DESCRIPTION: Interrupt service routine that will be called by hardware under certain conditions
      * These conditions are
      * 1-the interrupt mask of that module is enabled --> Done by the Developer through the UNIT ID
      * 2-the NVIC is enabled for that module --> Done by the Developer through the UNIT ID
      * 3- the global interrupt is enabled --> Done by the Developer
      * 4- Register the callback function pointer ---> Done by the Developer
      * 5- Rising the flag of that module under certain condition --> Done by Hardware
      *
      * That Function related to the UART interrupt of channel7
      * */
      UART7_IntHandler(){
          enum UART_IRQ_Event flag;

       //recieve data register contains data that need to be read
       if ( 1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel7]).bits.ReceiveMaskedInterruptStatus ){

           flag =UART_IRQ_RXNE;
       }

       //transmit data register will be empty
       else if(1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel7]).bits.TransmitMaskedInterruptStatus){
           flag=UART_IRQ_TXNF;
       }


       else if( 1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel7]).bits.OverrunErrorMaskedInterruptStatus ){
           flag=UART_IRQ_ORE;
       }

       else if(1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel7]).bits.ParityErrorMaskedInterruptStatus){
           flag=UART_IRQ_PE;
       }

       else if(1 == (*UART_MaskedInterruptStatusRegisters[UART_Channel7]).bits.FramingErrorMaskedInterruptStatus){
           flag=UART_IRQ_FE;
       }

      ///static volatile  CallbackFunc_t UART1_Callback[5]={NULL_PTR};

       if (UART7_Callback[flag] != NULL_PTR){

           (*UART7_Callback[flag])();

       }

     }

   /************************  UNIT ID: 6.3.9 **********************************/
    /* UNIT ID: 6.3.9
     *
     * UNIT NAME:UART_Initialization
     *
     * UNIT LOCATION: FLASH
     *
     * UNIT DESCRIPTION:
     * the function is responsible for initializing the UART Peripheral according to
     * the configuration structure defined in UART_config.c
     *
     * INPUT: pointer (of type UART_Config_t) which points to the configuration structure
     *
     * PRE-CONDITION:
     * the struct of type UART_Config_t in UART_config.c must be configured
     *
     *POST-CONDITION:
     *1- Integer Baud Rate Divisor Register will be configured
     *2- Fractional Baud Rate Divisor Register will be configured
     *3- The LineControl Registers will be configured
     *4- The UART Peripheral will be enabled
     *
     * */

  void UART_Initialization(UART_Config_t* pt_Config, GPIO_UARTConfigChannel_t* pt_UARTConfigChannel){


      /********************************************STEP1**************************************************/
      //Enable the UART module
      (SYSCTL_UARTRunModeClockGatingControl_Reg).bits.UARTModule_RunModeClockGatingControl |=( 1<<(pt_Config->Channel) );

      /********************************************STEP2 and STEP3 and STEP4**************************************************/
      //STEP 2 ---> Enable the clock to the appropriate GPIO module via the RCGCGPIO register
      //STEP 3 ---> Set the GPIO AFSEL bits for the appropriate pins
      //STEP 4 ---> Configure the PMCn fields in the GPIOPCTL register to assign the UART signals to the appropriate pins
      //STEP 5 ---> Enable digital function

      GPIO_EnableAFSEL_UART(pt_UARTConfigChannel);


      /********************************************STEP5**************************************************/
      (*UART_ControlRegisters[pt_Config->Channel]).bits.UARTEnable=0;


      /********************************************STEP6**************************************************/
      //(*UART_IntegerBaudRateDivisorRegisters[pt_Config->Channel]).bits.IntegerBaudRateDivisor=UART_DIV(pt_Config->pclk ,pt_Config->baud);
      //(*UART_FractionalBaudRateDivisorRegisters[pt_Config->Channel]).bits.FractionalBaudRateDivisor=Get_DivFraction(pt_Config->pclk, pt_Config->baud);
      //(*UART_IntegerBaudRateDivisorRegisters[pt_Config->Channel]).bits.IntegerBaudRateDivisor=104;
      //(*UART_FractionalBaudRateDivisorRegisters[pt_Config->Channel]).bits.FractionalBaudRateDivisor=11;

      /*16M/(16*115,200) = 8.680555556
       *BRD=8
       *UARTFBRD= (0.680555556*64+ 0.5)= 44.05555556 =44= 0x2C */
      (*UART_IntegerBaudRateDivisorRegisters[pt_Config->Channel]).bits.IntegerBaudRateDivisor=8;
      (*UART_FractionalBaudRateDivisorRegisters[pt_Config->Channel]).bits.FractionalBaudRateDivisor=0x2C;

      /*1M/(16*115,200) = 0.5425347222
       *BRD=8
       *UARTFBRD= (0.5425347222*64+ 0.5)= 35.222222222 =35= 0x23 */
      //(*UART_IntegerBaudRateDivisorRegisters[pt_Config->Channel]).bits.IntegerBaudRateDivisor=0;
      //(*UART_FractionalBaudRateDivisorRegisters[pt_Config->Channel]).bits.FractionalBaudRateDivisor=0x23;

      /*2M/(16*115,200) = 1.085069444
       *BRD=1
       *UARTFBRD= (0.085069444*64+ 0.5)= 5.9444444444 =5= 0x5 */
     // (*UART_IntegerBaudRateDivisorRegisters[pt_Config->Channel]).bits.IntegerBaudRateDivisor=1;
      //(*UART_FractionalBaudRateDivisorRegisters[pt_Config->Channel]).bits.FractionalBaudRateDivisor=0x5;


      /*16M/(16*128,000) = 7.8125
       *BRD=7
       *UARTFBRD= (0.8125*64+ 0.5)= 52.6728 =52= 0x34 */
      //(*UART_IntegerBaudRateDivisorRegisters[pt_Config->Channel]).bits.IntegerBaudRateDivisor=7;
      //(*UART_FractionalBaudRateDivisorRegisters[pt_Config->Channel]).bits.FractionalBaudRateDivisor=0x34;


    /********************************************STEP7**************************************************/
       (*UART_LineControlRegisters[pt_Config->Channel]).bits.WordLength = pt_Config->WordLenght;
       //(*UART_LineControlRegisters[pt_Config->Channel]).bits.EnableFIFOs=0;

       /*For the transmit channel, a single transfer request is
         asserted whenever there is at least one empty location in the transmit FIFO.*/
       (*UART_LineControlRegisters[pt_Config->Channel]).bits.EnableFIFOs=1;
       (*UART_LineControlRegisters[pt_Config->Channel]).bits.ParityEnable=0;

      /********************************************STEP8**************************************************/
       (*UART_ClockConfigurationRegisters[pt_Config->Channel]).bits.BaudClockSource= pt_Config->Clocksource;

       /********************************************STEP9**************************************************/
       //UART_InterruptFIFOLevelSelect[pt_Config->Channel]->bits.TXIFLSEL=_1_DIV_8_Empty;
      (*UART_ControlRegisters[pt_Config->Channel]).bits.UARTEnable=1;

  }


  /************************  UNIT ID: 6.3.10 **********************************/
   /* UNIT ID: 6.3.10
    *
    * UNIT NAME: UART_ConfigureInterruptSource
    *
    * UNIT LOCATION: FLASH
    *
    * UNIT DESCRIPTION: law 2falt el interrupt source ba3dd keda 3ayza 2fta7  tany leh 23od 2nady 3ala el initialization kol
    * shywaya 3ashan tynafez 7aga dy
    *
    * INPUT:
    *
    * PRE-CONDITION:
    *The UART peripheral must be enabled
    *The the Channel required must be initialized
    *
    *POST-CONDITION:
    *
    * */

  void UART_ConfigureInterruptSource(enum UART_IRQ_Event InterruptFlag, UART_InterruptMaskConfig_t InterruptMaskConfig, UART_Channel_t Channel){

      /*Check condition that the UART is already enabled */
      if(1 == (*UART_ControlRegisters[Channel]).bits.UARTEnable){


      if(UART_IRQ_PE == InterruptFlag){
          (*UART_InterruptMaskRegisters[Channel]).bits.ParityErrorInterruptMask=InterruptMaskConfig;
      }

      else if(UART_IRQ_RXNE == InterruptFlag){
          (*UART_InterruptMaskRegisters[Channel]).bits.ReceiveInterruptMask=InterruptMaskConfig;
      }

      else if(UART_IRQ_TXNF == InterruptFlag){
          (*UART_InterruptMaskRegisters[Channel]).bits.TransmitInterruptMask=InterruptMaskConfig;
      }

      else if(UART_IRQ_FE == InterruptFlag){
          (*UART_InterruptMaskRegisters[Channel]).bits.FramingErrorInterruptMask=InterruptMaskConfig;
      }


      }

  }


   void UART_TransmitChar_Polling(UART_Channel_t channel, u8_t *pTxBuffer){

       (*UART_ControlRegisters[channel]).bits.TransmitEnable=1;

       /*If the FIFO is disabled (FEN is 0), the transmit holding register
        is full.*/
       while( (*UART_FlagRegisters[channel]).bits.TransmitFIFOFull != 0);
       //while( (*UART_FlagRegisters[channel]).bits.TransmitFIFOEmpty != 0);
       (*UART_DataRegisters[channel]).bits.Data= *((u8_t *)pTxBuffer) ;

   }


    void UART_RecieveChar_Polling(UART_Channel_t channel, u8_t *pRxBuffer){

        (*UART_ControlRegisters[channel]).bits.ReceiveEnable=1;

        while( (*UART_FlagRegisters[channel]).bits.ReceiveFIFOEmpty != 0);

        *((u8_t *)pRxBuffer )= (*UART_DataRegisters[channel]).bits.Data ;

   }



   void UART_TransmitChar_Interrupt(UART_Channel_t channel, u8_t *pRxBuffer){



       (*UART_ControlRegisters[channel]).bits.TransmitEnable=1;

       NVIC_Enable_Interrupt( UART_InterruptNum_Arr[channel] );

       (*UART_InterruptMaskRegisters[channel]).bits.TransmitInterruptMask=1;

      (*UART_DataRegisters[channel]).bits.Data= *((u8_t *)pRxBuffer) ;

   }


    void UART_RecieveChar_Interrupt(UART_Channel_t channel, u8_t *pRxBuffer){

        (*UART_ControlRegisters[channel]).bits.ReceiveEnable=1;
         NVIC_Enable_Interrupt( UART_InterruptNum_Arr[channel] );
        (*UART_InterruptMaskRegisters[channel]).bits.ReceiveInterruptMask=1;

        *((u8_t *)pRxBuffer )=  (*UART_DataRegisters[channel]).bits.Data ;

   }

    void UART_Transmit_DMA(UART_Channel_t Channel, u8_t *SourceAddressBuffer, DMAChannelNum_t DMAChannelNum){

          UARTDMA_TxFlag=1;
         //DMA_ChannelsConfigTX[Channel] --> array of pointers to structures
          DMA_ChannelControlStructureSet(DMA_ChannelsConfigTX[Channel], (u8_t*)SourceAddressBuffer ,(u32_t*)UART_DataRegisters[Channel]  );
          *(DestinationAddressPointer23_UART)=(u32_t*)UART_DataRegisters[Channel];

          UART_InterruptFIFOLevelSelect[Channel]->bits.TXIFLSEL=_1_DIV_8_Empty;

         (*UART_DMAControlRegisters[Channel]).bits.TransmitDMAEnable=1;
         (*UART_ControlRegisters[Channel]).bits.TransmitEnable=1;
         UARTDMA_TxFlag=0;
     }

     void UART_Receive_DMA(UART_Channel_t Channel){

         //UARTDMA_RxFlag=1;
         /*DMA_ChannelControlStructureSet(DMA_ChannelsConfigRX[Channel],(u32_t*)UART_DataRegisters[Channel],(u8_t*)destAddressBuffer );
         *(SourceAddressPointer22_UART)=(u32_t*)UART_DataRegisters[Channel];

         DMA_ChannelAlternateControlStructureSet(DMA_ChannelsConfigRX[Channel],(u32_t*)UART_DataRegisters[Channel],&DestBufferB[0] );
         *(AlternateSourceAddressPointer22_UART)=(u32_t*)UART_DataRegisters[Channel];*/

         (*UART_DMAControlRegisters[Channel]).bits.ReceiveDMAEnable=1;
         (*UART_ControlRegisters[Channel]).bits.ReceiveEnable =1;
         //UARTDMA_RxFlag=0;
         //(*UART_ControlRegisters[Channel]).bits.UARTEnable=1;
     }

     void UART_DMA_Reload_PrimaryControlStructure(UART_Channel_t Channel, u8_t *destAddressBuffer){

         UARTDMA_RxFlag=1;
         DMA_ChannelControlStructureSet(DMA_ChannelsConfigRX[Channel],(u32_t*)UART_DataRegisters[Channel],(u8_t*)destAddressBuffer );
         *(SourceAddressPointer22_UART)=(u32_t*)UART_DataRegisters[Channel];
         UARTDMA_RxFlag=0;

     }

     void UART_DMA_Reload_AlternateControlStructure(UART_Channel_t Channel, u8_t *destAddressBuffer){

         UARTDMA_RxFlag=1;
         DMA_ChannelAlternateControlStructureSet(DMA_ChannelsConfigRX[Channel],(u32_t*)UART_DataRegisters[Channel],(u8_t*)destAddressBuffer );
         *(AlternateSourceAddressPointer22_UART)=(u32_t*)UART_DataRegisters[Channel];
         UARTDMA_RxFlag=0;

     }



    void UART_RecCharwTimeOut (char* data,UART_Channel_t channel ){

        GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 600, milli_Sec);

        if(0 == (*UART_FlagRegisters[channel]).bits.ReceiveFIFOFull ){

            *data= (*UART_DataRegisters[channel]).bits.Data ;
            return;
        }
        *data='\0';

  /*      Another Implementation
   *      u32_t SystemClkFreq;
   *      SystemClkFreq  = SC_GetSystemClock();

        int count=(UARTRecTimeOut*(SystemClkFreq/1000))/3; // divided by 3 as the decrement takes 3 clock ticks

        while ( 1 == ( (*UART_FlagRegisters[channel]).bits.ReceiveFIFOFull )  && count>0 ){
            count --;
        }

        if (0 == count){

            *data='\0';
        }

        else {
            *data= (*UART_DataRegisters[channel]).bits.Data ;
        }*/


    }

  /* the user(application) function is defined in the HAL or application layer
   * A pointer to the user function will be registered inside the UART0_Callback[] which is an array of pointer to function
   * the UART0_Callback is located inside the ISR function when an interrupt occurs the cpu executes that function by
   * dereferencing the pointer UART0_Callback[Flag]--->  *UART0_Callback[Flag]
   * there are five pointers in the array which specifies the source of the interrupt    */
    void UART0_RegisterCallbackFunction(enum UART_IRQ_Event Flag, CallbackFunc_t pt_callback){

        UART0_Callback[Flag]=pt_callback;
    }


    void UART1_RegisterCallbackFunction(enum UART_IRQ_Event Flag, CallbackFunc_t pt_callback){

         UART1_Callback[Flag]=pt_callback;
    }

    void UART2_RegisterCallbackFunction(enum UART_IRQ_Event Flag, CallbackFunc_t pt_callback){

         UART2_Callback[Flag]=pt_callback;
    }

    void UART3_RegisterCallbackFunction(enum UART_IRQ_Event Flag, CallbackFunc_t pt_callback){

         UART3_Callback[Flag]=pt_callback;
    }

    void UART4_RegisterCallbackFunction(enum UART_IRQ_Event Flag, CallbackFunc_t pt_callback){

         UART4_Callback[Flag]=pt_callback;
    }

    void UART5_RegisterCallbackFunction(enum UART_IRQ_Event Flag, CallbackFunc_t pt_callback){

         UART5_Callback[Flag]=pt_callback;

    }
    void UART6_RegisterCallbackFunction(enum UART_IRQ_Event Flag, CallbackFunc_t pt_callback){

         UART6_Callback[Flag]=pt_callback;

    }
    void UART7_RegisterCallbackFunction(enum UART_IRQ_Event Flag, CallbackFunc_t pt_callback){

         UART7_Callback[Flag]=pt_callback;

    }
