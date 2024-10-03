/*************************************************************************************************************************************/
/* Name: GPIO.c                                                                                                                    */
/* Author: Madonna Magdy                                                                                                            */
/* Version: V1                                                                                                                      */
/* Usage: This module contains the implementation for the GPIO functions                                                            */
/*************************************************************************************************************************************/

/* =====================================================================================*/
/*                                  INCLUDES                                            */
/* =====================================================================================*/
#include"GPIO_reg.h"
#include "gpio_config.h"
#include "GPIO.h"

#include<assert.h>
#include<stdlib.h>

/******************************************* ID Description of the Unit *********************************************************/
// first number of ID signifies the module used (the GPIO  module takes number 3)

  //The Second number signifies that whether you are using a function or an array or a variable
 //(The variable takes number1 ,The array takes number 2, The function takes number 3  )

 //The Third number signifies the number of a function or an array or a variable

/******************************************* ID Description of the Unit ********************************************************/


/******************************  ID Description For Testing *********************************************************/

 //First part is the ID description of the Unit

 //The second part signifies how many number of tests you use on a certain variable or function (on a certain unit)

/******************************  ID Description For Testing *********************************************************/


/************************  UNIT ID: 3.2.1 **********************************/
/* UNIT ID: 3.2.1
 *
 * UNIT NAME: EXTI_Callback
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
 * If you don't initialize EXTI_Callback[] with a null pointer
 * and you forgot to register the call back function there will
 * be segmentation fault because you are trying to access a wild pointer

 * The advantage of the if condition ---> (if(EXTI_Callback[] != NULL_PTR) )
 * you can't check on a garbage value but you can check on the null value
 * to see if the pointer to function (EXTI_Callback[]) doesn't hold the
 * address of a function or doesn't hold a value
 *
 *  */
 static volatile  CallbackFunc_t EXTI_Callback[Port_Indices]={NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR};
/************************  UNIT ID: 3.2.1 **********************************/



/************************  UNIT ID: 3.3.1 **********************************/
 /* UNIT ID: 3.3.1
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
  * That Function related to the external interrupt of PORTA
  * */
 EXTIAIntHandler(){

    if (EXTI_Callback[PortA] != NULL_PTR){

    (*EXTI_Callback[PortA])();

    }

}

/************************  UNIT ID: 3.3.2 **********************************/
 /* UNIT ID: 3.3.2
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
  * That Function related to the external interrupt of PORTB
  * */

 EXTIBIntHandler(){

    if (EXTI_Callback[PortB] != NULL_PTR){

    (*EXTI_Callback[PortB])();

    }

}


/************************  UNIT ID: 3.3.3 **********************************/
/* UNIT ID: 3.3.3
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
 * That Function related to the external interrupt of PORTC
 * */

EXTICIntHandler(){

    if (EXTI_Callback[PortC] != NULL_PTR){

    (*EXTI_Callback[PortC])();

    }

}

/************************  UNIT ID: 3.3.4 **********************************/
/* UNIT ID: 3.3.4
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
 * That Function related to the external interrupt of PORTD
 * */
EXTIDIntHandler(){

    if (EXTI_Callback[PortD] != NULL_PTR){

    (*EXTI_Callback[PortD])();

    }

}

/************************  UNIT ID: 3.3.5 **********************************/
/* UNIT ID: 3.3.5
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
 * That Function related to the external interrupt of PORTE
 * */
EXTIEIntHandler(){

    if (EXTI_Callback[PortE] != NULL_PTR){

    (*EXTI_Callback[PortE])();

    }

}

/************************  UNIT ID: 3.3.6 **********************************/
/* UNIT ID: 3.3.6
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
 * That Function related to the external interrupt of PORTF
 * */


EXTIFIntHandler(){

    if (EXTI_Callback[PortF] != NULL_PTR){

    (*EXTI_Callback[PortF])();
    }



}

