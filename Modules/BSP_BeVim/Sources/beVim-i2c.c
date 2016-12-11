 #include "../Includes/beVim-i2c.h"

void beVim_i2c_configure(unsigned char slave_address, unsigned char prescale){
  P3SEL |= SDA_PIN + SCL_PIN;                 // Assign I2C pins to USCI_B0
  UCB0CTL1 = UCSWRST;                        // Enable SW reset
  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;       // I2C Master, synchronous mode
  UCB0CTL1 = UCSSEL_2 + UCSWRST;              // Use SMCLK, keep SW reset
  UCB0BR0 = prescale;                         // set prescaler
  UCB0BR1 = 0;
  UCB0I2CSA = slave_address;                  // Set slave address
  UCB0CTL1 &= ~UCSWRST;                       // Clear SW reset, resume operation
  //UCB0I2CIE = UCNACKIE;
  
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

int beVim_i2c_write_bytes(unsigned char qty, unsigned char *c){
	
	unsigned char bytesToSend = qty;
        
        
	//START + WRITE
	beVim_i2c_transmit_condition(I2C_TRANSMITTER, I2C_START);
        
        
	//Transmitimos os qty bytes ateh que acabe todo o buffer.
	while(bytesToSend){
		
          
		UCB0TXBUF = *c;
                
                //Aguarda o proximo envio, ou flag de erro.		
		while(!(IFG2 & UCB0TXIFG) || !(UCB0STAT & UCNACKIFG)); 
                
                if((UCB0STAT & UCNACKIFG)){
                    return 0;
                }
                
		bytesToSend--;c++;
                    
	}       
        
        return 1;
}

int beVim_i2c_read_bytes(unsigned char qty, unsigned char *c){
	
	unsigned char bytesToRead = qty;
        unsigned char trials = 0;
	//START + READ
	beVim_i2c_transmit_condition(I2C_RECEIVER, I2C_START);
	
	//Aguardamos o recebimento do primeiro ACK.
        //Ao receber, UCTXSTT vai para 0;
	while((UCB0CTL1 & UCTXSTT) &&  trials < 100){
          trials++;
        };
        
        if(trials > 100)
          return 0;
        
        //Se o byte recebido for NACK , então aborta.
        if(UCB0STAT & UCNACKIFG)
          return 0;

       
                trials = 0;        
	while(bytesToRead){ 	
          
          //No último byte a ser lido, iniciar a condição de STOP. 
          if(bytesToRead == 1)
             beVim_i2c_transmit_condition(I2C_RECEIVER, I2C_STOP);
          
                    trials = 0;
		//Aguarda receber mensagem completa.
                    while(!(IFG2 & UCB0RXIFG) && !(UCB0STAT & UCNACKIFG) && (trials < 100)){
                    trials++;
                    }
                    
                    if(trials > 100)
                      return 0;
                if(UCB0STAT & UCNACKIFG)
                  return 0;		
		
          //Guarda valores recebidos. 
          *c = UCB0RXBUF;
          
          //Incrementa / Decrementa os valores. 
            c++; bytesToRead --;	
	}
        
        
        
        return 1;
}