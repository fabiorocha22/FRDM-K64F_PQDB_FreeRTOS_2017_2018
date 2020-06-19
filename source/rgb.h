/*
 * rgb.h
 *
 *  Created on: 09/01/2018
 *      Author: fabio
 */

#ifndef SOURCE_RGB_H_
#define SOURCE_RGB_H_

#include "board.h"
#include "fsl_port.h"

//ports leds
#define	RED_PORT	PORTB
#define	GREEN_PORT	PORTA
#define	BLUE_PORT	PORTB

//gpio leds
#define	RED_GPIO	GPIOB
#define	GREEN_GPIO	GPIOA
#define	BLUE_GPIO	GPIOB

//pinos correspondentes
#define	RED_PIN		9U
#define	GREEN_PIN	1U
#define	BLUE_PIN	23U

//todos desligados
#define	OFF	0

//cores primárias
#define RED		1
#define GREEN	2
#define BLUE	4

//cores secundárias
#define YELLOW (RED+GREEN)
#define CYAN   (GREEN+BLUE)
#define PURPLE (RED+BLUE)

//todos acesos
#define WHITE	(RED+GREEN+BLUE)

void rgbColor(int led);
void turnOn(int led);
void turnOff(int led);
void toggle(int led);
void rgbInit(void);

#endif /* SOURCE_RGB_H_ */
