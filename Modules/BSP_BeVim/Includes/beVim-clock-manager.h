/*
	beVim-clock-manager.h

	Author: Pedro Henrique Gonçalves Inazawa

	Implementa o controle de CLOCK no MSP430. 

	Importante observar que só há controle de parametros relacionados
	ao DCO e ao VLO. O restante é próprio de cada aplicação nessa versão
	da biblioteca, e deve ser setado num nível superior ao desta lib.

*/

#include <msp430.h> 

#ifdef __MSP430F2274
typedef enum cs{
	
	LFXT1CLK = 0,
	XT2CLK   = 1,
	DCOCLK   = 2,
	VLOCLK   = 3

}ClockSources;

typedef enum ct{
	MCLK = 0,
	SMCLK = 1,
	ACLK = 2
}ClockType;

typedef enum cspeed{

	_1MHZ     = 1,
	_8MHZ     = 8,
	_12MHZ    = 12,
	_16MHZ    = 16

}ClockSpeed;

#endif

/**
	@name: MCLK SOURCE
	@brief: Essa função escolhe de qual fonte nativa de clock o MSP430
	deve retirar o seu MASTER clock. 

	@param source: É a fonte nativa de clk do dispositivo.
	@param divider: É o divisor que deve ser colocado. Só 
	funciona para valores típicos 1, 2, 4, 8. Default: 1; 

*/
void beVim_Mclk_Source(ClockSources source, int divider);



/**
	@name: SMCLK SOURCE
	@brief: Essa função escolhe de qual fonte nativa de clock o MSP430
	deve retirar o seu SUBMASTER clock. 

	@param source: É a fonte nativa de clk do dispositivo.
	@param divider: É o divisor que deve ser colocado. Só 
	funciona para valores típicos 1, 2, 4, 8. Default: 1; 

*/
void beVim_SMclk_Source(ClockSources source, int divider);



/**
	@name: ACLK SOURCE
	@brief: Essa função escolhe de qual fonte nativa de clock o MSP430
	deve retirar o seu AUXILIARY clock. 

	@param source: É a fonte nativa de clk do dispositivo. Neste caso, o
	dispositivo poderia assumir até 2 CLKs (LFTX ou VLO), mas apenas o VLO está
	implementado. ESTE PARAMETRO DEVE SER VLO. O VLO DEVE SER CONFIGURADO ANTES 
	DE CHAMAR ESSA FUNÇÂO.
	@param divider: É o divisor que deve ser colocado. Só 
	funciona para valores típicos 1, 2, 4, 8. Default: 1; 

*/
void beVim_Aclk_Source(ClockSources source, int divider);


/**
	@name: CLK CONFIGURE
	@brief: Essa função configura (ativa, e diz qual a velocidade) das fontes
	de clk configuráveis no MSP430.

	@param source: É a fonte nativa de clk do dispositivo. (Até o momento, somente o 
	DCO e o VLO são suportados). O VLO não possui velocidade configuravel
	@param speed: é a velocidade do clock. Se o escolhido for VLO, este parametro nao importa.

*/
void beVim_Clock_Config(ClockSources source, ClockSpeed speed);
