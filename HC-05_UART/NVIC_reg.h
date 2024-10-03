
#ifndef NVIC_REG_H_
#define NVIC_REG_H_


#include"lstd.h"

#define NVIC_BaseAddress  0xE000E000


typedef struct{

    u32_t   :8;
    u32_t PRIGROUP :3;
    u32_t   :4;
    u32_t ENDIANES :1;
    u32_t VECTKEY  :16;


}APINT_bits;

typedef struct{

    u32_t Res :5;
    u32_t INTA :3;
    u32_t  res :5;
    u32_t INTB :3;
    u32_t  :5;
    u32_t INTC :3;
    u32_t  :5;
    u32_t INTD :3;
}PRI_bits;


#define NVIC_PRI0_REG       ((volatile PRI_bits*) (NVIC_BaseAddress+0x400))
#define NVIC_PRI1_REG       ((volatile PRI_bits*) (NVIC_BaseAddress+0x404))
#define NVIC_PRI2_REG       ((volatile PRI_bits*) (NVIC_BaseAddress+0x408))
#define NVIC_PRI3_REG       ((volatile PRI_bits*) (NVIC_BaseAddress+0x40C))
#define NVIC_PRI4_REG       ((volatile PRI_bits*) (NVIC_BaseAddress+0x410))
#define NVIC_PRI5_REG       ((volatile PRI_bits*) (NVIC_BaseAddress+0x414))
#define NVIC_PRI6_REG       ((volatile PRI_bits*) (NVIC_BaseAddress+0x418))
#define NVIC_PRI7_REG       ((volatile PRI_bits*) (NVIC_BaseAddress+0x41C))

#define NVIC_APINT_REG      (*(volatile APINT_bits*) (NVIC_BaseAddress+0xD0C))

#define NVIC_SET_ENABLE0    ((volatile u32_t*) 0xE000E100) //0xE000E100
#define NVIC_SET_ENABLE1    ((volatile u32_t*) (NVIC_BaseAddress+ 0x104))
#define NVIC_SET_ENABLE2    ((volatile u32_t*) (NVIC_BaseAddress+ 0x108))
#define NVIC_SET_ENABLE3    ((volatile u32_t*) (NVIC_BaseAddress+ 0x10C))

#define NVIC_CLEAR_ENABLE0   ((volatile u32_t*)(NVIC_BaseAddress+ 0x180) )
#define NVIC_CLEAR_ENABLE1   ((volatile u32_t*)(NVIC_BaseAddress+ 0x184) )
#define NVIC_CLEAR_ENABLE2   ((volatile u32_t*)(NVIC_BaseAddress+ 0x188) )
#define NVIC_CLEAR_ENABLE3   ((volatile u32_t*)(NVIC_BaseAddress+ 0x18C) )

#define NVIC_SET_PENDING0    ((volatile u32_t*)(NVIC_BaseAddress+ 0x200) )
#define NVIC_SET_PENDING1    ((volatile u32_t*)(NVIC_BaseAddress+ 0x204) )
#define NVIC_SET_PENDING2    ((volatile u32_t*)(NVIC_BaseAddress+ 0x208) )
#define NVIC_SET_PENDING3    ((volatile u32_t*)(NVIC_BaseAddress+ 0x20C) )

#define NVIC_CLEAR_PENDING0  ((volatile u32_t*)(NVIC_BaseAddress+ 0x280) )
#define NVIC_CLEAR_PENDING1  ((volatile u32_t*)(NVIC_BaseAddress+ 0x284) )
#define NVIC_CLEAR_PENDING2  ((volatile u32_t*)(NVIC_BaseAddress+ 0x288) )
#define NVIC_CLEAR_PENDING3  ((volatile u32_t*)(NVIC_BaseAddress+ 0x28C) )



#endif /* NVIC_REG_H_ */
