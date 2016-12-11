/*
	beVim-CD4015.c

*/
#include "../Includes/beVim-CD4015.h"

unsigned char currentState;
void clock(void){

	//Essa funcao gera uma borda de subida no pino selecionado
	
	if(P4OUT & _CLOCKPIN){

		//CLOCK ESTA EM HIGH SE ENTRAR NESSA CONDICAO

		//Reseta pino.
		P4OUT &= ~_CLOCKPIN;

		DELAY_US(500);
	}

	//clock em high
	P4OUT |= _CLOCKPIN;
}

void data(unsigned char bit){

	//Essa funcao gera um sinal 1 ou zero no pino de data.

	if(bit){

		P4OUT |= _DATAPIN;
	}
	else
		P4OUT &= ~_DATAPIN;
}

void beVim_set_state(unsigned char state){

	//Byte order CBA(lsb)
	unsigned char byteA = state & 0x01; //captura o primeiro bit
	unsigned char byteB = (state & 0x02)>>1; //captura o segundo bit
	unsigned char byteC = (state & 0x04)>>2; //captura o terceiro bit

	data(byteC);
	clock();
	data(byteB);
	clock();
	data(byteA);
	clock();

	currentState = state;
}

void beVim_reset_register_State(void){

	//Reseta o estado atual.
	data(OFF);
	clock();
	clock();
	clock();
	clock();

	currentState=0;
}

void beVim_set_next_state(void){

	unsigned char nextState;
	
	nextState = currentState+1;

	if(currentState > 7)
		nextState = 0;

	beVim_set_state(nextState);
}

void beVim_CD4015_configure(void){

	P4DIR |= _DATAPIN;
	P4DIR |= _CLOCKPIN;
        
        beVim_reset_register_State();
}