#include "msp430.h"
#include "../../Includes/beVim-clock-manager.h"
#include "../../Includes/beVim-gpios.h"
#include "../../Includes/beVim-i2c.h"
#include "../../Includes/beVim-mpu6000.h"

/*#define MPU6050_RA_XG_OFFS_TC 0x00 //[7] PWR_MODE, [6:1] XG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_RA_YG_OFFS_TC 0x01 //[7] PWR_MODE, [6:1] YG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_RA_ZG_OFFS_TC 0x02 //[7] PWR_MODE, [6:1] ZG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_RA_X_FINE_GAIN 0x03 //[7:0] X_FINE_GAIN
#define MPU6050_RA_Y_FINE_GAIN 0x04 //[7:0] Y_FINE_GAIN
#define MPU6050_RA_Z_FINE_GAIN 0x05 //[7:0] Z_FINE_GAIN
#define MPU6050_RA_XA_OFFS_H 0x06 //[15:0] XA_OFFS
#define MPU6050_RA_XA_OFFS_L_TC 0x07
#define MPU6050_RA_YA_OFFS_H 0x08 //[15:0] YA_OFFS
#define MPU6050_RA_YA_OFFS_L_TC 0x09
#define MPU6050_RA_ZA_OFFS_H 0x0A //[15:0] ZA_OFFS
#define MPU6050_RA_ZA_OFFS_L_TC 0x0B
#define MPU6050_RA_XG_OFFS_USRH 0x13 //[15:0] XG_OFFS_USR
#define MPU6050_RA_XG_OFFS_USRL 0x14
#define MPU6050_RA_YG_OFFS_USRH 0x15 //[15:0] YG_OFFS_USR
#define MPU6050_RA_YG_OFFS_USRL 0x16
#define MPU6050_RA_ZG_OFFS_USRH 0x17 //[15:0] ZG_OFFS_USR
#define MPU6050_RA_ZG_OFFS_USRL 0x18
#define MPU6050_RA_SMPLRT_DIV 0x19
#define MPU6050_RA_CONFIG 0x1A
#define MPU6050_RA_GYRO_CONFIG 0x1B
#define MPU6050_RA_ACCEL_CONFIG 0x1C
#define MPU6050_RA_FF_THR 0x1D
#define MPU6050_RA_FF_DUR 0x1E
#define MPU6050_RA_MOT_THR 0x1F
#define MPU6050_RA_MOT_DUR 0x20
#define MPU6050_RA_ZRMOT_THR 0x21
#define MPU6050_RA_ZRMOT_DUR 0x22
#define MPU6050_RA_FIFO_EN 0x23
#define MPU6050_RA_I2C_MST_CTRL 0x24
#define MPU6050_RA_I2C_SLV0_ADDR 0x25
#define MPU6050_RA_I2C_SLV0_REG 0x26
#define MPU6050_RA_I2C_SLV0_CTRL 0x27
#define MPU6050_RA_I2C_SLV1_ADDR 0x28
#define MPU6050_RA_I2C_SLV1_REG 0x29
#define MPU6050_RA_I2C_SLV1_CTRL 0x2A
#define MPU6050_RA_I2C_SLV2_ADDR 0x2B
#define MPU6050_RA_I2C_SLV2_REG 0x2C
#define MPU6050_RA_I2C_SLV2_CTRL 0x2D
#define MPU6050_RA_I2C_SLV3_ADDR 0x2E
#define MPU6050_RA_I2C_SLV3_REG 0x2F
#define MPU6050_RA_I2C_SLV3_CTRL 0x30
#define MPU6050_RA_I2C_SLV4_ADDR 0x31
#define MPU6050_RA_I2C_SLV4_REG 0x32
#define MPU6050_RA_I2C_SLV4_DO 0x33
#define MPU6050_RA_I2C_SLV4_CTRL 0x34
#define MPU6050_RA_I2C_SLV4_DI 0x35
#define MPU6050_RA_I2C_MST_STATUS 0x36
#define MPU6050_RA_INT_PIN_CFG 0x37
#define MPU6050_RA_INT_ENABLE 0x38
#define MPU6050_RA_DMP_INT_STATUS 0x39
#define MPU6050_RA_INT_STATUS 0x3A
#define MPU6050_RA_ACCEL_XOUT_H 0x3B
#define MPU6050_RA_ACCEL_XOUT_L 0x3C
#define MPU6050_RA_ACCEL_YOUT_H 0x3D
#define MPU6050_RA_ACCEL_YOUT_L 0x3E
#define MPU6050_RA_ACCEL_ZOUT_H 0x3F
#define MPU6050_RA_ACCEL_ZOUT_L 0x40
#define MPU6050_RA_TEMP_OUT_H 0x41
#define MPU6050_RA_TEMP_OUT_L 0x42
#define MPU6050_RA_GYRO_XOUT_H 0x43
#define MPU6050_RA_GYRO_XOUT_L 0x44
#define MPU6050_RA_GYRO_YOUT_H 0x45
#define MPU6050_RA_GYRO_YOUT_L 0x46
#define MPU6050_RA_GYRO_ZOUT_H 0x47
#define MPU6050_RA_GYRO_ZOUT_L 0x48
#define MPU6050_RA_EXT_SENS_DATA_00 0x49
#define MPU6050_RA_EXT_SENS_DATA_01 0x4A
#define MPU6050_RA_EXT_SENS_DATA_02 0x4B
#define MPU6050_RA_EXT_SENS_DATA_03 0x4C
#define MPU6050_RA_EXT_SENS_DATA_04 0x4D
#define MPU6050_RA_EXT_SENS_DATA_05 0x4E
#define MPU6050_RA_EXT_SENS_DATA_06 0x4F
#define MPU6050_RA_EXT_SENS_DATA_07 0x50
#define MPU6050_RA_EXT_SENS_DATA_08 0x51
#define MPU6050_RA_EXT_SENS_DATA_09 0x52
#define MPU6050_RA_EXT_SENS_DATA_10 0x53
#define MPU6050_RA_EXT_SENS_DATA_11 0x54
#define MPU6050_RA_EXT_SENS_DATA_12 0x55
#define MPU6050_RA_EXT_SENS_DATA_13 0x56
#define MPU6050_RA_EXT_SENS_DATA_14 0x57
#define MPU6050_RA_EXT_SENS_DATA_15 0x58
#define MPU6050_RA_EXT_SENS_DATA_16 0x59
#define MPU6050_RA_EXT_SENS_DATA_17 0x5A
#define MPU6050_RA_EXT_SENS_DATA_18 0x5B
#define MPU6050_RA_EXT_SENS_DATA_19 0x5C
#define MPU6050_RA_EXT_SENS_DATA_20 0x5D
#define MPU6050_RA_EXT_SENS_DATA_21 0x5E
#define MPU6050_RA_EXT_SENS_DATA_22 0x5F
#define MPU6050_RA_EXT_SENS_DATA_23 0x60
#define MPU6050_RA_MOT_DETECT_STATUS 0x61
#define MPU6050_RA_I2C_SLV0_DO 0x63
#define MPU6050_RA_I2C_SLV1_DO 0x64
#define MPU6050_RA_I2C_SLV2_DO 0x65
#define MPU6050_RA_I2C_SLV3_DO 0x66
#define MPU6050_RA_I2C_MST_DELAY_CTRL 0x67
#define MPU6050_RA_SIGNAL_PATH_RESET 0x68
#define MPU6050_RA_MOT_DETECT_CTRL 0x69
#define MPU6050_RA_USER_CTRL 0x6A
#define MPU6050_RA_PWR_MGMT_1 0x6B
#define MPU6050_RA_PWR_MGMT_2 0x6C
#define MPU6050_RA_BANK_SEL 0x6D
#define MPU6050_RA_MEM_START_ADDR 0x6E
#define MPU6050_RA_MEM_R_W 0x6F
#define MPU6050_RA_DMP_CFG_1 0x70
#define MPU6050_RA_DMP_CFG_2 0x71
#define MPU6050_RA_FIFO_COUNTH 0x72
#define MPU6050_RA_FIFO_COUNTL 0x73
#define MPU6050_RA_FIFO_R_W 0x74
#define MPU6050_RA_WHO_AM_I 0x75



#define SLAVE_ADDR  0x68
#define ACCX_ADDR_H 	0x3B //Read 2 bytes.
#define ACCX_ADDR_L 	0x3C //Read 2 bytes.
#define ACCY_ADDR_H	0x3D //Read 2 bytes.
#define ACCY_ADDR_L	0x3E //Read 2 bytes.
#define ACCZ_ADDR_H	0x3F //Read 2 Bytes.
#define ACCZ_ADDR_L	0x40 //Read 2 Bytes.
#define PWR_MGMT_1 0x6B 

#define WHOAMI_ADDR     0x75
#define PACKET_SIZE 0x08
#define PRESCALER 0x10	     //i2c speed must be max 400 khz
			    // Since we are using 1Mhz, we need 333 khz.

#define TERMINATION_STOP 0 //Tipos de terminadores para o i2c - stop condition
#define TERMINATION_START 1  //Tipos de terminadores para o i2c - start condition

#define __INTERRUPT_MODE

typedef enum m_mode{
	I2C_TRANSMITTER = 0,
	I2C_RECEIVER    = 1

}Master_Mode;

typedef enum m_condition{
	I2C_START      = 0,
	I2C_STOP       = 1,
        I2C_NACK       = 2

}Master_Condition;


void beVim_i2c_configure(unsigned char slave_address, unsigned char prescale){
  P3SEL |= SDA_PIN + SCL_PIN;                 // Assign I2C pins to USCI_B0
  UCB0CTL1 = UCSWRST;                        // Enable SW reset
  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;       // I2C Master, synchronous mode
  UCB0CTL1 = UCSSEL_2 + UCSWRST;              // Use SMCLK, keep SW reset
  UCB0BR0 = prescale;                         // set prescaler
  UCB0BR1 = 0;
  UCB0I2CSA = slave_address;                  // Set slave address
  UCB0CTL1 &= ~UCSWRST;                       // Clear SW reset, resume operation
  UCB0I2CIE = UCNACKIE;
  
  #ifdef __INTERRUPT_MODE
  IE2 = UCB0TXIE + UCB0RXIE;                            // Enable TX ready interrupt
  #endif

}

void beVim_i2c_wait_bus_busy(){
  while(UCB0STAT && UCBBUSY);
}
void beVim_i2c_transmit_condition(Master_Mode mode, Master_Condition condition){
	
	switch(mode){
		case I2C_RECEIVER:
			UCB0CTL1 &= ~(UCTR);
			break;
		case I2C_TRANSMITTER:
			UCB0CTL1 |= UCTR;
			break;
	
	}

	switch(condition){
		case I2C_STOP:
			UCB0CTL1 |= UCTXSTP;
			break;
		case I2C_START:
			UCB0CTL1 |= UCTXSTT;
		       break;	
                case I2C_NACK:
                        UCB0CTL1 |= UCTXNACK;
                        break;
            
	
	}

}
*/

