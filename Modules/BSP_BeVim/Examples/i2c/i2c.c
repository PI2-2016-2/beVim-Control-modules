#include "msp430.h"
#include "../../Includes/beVim-clock-manager.h"
#include "../../Includes/beVim-gpios.h"
#include "../../Includes/beVim-i2c.h"
#include "../../Includes/beVim-mpu6000.h"
#include "../../Includes/beVim-uart.h"
#include <stdio.h>

#define PRESCALER 0x10

  int main(void){

	int i = 0;
        int ACC_X = 0;
        
        unsigned char MyAddress;
        unsigned char accData[2] = {0,0};
        char *ACCX_STRING;

	WDTCTL = WDTHOLD+WDTPW;

	//LEDs para indicar os status do programa. 
	setDirection(1,0,output);
	setOutput(1,0,high);
	setDirection(1,1,output);
	setOutput(1,1,high);


	P3DIR |= 0x0F;

	//Portas de comunicação.
	setDirection(3,1,output);
	setDirection(3,2,output);
	P3SEL |= 0x06;

	//Inicializa o clock para MCLK e SMCLK e DCO
	beVim_Clock_Config(DCOCLK, _1MHZ);
	beVim_Mclk_Source(DCOCLK, 1);
	beVim_SMclk_Source(DCOCLK,1);
	
	
	//__bis_SR_register(GIE); // Enable_int

	beVim_i2c_configure(MPU6050_ADDRESS, PRESCALER);
          
        
        beVim_Accelerometer_Config();
        
        //Inicializa USCIA0 em modo UART
	beVim_UART_begin(_9600);
        
        setOutput(1,1,low);
	setOutput(1,0,low);
        
        while(1){
          MyAddress = beVim_Accelerometer_Read_Register(MPU6050_RA_WHO_AM_I);
         
          if(MyAddress == 0x68)
            setOutput(1,1,high);
          else
            setOutput(1,1,low);
          
          accData[0] = beVim_Accelerometer_Read_Register(  MPU6050_RA_ACCEL_XOUT_L);
          accData[1] = beVim_Accelerometer_Read_Register(  MPU6050_RA_ACCEL_XOUT_H);

          ACC_X = accData[0] + (accData[1]<<8);
          
          sprintf(ACCX_STRING,"%d", ACC_X);

          beVim_println(ACCX_STRING);
          
         
        //or(i =0; i< 0x60; i++);
        }
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
#elif defined(__GNUC__)
void __interrupt(USCIAB0RX_VECTOR) rx_ISR(void)
#else
#error Compiler not supported!
#endif
{
	//IFG2 &= ~UCB0RXIFG;
	//setOutput(1,1,high);
        
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
#elif defined(__GNUC__)
void __interrupt(USCIAB0TX_VECTOR) rx_ISR(void)
#else
#error Compiler not supported!
#endif
{
	//IFG2 &=	~UCB0TXIFG ;
	//toggleOutput(1,0);
}
