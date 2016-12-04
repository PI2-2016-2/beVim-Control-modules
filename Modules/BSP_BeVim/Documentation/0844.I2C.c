
#include "I2C.h"

char buff_status = 0;

char I2c_Tx;
char SAdd;
char SIAdd;
char SASent;
char SIASent;
char Register;
char ByteSent;
char ByteRecd;
char Result;
char Result2;
char RepStart;
char Seq_ReadTWriteF;
char *ptr_Rx_byte;
signed char I2cByteCnt;

char first_time;



void init_Clk(void){
  
  // Set up DCOCLK and thus SMCLK for 8 MHz (no dividers)
  BCSCTL1 = CALBC1_8MHZ; 
  DCOCTL = CALDCO_8MHZ;
  
}

void Cycle_delay(int cycles_sq){
  int i;
  for(i=0; i<cycles_sq; i++){
    for(i=0; i<cycles_sq; i++){ 
    }
  }
  
}

void ScopeTag(char length){
  P1OUT ^= 1;
  Cycle_delay(length);
  P1OUT ^= 1;
}

/*///////////////////////////////////
                 ISRs
*////////////////////////////////////


// USCIAB0RX Interrupt Service Routine
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
{
  ScopeTag(10);
}

  
  
// USCIAB0TX Interrupt Service Routine
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void){
    
  if(Seq_ReadTWriteF){
    // Single Byte Read Sequence
    
    if(SASent == False && SIASent == False){
      //Then first Interrupt so SA has been sent
      //  and you can load the buffer:      
      SASent = True;
      UCB0TXBUF = SIAdd;
      
    }else if(SASent == True && SIASent == False){
      //Then next interrupt so SA, and SIA are sent
      //  so start the Rx section
      UCB0I2CSA = SAdd;
      UCB0CTL1 &= ~UCTR;    
      UCB0CTL1 |= UCTXSTT;
      SIASent = True;
      SASent = False;
      
    }
    
    if(IFG2 & UCB0RXIFG){
      //If Rx flag is raised, (raised twice - I think once when ready, once when done)
      //  Then read Rxd byte and raise stop condition flag.
      if(first_time == True){
        Result = UCB0RXBUF;
      }else{
        Result2 = UCB0RXBUF;
      }
      first_time = False;
      UCB0CTL1 |= UCTXSTP;
      ByteRecd = True;
      ScopeTag(1);        
    }
    
  
  }else{
    // Single Byte Write Sequence
    
    if(SASent == False && SIASent == False){
      //Then first Interrupt so SA has been sent
      //  and you can load the buffer:      
      SASent = True;
      UCB0TXBUF = SIAdd;
      
    }else if(SASent == True && SIASent == False){
      //Then next interrupt so SA, and SIA are sent
      //  so start the Tx section
      //UCB0I2CSA = SAdd;
      //UCB0CTL1 |= UCTR;    
      //UCB0CTL1 |= UCTXSTT;
      SIASent = True;
      UCB0TXBUF = I2c_Tx;
      //SASent = False;
      
    }else if(SASent == True && SIASent == True){
      UCB0CTL1 |= UCTXSTP;
      ByteSent = True;
      ScopeTag(4);
    }    
    
  } 
    
  IFG2 &= ~(UCB0TXIFG + UCB0RXIFG);
  
}

/*///////////////////////////////////
             I2C Functions
*////////////////////////////////////

void Write8Bits(char my_SA, char my_SIA, char my_data, char my_start, char my_length){
    //      010 my_data: value to write
    // 76543210 bit numbers
    //    xxx   args: my_start=4, my_length=3 (start from right + 1, length to right)
    // 00011100 mask byte
    // 10101111 original value (sample)
    // 10100011 original & ~mask
    // 10101011 masked | value
  
  ReadI2C(my_SA, my_SIA);
  char prev_data = Result;
  
  //if (prev_data != 0) {
    
        char mask = ((1 << my_length) - 1) << (my_start - my_length + 1);
        // shift data into correct position
        my_data <<= (my_start - my_length + 1); 
        // zero all non-important bits in data
        my_data &= mask; 
        // zero all important bits in existing word
        prev_data &= ~(mask); 
        // combine data with existing word
        prev_data |= my_data; 
        
        WriteI2C(my_SA, my_SIA, prev_data);
  //} else {
        // do nothing;
  //}
  
  
}
  
