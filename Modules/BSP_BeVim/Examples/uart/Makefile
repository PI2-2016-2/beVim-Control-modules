GCC_DIR = /home/inazawa/ti/gcc/bin/
SUPPORT_FILE_DIRECTORY = ../../Includes
SUPPORT_FILE_DIRECTORY := ~/ti/gcc/include
MY_PROJECT_C_FILES = $(wildcard ./*.c)
OBJECTS = ${MY_PROJECT_C_FILES:.c=.o}


DEVICE  = msp430f2274
CC      = $(GCC_DIR)/msp430-elf-gcc
GDB     = $(GCC_DIR)/msp430-elf-gdb

CFLAGS = -I $(SUPPORT_FILE_DIRECTORY) -mmcu=$(DEVICE) -O0 -g3 -gdwarf-2 -ggdb
LFLAGS = -L $(SUPPORT_FILE_DIRECTORY)

all: Compile_App
	@echo COMPILANDO TUDO JUNTO....
	cp -R ../../Libs ./Libs
	cp ${OBJECTS} ./Libs/
	$(CC) $(CFLAGS) $(LFLAGS) -o CompiledApp.out ./Libs/*.o 

install: 
	mspdebug rf2500 "read prog_script"

Compile_App:${OBJECTS}
	@echo COMPILANDO O APLICATIVO...... 
	$(CC) $(CFLAGS) $(LFLAGS) -c ${MY_PROJECT_C_FILES}

debug: all
	$(GDB) $(DEVICE).out

clean: 
	@rm -R ./Libs
	@rm CompiledApp.out ${OBJECTS}
