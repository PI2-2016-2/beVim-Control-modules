/*
 * Uart.c
 *
 * Implements UART in bevim.
 * */

#include "msp430.h"
#include "../../Includes/beVim-clock-manager.h"
#include "../../Includes/beVim-uart.h"
#include "../../Includes/beVim-gpios.h"

//Descomente a linha a seguir para entrar em modo de interrupção
//#define INTERRUPT_MODE

volatile char charIsCorrect = 0;

//Se for pela interrupção, o rxString é preenchido pela lib
//Senao, deve ser preenchido pelas interrupooes do usuario.
#ifndef INTERRUPT_MODE
	char *rxString;
#else
	volatile char charCounter = 0;
	volatile char EOL = 0;
	char rxChar;
	char rxString[MAX_RX_CHAR];
#endif

int main(void){

	WDTCTL = WDTPW + WDTHOLD;
	
       //Inicializa os LEDs para o envio / recepçao de dados.	
	setDirection(1,0,output);
	setOutput(1,0,high);
	setDirection(1,1,output);
	setOutput(1,1,high);
	
	//Inicializa o clock para MCLK e SMCLK e DCO
	beVim_Clock_Config(DCOCLK, _1MHZ);
	beVim_Mclk_Source(DCOCLK, 1);
	beVim_SMclk_Source(DCOCLK,1);
	
	//Inicializa USCIA0 em modo UART
	beVim_UART_begin(_9600);
	
	#ifdef INTERRUPT_MODE
	IE2 |= UCA0RXIE;
	#endif

	beVim_println("Enviar uma string terminada com '\n' para o terminal. de ate 50 chars.");
	
	__bis_SR_register(GIE); // Enter LPM3 w/ int until Byte RXed
	
	while(1){
		
	//	if(charIsCorrect){
		
#ifndef INTERRUPT_MODE
		charIsCorrect = 0;
		rxString = beVim_gets();
		beVim_println(rxString);
		toggleOutput(1,0);
		free(rxString);	
		
#else
		if(EOL){
			EOL = 0;
			beVim_println(rxString);
			toggleOutput(1,0);
		}
#endif
				
	}	
		
}
#ifdef INTERRUPT_MODE
void __interrupt(USCIAB0RX_VECTOR) rx_ISR(void){
	
	charCounter++;
	rxChar = UCA0RXBUF;
	
	if(charCounter < MAX_RX_CHAR){
		if( rxChar == '\n'){
			rxString[charCounter-1] = '\0';

			EOL = 1;
			charCounter = 0;	
		}
		else{
			rxString[charCounter-1] = rxChar;
		}
	}
	else{
		rxString[MAX_RX_CHAR -1] = '\0';
		EOL = 1;
		charCounter = 0;
	}
}

void __interrupt(USCIAB0TX_VECTOR) tx_ISR(void){
	

}
#endif