/**************************************************************************************************************/
 /* creating an array of pointers to registers
  * the user (or the application layer) will not be allowed to have access to the hardware registers
  * because it's not his/her concern
  * he/she will only be allowed to call the interfacing functions in the GPIO.h file
  * for that reason a keyword static will be added
  *
  * A constant keyword is added because the location of the register never changes
  * so for safety no one can change the location of the pointer the only value that can be changed is the value INSIDE
  * the register ---> the value that the pointer is pointing to*/
/**************************************************************************************************************/
volatile GPIO_Direction_Reg static * const GPIO_Direction_Registers[Port_Indices]={

     (GPIO_Direction_Reg*) &GPIO_PortA_Direction,
     (GPIO_Direction_Reg*) &GPIO_PortB_Direction,
     (GPIO_Direction_Reg*) &GPIO_PortC_Direction,
     (GPIO_Direction_Reg*) &GPIO_PortD_Direction,
     (GPIO_Direction_Reg*) &GPIO_PortE_Direction,
     (GPIO_Direction_Reg*) &GPIO_PortF_Direction

};


/**************************************************************************************************************/
 /* creating an array of pointers to registers
  * the user (or the application layer) will not be allowed to have access to the hardware registers
  * because it's not his/her concern
  * he/she will only be allowed to call the interfacing functions in the GPIO.h file
  * for that reason a keyword static will be added
  *
  * A constant keyword is added because the location of the register never changes
  * so for safety no one can change the location of the pointer the only value that can be changed is the value INSIDE
  * the register ---> the value that the pointer is pointing to*/
/**************************************************************************************************************/
volatile GPIO_AFSEL_Reg static *const GPIO_AlternateFunctionSelect_Registers[Port_Indices]={

      GPIO_PortA_AlternateFunctionSelect,
      GPIO_PortB_AlternateFunctionSelect,
      GPIO_PortC_AlternateFunctionSelect,
      GPIO_PortD_AlternateFunctionSelect,
      GPIO_PortE_AlternateFunctionSelect,
      GPIO_PortF_AlternateFunctionSelect
};

 /************************************************ UNIT ID =3.2.2**************************************************************/
 /* creating an array of pointers to registers
  * the user (or the application layer) will not be allowed to have access to the hardware registers
  * because it's not his/her concern
  * he/she will only be allowed to call the interfacing functions in the GPIO.h file
  * for that reason a keyword static will be added
  *
  * A constant keyword is added because the location of the register never changes
  * so for safety no one can change the location of the pointer the only value that can be changed is the value INSIDE
  * the register ---> the value that the pointer is pointing to*/
 /**************************************************************************************************************/
 volatile GPIO_InterruptSense_Reg static* const GPIO_InterruptSense_Registers[Port_Indices] ={

      (GPIOIS_PortA_R),
      (GPIOIS_PortB_R),
      (GPIOIS_PortC_R),
      (GPIOIS_PortD_R),
      (GPIOIS_PortE_R),
      (GPIOIS_PortF_R)

 };
/**************************************************************************************************************/
 /* creating an array of pointers to registers
  * the user (or the application layer) will not be allowed to have access to the hardware registers
  * because it's not his/her concern
  * he/she will only be allowed to call the interfacing functions in the GPIO.h file
  * for that reason a keyword static will be added
  *
  * A constant keyword is added because the location of the register never changes
  * so for safety no one can change the location of the pointer the only value that can be changed is the value INSIDE
  * the register ---> the value that the pointer is pointing to*/
/**************************************************************************************************************/
 //volatile GPIO_InterruptBothEdges_Reg static* const GPIO_InterruptBothEdges_Registers[6] ={

 //     (GPIOIBE_PortA_R),
//      (GPIOIBE_PortA_R),
 //     (GPIOIBE_PortA_R),
 //     (GPIOIBE_PortA_R),
 //     (GPIOIBE_PortA_R),
 //     (GPIOIBE_PortA_R)

