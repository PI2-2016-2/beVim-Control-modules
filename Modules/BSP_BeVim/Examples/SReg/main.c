
#include <msp430.h>
#include "../../Includes/beVim-CD4015.h"
#include "../../Includes/beVim-clock-manager.h"
#include "../../Includes/beVim-gpios.h"
#include "../../Includes/beVim-i2c.h"
#include "../../Includes/beVim-mpu6000.h"
#include "../../Includes/beVim-uart.h"


#define PRESCALER 0x10
int i = 0;
int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  P3DIR |= 0x0F;
  P3SEL |= 0x06;
  setDirection(1,0,output);
	setDirection(1,1,output);

	setOutput(1,0,high);
	setOutput(1,1,high);
	setOutput(1,0,low); 
        	setOutput(1,1,low);
  
  beVim_CD4015_configure();
  
 
  beVim_Clock_Config(DCOCLK, _1MHZ);
  beVim_Mclk_Source(DCOCLK, 1);
  beVim_SMclk_Source(DCOCLK,1);

  beVim_i2c_configure(MPU6050_ADDRESS, PRESCALER);
  
   while(1){
    beVim_set_next_state();

    // if(beVim_Accelerometer_Read_Register(MPU6050_RA_WHO_AM_I) == 0x68)
      //      setOutput(1,1,high);
      //else
       // setOutput(1,1,low);
     
   
   }  
  
  
  
  return 0;
}
