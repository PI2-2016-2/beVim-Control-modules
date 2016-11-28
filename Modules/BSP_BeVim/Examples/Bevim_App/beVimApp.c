#include "msp430.h"
#include "../../Includes/beVim-clock-manager.h"
#include "../../Includes/beVim-uart.h"
#include "../../Includes/beVim-gpios.h"
#include "../../Includes/beVim-i2c.h"
#include "../../Includes/beVim-mpu6000.h"

//Inputs definidos do protocolo
#define _START_STOP_FLAG 		0x01
#define _ACTIVE_SENSOR_FLAG		0x02

//Outputs definidos
#define _TIMESTAMP_HEADER 		0x01
#define _FREQUENCY_OK_HEADER 		0x03

int isEnabled = 0;
char charRecebido;


int main(){
	
	unsigned char timer = 0;
	unsigned char timer2 = 0;
	unsigned char timer3 = 0;	
	WDTCTL = WDTPW + WDTHOLD;
	
	setDirection(1,0,output);
	setDirection(1,1,output);

	setOutput(1,0,high);
	setOutput(1,1,low);

	beVim_Clock_Config(DCOCLK, _1MHZ);
	beVim_Mclk_Source(DCOCLK, 1);
	beVim_SMclk_Source(DCOCLK, 1);

	beVim_UART_begin(_9600);
	beVim_i2c_configure(MPU6050_ADDRESS, 0X10);
//	__bis_SR_register(GIE);

	beVim_Accelerometer_Config();	
	
	//interrupt enabled for receiving. 
//	IE2 |= UCA0RXIE;
	
	while(1){
		
		 charRecebido = beVim_getc();		
		
//		if(charRecebido == _START_STOP_FLAG){
	if(charRecebido == 'a'){
			if(isEnabled){
				isEnabled = 0;
				setOutput(1,1,low);
				setOutput(1,0,high);
			}
				
			else {
				isEnabled = 1;			
				setOutput(1,0,low);
				setOutput(1,1,high);
			}

		}
		
		if(charRecebido == _ACTIVE_SENSOR_FLAG){
			beVim_putc(0x01);			
						
		}

		while(isEnabled){
			
			toggleOutput(1,0);

			beVim_putc(0x01);
			beVim_putc(timer3);
			beVim_putc(timer2);
			beVim_putc(timer);
			beVim_putc(0x11);
			beVim_putc(beVim_Accelerometer_Read_Register(MPU6050_RA_ACCEL_XOUT_H));
			beVim_putc(beVim_Accelerometer_Read_Register(MPU6050_RA_ACCEL_XOUT_L));
			

			timer++;
			if(timer == 0xff){
				timer = 0;
				timer2++;
			}
			if(timer2 == 0xff){
				timer2 = 0;
				timer3++;
			}
			if(timer3 == 0xff){
				timer3 = 0;
			}
				
			__delay_cycles(1000);			

		}



//		if(beVim_getc() == )
//			toggleOutput(1,1);
/*		if(isEnabled){
			beVim_putc(0x01);
			beVim_putc(timer++);
			beVim_putc(timer2);
			beVim_putc(timer3);
		
			beVim_putc(0x11);
		//	
			if(timer == 0xff){
				timer = 0;
				timer2++;
			}
			if(timer2 == 0xff){
				timer2 = 0;
				timer3++;
			}
			if(timer3 == 0xff){
				timer3 = 0;
			}
		}


	*/
	}


}

void __interrupt(USCIAB0TX_VECTOR) tx_ISR(void){
	
	toggleOutput(1,0);

}

void __interrupt(USCIAB0RX_VECTOR) rx_ISR(void){
	
	toggleOutput(1,1);
	charRecebido = UCA0RXBUF;

	if(charRecebido == _START_STOP_FLAG)
		isEnabled = 1;
	else if(charRecebido == _ACTIVE_SENSOR_FLAG)
		UCA0TXBUF = 0x01;		
		
}
