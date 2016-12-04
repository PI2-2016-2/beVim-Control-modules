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


void beVim_TA_OutputMode(char pin, OutputModeSet outputMode){

#ifdef __MSP430G2553
	switch(pin){
		case 4: //TA0.1 P1.2
			
			P1SEL |= BIT2;
			P1DIR |= BIT2;
			
			switch( outputMode){
				case ModeSet:
					TA0CCTL1 = OUTMOD_1; 
					break;
				case ModeToggleReset:
					TA0CCTL1 = OUTMOD_2;
					break;
				case ModeSetReset:
					TA0CCTL1 = OUTMOD_3;
					break;
				case ModeToggle:
					TA0CCTL1 = OUTMOD_4;
					break;
				case ModeReset:
					TA0CCLT1 = OUTMOD_5;
					break;
				case ModeToggleSet:
					TA0CCTL1 = OUTMOD_6;
					break;
				case ModeResetSet:
					TA0CCTL1 = OUTMOD_7;
					break;
	
			}		
			
			break;

		case 9: //TA1.1	P2.1

			P2SEL |= BIT1;
			P2DIR |= BIT1; 
			
			switch (outputMode){
				case ModeSet:
					TA1CCTL1 = OUTMOD_1; 
					break;
				case ModeToggleReset:
					TA1CCTL1 = OUTMOD_2;
					break;
				case ModeSetReset:
					TA1CCTL1 = OUTMOD_3;
					break;
				case ModeToggle:
					TA1CCTL1 = OUTMOD_4;
					break;
				case ModeReset:
					TA1CCLT1 = OUTMOD_5;
					break;
				case ModeToggleSet:
					TA1CCTL1 = OUTMOD_6;
					break;
				case ModeResetSet:
					TA1CCTL1 = OUTMOD_7;
					break;
			}		
			
			break;

		case 12: //TA1.2 P2.4
			
			P2SEL |= BIT4;
			P2DIR |= BIT4;
			
			switch( outputMode){
				case ModeSet:
					TA1CCTL2 = OUTMOD_1; 
					break;
				case ModeToggleReset:
					TA1CCTL2 = OUTMOD_2;
					break;
				case ModeSetReset:
					TA1CCTL2 = OUTMOD_3;
					break;
				case ModeToggle:
					TA1CCTL2 = OUTMOD_4;
					break;
				case ModeReset:
					TA1CCLT2 = OUTMOD_5;
					break;
				case ModeToggleSet:
					TA1CCTL2 = OUTMOD_6;
					break;
				case ModeResetSet:
					TA1CCTL2 = OUTMOD_7;
				|	break;
			}

				
			break;

		case 13: //TA1.2 P2.5
			
			P2SEL |= BIT5;
			P2DIR |= BIT5;

			switch( outputMode){
				case ModeSet:
					TA1CCTL2 = OUTMOD_1; 
					break;
				case ModeToggleReset:
					TA1CCTL2 = OUTMOD_2;
					break;
				case ModeSetReset:
					TA1CCTL2 = OUTMOD_3;
					break;
				case ModeToggle:
					TA1CCTL2 = OUTMOD_4;
					break;
				case ModeReset:
					TA1CCTL2 = OUTMOD_5;
					break;
				case ModeToggleSet:
					TA1CCTL2 = OUTMOD_6;
					break;
				case ModeResetSet:
					TA1CCTL2 = OUTMOD_7;
					break;
			}		

			break;
		case 14: //TA0.1 P1.5
			
			P1SEL |= BIT5;
			P1DIR |= BIT5;

			switch (outputMode){
				case ModeSet:
					TA0CCTL1 = OUTMOD_1; 
					break;
				case ModeToggleReset:
					TA0CCTL1 = OUTMOD_2;
					break;
				case ModeSetReset:
					TA0CCTL1 = OUTMOD_3;
					break;
				case ModeToggle:
					TA0CCTL1 = OUTMOD_4;
					break;
				case ModeReset:
					TA0CCTL1 = OUTMOD_5;
					break;
				case ModeToggleSet:
					TA0CCTL1 = OUTMOD_6;
					break;
				case ModeResetSet:
					TA0CCTL1 = OUTMOD_7;
					break;
			}		
			
			break;

		case 19: //TA0.1 P2.5
			
			P2SEL |= BIT5
			P2DIR |= BIT5;
			switch outputMode{
				case ModeSet:
					TA0CCTL1 = OUTMOD_1; 
					break;
				case ModeToggleReset:
					TA0CCTL1 = OUTMOD_2;
					break;
				case ModeSetReset:
					TA0CCTL1 = OUTMOD_3;
					break;
				case ModeToggle:
					TA0CCTL1 = OUTMOD_4;
					break;
				case ModeReset:
					TA0CCTL1 = OUTMOD_5;
					break;
				case ModeToggleSet:
					TA0CCTL1 = OUTMOD_6;
					break;
				case ModeResetSet:
					TA0CCTL1 = OUTMOD_7;
					break;
			}		
			
			break;

	}	
#endif

#ifdef __MSP430F2274
	switch(pin){
		case 6: //TA1 P2.3
			P2SEL |= BIT3;
			P2DIR |= BIT3;				

			switch(outputMode){
				case ModeSet:
					TA0CCTL1 = OUTMOD_1; 
					break;
				case ModeToggleReset:
					TA0CCTL1 = OUTMOD_2;
					break;
				case ModeSetReset:
					TA0CCTL1 = OUTMOD_3;
					break;
				case ModeToggle:
					TA0CCTL1 = OUTMOD_4;
					break;
				case ModeReset:
					TA0CCTL1 = OUTMOD_5;
					break;
				case ModeToggleSet:
					TA0CCTL1 = OUTMOD_6;
					break;
				case ModeResetSet:
					TA0CCTL1 = OUTMOD_7;
					break;
			}		

			
			break;
		case 7: //TA2 P2.4
			P2SEL |= BIT4;
			P2DIR |= BIT4;
			switch(outputMode){
				case ModeSet:
					TA0CCTL2 = OUTMOD_1; 
					break;
				case ModeToggleReset:
					TA0CCTL2 = OUTMOD_2;
					break;
				case ModeSetReset:
					TA0CCTL2 = OUTMOD_3;
					break;
				case ModeToggle:
					TA0CCTL2 = OUTMOD_4;
					break;
				case ModeReset:
					TA0CCTL2 = OUTMOD_5;
					break;
				case ModeToggleSet:
					TA0CCTL2 = OUTMOD_6;
					break;
				case ModeResetSet:
					TA0CCTL2 = OUTMOD_7;
					break;
			}		

			break;
	}
#endif
	

}

