#include"../Includes/beVim-uart.h"

//Responsavel pela abertura do USCI em modo Serial.
//TODO: Resolver a incompatibilidade do 16MHZ com a velocidade de 9600bps
void beVim_UART_begin(UartSpeed speed){
	
	#ifdef __MSP430F2274
	//Coloca os pinos desse modelo em modo tx e rx
	P3SEL |= BIT4 + BIT5; //TXD RXD
	P3DIR |= BIT4 + BIT5; // Seta como outputs.
	P3OUT = 0;  //All P3.x reset

	//Coloca a UCA em estado de reset, para configurar as suas portas.
	UCA0CTL1 |= UCSWRST;
	
	// Forca a ter 8 bits por pacote. 
	UCA0CTL0 &= ~BIT4; 

	UCA0CTL1 |= UCSSEL_2; //Obrigatoriamente sera escolhido o SMCLOCK, ja que a implementaçao com cristal é caso a caso.

	//registra o valor de BCSCTL1 em um inteiro
	switch(speed){
		case _9600:
			
				if(BCSCTL1 == CALBC1_1MHZ){
					UCA0BR0 = 0x68;//104
					UCA0BR1 = 0x0;
					UCA0MCTL = UCBRS_1;	
				}
				else if (BCSCTL1 == CALBC1_8MHZ){
					UCA0BR0 = 0x41;//833d
					UCA0BR1 = 0x3;
				    UCA0MCTL = UCBRS_2 + UCBRF_0;	
				}
				else if(BCSCTL1 == CALBC1_12MHZ){
					UCA0BR0 = 0xe2;//1250d
					UCA0BR1 = 0x4;
				    UCA0MCTL = UCBRS_0 + UCBRF_0;	
				}

				else if(BCSCTL1 == CALBC1_16MHZ){
					UCA0BR0 = 0x82;//1666d
					UCA0BR1 = 0x06;
				    UCA0MCTL = UCBRS_6 + UCBRF_0;	
				}	

				else{
					//a implementação default é a de 1MHz
					UCA0BR0 = 0x68;
					UCA0BR1 = 0x0;
					UCA0MCTL = UCBRS_1 + UCBRF_0;

				}
			break;

		case _19200:
			if(BCSCTL1 == CALBC1_1MHZ){
				UCA0BR0 = 0x34;//52d
				UCA0BR1 = 0x0;
				UCA0MCTL = UCBRS_0 + UCBRF_0;	
			}
				
			else if (BCSCTL1 == CALBC1_8MHZ){
				UCA0BR0 = 0xa0;//416d
				UCA0BR1 = 0x1;
			    UCA0MCTL = UCBRS_6 + UCBRF_0;	
			}

			else if(BCSCTL1 == CALBC1_12MHZ){
				UCA0BR0 = 0x71;//625d
				UCA0BR1 = 0x2;
			    UCA0MCTL = UCBRS_0 + UCBRF_0;	
			}

			else if(BCSCTL1 == CALBC1_16MHZ){
				UCA0BR0 = 0x41;//833d
				UCA0BR1 = 0x3;
			    UCA0MCTL = UCBRS_2 + UCBRF_0;	
			}

			else{
				UCA0BR0 = 0x34;//52d
				UCA0BR1 = 0x0;
				UCA0MCTL = UCBRS_0 + UCBRF_0;	
			}
			break;

		case _38400:
			if(BCSCTL1 == CALBC1_1MHZ){
				UCA0BR0 = 0x1a; //26d
				UCA0BR1 = 0x0;
				UCA0MCTL = UCBRS_0 + UCBRF_0;	
			}

			else if (BCSCTL1 == CALBC1_8MHZ){
				UCA0BR0 = 0xd0;//208d
				UCA0BR1 = 0;
			    UCA0MCTL = UCBRS_3 + UCBRF_0;	
			}

			else if(BCSCTL1 == CALBC1_12MHZ){
				UCA0BR0 = 0x38;//312d
				UCA0BR1 = 0x1;
			    UCA0MCTL = UCBRS_4 + UCBRF_0;	
			}

			else if(BCSCTL1 == CALBC1_16MHZ){
				UCA0BR0 = 0xa0;//416d
				UCA0BR1 = 0x1;
			    UCA0MCTL = UCBRS_6 + UCBRF_0;	
			}

			else{
				UCA0BR0 = 0x1a; //26d
				UCA0BR1 = 0x0;
				UCA0MCTL = UCBRS_0 + UCBRF_0;	
			}
	
			break;
		case _56000:
			if(BCSCTL1 == CALBC1_1MHZ){
				UCA0BR0 = 0x11;//17d
				UCA0BR1 = 0x0;
				UCA0MCTL = UCBRS_7 + UCBRF_0;	
			}

			else if (BCSCTL1 == CALBC1_8MHZ){
				UCA0BR0 = 0x8e;//142d
				UCA0BR1 = 0;
			    UCA0MCTL = UCBRS_7 + UCBRF_0;	
			}

			else if(BCSCTL1 == CALBC1_12MHZ){
				UCA0BR0 = 0xd6;//214
				UCA0BR1 = 0x0;
			    UCA0MCTL = UCBRS_2 + UCBRF_0;	
			}

			else if(BCSCTL1 == CALBC1_16MHZ){
				UCA0BR0 = 0x1d;//285
				UCA0BR1 = 0x1;
			    UCA0MCTL = UCBRS_6 + UCBRF_0;	
			}
			else{
				UCA0BR0 = 0x11;//17d
				UCA0BR1 = 0x0;
				UCA0MCTL = UCBRS_7 + UCBRF_0;	
			}

	
			break;
		case _115200:

			if(BCSCTL1 == CALBC1_1MHZ){
				UCA0BR0 = 0x8; // 8d
				UCA0BR1 = 0x0;
				UCA0MCTL = UCBRS_6 + UCBRF_0;	
			}

			else if (BCSCTL1 == CALBC1_8MHZ){
				UCA0BR0 = 0x45; //69d
				UCA0BR1 = 0;
			    UCA0MCTL = UCBRS_4 + UCBRF_0;	
			}

			else if(BCSCTL1 == CALBC1_12MHZ){
				UCA0BR0 = 0x68; //104
				UCA0BR1 = 0x0;
			    UCA0MCTL = UCBRS_1 + UCBRF_0;	
			}

			else if(BCSCTL1 == CALBC1_16MHZ){
				UCA0BR0 = 0x8a; //138
				UCA0BR1 = 0x0;
			    UCA0MCTL = UCBRS_7 + UCBRF_0;	
			}

			else{
				UCA0BR0 = 0x8; // 8d
				UCA0BR1 = 0x0;
				UCA0MCTL = UCBRS_6 + UCBRF_0;	
				
			}
			break;

		case _128000:
			if(BCSCTL1 == CALBC1_1MHZ){
					UCA0BR0 = 0x7; //7d
					UCA0BR1 = 0x0;
				    UCA0MCTL = UCBRS_7 + UCBRF_0;	
					}
			
			else if (BCSCTL1 == CALBC1_8MHZ){
					UCA0BR0 = 0x3e; //62
					UCA0BR1 = 0;
				    UCA0MCTL = UCBRS_4 + UCBRF_0;	
					}

			else if(BCSCTL1 == CALBC1_12MHZ){
					UCA0BR0 = 0x5d; //93
					UCA0BR1 = 0x0;
				    UCA0MCTL = UCBRS_6 + UCBRF_0;	
					}

			else if(BCSCTL1 == CALBC1_16MHZ){
					UCA0BR0 = 125; //125
					UCA0BR1 = 0x0;
				    UCA0MCTL = UCBRS_0 + UCBRF_0;	
					}

			else{
				UCA0BR0 = 0x7;
				UCA0BR1 = 0x0;
				UCA0MCTL = UCBRS_7 + UCBRF_0;
			}
	
			break;

		case _256000:
			if(BCSCTL1 == CALBC1_1MHZ){
					UCA0BR0 = 0x3;
					UCA0BR1 = 0x0;
					UCA0MCTL = UCBRS_7 + UCBRF_0;	
			}

			else if (BCSCTL1 == CALBC1_8MHZ){
					UCA0BR0 = 0x1f;
					UCA0BR1 = 0;
				    UCA0MCTL = UCBRS_2 + UCBRF_0;	
			}

			
			else if(BCSCTL1 == CALBC1_12MHZ){
					UCA0BR0 = 0x2e;
					UCA0BR1 = 0x0;
				    UCA0MCTL = UCBRS_7 + UCBRF_0;	
			}

			else if(BCSCTL1 == CALBC1_16MHZ){
					UCA0BR0 = 0x3e;
					UCA0BR1 = 0x0;
					UCA0MCTL = UCBRS_4 + UCBRF_0;	
			}
			else{
				UCA0BR0 = 0x3;
				UCA0BR1 = 0x0;
				UCA0MCTL = UCBRS_7 + UCBRF_0;	
			}
	
			break;
	
	}

	UCA0CTL1 &= ~UCSWRST; //Initialize USCI state machine
#endif
}