// };
/*****************************************Pre-Condition for accessing the GPIOIBE Reg  ****************************************************/
/*
 * the interrupt sense register must be configured first
 */
 volatile GPIO_InterruptEvent_Reg static* const GPIO_InterruptEvent_Registers[Port_Indices] ={

      (GPIOIEV_PortA_R),
      (GPIOIEV_PortB_R),
      (GPIOIEV_PortC_R),
      (GPIOIEV_PortD_R),
      (GPIOIEV_PortE_R),
      (GPIOIEV_PortF_R)

 };

 /**************************************************************************************************************/
  /* creating an array of pointers to registers
   * the user (or the application layer) will not be allowed to have access to the hardware registers
   * because it's not his/her concern
   * he/she will only be allowed to call the interfacing functions in the GPIO.h file
   * for that reason a keyword static will be added
   *
   * A constant keyword is added because the location of the register never changes
   * so for safety no one can change the location of the pointer the only value that can be changed is the value INSIDE
   * the register ---> the value that the pointer is pointing to*/
 /**************************************************************************************************************/
 volatile GPIO_InterruptMask_Reg static* const GPIO_InterruptMask_Registers[Port_Indices] ={

      (GPIOIM_PortA_R),
      (GPIOIM_PortB_R),
      (GPIOIM_PortC_R),
      (GPIOIM_PortD_R),
      (GPIOIM_PortE_R),
      (GPIOIM_PortF_R)

 };

 /**************************************************************************************************************/
  /* creating an array of pointers to registers
   * the user (or the application layer) will not be allowed to have access to the hardware registers
   * because it's not his/her concern
   * he/she will only be allowed to call the interfacing functions in the GPIO.h file
   * for that reason a keyword static will be added
   *
   * A constant keyword is added because the location of the register never changes
   * so for safety no one can change the location of the pointer the only value that can be changed is the value INSIDE
   * the register ---> the value that the pointer is pointing to*/
 /**************************************************************************************************************/
 volatile GPIO_Data_Reg static * const GPIO_Data_Registers[Port_Indices]={

       (GPIO_Data_Reg*) &GPIO_PortA_Data,
       (GPIO_Data_Reg*) &GPIO_PortB_Data,
       (GPIO_Data_Reg*) &GPIO_PortC_Data,
       (GPIO_Data_Reg*) &GPIO_PortD_Data,
       (GPIO_Data_Reg*) &GPIO_PortE_Data,
       (GPIO_Data_Reg*) &GPIO_PortF_Data

 };


 /**************************************************************************************************************/
  /* creating an array of pointers to registers
   * the user (or the application layer) will not be allowed to have access to the hardware registers
   * because it's not his/her concern
   * he/she will only be allowed to call the interfacing functions in the GPIO.h file
   * for that reason a keyword static will be added
   *
   * A constant keyword is added because the location of the register never changes
   * so for safety no one can change the location of the pointer the only value that can be changed is the value INSIDE
   * the register ---> the value that the pointer is pointing to*/
 /**************************************************************************************************************/
 volatile GPIO_DigitalEnable_Reg static * const GPIO_DigitalEnable_Registers[Port_Indices]={
        GPIO_PortA_DigitalEnable,
        GPIO_PortB_DigitalEnable,
        GPIO_PortC_DigitalEnable,
        GPIO_PortD_DigitalEnable,
        GPIO_PortE_DigitalEnable,
        GPIO_PortF_DigitalEnable

 };


 /**************************************************************************************************************/
  /* creating an array of pointers to registers
   * the user (or the application layer) will not be allowed to have access to the hardware registers
   * because it's not his/her concern
   * he/she will only be allowed to call the interfacing functions in the GPIO.h file
   * for that reason a keyword static will be added
   *
   * A constant keyword is added because the location of the register never changes
   * so for safety no one can change the location of the pointer the only value that can be changed is the value INSIDE
   * the register ---> the value that the pointer is pointing to*/
 /**************************************************************************************************************/
 volatile u32_t static * const GPIO_PortControl_Registers[Port_Indices]={

      GPIO_PortA_PortControl,
      GPIO_PortB_PortControl,
      GPIO_PortC_PortControl,
      GPIO_PortD_PortControl,
      GPIO_PortE_PortControl,
      GPIO_PortF_PortControl

 };

 /**************************************************************************************************************/
  /* creating an array of pointers to registers
   * the user (or the application layer) will not be allowed to have access to the hardware registers
   * because it's not his/her concern
   * he/she will only be allowed to call the interfacing functions in the GPIO.h file
   * for that reason a keyword static will be added
   *
   * A constant keyword is added because the location of the register never changes
   * so for safety no one can change the location of the pointer the only value that can be changed is the value INSIDE
   * the register ---> the value that the pointer is pointing to*/
 /**************************************************************************************************************/
