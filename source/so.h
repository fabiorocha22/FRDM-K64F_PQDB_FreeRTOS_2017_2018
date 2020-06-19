/*
 * so.h
 *
 *  Created on: 11/01/2018
 *      Author: fabio
 */

#ifndef SOURCE_SO_H_
#define SOURCE_SO_H_

#include "board.h"
#include "fsl_port.h"

#define SO_EN_PORT		PORTD
#define SO_CLK_PORT		PORTD
#define SO_DATA_PORT	PORTC

#define SO_EN_GPIO		GPIOD
#define SO_CLK_GPIO		GPIOD
#define SO_DATA_GPIO	GPIOC

#define SO_EN_PIN		0U
#define SO_CLK_PIN		2U
#define SO_DATA_PIN		12U

void soInit (void);
void soWrite(int value);

#endif /* SOURCE_SO_H_ */
