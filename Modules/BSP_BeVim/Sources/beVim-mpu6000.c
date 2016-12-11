/*
	bevim-mpu60xx.c

	Uma biblioteca para interfacear o MPU60xx com o projeto BEVIM

	Autor: Pedro Inazawa.


*/
#include "../Includes/beVim-mpu6000.h"


/*
	@brief: Função para leitura de um registrador do acelerometro (pode funcionar para outros periféricos i2c que seguem a mesma norma.)
	@param: reg - Registrador a ser lido (max 1 byte)
*/
unsigned char beVim_Accelerometer_Read_Register(unsigned char reg){
        
  unsigned char result;
  beVim_i2c_write_bytes(1,&reg);
  beVim_i2c_read_bytes(1,&result);
  
  return result;
}

/*
	@brief: função para a escrita num registrador qualquer do MPU6000.
	@param: reg - Registrador a ser escrito.
	@param: value - Qual o novo valor do registrador. 
*/
void beVim_Accelerometer_Write_Register(unsigned char reg, unsigned char value){
  int i;
  unsigned char write_to_device[2] = {reg, value};
  
  beVim_i2c_write_bytes(2,write_to_device);
  beVim_i2c_transmit_condition(I2C_TRANSMITTER, I2C_STOP);
   for(i =0; i< 0x60; i++);
}

void beVim_Accelerometer_Config(){
        beVim_Accelerometer_Write_Register(MPU6050_RA_PWR_MGMT_1, 0x02);
	beVim_Accelerometer_Write_Register(MPU6050_RA_SMPLRT_DIV, 0x07);
        beVim_Accelerometer_Write_Register(MPU6050_RA_CONFIG, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_GYRO_CONFIG, 0x08);
        beVim_Accelerometer_Write_Register(MPU6050_RA_ACCEL_CONFIG, 0x16); //Configura o sensor para amostragem de 8 g
        beVim_Accelerometer_Write_Register(MPU6050_RA_FF_THR, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_FF_DUR, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_MOT_THR, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_MOT_DUR, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_ZRMOT_THR, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_ZRMOT_DUR, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_FIFO_EN, 0x00);                                           
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_MST_CTRL, 0x00);                                           
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV0_ADDR, 0x00);                                         
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV0_REG, 0x00);                                           
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV0_CTRL, 0x00);                                        
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV1_ADDR, 0x00);                                        
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV1_REG, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV1_CTRL, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV2_ADDR, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV2_REG, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV2_CTRL, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV3_ADDR, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV3_REG, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV3_CTRL, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV4_ADDR, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV4_REG, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV4_DO, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV4_CTRL, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV4_DI, 0x00);                       
        beVim_Accelerometer_Write_Register(MPU6050_RA_INT_PIN_CFG, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_INT_PIN_CFG, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV0_DO, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV1_DO, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV2_DO, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_SLV3_DO, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_I2C_MST_DELAY_CTRL, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_SIGNAL_PATH_RESET, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_MOT_DETECT_CTRL, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_USER_CTRL, 0x00);
    
        beVim_Accelerometer_Write_Register(MPU6050_RA_PWR_MGMT_2, 0x00);
        beVim_Accelerometer_Write_Register(MPU6050_RA_FIFO_R_W, 0x00);
}
