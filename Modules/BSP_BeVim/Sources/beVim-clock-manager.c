#include"../Includes/beVim-clock-manager.h"


void beVim_Mclk_Source(ClockSources source, int divider){
	
	#ifdef __MSP430F2274
		
		switch(source){
			
			case DCOCLK:
				BCSCTL2 |= SELM_0; 
				break;
			case XT2CLK:
				BCSCTL2 |= SELM_2;
				break;
			case LFXT1CLK:
			case VLOCLK:
				BCSCTL2 |= SELM_3;
				break;
			default:
				BCSCTL2 |= SELM_0; 
				break;
		}
		
		switch(divider){
			
			case 2:
				BCSCTL2 |=  DIVM_1;
				break;
			case 4:
				BCSCTL2 |=  DIVM_2;
				break;
			case 8:
				BCSCTL2 |=  DIVM_3;
				break;
			default:
			case 1:
				BCSCTL2 |=  DIVM_0;
				break;


		}
	#endif


}
void beVim_SMclk_Source(ClockSources source, int divider){
	#ifdef __MSP430F2274
	
		switch(source){
			case XT2CLK:
			case LFXT1CLK:
				BCSCTL2 |= SELS;		
				break;
			case DCOCLK:
				BCSCTL2 &= ~SELS;
				break;

			default:
				BCSCTL2 &= ~SELS;
				break;
			
			
	
		}

		switch(divider){

			case 1:
				BCSCTL2 |= DIVS_0;
				break;
			case 2:
				BCSCTL2 |= DIVS_1;
				break;
			case 4:
				BCSCTL2 |= DIVS_2;
				break;
			case 8:
				BCSCTL2 |= DIVS_3;
				break;

			default:
				BCSCTL2 |= DIVS_0;
				break;
		}
			
	#endif
}
void beVim_Clock_Config(ClockSources source, ClockSpeed speed){
	
	//Essa função só implementa o controle de DCO, já que o restante
	// exige implementações muito particulares.
	#ifdef __MSP430F2274
		
		switch(source){

			//Fonte de CLK é o DCO
			case DCOCLK:
				switch(speed){
					case  _1MHZ:
						BCSCTL1 = CALBC1_1MHZ;
						DCOCTL = CALDCO_1MHZ;
						break;
					case  _8MHZ:
						BCSCTL1 = CALBC1_8MHZ;
						DCOCTL = CALDCO_8MHZ;
						break;
					case  _12MHZ:
						BCSCTL1 = CALBC1_12MHZ;
						DCOCTL = CALDCO_12MHZ;
						break;
					case  _16MHZ:
						BCSCTL1 = CALBC1_16MHZ;
						DCOCTL = CALDCO_16MHZ;
						break;
				}	
				break;

			case VLOCLK:
						//Configura o ACLK para receber o VLO.
					BCSCTL1 &= ~XTS;
					BCSCTL3 |= LFXT1S_2;	
					break;
					
			default:
				break;
		}		


	#endif
}

void beVim_Aclk_Source(ClockSources source, int divider){

	// Essa implementação apenas contempla ACLK com o VLO.
	// Isso foi feito pois implementações com cristais envolvem outros
	// elementos que são próprios de cada implementação. 


	#ifdef __MSP430F2274

	switch(source){


		case VLOCLK:
			
			//Configura o divisor agora.			
			switch(divider){

				case 1:
					BCSCTL1 |= DIVA_0;
					break; 
				case 2:
					BCSCTL1 |= DIVA_1;
					break; 
				case 4:
					BCSCTL1 |= DIVA_2;
					break; 
				case 8:
					BCSCTL1 |= DIVA_3;
					break; 

				default:
					BCSCTL1 |= DIVA_0;
					break; 

			}

			break;

		default:
			break; 
	}

	#endif
}