volatile u32_t static * const GPIO_LOCK_Registers[Port_Indices]={

       GPIO_PortA_LOCK,
       GPIO_PortB_LOCK,
       GPIO_PortC_LOCK,
       GPIO_PortD_LOCK,
       GPIO_PortE_LOCK,
       GPIO_PortF_LOCK

};

/**************************************************************************************************************/
 /* creating an array of pointers to registers
  * the user (or the application layer) will not be allowed to have access to the hardware registers
  * because it's not his/her concern
  * he/she will only be allowed to call the interfacing functions in the GPIO.h file
  * for that reason a keyword static will be added
  *
  * A constant keyword is added because the location of the register never changes
  * so for safety no one can change the location of the pointer the only value that can be changed is the value INSIDE
  * the register ---> the value that the pointer is pointing to*/
/**************************************************************************************************************/
volatile GPIO_CR_Reg static *const GPIO_Port_Commit[Port_Indices]={

      GPIO_PortA_Commit,
      GPIO_PortB_Commit,
      GPIO_PortC_Commit,
      GPIO_PortD_Commit,
      GPIO_PortE_Commit,
      GPIO_PortF_Commit

};

/**************************************************************************************************************/
 /* creating an array of pointers to registers
  * the user (or the application layer) will not be allowed to have access to the hardware registers
  * because it's not his/her concern
  * he/she will only be allowed to call the interfacing functions in the GPIO.h file
  * for that reason a keyword static will be added
  *
  * A constant keyword is added because the location of the register never changes
  * so for safety no one can change the location of the pointer the only value that can be changed is the value INSIDE
  * the register ---> the value that the pointer is pointing to*/
/**************************************************************************************************************/
volatile GPIO_ICR_Reg static * const GPIO_InterruptClear_Registers[Port_Indices]={

       (GPIO_ICR_Reg*) &GPIO_PortA_InterruptClear,
       (GPIO_ICR_Reg*) &GPIO_PortB_InterruptClear,
       (GPIO_ICR_Reg*) &GPIO_PortC_InterruptClear,
       (GPIO_ICR_Reg*) &GPIO_PortD_InterruptClear,
       (GPIO_ICR_Reg*) &GPIO_PortE_InterruptClear,
       (GPIO_ICR_Reg*) &GPIO_PortF_InterruptClear


};


volatile GPIOPUR_Reg static* const GPIO_PullUp_Registers[Port_Indices]={
        GPIO_PortA_PullUp_R,
        GPIO_PortB_PullUp_R,
        GPIO_PortC_PullUp_R,
        GPIO_PortD_PullUp_R,
        GPIO_PortE_PullUp_R,
        GPIO_PortF_PullUp_R

};

volatile unsigned long GPIO_BIT_BAND_Registers[Port_Indices]={

      GPIO_PORTA_BIT_BAND_R,
      GPIO_PORTB_BIT_BAND_R,
      GPIO_PORTC_BIT_BAND_R,
      GPIO_PORTD_BIT_BAND_R,
      GPIO_PORTE_BIT_BAND_R,
      GPIO_PORTF_BIT_BAND_R
};



