/*
	beVim i2c.c

	Uma biblioteca para I2C blocante (Sem interrupção ) para MSP430

	Autor: Pedro Inazawa

	ATENÇÃO: Utilizar as funções abaixo em um escopo SEM INTERRUPção.

	Senão dá pau =)
*/

#include<msp430.h>

#ifndef __BEVIM_I2C

    #define __BEVIM_I2C

    #ifdef __MSP430F2274
    #define SDA_PIN BIT1 // 3.1
    #define SCL_PIN BIT2 // 3.2
    #endif
    
    /*Modos de funcionamento do módulo USCI_B0 - TRANSMITTER e RECEIVER*/
    typedef enum m_mode{
            I2C_TRANSMITTER = 0,
            I2C_RECEIVER    = 1
    
    }Master_Mode;
    
    /*Tipos de condições para a sinalização no barramento. - */
    typedef enum m_condition{
            I2C_START      = 0,
            I2C_STOP       = 1,
        I2C_NACK       = 2
    
    }Master_Condition;
    
    /*
            @brief:Configura o módulo USCI_B0 para ser utilizado com I2C.
            @param: slave_address - endereço de 7 bits do slave.
            @param: prescale - Divisor do clock (pela lib, está multiplexado ao SMclock)
    
    */
    void beVim_i2c_configure(unsigned char slave_address, unsigned char prescale);
    
    /*
            @brief: Identifica se o barramento está sendo utilizado.
    
    */
    void beVim_i2c_wait_bus_busy(void);
    
    
    /*
            @brief: Transmite as condições de STOP, START e NACK.
            @param: mode  - Modos de inicialização do módulo I2c.
            @param: condition - Condição a ser sinalizada para o barramento.
    
    */
    void beVim_i2c_transmit_condition(Master_Mode mode, Master_Condition condition);
    
    
    /*
            @brief: Escreve no barramento. START<transmitter> e envio de qty Bytes. Sem condição final.
            @param: c - ponteiro para vetor com os bytes a serem enviados.
            @param: qty - quantidade de posições a serem enviadas. 
            @return: 1 se a escrita foi ok, 0 se a escrita NOK.
    */
    int beVim_i2c_write_bytes(unsigned char qty, unsigned char *c);
    
    
    /*
            @brief: Le do barramento. START<RECEIVER> -> Leitura de n bytes. Condição final de STOP
            @param:  qty - Quantidade de parametros a serem lidos.
            @param:    c - Vetor de bytes a serem lidos.  
            @return : 1 se leu todos os bytes, 0 se erro.
    */
    int beVim_i2c_read_bytes(unsigned char qty, unsigned char *c);
#endif