/*
int beVim_i2c_write_bytes(unsigned char qty, unsigned char *c){
	
	unsigned char bytesToSend = qty;
        
        
	//START + WRITE
	beVim_i2c_transmit_condition(I2C_TRANSMITTER, I2C_START);
        
        
	//Transmitimos os qty bytes atÃ© que acabe todo o buffer.
	while(bytesToSend){
		
          
		UCB0TXBUF = *c;
                
                //Aguarda o proximo envio, ou flag de erro.		
		while(!(IFG2 & UCB0TXIFG) && !(UCB0STAT & UCNACKIFG)); 
                
                if((UCB0STAT & UCNACKIFG)){
                    return 0;
                }
                
		bytesToSend--;c++;
                    
	}       
        
        return 1;
}

int beVim_i2c_read_bytes(unsigned char qty, unsigned char *c){
	
	unsigned char bytesToRead = qty;

	//START + READ
	beVim_i2c_transmit_condition(I2C_RECEIVER, I2C_START);
	
	//Aguardamos o recebimento do primeiro ACK.
        //Ao receber, UCTXSTT vai para 0;
	while((UCB0CTL1 & UCTXSTT));
        
        
        //Se o byte recebido for NACK , então aborta.
        if(UCB0STAT & UCNACKIFG)
          return 0;

       
        
	while(bytesToRead){ 	
          
          //No último byte a ser lido, iniciar a condição de STOP. 
          if(bytesToRead == 1)
             beVim_i2c_transmit_condition(I2C_RECEIVER, I2C_STOP);
          
		//Aguarda receber mensagem completa.
          while(!(IFG2 & UCB0RXIFG) && !(UCB0STAT & UCNACKIFG));

                if(UCB0STAT & UCNACKIFG)
                  return 0;		
		
          //Guarda valores recebidos. 
          *c = UCB0RXBUF;
          
          //Incrementa / Decrementa os valores. 
            c++; bytesToRead --;	
	}
        
        
        
        return 1;
}

unsigned char beVim_Accelerometer_Read_Register(unsigned char reg){
        
  unsigned char result;
  beVim_i2c_write_bytes(1,&reg);
  beVim_i2c_read_bytes(1,&result);
  
  return result;
}

void beVim_Accelerometer_Write_Register(unsigned char reg, unsigned char value){
  int i;
  unsigned char write_to_device[2] = {reg, value};
  
  beVim_i2c_write_bytes(2,write_to_device);
  beVim_i2c_transmit_condition(I2C_TRANSMITTER, I2C_STOP);
   for(i =0; i< 0x60; i++);
}
*/
  int main(void){

	int i = 0;
	unsigned char c[2] = {WHOAMI_ADDR, ACCX_ADDR_L};
	 unsigned char result[2] = {0,0};

	WDTCTL = WDTHOLD+WDTPW;

	//LEDs para indicar os status do programa. 
	setDirection(1,0,output);
	setOutput(1,0,high);
	setDirection(1,1,output);
	setOutput(1,1,high);


	P3DIR |= 0x0F;

	//Portas de comunicaÃ§Ã£o.
	setDirection(3,1,output);
	setDirection(3,2,output);
	P3SEL |= 0x06;

	//Inicializa o clock para MCLK e SMCLK e DCO
	beVim_Clock_Config(DCOCLK, _1MHZ);
	beVim_Mclk_Source(DCOCLK, 1);
	beVim_SMclk_Source(DCOCLK,1);
	
	
	//__bis_SR_register(GIE); // Enable_int

	beVim_i2c_configure(SLAVE_ADDR, PRESCALER);
          
        unsigned char MyAddress;
        unsigned char accData;
        
        beVim_Accelerometer_Write_Register(MPU6050_RA_SMPLRT_DIV, 0x07);
        beVim_Accelerometer_Write_Register(MPU6050_RA_CONFIG, 0x00);
        beVim_Accelerometer_Write_Register( MPU6050_RA_GYRO_CONFIG, 0x08);
        beVim_Accelerometer_Write_Register(MPU6050_RA_ACCEL_CONFIG, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_FF_THR, 0x00);
        beVim_Accelerometer_Write_Register( MPU6050_RA_FF_DUR, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_MOT_THR, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_MOT_DUR, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_ZRMOT_THR, 0x00);
        beVim_Accelerometer_Write_Register( MPU6050_RA_ZRMOT_DUR, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_FIFO_EN, 0x00);                                           
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_MST_CTRL, 0x00);                                           
        beVim_Accelerometer_Write_Register( MPU6050_RA_I2C_SLV0_ADDR, 0x00);                                         
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV0_REG, 0x00);                                           
        beVim_Accelerometer_Write_Register(  MPU6050_RA_I2C_SLV0_CTRL, 0x00);                                        
        beVim_Accelerometer_Write_Register(   MPU6050_RA_I2C_SLV1_ADDR, 0x00);                                        
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV1_REG, 0x00);
        beVim_Accelerometer_Write_Register( MPU6050_RA_I2C_SLV1_CTRL, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV2_ADDR, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV2_REG, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV2_CTRL, 0x00);
        beVim_Accelerometer_Write_Register( MPU6050_RA_I2C_SLV3_ADDR, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV3_REG, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV3_CTRL, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV4_ADDR, 0x00);
        beVim_Accelerometer_Write_Register( MPU6050_RA_I2C_SLV4_REG, 0x00);
        beVim_Accelerometer_Write_Register( MPU6050_RA_I2C_SLV4_DO, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV4_CTRL, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV4_DI, 0x00);                       
        beVim_Accelerometer_Write_Register(MPU6050_RA_INT_PIN_CFG, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_INT_PIN_CFG, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV0_DO, 0x00);
        beVim_Accelerometer_Write_Register( MPU6050_RA_I2C_SLV1_DO, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV2_DO, 0x00);
        beVim_Accelerometer_Write_Register( MPU6050_RA_I2C_SLV3_DO, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_MST_DELAY_CTRL, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_SIGNAL_PATH_RESET, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_MOT_DETECT_CTRL, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_USER_CTRL, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_PWR_MGMT_1, 0x02);
        beVim_Accelerometer_Write_Register(MPU6050_RA_PWR_MGMT_2, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_FIFO_R_W, 0x00);
        
        setOutput(1,1,low);
	setOutput(1,0,low);
        unsigned char powerMngt = 0x00;
        
        while(1){
          MyAddress = beVim_Accelerometer_Read_Register(WHOAMI_ADDR);
         
          if(MyAddress == 0x68)
            setOutput(1,1,high);
          else
            setOutput(1,1,low);
          
          accData = beVim_Accelerometer_Read_Register(  MPU6050_RA_ACCEL_XOUT_L);
           if((accData > 250))
            setOutput(1,0,high);
          else
            setOutput(1,0,low);
         
        for(i =0; i< 0x60; i++);
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
