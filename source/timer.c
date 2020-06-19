/*
 * timer.c
 *
 *  Created on: 20/03/2018
 *      Author: fabio
 */

#include "fsl_debug_console.h"
#include "board.h"

#include "fsl_lptmr.h"
#include "fsl_gpio.h"

#include "pin_mux.h"
#include "clock_config.h"

//#define LPTMR_LED_HANDLER LPTMR0_IRQHandler
#define LPTMR_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_LpoClk)
#define LPTMR_USEC_COUNT 1000000U

volatile uint32_t lptmrCounter = 0U;

int interval;
lptmr_config_t lptmrConfig;

void timerStart(unsigned int count_val){

	interval = count_val;

	LPTMR_SetTimerPeriod(LPTMR0, USEC_TO_COUNT(count_val, LPTMR_SOURCE_CLOCK));

	//LPTMR_EnableInterrupts(LPTMR0, kLPTMR_TimerInterruptEnable);

	//EnableIRQ(LPTMR0_IRQn);

	LPTMR_StartTimer(LPTMR0);
}

unsigned int timerRead(void){
	return LPTMR_GetCurrentTimerCount(LPTMR0);
}

void timerWait(void){
	PRINTF("\n INTERVAL: %d \r\n", LPTMR_GetCurrentTimerCount(LPTMR0));
	while(LPTMR_GetCurrentTimerCount(LPTMR0) <= interval){
		PRINTF("\n lptmrCounter: %d \r\n", LPTMR_GetCurrentTimerCount(LPTMR0));
	}
	LPTMR_StopTimer(LPTMR0);
}

int timerFinished(void){
	if(lptmrCounter >= interval){
		return 1;
	}
	else{
		return 0;
	}
}

void timerDelay(unsigned int time){
	timerStart(time);
	timerWait();
}

void timerInit(void){
	interval = 0;
	LPTMR_GetDefaultConfig(&lptmrConfig);
	LPTMR_Init(LPTMR0, &lptmrConfig);
}
