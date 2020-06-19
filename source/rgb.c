/*
 * rgb.c
 *
 *  Created on: 09/01/2018
 *      Author: fabio
 */

#include "rgb.h"

void rgbColor(int led) {
	if (led & RED) {
		GPIO_SetPinsOutput(RED_GPIO, 1 << RED_PIN);
	} else {
		GPIO_ClearPinsOutput(RED_GPIO, 1 << RED_PIN);
	}
	if (led & GREEN) {
		GPIO_SetPinsOutput(GREEN_GPIO, 1 << GREEN_PIN);
	} else {
		GPIO_ClearPinsOutput(GREEN_GPIO, 1 << GREEN_PIN);
	}
	if (led & BLUE) {
		GPIO_SetPinsOutput(BLUE_GPIO, 1 << BLUE_PIN);
	} else {
		GPIO_ClearPinsOutput(BLUE_GPIO, 1 << BLUE_PIN);
	}
}

void turnOn(int led) {
	if (led & RED) {
		GPIO_SetPinsOutput(RED_GPIO, 1 << RED_PIN);
	}
	if (led & GREEN) {
		GPIO_SetPinsOutput(GREEN_GPIO, 1 << GREEN_PIN);
	}
	if (led & BLUE) {
		GPIO_SetPinsOutput(BLUE_GPIO, 1 << BLUE_PIN);
	}
}

void turnOff(int led) {
	if (led & RED) {
		GPIO_ClearPinsOutput(RED_GPIO, 1 << RED_PIN);
	}
	if (led & GREEN) {
		GPIO_ClearPinsOutput(GREEN_GPIO, 1 << GREEN_PIN);
	}
	if (led & BLUE) {
		GPIO_ClearPinsOutput(BLUE_GPIO, 1 << BLUE_PIN);
	}
}

void toggle(int led){
	if (led & RED) {
		GPIO_TogglePinsOutput(RED_GPIO, 1 << RED_PIN);
	}
	if (led & GREEN) {
		GPIO_TogglePinsOutput(GREEN_GPIO, 1 << GREEN_PIN);
	}
	if (led & BLUE) {
		GPIO_TogglePinsOutput(BLUE_GPIO, 1 << BLUE_PIN);
	}
}

void rgbInit(void) {
	CLOCK_EnableClock(kCLOCK_PortA);
	CLOCK_EnableClock(kCLOCK_PortB);

	PORT_SetPinMux(RED_PORT, RED_PIN, kPORT_MuxAsGpio);
	PORT_SetPinMux(GREEN_PORT, GREEN_PIN, kPORT_MuxAsGpio);
	PORT_SetPinMux(BLUE_PORT, BLUE_PIN, kPORT_MuxAsGpio);

	RED_GPIO->PDDR |= (1U << RED_PIN);
	GREEN_GPIO->PDDR |= (1U << GREEN_PIN);
	BLUE_GPIO->PDDR |= (1U << BLUE_PIN);
}
