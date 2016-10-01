#MotorControlBoard!!

#Introdução
O inversor de frequencia escolhido para o projeto pode ser controlado usando uma referencia analogica de tensao ou de corrente para aferir a velocidade do motor a ser controlado. Foi definido que sera usada a referencia analogica de tensao pois a mesma e controlada por uma tensao que varia de 0 a 10V enquanto a referencia por corrente se da dentro de um intervalo de 4 a 20mA, o circuito de condicionamento de sinais para o intervalo de tensao acima e mais simples e robusto do que o de corrente baseado no microprocessador escolhido (MSP430). O microcontrolador nao possui uma saida de tensao analogica porem possui saidas capazes de serem utilizadas com PWM (Pulse Width Modulation), usando um simples circuito de conversao de sinais se torna possivel converter uma saida de tensao digital de PWM que varia de 0 a 3.3V (tensao maxima e minima de saida do MSP430) em uma saida de tensao analogica de 0 a 10V.

#PWM
Um sinal PWM e' uma serie de pulsos digitais com frequencia fixa porem com com periodo variavel. Assim como e' possivel transmitir um sinal analogico por primeiramente modulando o sinal em uma onda portardora e depois removendo a portadora e ficando apenas com o sinal, tambem e' possivel gerar uma tensao analogica moduladp em uma portadora digital e depois extraindo essa tensao analogica com um filtro-passa-baixas.

figura duty-cycle

Em PWM o tempo em que o sinal fica em nivel logico alto ou baixo nao costuma ser muito usado, o mais comum e' classificar o sinal de acordo com seu duty-cycle. A relacao entre duty-cycle, amplitude e tensao nominal de saida do DAC se torna bem intuitiva. No dominio da frequencia, um filtro passa-baixas suprime componentes de alta frequencia, consequentemente no dominio do tempo isso acaba "amaciando" e de certa forma tirando uma media do sinal, filtrando um sinal PWM com um filtro-passa-baixas extrai seu valor medio. 

formula tensao-dac

FILTRO PASSA BAIXAS ATIVO-REQUER FREQUENCIA DE PWM MSP











http://www.allaboutcircuits.com/technical-articles/turn-your-pwm-into-a-dac/


