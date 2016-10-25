
#Diretorio onde estao os compiladores e os arrquivos da biblioteca.
GCC_DIR =  /home/inazawa/ti/gcc/bin
SUPPORT_FILE_DIRECTORY = /home/inazawa/ti/gcc/include
SOURCE_DIR = /home/inazawa/Documents/pi2/beVim-Control-modules/Modules/BSP_BeVim/Sources

HEADER_DIR = /home/inazawa/Documents/pi2/beVim-Control-modules/Modules/BSP_BeVim/Includes

DEVICE  = msp430f2274
CC      = $(GCC_DIR)/msp430-elf-gcc
GDB     = $(GCC_DIR)/msp430-elf-gdb


MODULES_TO_BE_COMPILED= $(wildcard /home/inazawa/Documents/pi2/beVim-Control-modules/Modules/BSP_BeVim/Sources/*.c)
OBJECTS= ${MODULES_TO_BE_COMPILED:.c=.o}

#A diretiva -I inclui locais onde procurar os headers do projeto de forma mais crítica.
#a diretiva -L inclui de maneira mais aberta esse dado.

CFLAGS = -I $(SUPPORT_FILE_DIRECTORY) -mmcu=$(DEVICE) -Wall -O0 -g3 -gdwarf-2 -ggdb
LFLAGS = -L $(SUPPORT_FILE_DIRECTORY) -L $(HEADER_DIR) 

all: Compile_Lib
	cp ${OBJECTS} ./Libs
	@rm ./*.o	
	@echo ${OBJECTS}
	@echo Biblioteca compilada com sucesso!!


Compile_Lib: ${OBJECTS} 
	$(CC) $(CFLAGS) $(LFLAGS) -c ${MODULES_TO_BE_COMPILED} 

debug: all
	$(GDB) $(DEVICE).out

clean:
	-@rm ./Libs/*.o
	-@rm ./Sources/*.o
	@echo All Cleaned Up. 	