void static inline GPIO_EnableRunModeClockGateControl(GPIO_PortNumIndexArr_t PortNumIndexArr){

     GPIO_RunModeClockGatingControl->Bits.GPIOPortRunModeClockGatingControl |= (1<<PortNumIndexArr);

     while( (GPIO_RunModeClockGatingControl->Bits.GPIOPortRunModeClockGatingControl & (1<<PortNumIndexArr)) == 0);

 }

 /*****************************  UNIT ID: 3.3.9 **********************************/
 /* UNIT ID: 3.3.9
  *
  * UNIT NAME : GPIO_SetPinStatus
  *
  * UNIT LOCATION: .text section
  *
  * UNIT DESCRIPTION: This function is responsible for setting a defined status for GPIO pin [OUTPUT - INPUT_FLOAT]
  *
  * PRE-CONDITION 1:the port clock of the specified pin must be enabled through the
  * function with UNIT ID: 3.3.7
  *
  * PRE-CONDITION 2: the selected channel within the maximum ChannelNum_t definition
  * PRE-CONDITION 3: the selected port within the maximum PortNum_t definition
  * PRE-CONDITION 4: the selected state within the maximum PinState_t definition
  *
  * POST-CONDITIONS: the pin with number ChannelNum will be a digital pin
  * POST-CONDITIONS: the pin status with number ChannelNum will be State
  *
  * @input : the number of the port
  * @input : the number of the pin
  * @input : the pin state
  *
  * @return:void
  */

void GPIO_SetPinStatus(GPIO_PortNumIndexArr_t PortNumIndexArr, GPIO_ConfigureChannelNum_t ConfigureChannelNum, GPIO_PinState_t PinState ){

    //assert( (PortNum =>MinNumPort) && (PortNum <= MaxNumPort));
    //assert( (ChannelNum =>MinNumChannel) && (ChannelNum <= MaxNumChannel));
    //assert( (State =>MinNumState) && (State <= MaxNumState));


    switch (PinState){

    case InputFloat:
    (*GPIO_Direction_Registers[PortNumIndexArr]).bits.Direction &= ~(1<<ConfigureChannelNum);
    break;

    case Output:
    (*GPIO_Direction_Registers[PortNumIndexArr]).bits.Direction |=(1<<ConfigureChannelNum);
    break;

    }


}

void GPIO_SetData(GPIO_PortNumIndexArr_t PortNumIndexArr , GPIO_ConfigureChannelNum_t ConfigureChannelNum, GPIO_OutputValue_t OutputValue){

    /* check that already the pin is an output pin before writing on the data register */
    //if ( (*GPIO_Direction_Registers[PortNumIndexArr]).bits.Direction>>ConfigureChannelNum & 1  ){

        switch (OutputValue){

         case OutputLow:
             (*GPIO_Data_Registers[PortNumIndexArr]).bits.Data &= ~(1<<ConfigureChannelNum);
           break;

        case OutputHigh:
            (*GPIO_Data_Registers[PortNumIndexArr]).bits.Data |= (1<<ConfigureChannelNum);
           break;
        }


   // }

}


void GPIO_TogglePinValue(GPIO_PortNumIndexArr_t PortNumIndexArr, GPIO_ConfigureChannelNum_t ConfigureChannelNum){

    /* check that already the pin is an output pin before writing on the data register */
   // if ( (*GPIO_Direction_Registers[PortNum]).bits.Direction>>ChannelNum & 1  ){

        (*GPIO_Data_Registers[PortNumIndexArr]).bits.Data ^= (1<<ConfigureChannelNum);
    //}


}

void GPIO_ConfigureAlternateFunctionSelect(GPIO_PortNumIndexArr_t PortNumIndexArr, GPIO_ConfigureChannelNum_t ConfigureChannelNum , GPIO_AFSELMode_t AFSELMode){

    switch(AFSELMode){

    case Disable_AFSEL:
        (*GPIO_AlternateFunctionSelect_Registers[PortNumIndexArr]).bits.AlternateFunctionSelect &= ~(1<<ConfigureChannelNum);
        break;

    case Enable_AFSEL:
       (*GPIO_AlternateFunctionSelect_Registers[PortNumIndexArr]).bits.AlternateFunctionSelect |= (1<<ConfigureChannelNum);
        break;
    }

}


