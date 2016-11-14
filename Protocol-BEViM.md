#Protocolo BEViM de Comunicação Serial
##Histórico de Alterações
| Data | Versão | Descrição | Responsáveis |
|:------:|:-------:|:--------:|:---------:|
|09/11/2016|1.0| Formalização do protocolo de comunicação oficial entre MSP e Servidor de dados I/O | Pedro Inazawa, João Guimarães, Matheus Ferraz, Paulo Borba |

##Formalização do protocolo

Este protocolo foi desenvolvido de forma a tentar otimizar a comunicação entre MSP e o servidor de dados que irá enviar as informações para a aplicação em alto nível. O design deste protocolo levou-se em consideração o mapeamento de flags, metadados e dados de forma a obter o melhor desempenho de comunicação possível, sem gargalar entre taxa de transmissão dos hardwares.

##Design do protocolo

Nesta seção será explicado o design adotado para o protocolo de envio e recebimento de informações dentro da comunicação serial via UART.

###INPUT de Comandos:

Foram definidos uma lista de inputs especiais de modo que torne facilitado o envio de comandos de controle ao MSP, levando em consideração que o tamanho da mensagem neste primeiro contexto de envio não interfere em nada e possui o tamanho de 1 BYTE.

|FLAG|COMANDO|RESULTADO|
|:-------:|:------:|:-------:|
| Inicio/Parada | 0x01 | Inicia ou finaliza um ensaio (um conjunto de jobs). É importante observar que esse comando inicializa ou fecha a fase de espera por novos jobs. |
| Sensores Ativos |0x02 | Contabiliza todos os sensores ativos, e retorna em Mensagem padrão os sensores ativos no sistema. |
| Frequência Desejada | x | Neste comando X representa o valor da frequência que o usuário deverá informar nos jobs, que serão repassados que o sistema de controle, para que o motor vibre da frequência determinada para análise (Entre 50Hz e 100Hz). |

###OUTPUT de Dados:

Nesta seção irá formaliza o formato padrão de saída de dados bem como alguns significados pré-definidos para otimização da consulta de dados pela porta serial.

* **Formato =  __[HEADER]__ + __[DADO]__**

| Dados Esperados | Formato Utilizado | Formato em Bytes |
|:--------:|:--------:|:----------:|
| Timestamp | [0x01] + [DADO] | [1 BYTE] + [3 BYTES] |
| Sensor | [4 bits para sensor / 4 bits para eixo] + [DADO] | [1 BYTE] + [2 BYTES (Em Complemento de 2)] |
| Frequencia Atingida | [0x03] | [1 BYTE] |

* Timestamp - Resolução 5 ms/bit
* Sensor - Os 4 MSB do Byte definem qual o sensor que é em binário e os 4 LSB deinem qual é o eixo que o dado está sendo amostrado.
* Frequencia Atingida - Flag para indicar que a frequência desejada foi atingida.

###Leitura dos Sensores Ativos:

Para identificação dos sensores ativos, foi acordado a utilização de um BYTE apenas, sendo esse byte responsável pela representação de 8 sensores, e podendo ser escalável com adição de mais bytes, caso tenha adição de mais de 8 sensores ao sistema.

* 1 BYTE composto por 8 bits, sendo cada bit responsável por um sensor.
* 0 Indica que o Sensor está desativado e 1 indica que o sensor está ativado.

*Exemplo abaixo da análise de um BYTE para identificação dos sensores ativos:

| 0 | 0 | 1 | 1 | 0 | 1 | 1 | 1 |
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
| S8 | S7 | S6 | S5 | S4 | S3 | S2 | S1 |

* Isso indica que os sensores S6, S5, S3, S2 e S1 estão ativos


###Sequência do OUTPUT de Dados:

Na tabela abaixo temos um exemplo da ordem do OUTPUT dos dados que serão enviados pela via serial

| Dado | Ordenação |
|:---------:|:----------:|
| Timestamp | 1° |
| Sensor 1 - Eixo X | 2° |
| Sensor 1 - Eixo Y | 3° |
| Sensor 1 - Eixo Z | 4° |
| Sensor 2 - Eixo X | 5° |
| Sensor 2 - Eixo Y | 6° |
| Sensor 2 - Eixo Z | 7° |
| Sensor 3 - Eixo X | 8° |
| Sensor 3 - Eixo Y | 9° |
| Sensor 3 - Eixo Z | 10° |
| Sensor 4 - Eixo X | 11° |
| Sensor 4 - Eixo Y | 12° |
| Sensor 4 - Eixo Z | 13° |
| Sensor 5 - Eixo X | 14° |
| Sensor 5 - Eixo Y | 15° |
| Sensor 5 - Eixo Z | 16° |
| Sensor 6 - Eixo X | 17° |
| Sensor 6 - Eixo Y | 18° |
| Sensor 6 - Eixo Z | 19° |

##Escala dos dados

Segundo o datasheet dos acelerômetros, a resolução dos sensores medem até 16G em uma escala 0 até 1024 AD por causa da resolução, e utilizam 2 BYTES para demonstrar essa medição. Para isso então foi feito uma escala em AD:

* AD = 0 então G = 0
* AD = 1024 então G = 16

Sendo Valor de G = 9,80665 m/s^2
