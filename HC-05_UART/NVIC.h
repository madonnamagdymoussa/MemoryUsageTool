#ifndef NVIC_H_
#define NVIC_H_

#include "lstd.h"
#include"NVIC_config.h"
void NVIC_Enable_Interrupt(u32_t au32_InterruptNum);
void NVIC_Clear_Interrupt(u32_t au32_InterruptNum);
void NVIC_Set_Pending(u32_t au32_InterruptNum);
void NVIC_Clear_Pending(u32_t au32_InterruptNum);
void NVIC_AssignPriority(NVIC_PriorityGroupSet_t GroupPriority, NVIC_SubPriorityGroupSet_t SubPriority , u8_t ID);
void NVIC_SetPriorityGrouping(PRIGROUP_bits priorityGroup);


#endif
