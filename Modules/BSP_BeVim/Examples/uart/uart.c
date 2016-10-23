/*
 * Uart.c
 *
 * Implements UART in bevim.
 * */

#include"msp430.h"
#include "../../Includes/beVim-clock-manager.h"
#include "../../Includes/beVim-uart.h"
#include "../../Includes/beVim-gpios.h"

char charIsCorrect = 0;

void main(void){

	WDTCTL = WDTPW + WDTHOLD;

	setDirection(1,0,output);
	setOutput(1,0,high);
	setDirection(1,1,output);
	setOutput(1,1,high);
	

	beVim_Clock_Config(DCOCLK, _1MHZ);
	beVim_Mclk_Source(DCOCLK, 1);
	beVim_SMclk_Source(DCOCLK,1);

	beVim_UART_begin(_9600);
	IE2 |= UCA0RXIE;

	beVim_println("Enviar um 'a'  para o terminal.");

	__bis_SR_register(GIE); // Enter LPM3 w/ int until Byte RXed
	while(1){
		
		if(charIsCorrect){
			charIsCorrect = 0;
			beVim_println("CaracterCorreto");
			toggleOutput(1,0);
		}

			
	}	
		
}

void __interrupt(USCIAB0RX_VECTOR) rx_ISR(void){
	
	if(UCA0RXBUF == 'a'){
		charIsCorrect = 1;
	}

}

void __interrupt(USCIAB0TX_VECTOR) tx_ISR(void){
	

}
