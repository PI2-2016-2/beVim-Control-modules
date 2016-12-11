/*
	beVim-CD4015.h

*/

#include <msp430.h>


//Definido para a porta 4 do microcontrolador. 
#define _DATAPIN BIT3         //F2274: PINO 8
#define _CLOCKPIN BIT4        //F2274: PINO 9

#define CPU_F 1000000 

#define DELAY_US(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define DELAY_MS(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

#define OFF 0



void clock(void);
void data(unsigned char bit);
void beVim_set_state(unsigned char state);
void beVim_reset_register_state(void);
void beVim_set_next_state(void);
void beVim_CD4015_configure(void);
