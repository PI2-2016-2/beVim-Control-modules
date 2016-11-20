#Protocolo de comunicação
##Changelog 
* Pedro Henrique Gonçalves Inazawa - 22/09  - Criação.

##Protocolo

Este tópico descreve como o protocolo funciona e quais as perguntas e respostas que o protocolo espera.

###Comandos reservados
Inicialmente, há uma lista de comandos especiais que são reservados.

|COMANDO|RESULTADO|
|:------:|:-------:|
|-1      |Inicia ou finaliza um perfil(um conjunto de jobs). A cada comando, o timer global é resetado. É importante observar que esse comando inicializa ou fecha a fase de espera por novos jobs|
|-2|Contabiliza todos os sensores ativos, e retorna em Mensagem padrão os sensores ativos no sistema.|


###Mensagens Padrao
Uma vez que um job esteja ativo, o protocolo prevê que cada sensor retorne valores determinados. A organização padrão desses resultados terá o seguinte formato:

|Sensor|Eixo1[Escala AD]|Eixo2[Escala AD]|Eixo3[Escala AD]|Timestamp [MS]|String|
|:-----:|:----:|:----:|:----:|:------:|:------:|
|S1|0|0|0|100|S1,0,0,0,100|

A escala AD varia de um valor de 0 a 1024.
