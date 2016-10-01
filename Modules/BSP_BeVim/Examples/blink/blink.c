/*
 *	Blink.c 
 *	Autor: Pedro Inazawa
 *
 *	THis examplify how to use the BSP's implementation of GPIOs in beVim.
 *
 * */

#include"msp430.h"
#include"../../Includes/beVim-gpios.h"



void main(void){
	

/*	WDTCTL = WDTHOLD+ WDTPW;
	
	int i =0, j =0;

	while(1){
		
		setOutput(1,0,high);

			while(j <100000) { j++;}
		
		j = 0;

		while(j < 100000){ j++;}

		j = 0;

		setOutput(1,0,low);

			while(j <100000) { j++;}
		
		j = 0;

		while(j < 100000){ j++;}

		j = 0;

	setOutput(1,0,low);

	
	}

*/

volatile int i;
 
  // stop watchdog timer
  WDTCTL = WDTPW | WDTHOLD;

  setDirection(1,0,output);
  setDirection(1,3,input);
  setDirection(1,1,input);
  
  pullInput(1,3,high);
  pullInput(1,1,high);

  setOutput(1,0,low);


 
  int k =0;

 
  // set up bit 0 of P1 as output
 // P1DIR = 0x01;
  // intialize bit 0 of P1 to 0
//  P1OUT = 0x00;
 
  // loop forever
  for (;;) {
	
 	  if(getInput(1,3) ==low ){
	 	toggleOutput(1,0);
	 
	 }
	 else setOutput(1,0,high);
	/*if(k == 0){
		setOutput(1,0,low);
		k++;
	}
	else{
		setOutput(1,0,high);
		k--;
	}*/

	    // toggle bit 0 of P1
    //P1OUT ^= 0x01;
	

    // delay for a while
    for (i = 0; i < 0x6000; i++);
  }
}
