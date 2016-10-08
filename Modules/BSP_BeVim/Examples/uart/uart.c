/*
 * Uart.c
 *
 * Implements UART in bevim.
 * */

#include"msp430.h"
#include "../../Includes/beVim-clock-manager.h"

#define TXLED BIT0
#define RXLED BIT6
#define TXD BIT2
#define RXD BIT1

char msg[] = "Good Vibes\n";
unsigned int i;


void main(void){

	int i = 0;
	WDTCTL = WDTPW + WDTHOLD;
	
	P1DIR = 0xFF; //All P1.x outputs
	P1OUT = 0;   // All P1.X reset


	P2DIR = 0xFF;  //All p2.x outputs
	P2OUT = 0; // All P2.x reset
	
	P3SEL = 0x30; // P3.4,5= USCI_A0 TXD/RXD
	P3DIR = 0xFF; // All P3.x outputs
	
	P3OUT = 0;  //All P3.x reset
	P4DIR = 0xFF; // All P4.x Outputs
	
	P4OUT  = 0;
	
	//CONFIGURANDO O CLOCK
//	BCSCTL1 = CALBC1_1MHZ;
//	DCOCTL = CALDCO_1MHZ;

	beVim_Clock_Config(DCOCLK, _1MHZ);
	beVim_Mclk_Source(DCOCLK, 1);
	beVim_SMclk_Source(DCOCLK,1);

	UCA0CTL1 |= UCSWRST;
	UCA0CTL1 |= UCSSEL_2; //clk = SMCLK
	
	UCA0BR0 = 104; // tabela da pagina 424 do MSP430x2xx User's guide.
	UCA0BR1 = 0x00;

	UCA0MCTL = UCBRF_1 + UCBRS_0; //Modulation ucbrsx = 3;

	UCA0CTL1 &= ~UCSWRST; //Initialize USCI state machine

	IE2 |= UCA0RXIE;

	__bis_SR_register(LPM3_bits+GIE); // Enter LPM3 w/ int until Byte RXed
	while(1){
	//	i = 0;
	//	UCA0TXBUF = 'a';
	//	for(i = 0; i<0x600;i++);
	}	
		
}

//#pragma vector=USCIAB0RX_VECTOR
//__interrupt void USCI0RX_ISR(void){
void __interrupt(USCIAB0RX_VECTOR) rx_ISR(void){
	
	if(UCA0RXBUF == 'a'){
		i = 0;
		UC0IE |= UCA0TXIE;
		UCA0TXBUF = msg[i++];
	}

}

//#pragma vector=USCIAB0TX_VECTOR
//__interrupt void USCI0TX_ISR(void){
void __interrupt(USCIAB0TX_VECTOR) tx_ISR(void){
	
	UCA0TXBUF = msg[i++]; //tx next character
	if (i == sizeof(msg) -1)
		UC0IE &= ~UCA0TXIE;
	
	P1OUT |= BIT0;

}
