#include"msp430.h"
#include"../../Includes/beVim-gpios.h"

void main(void){
	

	WDTCTL = WDTHOLD+ WDTPW;

	setDirection(1,0,output);

	setOutput(1,0,high);

	return 0;

}
