# FRDM-K64F_PQDB_FreeRTOS_2017_2018
Projeto de iniciação científica realizado de março de 2017 a fevereiro de 2018 pela FAPEMIG, orientado pelo professor Rodrigo Maximiano Antunes de Almeida. Título: Desenvolvimento de Plataforma Embarcada para Ensino.


## Biblioteca ad.h
Esta biblioteca implementa a interface de código para a utilização do conversor analógico-digital. Para a utilização deste periférico é necessária a inicialização do dispositivo e a rotina de leitura dos dados, tais que podem ser do sensor de temperatura, do sensor de luminosidade ou do potenciômetro.
  
#### Função void adInit(void)

Nesta rotina é inicializado o ADC de 16 bits de resolução, é configurado o trigger de hardware, é feita a auto calibração.
Além disso, a interrupção de sinalização de fim de conversão não foi habilitada. Este procedimento foi realizado para os  
três periféricos que se relacionam com o microcontrolador através dos dados da tabela abaixo.

##### Definições de interface com o  ADC do microcontrolador
                        
| Definições | Temperatura | LDR  | Potenciômetro |
|------------|-------------|------|---------------|
| Base       | ADC0        | ADC0 | ADC1          |
| Grupo      | 0U          | 0U   | 0U            |
| Canal      | 12U         | 13U  | 14U           |
      
#### Função int adRead(int channel)
		 
Este procedimento realiza a leitura do valor do ADC assim que a conversão é finalizada. Para garantir que a conversão terminou verifica-se se a flag de fim de conversão foi sinalizada.
 
## Biblioteca so.h

Na placa PQDB alguns periféricos foram multiplexados com o intuito de economizar a quantidade de terminais utilizados do microcontrolador. Esta biblioteca implementa os códigos necessários para realizar esta multiplexação dos periféricos através do registrador de deslocamento 74HC595.
	
#### Função void soInit (void)

Para a comunicação com o circuito integrado foram utilizados três terminais que são caracterizados como é indicado na tabela abaixo. Para a inicialização foi habilitado o clock para as ports utilizadas, foi definida a operação do registro como GPIO e foi definida a direção dos terminais como saída através do registrador PDDR.

##### Terminais utilizados na multiplexação
| Definições | Enable | Clock | Data  |
|------------|--------|-------|-------|
| PORT       | PORTD  | PORTD | PORTC |
| GPIO       | GPIOD  | GPIOD | GPIOC |
| PINO       | 0U     | 2U    | 12U   |

#### Função void soWrite(int value)

Nesta seção é realizado o deslocamento de cada um dos 8 bits um a cada pulso de clock transferindo a informação desejada por completo. Se a informação for maior que 8 bits é possível particionar em pacotes deste tamanho e mandar ao registrador por etapas.

## Biblioteca lcd.h

Esta biblioteca implementa os códigos de comunicação e utilização do display LCD. Vale ressaltar que sua interface com o microcontrolador não é direta, mas utiliza o registrador de deslocamento como intermediário para diminuir o número de terminais utilizados.

#### Função void lcdCommand(char value)

Esta função analisa o valor de comando e envia ao LCD com um tempo de delay necessário de 40µs. Este comando pode ser de limpeza do display, ou um deslocamento de linha ou coluna.
	
#### Função void lcdChar(char value)
	
Este procedimento habilita a escrita e envia o caractere recebido como parâmetro ao LCD através do registrador de deslocamento. Neste momento são enviados dois pacotes de 4 bits.
	
#### Função void lcdString(char msg[])

Esta função envia os dados ao LCD por meio de um vetor de caracteres, um por um.
	
#### Função void lcdNumber(int value)

Esta função envia um número inteiro ao LCD por meio de uma conversão para caracteres por meio da tabela ASCII.
	
#### Função void lcdPosition(int line, int col)

Esta função seleciona uma posição do LCD baseada na linha e na coluna enviados como parâmetros. O próximo dado a ser inserido no LCD partirá desta posição selecionada.
	
#### Função void lcdInit(void)

As interfaces de comunicação RS e EN são configuradas nesta rotina, de modo que é habilitado o clock, as portas são definidas como GPIO e como saídas digitais. A tabela abaixo indica os detalhes de comunicação dos terminais RS e EN com o microcontrolador.

##### Conexão do microcontrolador ao display LCD
| Definições | RS    | EN    |
|------------|-------|-------|
| PORT       | PORTC | PORTC |
| GPIO       | GPIOC | GPIOC |
| PINO       | 3U    | 2U    |

## Biblioteca rgb.h

Esta biblioteca implementa a comunicação do microcontrolador com o led RGB. Este tipo de led necessita que de três terminais de sinal digital para acessar as três componentes, vermelha, verde e azul, respectivamente.

#### Função void rgbColor(int led)

Esta rotina seleciona a componente do led que o usuário deseja acessar de modo que as cores são enumeradas segundo a tabela abaixo. Dessa maneira, é possível não somente acessar as cores primárias, mas também implementar a composição de cores.

##### Enumeração de acesso às cores primárias do led RGB
|        | Vermelho | Verde | Azul |
|--------|----------|-------|------|
| Número | 1        | 2     | 4    |

#### Função void turnOn(int led)

Esta rotina liga uma cor específica escolhida via parâmetro.

#### Função void turnOff(int led)

Esta rotina desliga uma cor específica escolhida via parâmetro.

#### Função void toggle(int led)

Esta rotina alterna o estado de uma cor específica escolhida via parâmetro.

#### Função void rgbInit(void)
	
As interfaces de comunicação com as componentes do led são configuradas nesta rotina, de modo que é habilitado o clock, as portas são definidas como GPIO e como saídas digitais. A tabela abaixo indica os detalhes de comunicação dos terminais com o microcontrolador.

##### Conexão do microcontrolador ao led RGB
| Definições | Vermelho | Verde | Azul  |
|------------|----------|-------|-------|
| PORT       | PORTB    | PORTA | PORTB |
| GPIO       | GPIOB    | GPIOA | GPIOB |
| PINO       | 9U       | 1U    | 23U   |

## Biblioteca ssd.h

Esta biblioteca implementa a comunicação com os displays de 7 segmentos. São quatro displays multiplexados na placa de modo a economizar terminais do microcontrolador.

#### Função void ssdDigit(char position, char value)

Esta função salva o valor desejado a um display especifico em um vetor, na posição correspondente. Este valor enviado deve estar no formato correto para ser devidamente decodificado no display.

#### Função void ssdUpdate(void)

Esta função percorre os displays sequencialmente e atualiza seus valores para o correspondente armazenado no vetor.
	
#### Função void ssdOff(void)

Esta função desliga todos os displays.

#### Função void ssdInit(void)

Esta função realiza a interface de comunicação com os displays assim como sua inicialização, habilitando os clocks e definindo os terminais utilizados como GPIO de saída digital. A tabela abaixo indica os detalhes de comunicações dos terminais aos displays.

##### Conexão do microcontrolador aos displays de 7 segmentos
| Definições | DISPLAY1 | DISPLAY2 | DISPLAY3 | DISPLAY4 |
|------------|----------|----------|----------|----------|
| PORT       | PORTB    | PORTA    | PORTB    | PORTA    |
| GPIO       | GPIOB    | GPIOA    | GPIOB    | GPIOA    |
| PINO       | 9U       | 1U       | 23U      | 2U       |
