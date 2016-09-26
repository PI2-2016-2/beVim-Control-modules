# beVim-Control-modules
Aplicação baixo nível e módulos de controle do projeto BeVim.

#Introdução

O sistema BeVim foi imaginado com o objetivo de controlar a vibração de uma bancada de testes para ensaios vibracionais.

Dessa forma, três sistemas básicos foram criados: 

* [Sistema de Sensoriamento](../blob/master/Modules/MeasureBoard/Documentation/MeasureBoard.md): Responsável pela leitura e disponibilização dos dados tanto para os módulos de maior nível dentro do sistema (as CPUs, que se comunicam via UART) quanto por ser MESTRE da comunicação i2c com os módulos logo abaixo.

* [Sistema de Controle de Motores](../blob/master/Modules/MotorControlBoard/Documentation/MotorControlBoard.md): é um módulo controlado por i2c, que se une a rede criada pelo módulo de sensoriamento. Este é capaz de vibrar os motores, informando os dados pela rede para o módulo de sensoriamento.

* [Subsistema de expansão de Sensores](../blob/master/Modules/ExpansionBoard/Documentation/ExpansionBoard.md): É um módulo que permite expandir a quantidade de sensores no sistema (de 8 em 8 sensores).

Para mais detalhes sobre esse sistema, consulte a [Arquitetura do Sistema](../blob/master/Documentation/SystemArchitecture.md)






