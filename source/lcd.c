/*
 * lcd.c
 *
 *  Created on: 10/01/2018
 *      Author: fabio
 */

#include "lcd.h"

#include "fsl_debug_console.h"

//para um cristal de 8MHz cada instrução
//gasta 33,33 ns

void Delay5us(void){ // 150 instruções
	unsigned char i;
	for(i = 0; i < 49; i++); //3 + 3 * 49 = 150
}

void Delay40us(void){ // 1200 instruções
	unsigned int i;
	for(i = 0; i < 399*15; i++); //3 + 3 * 399 = 1200
}

void Delay80us(void){
	Delay40us();
	Delay40us();
}

void Delay160us(void){
	Delay80us();
	Delay80us();
}

void Delay2ms(void){ // 60006 instruções
	unsigned int i;
	for(i = 0; i < 20001*15; i++); //3 + 3 * 20001 = 60006
}

void Delay5ms(void){ // 150015 instruções
	unsigned int i;
	for(i = 0; i < 50004*15; i++); //3 + 3 * 50004 = 150015
}

void Delay10ms(void){ // 150015 instruções
	Delay5ms();
	Delay5ms();
}

void Delay15ms(void){ // 450045 instruções
	long int i;
	Delay5ms();
	Delay5ms();	Delay5ms();
}

//Gera um clock no enable
void pulseEnablePin(void){
	GPIO_SetPinsOutput(LCD_EN_GPIO, 1U << LCD_EN_PIN);
//	Delay5us();

	GPIO_ClearPinsOutput(LCD_EN_GPIO, 1U << LCD_EN_PIN);
//	Delay5us();
}

//Envia 4 bits e gera um clock no enable
void pushNibble(char value, int rs){
	soWrite(value);
	if(rs)
		GPIO_SetPinsOutput(LCD_RS_GPIO, 1U << LCD_RS_PIN);
	else
		GPIO_ClearPinsOutput(LCD_RS_GPIO, 1U << LCD_RS_PIN);
	pulseEnablePin();
}

//Envia 8 bits em dois pacotes de 4
void pushByte(char value, int rs){
	if(rs)
		GPIO_SetPinsOutput(LCD_RS_GPIO, 1U << LCD_RS_PIN);
	else
		GPIO_ClearPinsOutput(LCD_RS_GPIO, 1U << LCD_RS_PIN);

	soWrite(value >> 4);
	pulseEnablePin();
	soWrite(value);
	pulseEnablePin();
}

void lcdCommand(char value){
	pushByte(value, 0);
	Delay40us();
	if((value==0x03)||(value==0x02)||(value==0x01)){
		Delay2ms();
	}
}

void lcdPosition(int line, int col){
	if (line == 0) {
		lcdCommand(0x80 + (col % 16));
	}
	if (line == 1) {
		lcdCommand(0xC0 + (col % 16));
	}
}

void lcdChar(char value){
	pushByte(value, 1);
	Delay40us();
}

//Imprime um texto(vetor de char)
void lcdString(char msg[]){
	int i = 0;
	while (msg[i] != 0) {
		lcdChar(msg[i]);
		i++;
	}
}

void lcdNumber(int value){
	int i = 1000000; //M�ximo 999.999
	while (i > 0) {
		lcdChar((value / i) % 10 + 48);
		i /= 10;
	}
}

//Rotina de inicialização
void lcdInit(void){
	soInit();

	CLOCK_EnableClock(kCLOCK_PortC);

	PORT_SetPinMux(LCD_EN_PORT, LCD_EN_PIN, kPORT_MuxAsGpio);
	PORT_SetPinMux(LCD_RS_PORT, LCD_RS_PIN, kPORT_MuxAsGpio);

	LCD_EN_GPIO->PDDR |= (1U << LCD_EN_PIN);
	LCD_RS_GPIO->PDDR |= (1U << LCD_RS_PIN);

	Delay15ms();
	// Comunicação começa em estado incerto
	pushNibble(0x03, 0);
	Delay5ms();
	pushNibble(0x03, 0);
	Delay160us();
	pushNibble(0x03, 0);
	Delay160us();
	// Mudando comunicação para 4 bits
	pushNibble(0x02, 0);
	Delay10ms();
	// Configura o display
	lcdCommand(0x28);         //8bits, 2 linhas, fonte: 5x8
	lcdCommand(0x08 + 0x04);  //display on
	lcdCommand(0x01);         //limpar display, voltar p/ posi��o 0
}

