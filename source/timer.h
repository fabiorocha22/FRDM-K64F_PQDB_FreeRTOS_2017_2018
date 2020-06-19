/*
 * timer.h
 *
 *  Created on: 20/03/2018
 *      Author: fabio
 */

#ifndef SOURCE_TIMER_H_
#define SOURCE_TIMER_H_

void timerStart(unsigned int count_val);
unsigned int timerRead(void);
void timerWait(void);
int  timerFinished(void);
void timerDelay(unsigned int time);
void timerInit(void);

#endif /* SOURCE_TIMER_H_ */
