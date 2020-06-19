/*
 * ssd.h
 *
 *  Created on: 16/01/2018
 *      Author: fabio
 */

#ifndef SOURCE_SSD_H_
#define SOURCE_SSD_H_

#include "so.h"
#include "FreeRTOS.h"

#define DISP4_PORT	PORTA
#define DISP3_PORT	PORTB
#define DISP2_PORT	PORTA
#define DISP1_PORT	PORTB

#define DISP4_GPIO	GPIOA
#define DISP3_GPIO	GPIOB
#define DISP2_GPIO	GPIOA
#define DISP1_GPIO	GPIOB

#define DISP4_PIN	2U
#define DISP3_PIN	23U
#define DISP2_PIN	1U
#define DISP1_PIN	9U

void ssdDigit(char position, char value);
void ssdUpdate(void);
void ssdOff(void);
void ssdInit(void);

#endif /* SOURCE_SSD_H_ */
