#Historico
	+ Pedro Henrique gonçalves Inazawa - Criação.

#Introdução

	Quando se utiliza um sistema microcontrolado, em muitas ocasiões é necessário implementar de forma recursiva alguns de seus periféricos (Timers, gpios, interfaces de comuicaão). Em muitos casos, isso é um problema, pois a quantidade de códigos aumenta de forma rápida, assim como a sua inconsistencia. Dessa forma, para simplificar e poder ao mesmo tempo padronizar a implementação, foi criado o conceito de Basic Support Package ou BSP. Esses BSPs são códigos que implementam algumas interfaces dos microcontroladores mais utilizadas, dessa forma não obrigando o programador a reimplementar a cada uso. 

#Dispositivos suportados
	+MSP430 G2452	
	  + GPIOs - Suporte a mudanças de estado de gpios, e direção das portas

#Como utilizar essa ferramenta?

	Inicialmente, utilizando o Makefile da raiz da pasta, compile todas as bibliotecas. Logo depois, na pasta examples, construa seu projeto utilizando os arquivos .o presentes na pasta Libs.