void GPIO_ConfigureAnalogModeSelect(GPIO_PortNumIndexArr_t PortNumIndexArr, GPIO_ConfigureChannelNum_t ConfigureChannelNum, GPIO_AMSELMode_t AMSELMode){

    switch (AMSELMode){

    case Disable_AMSEL:
       // (*GPIO_AnalogModeSelect_Registers[PortNumIndexArr]).bits.AnalogModeSelect &= ~(1<<ConfigureChannelNum);
        break;

    case Enable_AMSEL:
        //(*GPIO_AnalogModeSelect_Registers[PortNumIndexArr]).bits.AnalogModeSelect |= (1<<ConfigureChannelNum);
        break;
    }

}

void GPIO_ConfigurePortControl(GPIO_PortNumIndexArr_t PortNumIndexArr, GPIO_ConfigureChannelNum_t ConfigureChannelNum, GPIO_ConfigureMuxValue_t ConfigureMuxValue ){

/****************************************************************************************************************/
    *GPIO_PortControl_Registers[PortNumIndexArr] &= ~( (u32_t)0xF << (ConfigureChannelNum*4) );

    /* IMPORTANT NOTE:
     * that  Operation was performed because
     *
     * IF the bit in that register was already set
     * with a value 1 before and IF you initialize it
     * with a value zero,
     * the value inserted in the register will be not be zero
     * it will be one because it is an OR operation in the line below
     */
/****************************************************************************************************************/

    *GPIO_PortControl_Registers[PortNumIndexArr] |= ( (u32_t)ConfigureMuxValue << ConfigureChannelNum*4);

    //to remove that warning --> implicit conversion changes signedness 'int' to 'unsigned long'
    //    casting was performed


}

void GPIO_ConfigureDigitalEnable(GPIO_PortNumIndexArr_t PortNumIndexArr, GPIO_ConfigureChannelNum_t ConfigureChannelNum, GPIO_DigitalMode_t DigitalMode){


    switch (DigitalMode){

    case DisableDigitalFunction:
        (*GPIO_DigitalEnable_Registers[PortNumIndexArr]).bits.DigitalEnable &= ~(1<<ConfigureChannelNum);
        break;

    case EnableDigitalFunction:
        (*GPIO_DigitalEnable_Registers[PortNumIndexArr]).bits.DigitalEnable |=(1<<ConfigureChannelNum);
        break;

    }

}

void GPIO_ConfigureCommit(GPIO_PortNumIndexArr_t PortNumIndexArr, GPIO_ConfigureChannelNum_t ConfigureChannelNum, GPIO_LockMode_t LockMode){

    switch (LockMode){

    case EnableLock:
        *GPIO_LOCK_Registers[PortNumIndexArr] = 0;
        break;

    case DisableLock:
        *GPIO_LOCK_Registers[PortNumIndexArr] = 0x4C4F434B;
        (*GPIO_Port_Commit[PortNumIndexArr]).bits.commit |=(1<<ConfigureChannelNum);
        break;

    }
}


void GPIO_EXTIClearInterrupt(GPIO_PortNumIndexArr_t PortNumIndexArr, GPIO_ConfigureChannelNum_t ConfigureChannelNum){

    (*GPIO_InterruptClear_Registers[PortNumIndexArr]).bits.InterruptClear |= (1<<ConfigureChannelNum);

}

void GPIO_ConfigureInterruptMask(GPIO_PortNumIndexArr_t PortNumIndexArr, GPIO_ConfigureChannelNum_t ConfigureChannelNum, GPIO_InterruptMaskMode_t InterruptMaskMode){

    switch(InterruptMaskMode){

    case Enable_InterruptMask:
        (*GPIO_InterruptMask_Registers[PortNumIndexArr]).Bits.InterruptMaskEnable |= (1<<ConfigureChannelNum);
    break;

    case Disable_InterruptMask:
        (*GPIO_InterruptMask_Registers[PortNumIndexArr]).Bits.InterruptMaskEnable &= ~(1<<ConfigureChannelNum);
    break;

    }

}

/*******************************************************************************************/
/*                    GPIO---->Input/Output pins                                          */
/*******************************************************************************************/

