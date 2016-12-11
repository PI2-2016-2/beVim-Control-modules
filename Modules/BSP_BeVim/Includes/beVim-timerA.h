#include "msp430.h"	

#ifndef _BEVIM_TA
#define _BEVIM_TA


typedef enum {
	stop 			= 0,
	countUp 		= 1, // conta até CCR0. zera, conta novamente
	countUpDown 		= 2, // Conta ate CCR0, volta até 0000
	countContinuous 	= 3 // Conta até FFFF, zera, conta novamente
} TACountingMode;

typedef enum{
	_TACLK 			= 0,
	_ACLK  			= 1,
	_SMCLK 			= 2,
	_INCLK 			= 3
} TAClockSources;

typedef enum {
	
	ModeSet 		= 0,
	ModeToggleReset 	= 1,
	ModeSetReset 		= 2,
	ModeToggle 		= 4,
	ModeReset 		= 5,
	ModeToggleSet		= 6,
	ModeResetSet		= 7

}OutputModeSet;

typedef enum {
	_overflow 		= 0,
	_ccr0			= 1,
	_ccr1			= 2,
	_ccr2			= 3	
} TAInterruptTypes;

//Stops and resets the timerA;
void beVim_TA_reset();

//Divider should only be 2,4,8,10
void beVim_TA_configure(TAClockSources clockSource, char divider, TACountingMode countingMode);

//Only works in upDown and up modeee
void beVim_TA_CountUpTo(int LSB);

void beVim_TA_OutputMode(char pin, OutputModeSet outputMode);

void beVim_TA_Enable_CCR0_Interrupt();
void beVim_TA_Disable_CCR0_Interrupt();

void beVim_TA_Enable_CCR1_Interrupt();
void beVim_TA_Disable_CCR1_Interrupt();

void beVim_TA_Enable_CCR2_Interrupt();
void beVim_TA_Disable_CCR2_Interrupt();


/*Essa função funciona para ligar a interrupção por OVERFLOW do timer A 
(Utilizada quando a forma de contagem é por meio do MODO CONTÍNUO. */
void beVim_TA_Enable_OVF_Interrupt();

/*Essa função funciona para desligar a interrupção por OVERFLOW do timer A 
(Utilizada quando a forma de contagem é por meio do MODO CONTÍNUO. */
void beVim_TA_Disable_OVF_Interrupt();

int beVim_TA_CurrentCount();

void beVim_TA_CCR1_CountUpTo(int LSB);

void beVim_TA_CCR2_CountUpTo(int LSB);

void beVim_Register_Callback(void (*func)(),TAInterruptTypes type);


#endif