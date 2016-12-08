#include "msp430.h"
#include "../../Includes/beVim-clock-manager.h"
#include "../../Includes/beVim-uart.h"
#include "../../Includes/beVim-gpios.h"
#include "../../Includes/beVim-i2c.h"
#include "../../Includes/beVim-mpu6000.h"
#include "../../Includes/beVim-timerA.h"
#include "../../Includes/beVim-frequency.h"

//Inputs definidos do protocolo
#define _START_STOP_FLAG 		0x01 //'a' 	//0x01
#define _ACTIVE_SENSOR_FLAG		0x02 //'b'     //0x02

//Outputs definidos
#define _TIMESTAMP_HEADER 		0x01
#define _FREQUENCY_OK_HEADER 	        0x03

//Defini√ßoes para o TIMER (gera interrup√ß√£o de 5 em 5 ms, habilitando a leitura do sensor)
#define TA_CLOCK_SOURCE 		_SMCLK
#define TA_CLOCK_DIV			8					// Divisor de 8 - Freq = 125 khz
#define TA_COUNT_MODE			countUp
#define TA_CCR0_LIMIT			625					//Limite Superior (Reset)  - 5 ms
#define TA_CCR1_LIMIT			622					//Limite Inferior (Set)
#define TA_PWM_STEP		        2					//Passo para o PWM diminuir

//Definicoes para os valores de pico do acelerometro
#define PEAK_LEVEL		        1.5	//valor acima do qual se considera um pico (em G)
#define PEAK_LEVEL_TOLERANCE            0.1     //Valor de tolerancia ao valor m·ximo do pico (de 0 a 1)
#define ACCEL_LSB_DIVIDER		4096	//Valor do LSB recebido do accelerometro.
#define TIMER_OVFs_TO_1_S               200     //Quantidade de ciclos que devem ser feitos para contabilizar 1 segundo

//Definicoes para o avanco ou recuo de frequencia
#define CENTER_FREQ_TOLERANCE           1     //Faixa na qual a frequencia È considerada atingida pelo experimento.

//Variaveis relacionadas ao protocolo
char 		isEnabled 			= 0;
char 		readNow 			= 0;
char 		sendAvailableSensor 		= 0;
char 		charRecebido 			= 0;
unsigned char 	timer 				= 0;
unsigned char 	timer2 				= 0;
unsigned char 	timer3 				= 0;
unsigned char 	freqRequerida			= 0;
char 		tempVar                         = 0;

//Variavel relacionada a contagem do tempo. 
int             countOverflows                  = 0;            