void GPIO_ConfigureOutputPin(GPIO_ConfigurePin_t* pt_ConfigurePin){

    GPIO_EnableRunModeClockGateControl(pt_ConfigurePin->PortNumIndexArr);

    GPIO_SetPinStatus(pt_ConfigurePin->PortNumIndexArr, pt_ConfigurePin->ConfigureChannelNum , Output);

    GPIO_SetData(pt_ConfigurePin->PortNumIndexArr , pt_ConfigurePin->ConfigureChannelNum, OutputLow);

    GPIO_ConfigureDigitalEnable(pt_ConfigurePin->PortNumIndexArr, pt_ConfigurePin->ConfigureChannelNum, EnableDigitalFunction);

    GPIO_ConfigureCommit(pt_ConfigurePin->PortNumIndexArr, pt_ConfigurePin->ConfigureChannelNum ,DisableLock);

 }

void GPIO_SetPinDirection(GPIO_PortNumIndexArr_t PortNumIndexArr, GPIO_ConfigureChannelNum_t ConfigureChannelNum, GPIO_PinState_t PinState ){
    //assert( (PortNum =>MinNumPort) && (PortNum <= MaxNumPort));
    //assert( (ChannelNum =>MinNumChannel) && (ChannelNum <= MaxNumChannel));
    //assert( (State =>MinNumState) && (State <= MaxNumState));

    switch (PinState){

    case InputFloat:
    (*GPIO_Direction_Registers[PortNumIndexArr]).bits.Direction &= ~(1<<ConfigureChannelNum);
    break;

    case Output:
    (*GPIO_Direction_Registers[PortNumIndexArr]).bits.Direction |=(1<<ConfigureChannelNum);
    break;

    }


}

void GPIO_SetInputStatus(GPIO_PortNumIndexArr_t PortNumIndexArr, GPIO_ConfigureChannelNum_t ConfigureChannelNum){

    GPIO_PullUp_Registers[PortNumIndexArr]->Bits.PullUpEnable |=(1<<ConfigureChannelNum);
}


void GPIO_ConfigureInputPin(GPIO_ConfigurePin_t* pt_ConfigurePin){

    GPIO_EnableRunModeClockGateControl(pt_ConfigurePin->PortNumIndexArr);

    if( (PortF == (pt_ConfigurePin->PortNumIndexArr)) && ((pt_ConfigurePin->ConfigureChannelNum) == Channel_0)){

    GPIO_ConfigureCommit(PortF, Channel_0 ,DisableLock);
    }

    GPIO_SetPinDirection(pt_ConfigurePin->PortNumIndexArr, pt_ConfigurePin->ConfigureChannelNum , InputFloat);

    GPIO_SetInputStatus(pt_ConfigurePin->PortNumIndexArr, pt_ConfigurePin->ConfigureChannelNum);

   GPIO_ConfigureDigitalEnable(pt_ConfigurePin->PortNumIndexArr, pt_ConfigurePin->ConfigureChannelNum, EnableDigitalFunction);


}


void GPIO_ToggleBitBandBits(GPIO_ConfigureChannelNum_t ChannelNum, GPIO_PortNumIndexArr_t PortNumIndexArr){

 *((unsigned long volatile *)(GPIO_BIT_BAND_Registers[PortNumIndexArr]+ (1<<(2+ChannelNum)) )) ^= (1<<ChannelNum);

}


u32_t GPIO_ReadBitBandBits(GPIO_ConfigureChannelNum_t ChannelNum, GPIO_PortNumIndexArr_t PortNumIndexArr){

    return *((unsigned long volatile *)(GPIO_BIT_BAND_Registers[PortNumIndexArr]+ (1<<(2+ChannelNum)) ));

}

void GPIO_WriteBitBandBits(GPIO_ConfigureChannelNum_t ChannelNum, GPIO_PortNumIndexArr_t PortNumIndexArr, GPIO_OutputValue_t  OutputValue){

    switch (OutputValue){
    case OutputHigh:
      *((unsigned long volatile *)(GPIO_BIT_BAND_Registers[PortNumIndexArr]+ (1<<(2+ChannelNum)) )) = (1<<ChannelNum);
      break;

    case OutputLow:
        *((unsigned long volatile *)(GPIO_BIT_BAND_Registers[PortNumIndexArr]+ (1<<(2+ChannelNum)) )) &= ~(1<<ChannelNum);
        break;

    }

}




