#include "../Includes/beVim-timerA.h"

void beVim_TA_reset(){

	//Resets the counter;
	TACTL |= TACLR;
	
	//Stops the counter;
	TACTL = MC_0;

}

void beVim_TA_configure(TAClockSources clockSource, char divider, TACountingMode countingMode){

	switch(clockSource){
		case _TACLK:
			TACTL |= TASSEL_0;
			break;
		case _ACLK:
			TACTL |= TASSEL_1;
			break;
		case _SMCLK:
			TACTL |= TASSEL_2;
			break;
		case _INCLK:
			TACTL |= TASSEL_3;
			break;

		default:
			TACTL |= TASSEL_2;
			break;
	}

	switch(divider){
		case 1:
			TACTL |= ID_0;
			break;
		case 2:
			TACTL |= ID_1;
			break;
		case 4:
			TACTL |= ID_2;
			break;
		case 8:
			TACTL |= ID_3;
			break;

		default:
			TACTL |= ID_0;
			break;
	}

	switch(countingMode){
		case stop:
			TACTL |= MC_0;
		case countUp:
			TACTL |= MC_1;
			break;
		case countUpDown:
			TACTL |= MC_2;
			break;
		case countContinuous:
			TACTL |= MC_3;
			break;

		default:
			TACTL |= MC_1;
			break;

	}
}


int beVim_TA_CurrentCount(){

	return TAR;
}

void beVim_TA_OutputMode(OutputModeSet outputMode){}

void beVim_TA_Enable_OVF_Interrupt(){
	TACTL |= TAIE;
}

void beVim_TA_Disable_OVF_Interrupt(){
	TACTL &= ~TAIE;
}

void beVim_TA_Enable_CCR0_Interrupt(){
	CCTL0 |= CCIE;
}

void beVim_TA_Disable_CCR0_Interrupt(){
	CCTL0 &= ~CCIE;
}

void beVim_Register_Callback(void *func,TAInterruptTypes type){

		switch(type){
			case _ccr0:
				interrupt_Sequence[0] = func;
			break;

			case _ccr1:
				interrupt_Sequence[1] = func;
			break;

			case _ccr2:
				interrupt_Sequence[2] = func;

			case _overflow:
				interrupt_Sequence[3] = func;
			break;
		}

}

void beVim_TA_CountUpTo(int LSB){
	  TACCR0 = LSB;

}

void __interrupt(TIMERA0_VECTOR) Timer_A_ISR (void)
{
  switch( TA0IV )
  {
    case  2:  
    	interrupt_Sequence[1]();
    	break;                        // CCR1 not used
    case  4:  
	interrupt_Sequence[2]();
    	break;                        // CCR2 not used
    case 10:
      	interrupt_Sequence[3]();     // overflow
        break;
    default:
	interrupt_Sequence[0]();    // CCR0 or other interrupt
	break;
  }
}

