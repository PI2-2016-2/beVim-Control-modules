#Documento de arquitetura

##Histórico
24/setembro - Pedro Henrique Gonçalves Inazawa - Criação

##Sobre este documento
Este documento descreve a arquitetura atual do projeto, bem como documenta as mudanças que o projeto sofreu com o decorrer do processo de desenvolvimento.

#Sistema de controle BeVim.

##Módulos
O sistema BeVim é composto pelos seguintes módulos

 *Módulo de Sensoriamento - Parte responsável pela leitura de sensores, comunicação com a CPU e controle dos módulos de motores.
 *Módulo de Motor - Parte responsável pelo controle de inversores, e pela retroalimentação em malha fechada para atingir frequencias altas.

Ambos os moódulos são conectados entre si por uma rede I2C (InterIntegrated Circuits), onde o módulo de sensoriamento sempre atua como mestre no processo de comunicação. Esse procedimento foi escolhido pela possibilidade de se adicionar de maneira fácil outros módulos (de motor, por exemplo, ou outros que sejam de interesse a serem desenvolvidos), não interferindo com outros sistemas perifericos a mesa. 

A seguir, serão explicados de maneira mais detalhada cada um dos módulos que envolvem a mesa. 

###Módulo de Sensoriamento.

O módulo de sensoriamento é o responsável pela implementação da interface (via protocolo BeVim) com o sistema que controla a mesa em alto nível - a CPU. Ao mesmo tempo, esse módulo executa um controle da leitura dos sensores digitais do projeto, e dos outros módulos acoplados (os de motores).

Este módulo é composto dos seguintes submódulos:

 *Submódulo de Comunicação Serial : Este submódulo é o responsável pela implementaçao das várias comunicações disponíveis no sistema, que são a UART, a SPI e a I2c. Este é um módulo misto de Firmware e Hardware, que será Mestre nas comunicações seriais de I2c/SPI e escravo na comunicação UART.

 *Submódulo de Acomodação de sensores : Este submódulo é o responsável pela implementação do sistema de 

###Módulo de Motor - 
