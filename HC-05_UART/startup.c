
/*@Eng Madonna Magdy*/ 
/*File name : startup.s*/


#include <stdint.h>

extern int main(void);
 
void Reset_Handler();

void Default_Handler(){

Reset_Handler();

}




void NMI_Handler() __attribute__((weak, alias("Default_Handler")));;
void H_fault_Handler()__attribute__((weak, alias("Default_Handler")));;
void MM_fault_Handler()__attribute__((weak, alias("Default_Handler")));;
void Bus_Fault()__attribute__((weak, alias("Default_Handler")));;
void Usage_Fault_Handler()__attribute__((weak, alias("Default_Handler")));;

static unsigned long Stack_top[256]; 
 
 
void (*const gp_fn_vectors[])() __attribute__((section(".vectors")))  = {

	(void (*) ())((unsigned long)&Stack_top + sizeof(Stack_top)),

    &Reset_Handler, 
    &NMI_Handler,
   &H_fault_Handler,
   &MM_fault_Handler,
   &Bus_Fault,
   &Usage_Fault_Handler

};


extern unsigned int _E_text ;
extern unsigned int _S_DATA ;
extern unsigned int _E_DATA ;
extern unsigned int _S_BSS ;
extern unsigned int _E_BSS ;


void Reset_Handler (){

unsigned int DATA_size = (unsigned char *)&_E_DATA - (unsigned char *)&_S_DATA ;
unsigned int BSS_size = (unsigned char *)&_S_BSS - (unsigned char *)&_E_BSS ;


unsigned char* p_src = (unsigned char*)&_E_text;
unsigned char* p_dst = (unsigned char*)&_S_DATA;

for (int i =0 ; i<DATA_size ; i++){
	
	*((unsigned char *)p_dst++) = *((unsigned char*) p_dst++); 
}
 
for (int i=0 ; i<BSS_size ; i++){
	
	*((unsigned char *)p_dst++) = (unsigned char)0;
	
}


 main();

}