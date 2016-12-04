#include "msp430.h"
#include "../../Includes/beVim-gpios.h"
#include "../../Includes/beVim-timerA.h"
#include "../../Includes/beVim-clock-manager.h" 


int counter = 0;
void pisca_led(){

	counter++;
	toggleOutput(1,0);
	toggleOutput(1,1);
	
	if(TA0CCR1 > 625){
		toggleOutput(1,1);
		TA0CCR1 = 0;
	}

}

void DOWN(){
	TA0CCR1--;

	if(TA0CCR1 == 0)
		TA0CCR1 = 622;
}

int main(){

	WDTCTL = WDTPW + WDTHOLD;
	setDirection(1,0,output);
	setDirection(1,1,output);

	setOutput(1,0,low);
	setOutput(1,1,low);
	
	P2DIR |= BIT3;

	beVim_Clock_Config(DCOCLK, _1MHZ);
	beVim_Mclk_Source(DCOCLK, 1);
	beVim_SMclk_Source(DCOCLK, 1);
	
	beVim_TA_OutputMode(6,ModeToggleReset); //Pino 6 do MSP430F2274

	beVim_TA_CountUpTo(625);			//LIMITE MAIS ALT0 (que faz reset)
	beVim_TA_CCR1_CountUpTo(623);			//LIMITE MAIS BAIXO (que set)
	
	beVim_Register_Callback(pisca_led,_ccr0);
	beVim_TA_Enable_CCR0_Interrupt();
	
//	beVim_Register_Callback(DOWN,_ccr1);
//	beVim_TA_Enable_CCR1_Interrupt();

	beVim_TA_configure(_SMCLK, 8, countUp);
	__bis_SR_register(GIE);
	
	while(1){
		if(counter == 10){
			DOWN();
			counter = 0;
		}

	}

}