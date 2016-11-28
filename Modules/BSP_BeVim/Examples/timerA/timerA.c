#include "msp430.h"
#include "../../Includes/beVim-gpios.h"
#include "../../Includes/beVim-uart.h"
#include "../../Includes/beVim-timerA.h"
#include "../../Includes/beVim-clock-manager.h" 

void pisca_led(){

	toggleOutput(1,1);
}

int main(){

	WDTCTL = WDTPW + WDTHOLD;

	setDirection(1,0,output);
	setDirection(1,1,output);

	setOutput(1,0,low);
	setOutput(1,1,low);

	beVim_Clock_Config(DCOCLK, _1MHZ);
	beVim_Mclk_Source(DCOCLK, 1);
	beVim_SMclk_Source(DCOCLK, 1);
	
	__bis_SR_register(GIE);
	beVim_TA_Enable_CCR0_Interrupt();
	beVim_TA_CountUpTo(60000);
	beVim_Register_Callback(pisca_led,_ccr0);
	beVim_TA_configure(_SMCLK, 8, countUp);

	while(1);


}
