/*************************************************************************************************************************************/
/* Name: Interrupt_driver.c                                                                                                                    */
/* Author: Madonna Magdy                                                                                                            */
/* Version: V1                                                                                                                      */
/* Usage: This module contains the implementation for the interrupt functions                                                       */
/*************************************************************************************************************************************/

/********************************************  Includes  ***************************************************************************/
#include "NVIC_reg.h"
#include "lstd.h"
#include "NVIC_config.h"
#include "NVIC.h"



 /**************************************************************************************************************/
 /* creating an array of pointers to registers
  * the user (or the application layer) will not be allowed to have access to the hardware registers
  * because it's not his/her concern
  * he/she will only be allowed to call the interfacing functions in the timer.h file
  * for that reason a keyword static will be added*/
 /**************************************************************************************************************/
 volatile u32_t static* const Interrupt_Enable_Registers[4] ={

      (u32_t*)NVIC_SET_ENABLE0,
      (u32_t*)NVIC_SET_ENABLE1,
      (u32_t*)NVIC_SET_ENABLE2,
      (u32_t*)NVIC_SET_ENABLE3

 };
 /**************************************************************************************************************/
 /* creating an array of pointers to registers
  * the user (or the application layer) will not be allowed to have access to the hardware registers
  * because it's not his/her concern
  * he/she will only be allowed to call the interfacing functions in the timer.h file
  * for that reason a keyword static will be added*/
 /**************************************************************************************************************/
 volatile u32_t static* const Interrupt_Clear_Registers[4] ={

        (NVIC_CLEAR_ENABLE0),
        (NVIC_CLEAR_ENABLE1),
        (NVIC_CLEAR_ENABLE2),
        (NVIC_CLEAR_ENABLE3)

 };

 /**************************************************************************************************************/
 /* creating an array of pointers to registers
  * the user (or the application layer) will not be allowed to have access to the hardware registers
  * because it's not his/her concern
  * he/she will only be allowed to call the interfacing functions in the timer.h file
  * for that reason a keyword static will be added*/
 /**************************************************************************************************************/
 volatile u32_t static *const Set_Pending_Register[4]={
     (NVIC_SET_PENDING0),
     (NVIC_SET_PENDING1),
     (NVIC_SET_PENDING2),
     (NVIC_SET_PENDING3)

 };

 /**************************************************************************************************************/
 /* creating an array of pointers to registers
  * the user (or the application layer) will not be allowed to have access to the hardware registers
  * because it's not his/her concern
  * he/she will only be allowed to call the interfacing functions in the timer.h file
  * for that reason a keyword static will be added*/
 /**************************************************************************************************************/
 volatile u32_t static *const Clear_Pending_Register[4]={
    NVIC_CLEAR_PENDING0,
    NVIC_CLEAR_PENDING1,
    NVIC_CLEAR_PENDING2,
    NVIC_CLEAR_PENDING3

 };

 /**************************************************************************************************************/
 /* creating an array of pointers to registers
  * the user (or the application layer) will not be allowed to have access to the hardware registers
  * because it's not his/her concern
  * he/she will only be allowed to call the interfacing functions in the timer.h file
  * for that reason a keyword static will be added*/
 /**************************************************************************************************************/
   volatile PRI_bits static *const Interrupt_Priority_Register[8]={
   (NVIC_PRI0_REG),
   (NVIC_PRI1_REG),
   (NVIC_PRI2_REG),
   (NVIC_PRI3_REG),
   (NVIC_PRI4_REG),
   (NVIC_PRI5_REG),
   (NVIC_PRI6_REG),
   (NVIC_PRI7_REG)

 };


/**************************************************************************************************************/
void NVIC_Enable_Interrupt(u32_t au32_InterruptNum){

    u8_t au8_RegNum=(u8_t)(au32_InterruptNum/32);  /* To get the register num (EN0, EN1, ... etc) it will be equivalent to the quotient remainder  equation */
                                            /*  InterruptNum = (32 x register number) + bit number */
                                           /*   InterruptNum = (32 x quotient )       + remainder  */

    u8_t au8_BitNum =  (u8_t) (au32_InterruptNum - (32*au8_RegNum));

    *Interrupt_Enable_Registers[au8_RegNum]|=(1<<au8_BitNum);

 }

/**************************************************************************************************************/
void NVIC_Clear_Interrupt(u32_t au32_InterruptNum){

    u8_t au8_RegNum=(u8_t)(au32_InterruptNum/32);  /* To get the register num (EN0, EN1, ... etc) it will be equivalent to the quotient remainder equation */
                                            /*  InterruptNum = (32 x register number) + bit number */
                                           /*   InterruptNum = (32 x quotient )       + remainder  */

    u8_t au8_BitNum = (u8_t)(au32_InterruptNum - (32*au8_RegNum));

    *Interrupt_Clear_Registers[au8_RegNum] &= ~(1<<au8_BitNum);



 }

/**************************************************************************************************************/
void NVIC_Set_Pending(u32_t au32_InterruptNum){

    u8_t au8_RegNum=(u8_t)(au32_InterruptNum/32);  /* To get the register num (EN0, EN1, ... etc) it will be equivalent to the quotient remainder  equation */
                                            /*  InterruptNum = (32 x register number) + bit number */
                                           /*   InterruptNum = (32 x quotient )       + remainder  */

    u8_t au8_BitNum = (u8_t)(au32_InterruptNum - (32*au8_RegNum));

    *Set_Pending_Register[au8_RegNum]|=(1<<au8_BitNum);



 }

/**************************************************************************************************************/
void NVIC_Clear_Pending(u32_t au32_InterruptNum){

    u8_t au8_RegNum=(u8_t)(au32_InterruptNum/32);  /* To get the register num (EN0, EN1, ... etc) it will be equivalent to the quotient remainder equation */
                                            /*  InterruptNum = (32 x register number) + bit number */
                                           /*   InterruptNum = (32 x quotient )       + remainder  */

    u8_t au8_BitNum =(u8_t)( au32_InterruptNum - (32*au8_RegNum) );

    *Clear_Pending_Register[au8_RegNum] &= ~(1<<au8_BitNum);



 }
/**************************************************************************************************************/

void NVIC_SetPriorityGrouping(PRIGROUP_bits priorityGroup){

    NVIC_APINT_REG.VECTKEY=0x05FA;

    NVIC_APINT_REG.PRIGROUP=priorityGroup;

}

/**************************************************************************************************************/
void NVIC_AssignPriority(NVIC_PriorityGroupSet_t GroupPriority, NVIC_SubPriorityGroupSet_t SubPriority , u8_t ID){

    u8_t RegNum;
    RegNum= (u8_t)(ID/4); // ----> Equation to the number of the priority register




    if( ID == RegNum*4){
    (*Interrupt_Priority_Register[RegNum]).INTA |= (GroupPriority|SubPriority);

    }

    else  if(ID == RegNum*4 +1){
        (*Interrupt_Priority_Register[RegNum]).INTB |= (GroupPriority|SubPriority);

    }

    else if(ID == RegNum*4 +2){
        (*Interrupt_Priority_Register[RegNum]).INTC |= (GroupPriority|SubPriority);

    }

    else if (ID == RegNum*4 +3){
        (*Interrupt_Priority_Register[RegNum]).INTD |= (GroupPriority|SubPriority);

    }



}