/*
 * putc - Função responsavel pela impressao de um char no console serial.*/
int beVim_putc(char c){

	while(!(IFG2 & UCA0TXIFG));
	UCA0TXBUF = c;


	return c;

}

/*	getc - Responsavel pela captura de um caracter.
 *	Atençao - Nao utilizar em conjunto com interrupçoes de rx
 * */
char beVim_getc(){
	while(!(IFG2 & UCA0RXIFG));
	char c = UCA0RXBUF;	
	return c;
}


int beVim_print(char *c){
	
	int i = 0;

	while( *c != '\0'){
		
		beVim_putc(*c);
		c++;
		i++;
	}
	
	return i;

} 

int beVim_println(char *c){

	int i = 0;

	while( *c != '\0'){
		
		beVim_putc(*c);
		c++;
		i++;
	}
//
		beVim_putc('\n');
		beVim_putc('\r');
	
	return i+2;
} 

char * beVim_gets(){

	char rxChar;
	char *rxString;
	
	char ovf = 0, endDetected =0;
	int charCounter = 0;
	
	//aqui se soma 1 ao MAX_RX_CHAR pois deve-se ter o tamanho oficial da 
	//biblioteca + o espaço de um \0.
	rxString = (char*)malloc((MAX_RX_CHAR+1)*sizeof(char));

	while (!(ovf || endDetected)){
		rxChar = beVim_getc();
		beVim_putc(rxChar);

		charCounter++;

		if(charCounter == MAX_RX_CHAR)
			ovf = 1;

		else if (rxChar == STRING_DELIMITER)
			endDetected = 1;
		
		else{
			rxString[charCounter -1] = rxChar;
		}
		
	}

	if(ovf){
		//Encerra a string com caracter finalizador no último espaço.
		//Lembrando: A função foi mallocada com MAX_RX_CHAR+1, isto é
		//Pode assumir até MAX_RX_CHAR caracteres sem SIGSEGV
		rxString[MAX_RX_CHAR] = '\0';
	}
	else if (endDetected){
		//Encerra a string com um caracter finalizador
		//no primeiro espaço vago da string. No caso,
		rxString[charCounter] = '\0';
	}


	return rxString;
	
}

