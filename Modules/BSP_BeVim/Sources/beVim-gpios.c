#include"../Includes/beVim-gpios.h"


/*Reponsavel por setar as direções das IOs*/
void setDirection( int port, int pin ,GpioDirection dir){
	
	int bit = 1 << pin;

	if(dir == input)
		bit = ~bit;
		
	switch(port){
		case 1:
			switch(dir){
				case input:
					P1DIR &= bit;
					break;
				case output:
					P1DIR |= bit ;
					break;
				default:
					break;
			}	
			break;

		case 2:
			switch(dir){
				case input:
					P2DIR &= bit;
					break;
				case output:
					P2DIR |= bit;
					break;
				default:
					break;
			}	
	
			break;
		default:
			break;
	
	}
}

void setOutput(int port, int pin, LogicState state){
	
	int bit = 1 << pin;

	if(state == low)
		bit = ~bit;
			
		
	switch(port){
		case 1:
			switch(state){
				case low:
					P1OUT &= bit;
					break;
				case high:
					P1OUT |= bit;
					break;
			}
			break;
		case 2:
			switch(state){
				case low:
					P2OUT &= bit;
					break;
				case high:
					P2OUT |= bit;
					break;
			}
	
			break;
		default:
			break;
	
	
	}
	

}

LogicState getInput(int port, int pin){
	
	int bit = 1 << pin;


	switch(port){
		case 1:
			bit = P1IN& bit; 
			break;
		case 2:
			bit = P2IN & bit;
			break;
		default:
			break;			
	
	}

	if(bit > 0 )
		return high;
	else
		return low;

}


void toggleOutput(int port, int pin){

	int bit  = 1 << pin;

	
	switch(port){
		
		case 1:
			P1OUT ^= bit;
			break;
		case 2:
			P2OUT ^= bit;
			break;
	
	}

}

void pullInput(int port, int pin, LogicState state){

	int bit = 1 << pin;

	switch(port){
		case 1: 
			P1REN |= bit;
			break;
		case 2:
			P2REN |= bit;
			break;
	}

	setOutput(port, pin, state);

}