void beVim_TA_Enable_OVF_Interrupt(){
	TACTL |= TAIE;
}

void beVim_TA_Disable_OVF_Interrupt(){
	TACTL &= ~TAIE;
}

void beVim_TA_Enable_CCR0_Interrupt(){
	TA0CCTL0 |= CCIE;
}

void beVim_TA_Disable_CCR0_Interrupt(){
	TA0CCTL0 &= ~CCIE;
}

void beVim_TA_Enable_CCR1_Interrupt(){
	TA0CCTL1 |= CCIE;
}

void beVim_TA_Disable_CCR1_Interrupt(){
	TA0CCTL1 &= ~CCIE;
}


void beVim_TA_Enable_CCR2_Interrupt(){
	TA0CCTL2 |= CCIE;
}

void beVim_TA_Disable_CCR2_Interrupt(){
	TA0CCTL2 &= ~CCIE;
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

void beVim_TA_CCR1_CountUpTo(int LSB){
	  TA0CCR1 = LSB;
}

void beVim_TA_CCR2_CountUpTo(int LSB){
	  TA0CCR2 = LSB;

}
void __interrupt(TIMERA0_VECTOR) Timer_A_ISR0(void){

	interrupt_Sequence[0]();    // CCR0 or other interrupt

}

void __interrupt(TIMERA1_VECTOR) Timer_A_ISR1 (void)
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
      }
}

