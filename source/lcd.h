/*
 * lcd.h
 *
 *  Created on: 10/01/2018
 *      Author: fabio
 */

#ifndef SOURCE_LCD_H_
#define SOURCE_LCD_H_

#include "so.h"
#include "board.h"
#include "fsl_port.h"
#include "FreeRTOS.h"
#include "task.h"

#define LCD_RS_PORT PORTC
#define LCD_EN_PORT	PORTC

#define LCD_RS_GPIO GPIOC
#define LCD_EN_GPIO GPIOC

#define LCD_RS_PIN	3U
#define LCD_EN_PIN	2U

void lcdCommand(char value);
void lcdChar(char value);
void lcdString(char msg[]);
void lcdNumber(int value);
void lcdPosition(int line, int col);
void lcdInit(void);

#endif /* SOURCE_LCD_H_ */
