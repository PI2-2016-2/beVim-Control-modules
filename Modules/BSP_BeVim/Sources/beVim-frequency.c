/*
 * beVim-Frequency.c
 *
 * Autor: Pedro Inazawa
 *
 * */
#include "../Includes/beVim-frequency.h"

unsigned char beVim_calcula_Freq(unsigned char *ts_picoA,unsigned char *ts_picoB){
	
	unsigned long int tsDiff = _diferencaTriByteModule(ts_picoA, ts_picoB);

	unsigned char freq;

	//O valor da diferenca esta em ms daqui em diante.
	tsDiff = tsDiff * TS_RESOLUTION_IN_MS;

	//O valor da frequencia será calculado como 1000/tsDiff
	//pois como f = 1/T e T é dado em ms , isto é, 1/1000 s, 
	//podemos converter para f = 1000/T
	freq = (unsigned char)(1000/tsDiff);

	return freq;
}

unsigned long int _diferencaTriByteModule(unsigned char *ts_picoA, unsigned char *ts_picoB){
	//Esta lib foi feita para operar com ts_pico sendo de 3 bytes. a variável mais
	//segura de se trabalhar foi a unsigned long int, de 4 bytes.
	//
	//Observar que sempre o MSB vem nos bytes mais a esquerda no MSP430.	
	unsigned long int valA    = 0;
	unsigned long int valB    = 0;
	unsigned long int tempVar = 0;
	
	tempVar = (unsigned long int)ts_picoA[2];
	valA += ts_picoA[2];
	tempVar = (unsigned long int)ts_picoA[1];
	valA += (tempVar<< 8) & 0x0000ff00;
	tempVar = (unsigned long int)ts_picoA[0];
	valA += (tempVar << 16) & 0x00ff0000;

	tempVar = (unsigned long int)ts_picoB[2];
	valB += ts_picoB[2];
	tempVar = (unsigned long int)ts_picoB[1];
	valB += (tempVar<< 8) & 0x0000ff00;
	tempVar = (unsigned long int)ts_picoB[0];
	valB += (tempVar << 16) & 0x00ff0000;

	if(valA > valB)
		return valA - valB;
	else
		return valB - valA;
}
