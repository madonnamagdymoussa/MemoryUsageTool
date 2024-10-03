################################# Name of the crossToolChain #############################################################################
CC=arm-none-eabi-
################################# Name of the Micro-controller ###########################################################################
CFLAGS= -mcpu=cortex-m4 -gdwarf-2 -g -O0 -fdebug-prefix-map=$(CURDIR)=.	-ffunction-sections -fdata-sections 
################################# Path of the directory that we need to include ##########################################################
INCS=-I .
################################# External Libraries that are not standard ###############################################################
LIBS = 
################################# Ojects file that we need to link with each other #######################################################
# first line means that ANY file .c in that directory will be placed inside the source --> SRC    
# Second line means that all the .c files in the source will be converted to .o files     
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
##########################################################################################################################################


################################# Ojects file that we need to link with each other #######################################################
# first line tells the linker that ANY file .s in that directory will be placed inside the AS 
# Second line tells the linker that all the .s files in the source will be converted to .o files     
AS = $(wildcard *.s)
ASOBJ = $(AS:.s=.o)
###########################################################################################################################################
project_name = DMA_Project


##################################################### Command for producing the binary file ###############################################
#Target : Dependancies 
all: $(project_name).bin
   @echo "============Build is done============"

 #  %.o:%.s
 # $(CC)as.exe $(CFLAGS) $< -o $@

%.o:%.c   
	$(CC)gcc.exe	-c		$(CFLAGS)	$(INCS)	$<	-o	$@
   
$(project_name).elf: $(OBJ) $(ASOBJ)
	$(CC)ld.exe		 -T 	linker_script.ld	$(LIBS)		$(OBJ)		$(ASOBJ)	-o		$@ -Map=$(project_name).map --cref --print-memory-usage $(LIBS) --gc-sections
		

$(project_name).bin: $(project_name).elf
	$(CC)objcopy.exe	-O		binary		$<		$@

clean_all:
	rm		*.o		*.elf		*.bin

clean:
	rm		*.elf		*.bin
		