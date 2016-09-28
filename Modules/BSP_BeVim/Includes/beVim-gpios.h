#include<msp430.h>

typedef enum logicstates{
	low = 0,
	high = 1
}LogicState;

typedef enum inout_state {
	input = 0,
	output = 1

} GpioDirection;

/*
 * @name: SetDirection
 * @param: port - Porta da qual se quer modificar parametro.
 * @param: pin - pino do qual se quer modificar parametro.
 * @param: GpioDirection - Qual direção que a porta deve ter.
 *
 * @brief: Essa funcao modifica o parametro direção da porta dada por parametro.
 * */
void setDirection(int port, int pin, GpioDirection dir);

/**
 * @name Set Output
 * */
void setOutput(int port, int pin, LogicState state);


/**
 * @name Get Input
 */
LogicState getInput(int port, int pin);


