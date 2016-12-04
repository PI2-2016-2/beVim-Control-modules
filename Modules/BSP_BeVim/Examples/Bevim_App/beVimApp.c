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
#define _FREQUENCY_OK_HEADER 	0x03

//Definiçoes para o TIMER (gera interrupção de 5 em 5 ms, habilitando a leitura do sensor)
#define TA_CLOCK_SOURCE 		_SMCLK
#define TA_CLOCK_DIV			8					// Divisor de 8 - Freq = 125 khz
#define TA_COUNT_MODE			countUp
#define TA_CCR0_LIMIT			625					//Limite Superior (Reset)  - 5 ms
#define TA_CCR1_LIMIT			622					//Limite Inferior (Set)
#define TA_PWM_STEP				2					//Passo para o PWM diminuir

//Definicoes para os valores de pico do acelerometro
#define PEAK_MINIMUM_LEVEL		1.5	//valor acima do qual se considera um pico (em G)
#define ACCEL_LSB_DIVIDER		16384	//Valor do LSB recebido do accelerometro.

//Variaveis relacionadas ao protocolo
int 		isEnabled 			= 0;
char 		readNow 			= 0;
char 		sendAvailableSensor 		= 0;
char 		charRecebido 			= 0;
unsigned char 	timer 				= 0;
unsigned char 	timer2 				= 0;
unsigned char 	timer3 				= 0;
unsigned char 	freqRequerida			= 0;
char 		tempVar = 0;

void mudaContador(){

	readNow = 1;
	timer++;
	
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
	unsigned char timestampPicoA[] 		= {0,0,0};
	unsigned char timestampPicoB[] 		= {0,0,0};	
	unsigned char frequenciaInstantanea = 0;
	int           aceleracaoAtual 		= 0;
	unsigned char aceleracaoRaw[]   	= {0,0};
	char 	      peakCycle			    = 0; 		//Essa variavel define se esta sendo analizado o primeiro ou o segundo pico.
	int 		  PWMAtual              = TA_CCR1_LIMIT; 
	float		accAtualFloat		= 0.0;
	//Variaveis para guardar os valores de picos

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
				
				//Desliga a interrupção global	
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
				
					//Transformação para inteiro com sinal.
				aceleracaoAtual = (((aceleracaoRaw[0] <<8 ) & 0xff00) | (aceleracaoRaw[1] & 0xff));
				accAtualFloat = (float)(aceleracaoAtual)/(float)(ACCEL_LSB_DIVIDER);
					
					//se Cumprir o requisito de nivel de pico, então atualiza ts
				if(accAtualFloat >= PEAK_MINIMUM_LEVEL){
					if(peakCycle == 0){
						timestampPicoA[0] = timer3;
					        timestampPicoA[1] = timer2;
					        timestampPicoA[2] = timer;
						peakCycle++;
					}
					else {
						timestampPicoB[0] = timer3;
						timestampPicoB[1] = timer2; 
						timestampPicoB[2] = timer;
						peakCycle--;
					}
					
				}
					//Se não for, zera a ts, e espera um novo ciclo. A idéia é avaliar só ts contiguas.	
				else { 
					timestampPicoA[0]=timestampPicoA[1]=timestampPicoA[2] = 0;
					timestampPicoB[0]=timestampPicoB[1] = timestampPicoB[2] = 0;
					peakCycle = 0;
				}
				
				//Descritivo do sensor
				beVim_putc(0x11);
				beVim_putc(aceleracaoRaw[0]);
				beVim_putc(aceleracaoRaw[1]);
				
				//beVim_putc(beVim_Accelerometer_Read_Register(MPU6050_RA_ACCEL_XOUT_H));
				//beVim_putc(beVim_Accelerometer_Read_Register(MPU6050_RA_ACCEL_XOUT_L));
				

				frequenciaInstantanea = beVim_calcula_Freq(timestampPicoA, timestampPicoB);				

				//freq
				beVim_putc(0x03);
				beVim_putc((char)frequenciaInstantanea);

				//Liga a interrupção Global.
				__bis_SR_register(GIE);
				
				//Avalia se a frequencia está OK, ou avança
				if(frequenciaInstantanea < freqRequerida){
					PWMAtual = PWMAtual - TA_PWM_STEP;
					
					if(PWMAtual <= 0)
						PWMAtual = TA_CCR1_LIMIT;

					beVim_TA_CCR1_CountUpTo(PWMAtual);

				}
				else if(frequenciaInstantanea > freqRequerida){
					
					PWMAtual = PWMAtual + TA_PWM_STEP;
					
					if(PWMAtual >= TA_CCR1_LIMIT)
						PWMAtual = 0;

					beVim_TA_CCR1_CountUpTo(PWMAtual);					
				}

				
			}		
				

		}


	}

}

void __interrupt(USCIAB0RX_VECTOR) RX_ISR(void){

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
