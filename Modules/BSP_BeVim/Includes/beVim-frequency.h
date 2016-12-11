/*beVim-frequency.h
 * autor: Pedro Inazawa
 *
 * Essa biblioteca faz calculos de frequencia baseados numa timestamp de 3 bytes, que aumenta conforme uma
 * resolução.
 * */

//Construcao: MSB | ... | LSB
//ts_pico1[3] = {x,y,z}
//ts_pico2[3] = {a,b,c}

//Resolução da timestamp em ms.
#define TS_RESOLUTION_IN_MS 5


//A frequencia minima da  mesa é 1 hz ====> PERIODO 1   s    ou 200 * 5 ms
//A frequencia máxima da mesa é 100hz ====> PERIODO 0.1 s    ou  10 * 5 ms
//a timestamp eleva de 5ms em 5ms


/*
 * @name: Calcula frequencia
 * @param: ponteiros para os valores de timestamp, com 3 bytes cada um, separados em chars sem sinal.
 *
 * @return: Char sem sinal com o valor da frequencia em HZ dentro dos patamares permitidos (até o valor máximo do tipo, 255 hz).
 * */
unsigned char beVim_calcula_Freq( unsigned char *ts_picoA, unsigned char *ts_picoB);


/*
 * @name: Modulo da diferença entre dois valores de 3 bytes
 * @param: ponteiro para um vetor de chars que tenha os três bytes do número separado
 *
 * @return: numero de 4 bytes com o valor da diferença em módulo
 * */
unsigned long int _diferencaTriByteModule(unsigned char *ts_picoA, unsigned char *ts_picoB);
