# beVim-Control-modules
Aplicação baixo nível e módulos de controle do projeto BeVim.
#Histórico

. Pedro Henrique Gonçalves Inazawa - Criação

#Introdução

O sistema BeVim se trata de uma bancada de testes, criada com o intuito de fazer ensaios vibracionais em diversas estruturas. Nesse contexto, dentre os 4 grandes módulos do projeto, o sistema de Controle visa fazer uma "ponte' entre as camadas mais inferiores do projeto (sistema mecânico e de rotação do motor) com as camadas de mais alto nível (sistema web), promovendo interação entre ambos. 

Os objetivos desse grande grupo são:

 * promover o controle transparente das funções de vibração da mesa, ao mesmo tempo que fornecendo dados de como ela está operando. 

 * Ser um sistema modular e escalável também, isto é, deve ser possível aumentar a quantidade de sensores e de motores da mesa da forma que melhor convier para os ensaios feitos na mesa.

 * Promover a vibração correta e com uma estimativa de erro, com um melhor ajuste entre as frequencias de 50 a 100 Hz.


##Módulos básicos do sistema de controle

Três sistemas básicos foram criados: 

 * [Sistema de Sensoriamento](Modules/MeasureBoard/Documentation/MeasureBoard.md): Responsável pela leitura e disponibilização dos dados tanto para os módulos de maior nível dentro do sistema (as CPUs, que se comunicam via UART) quanto por ser MESTRE da comunicação i2c com os módulos logo abaixo.

 * [Sistema de Controle de Motores](Modules/MotorControlBoard/Documentation/MotorControlBoard.md): é um módulo controlado por i2c, que se une a rede criada pelo módulo de sensoriamento. Este é capaz de vibrar os motores, informando os dados pela rede para o módulo de sensoriamento.

 * [Subsistema de expansão de Sensores](Modules/ExpansionBoard/Documentation/ExpansionBoard.md): É um módulo que permite expandir a quantidade de sensores no sistema (de 8 em 8 sensores).

Para mais detalhes sobre esse sistema, consulte a [Arquitetura do Sistema](Documentation/SystemArchitecture.md)

Para mais detalhes sobre os protocolos de comunicação implementados pelo projeto, consulte a [Descrição de protocolos](Simulators/BeVim-Protocol-Simulator/Documentation/Protocol.md)






