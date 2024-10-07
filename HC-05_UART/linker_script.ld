MEMORY{
 flash(RX) : ORIGIN = 0x00000000, LENGTH = 512M 
 sram(RWX) : ORIGIN = 0x20000000, LENGTH = 512M

}


SECTIONS{

    .vectors : {
        KEEP(*(.vectors*))
        _E_vectors = .;  
    } > flash

    .text : {
        *(.text*)
        _E_text = .;  
    } > flash

    .rodata : {
        KEEP(*(.rodata*))
    } > flash
   
   .data : {

   _S_DATA = . ;
   KEEP(*(.data)) 
   . = ALIGN(0x4);
   _E_DATA = . ;
   
   }>sram AT> flash

 .bss : {
 _S_BSS = . ;
 KEEP(*(.bss*)) 
 _E_BSS = . ;
 
 }>sram
 
 }