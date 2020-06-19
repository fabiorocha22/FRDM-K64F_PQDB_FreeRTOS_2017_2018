/*
 * so.c
 *
 *  Created on: 11/01/2018
 *      Author: fabio
 */

#include "so.h"

void soInit(void){
	CLOCK_EnableClock(kCLOCK_PortC);
	CLOCK_EnableClock(kCLOCK_PortD);

	PORT_SetPinMux(SO_EN_PORT, SO_EN_PIN, kPORT_MuxAsGpio);
	PORT_SetPinMux(SO_CLK_PORT, SO_CLK_PIN, kPORT_MuxAsGpio);
	PORT_SetPinMux(SO_DATA_PORT, SO_DATA_PIN, kPORT_MuxAsGpio);

	SO_EN_GPIO->PDDR |= (1U << SO_EN_PIN);
	SO_CLK_GPIO->PDDR |= (1U << SO_CLK_PIN);
	SO_DATA_GPIO->PDDR |= (1U << SO_DATA_PIN);
}

//pulso de clock para habilitar os dados na saída
void PulseEnClock(void){
	GPIO_SetPinsOutput(SO_EN_GPIO, 1U << SO_EN_PIN);
	GPIO_ClearPinsOutput(SO_EN_GPIO, 1U << SO_EN_PIN);
}

//pulso de clock para enviar um bit
void PulseClockData(void){
	GPIO_SetPinsOutput(SO_CLK_GPIO, 1U << SO_CLK_PIN);
	GPIO_ClearPinsOutput(SO_CLK_GPIO, 1U << SO_CLK_PIN);
}

void soWrite(int value){
	char i;
	GPIO_ClearPinsOutput(SO_CLK_GPIO, 1U << SO_CLK_PIN);
	for(i = 0; i < 8; i++){
		if(value & 0x80)
			GPIO_SetPinsOutput(SO_DATA_GPIO, 1U << SO_DATA_PIN);
		else
			GPIO_ClearPinsOutput(SO_DATA_GPIO, 1U << SO_DATA_PIN);
		PulseClockData();
		value <<= 1;
	}
	PulseEnClock();
}
