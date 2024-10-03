
#ifndef NVIC_CONFIG_H_
#define NVIC_CONFIG_H_

/*************************************************************************/
/*                           MACROS                                      */
/*************************************************************************/
#define UART0_InterruptNum   (5)
#define UART1_InterruptNum   (6)



/*************************************************************************/
/*                           ENUM                                        */
/*************************************************************************/
typedef enum{

    GroupPriority8_Sub1 = 0x4,
    GroupPriority4_Sub2 = 0x5,
    GroupPriority2_Sub4 = 0x6,
    GroupPriority1_Sub8 = 0x7


} PRIGROUP_bits;

typedef enum{

    GroupPriority0,
    GroupPriority1,
    GroupPriority2,
    GroupPriority3,
    GroupPriority4,
    GroupPriority5,
    GroupPriority6,
    GroupPriority7,
    GroupPriority8

}NVIC_PriorityGroupSet_t;

typedef enum{

    SubGroupPriority0,
    SubGroupPriority1,
    SubGroupPriority2,
    SubGroupPriority3,
    SubGroupPriority4,
    SubGroupPriority5,
    SubGroupPriority6,
    SubGroupPriority7,
    SubGroupPriority8


}NVIC_SubPriorityGroupSet_t;




#endif /* NVIC_CONFIG_H_ */