void GPIO_EnableAFSEL_GPTM(GPIO_TimerConfigChannel_t * pt_TimerConfigChannel){

    GPIO_EnableRunModeClockGateControl(pt_TimerConfigChannel->PortNumIndexArr);

    //GPIO_SetPinStatus(TimerPWMConfigChannel->PortNumIndexArr, TimerPWMConfigChannel->ConfigureChannelNum, Output );

    //GPIO_SetData(TimerPWMConfigChannel->PortNumIndexArr , TimerPWMConfigChannel->ConfigureChannelNum, OutputHigh);

    GPIO_ConfigureAlternateFunctionSelect(pt_TimerConfigChannel->PortNumIndexArr, pt_TimerConfigChannel->ConfigureChannelNum , Enable_AFSEL);
    GPIO_ConfigurePortControl(pt_TimerConfigChannel->PortNumIndexArr, pt_TimerConfigChannel->ConfigureChannelNum, MuxValue_7 );
    GPIO_ConfigureInterruptMask(pt_TimerConfigChannel->PortNumIndexArr, pt_TimerConfigChannel->ConfigureChannelNum, Disable_InterruptMask);


    GPIO_ConfigureDigitalEnable(pt_TimerConfigChannel->PortNumIndexArr, pt_TimerConfigChannel->ConfigureChannelNum, EnableDigitalFunction);

}

/************************  UNIT ID:  **********************************/
 /* UNIT ID:
  *
  * UNIT NAME: GPIO_EnableAFSEL_UART
  *
  * UNIT LOCATION: FLASH
  *
  * UNIT DESCRIPTION:
  * The UART signals are alternate functions for some GPIO signals for that reason we need to
  *
  * 1-Enable the Alternative function select of the specified port and channel
  * in GPIO peripheral to use these signals as UART signals not GPIO signals
  * but, once we enable the the alternative function select in the GPIO peripheral
  * we can use it as I2C,SSI,...
  * the port control register is responsible for selecting one out these peripheral for each
  * channel related to specific port
  *
  * 2- configure the port control register by writting the MUX value to select a peripheral
  * for each channel
  *
  *
  * */

void GPIO_EnableAFSEL_UART(GPIO_UARTConfigChannel_t* pt_UARTConfigChannel){

    GPIO_EnableRunModeClockGateControl(pt_UARTConfigChannel->PortNumIndexArr);

    GPIO_ConfigureAlternateFunctionSelect(pt_UARTConfigChannel->PortNumIndexArr, pt_UARTConfigChannel->ChannelNumRx,Enable_AFSEL); // U0RX
    GPIO_ConfigureAlternateFunctionSelect(pt_UARTConfigChannel->PortNumIndexArr, pt_UARTConfigChannel->ChannelNumTx,Enable_AFSEL); // U0TX

    GPIO_ConfigurePortControl(pt_UARTConfigChannel->PortNumIndexArr,pt_UARTConfigChannel->ChannelNumRx,MuxValue_1);
    GPIO_ConfigurePortControl(pt_UARTConfigChannel->PortNumIndexArr,pt_UARTConfigChannel->ChannelNumTx,MuxValue_1);

    GPIO_ConfigureDigitalEnable(pt_UARTConfigChannel->PortNumIndexArr, pt_UARTConfigChannel->ChannelNumRx, EnableDigitalFunction);
    GPIO_ConfigureDigitalEnable(pt_UARTConfigChannel->PortNumIndexArr, pt_UARTConfigChannel->ChannelNumTx, EnableDigitalFunction);


}

void RegisterCallbackFunction(GPIO_PortNumIndexArr_t PortNumIndexArr,CallbackFunc_t pt_callback){

    EXTI_Callback[PortNumIndexArr]=pt_callback;

    /* insert the required callback function in the pointer to function --> EXTI_Callback[PortNum]  */


}



