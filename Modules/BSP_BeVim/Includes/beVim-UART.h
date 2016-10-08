/*
	beVim UART.h

	Author: Pedro Inazawa

	this library implements an interface to use UART in MSP430 devices
*/


void beVim_UART_begin(int speed);
void beVim_UART_begin(int speed){

	//Coloca a UCA em estado de reset, para configurar as suas portas.
	UCACTL1 |= UCSWRST;

		
}