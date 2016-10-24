/*
	beVim UART.h

	Author: Pedro Inazawa

	this library implements an interface to use UART in MSP430 devices
*/

#include <msp430.h>
#include <stdlib.h>
//Quantidade maxima de caracteres que pode ser recebida
#define MAX_RX_CHAR 50

//Delimitador de strings a serem recebidas.
#define STRING_DELIMITER '\n'

#ifdef __MSP430F2274
/*
 * Valores de velocidades suportados pela biblioteca até o momento.
 * */
typedef enum uartspeed{
	_9600	 = 0,
	_19200   = 1,
	_38400   = 2,
	_56000   = 3,
	_115200  = 4,
	_128000	 = 5,
	_256000  = 6

}UartSpeed;
#endif


/*
 * @name: UART Begin
 * @brief: Configura o MSP430 para UART na Baud desejada. Esta implementação privilegia osciladores internos, então não há possibilidade de utilizae o ACLK com cristal externo (e o ACLK com VLO é muito lento para qualquer implementação de baud relevante)
			Suporta as seguintes velocidades: 9600 19200 38400 56000 115200 128000 256000
 */

void beVim_UART_begin(UartSpeed speed);

/*
 * @name: UART putch (VERSAO BLOCANTE)
 * @brief : Envia apenas um char para o buffer de transmissão do MSP430. 
 * @param c: byte a ser enviado.
 */
int beVim_putc( char c);

/*@name: UART print (VERSAO BLOCANTE)
 * @brief: Função responsavel por imprimir na serial uma string completa. 
 * @param c: Endereço do primeiro item da string.
 * */
int beVim_print(char *c);

/*@name: UART println (VERSAO BLOCANTE)
 * @brief: Função responsavel por imprimir na serial uma string completa. Esta função acrescenta um \n\r ao final da string.
 * @param c: Endereço do primeiro item da string.
 * */
int beVim_println(char *c);

/* @name: UART getchar (VERSAO BLOCANTE)
 *
 * @brief: Função responsável pela captura de um dado da porta serial. Esta função
 * aguarda o dado estar disponível e depois retorna o caracter obtido
 *
 * @return: Caracter Recebido
 *
 * */
char beVim_getc();

/**
 * @name: UART gets()  (VERSAO BLOCANTE)
 * @brief: Captura uma string de tamanho maximo MAX_RX_CHAR da UART.
 * @return: Ponteiro para a string capturada. 
 */

char *beVim_gets();
