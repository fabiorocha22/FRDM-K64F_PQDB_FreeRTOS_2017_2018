/*
 * keypad.h
 *
 *  Created on: 10/01/2018
 *      Author: fabio
 */

#ifndef SOURCE_KEYPAD_H_
#define SOURCE_KEYPAD_H_

unsigned int kpRead(void);
char kpReadKey(void);
void kpDebounce(void);
void kpInit(void);

#endif /* SOURCE_KEYPAD_H_ */