// Single Byte Read Sequence:
//Master  S  AD+W     RA     DATA     P
//Slave           ACK    ACK      ACK 
void WriteI2C(char my_SA, char my_SIA, char my_Data){
    
  SAdd = my_SA;
  SIAdd = my_SIA;
  I2c_Tx = my_Data;
  
  Cycle_delay(200);
  
  Seq_ReadTWriteF = False;
  ByteSent = False;
  SASent = False;
  SIASent = False;
  first_time = True;    
  
  // Begin Tx
    P1OUT &= ~BIT0;
    ScopeTag(1);
    
    UCB0I2CSA = SAdd;
    UCB0CTL1 |= UCTR;
    UCB0CTL1 |= UCTXSTT;           
  
  // Begin Rx
    //wait for byte to be Rxd    
    while(ByteSent == False || (UCB0CTL1 & UCTXSTP) ){
    }
    
    ScopeTag(1); 
  
}

// Single Byte Read Sequence:
//Master  S  AD+W     RA     S  AD+R           NACK  P
//Slave           ACK    ACK         ACK  DATA

void ReadI2C(char my_SA, char my_SIA)
{

  SAdd = my_SA;
  SIAdd = my_SIA;

  Cycle_delay(200);

  Seq_ReadTWriteF = True;
  ByteRecd = False;
  SASent = False;
  SIASent = False;
  first_time = True;    

  // Begin Tx
    P1OUT &= ~BIT0;
    ScopeTag(1);
    
    UCB0I2CSA = SAdd;
    UCB0CTL1 |= UCTR;
    UCB0CTL1 |= UCTXSTT;           

  // Begin Rx
    //wait for byte to be Rxd    
    while(ByteRecd == False || (UCB0CTL1 & UCTXSTP) ){
    }
    ScopeTag(1); 
    
    Result *= 1;
    
}

//NOTE: Initializing or Reconfiguring the USCI Module
//The recommended USCI initialization or reconfiguration process is:
//1. Set UCSWRST (BIS.B #UCSWRST,&UCxCTL1)
//2. Initialize all USCI registers with UCSWRST=1 (including UCxCTL1)
//3. Configure ports.
//4. Clear UCSWRST via software (BIC.B #UCSWRST,&UCxCTL1)
//5. Enable interrupts (optional) via UCxRXIE and/or UCxTXIE

void init_I2C(){
  
  //1. 
  //    Hold Reset
  UCB0CTL1 |= UCSWRST;
  
  //2. 
  //    Master, I2C Mode, Synchronous;
  //    SMCLK = DCOCLK = 8 Mhz, Transmitter;
  //    USCI Clock = SMCLK / 80 = 100 kHz;
  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;
  UCB0CTL1 = UCSSEL1 + UCSSEL0 + UCTR + UCSWRST;
  UCB0BR0  = 77;
  UCB0BR1  = 0;
  
  //3.
  //    Select P1.6 and P1.7 for I2C mode.
  //P1DIR = from USCI
  P1SEL  = BIT6 + BIT7;
  P1SEL2 = BIT6 + BIT7;
  
  //4.
  //    Release Reset
  UCB0CTL1 &= ~UCSWRST;
  
  //5.
  //    Enable Interrupts
  UCB0I2CIE = UCNACKIE;
  IFG2 &= ~(UCB0TXIFG + UCB0RXIFG);
  IE2 |= UCB0TXIE + UCB0RXIE; 
  __enable_interrupt();
  //__bis_SR_register(GIE);
}