void mudaContador(){

	readNow = 1;
	timer++;
        countOverflows++;
	
	toggleOutput(1,1);

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

void configuraTimer(){
	
	
	beVim_TA_OutputMode(6,ModeToggleReset); //Pino 6 do MSP430F2274
	
	beVim_TA_CountUpTo(TA_CCR0_LIMIT);		//Limite superior do contador
	beVim_TA_CCR1_CountUpTo(TA_CCR1_LIMIT);  //Limite Inferior do Contador
	
	
	beVim_Register_Callback(mudaContador, _ccr0);
	beVim_TA_Enable_CCR0_Interrupt();

	beVim_TA_configure(TA_CLOCK_SOURCE ,TA_CLOCK_DIV,TA_COUNT_MODE);
}

void configuraClock(){
	beVim_Clock_Config(DCOCLK, _1MHZ);
	beVim_Mclk_Source(DCOCLK, 1);
	beVim_SMclk_Source(DCOCLK, 1);

}

void configuraUart(){

	beVim_UART_begin(_9600);
	IE2 |= UCA0RXIE;
}

void configuraLed(){
	setDirection(1,0,output);
	setDirection(1,1,output);
	setOutput(1,0,high);
	setOutput(1,1,low);

}

void configuraI2C(){

	beVim_i2c_configure(MPU6050_ADDRESS, 0X10);
	beVim_Accelerometer_Config();	

}


int main(){
	
	//Variaveis para receber a timestamp do detector de picos
	unsigned char frequenciaInstantanea     = 0;
	int           aceleracaoAtual 		= 0;
	unsigned char aceleracaoRaw[]   	= {0,0};
	int 	      PWMAtual                  = TA_CCR1_LIMIT; 
	double        accAtualDouble		= 0.0;
        int           contaZero                 = 0;
        char          upZone                    = 1;          //Flag que indica se a mediÁ„o de faixa de frequencia est· na zona superior ou inferio
                                                              //da faixa limiar
        int           contaZeros                =0;

	WDTCTL = WDTPW + WDTHOLD;
	
	configuraLed();
	configuraClock();
	configuraUart();
	configuraI2C();
	__bis_SR_register(GIE);
	
	
	while(1){
			
		if(sendAvailableSensor){
			beVim_putc(0x01);
			sendAvailableSensor--;		
		}

		while(isEnabled){
			
					
			if(readNow){
				
				//Desliga a interrup√ß√£o global	
				__bic_SR_register(GIE);
				
				//Apaga a Flag
				readNow--;

				//Pisca o LED

				//printa a timestamp
				beVim_putc(0x01);
				beVim_putc(timer3);
				beVim_putc(timer2);
				beVim_putc(timer);
				
				//Leitura de sensor.
				aceleracaoRaw[0] = (unsigned char)beVim_Accelerometer_Read_Register(MPU6050_RA_ACCEL_XOUT_H);
				aceleracaoRaw[1] = (unsigned char)beVim_Accelerometer_Read_Register(MPU6050_RA_ACCEL_XOUT_L);
				
				//Transformacao para inteiro com sinal.
				aceleracaoAtual = (aceleracaoRaw[0] <<8 ) | (aceleracaoRaw[1]);
				accAtualDouble =  (double)aceleracaoAtual/ACCEL_LSB_DIVIDER;
					
				if((accAtualDouble > (PEAK_LEVEL * (1+PEAK_LEVEL_TOLERANCE))) && (upZone)){
                                    contaZeros++;
                                    upZone = 0;
				}
				else if((accAtualDouble < (PEAK_LEVEL * (1-PEAK_LEVEL_TOLERANCE))) && ~(upZone)){
                                    contaZeros++;
                                      upZone = 1;
				}
                                
                                 if(countOverflows == TIMER_OVFs_TO_1_S){
                                      
                                     frequenciaInstantanea = contaZeros/2;
                                     contaZeros = 0;
                                     countOverflows = 0;
                                 }                                                     
                                                          
				//Descritivo do sensor
				beVim_putc(0x11);
				beVim_putc(aceleracaoRaw[0]);
				beVim_putc(aceleracaoRaw[1]);			

				//freq
				beVim_putc(0x03);
				beVim_putc((char)frequenciaInstantanea);

				//Liga a interrupÁ„o Global.
				__bis_SR_register(GIE);
				
                                //Avaliacao de frequencia e potencial mudanca.
				if(frequenciaInstantanea < (freqRequerida -CENTER_FREQ_TOLERANCE)){
					PWMAtual = PWMAtual - TA_PWM_STEP;
					
					if(PWMAtual <= 0)
						PWMAtual = TA_CCR1_LIMIT;

					beVim_TA_CCR1_CountUpTo(PWMAtual);

				}
				else if(frequenciaInstantanea > (freqRequerida + CENTER_FREQ_TOLERANCE)){
					
					PWMAtual = PWMAtual + TA_PWM_STEP;
					
					if(PWMAtual >= TA_CCR1_LIMIT)
						PWMAtual = 0;

					beVim_TA_CCR1_CountUpTo(PWMAtual);					
				}

				
			}		
				

		}


	}

}
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCIAB0RX_VECTOR
__interrupt void RX_ISR(void)
#elif defined(__GNUC__)
void __interrupt(USCIAB0RX_VECTOR) RX_ISR(void)
#else
#error Compiler not supported!
#endif
{

	 charRecebido = beVim_getc();		

	if(charRecebido == _START_STOP_FLAG){
	 	if(isEnabled == 1){
	 		tempVar = 0 ;
	 		isEnabled = 0;
	 		readNow = 0;
			setOutput(1,1,low);
			setOutput(1,0,high);
			beVim_TA_reset();
			beVim_TA_CCR1_CountUpTo(TA_CCR1_LIMIT);
	 	} 
	 	else{
	 		tempVar =1;
	 		
	 	}
	 }
	 	
	else if(charRecebido == _ACTIVE_SENSOR_FLAG)
	 	sendAvailableSensor = 1;
	
	else if(tempVar == 1){

		isEnabled = 1;
		freqRequerida = (unsigned char) charRecebido;
			setOutput(1,0,low);
			setOutput(1,1,high);
       			configuraTimer(); 
	}
	 	
}
