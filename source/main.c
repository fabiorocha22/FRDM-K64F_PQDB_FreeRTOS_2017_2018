/*
 * Copyright (c) 2013 - 2016, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <string.h>

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "fsl_port.h"
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"

#include "rgb.h"
#include "lcd.h"
#include "ssd.h"
#include "ad.h"
#include "timer.h"

#define task_PRIORITY (configMAX_PRIORITIES - 1)

/*Variáveis globais*/

int pot, temp, ldr;
unsigned int i;
TaskHandle_t habRED, habBLUE, habGREEN;
uint8_t delay = 10;

/*-----------------*/

void TOGGLE_HAB(uint8_t *hab){
	if(*hab == 0)
		*hab = 1;
	else
		*hab = 0;
}

static void red_task(void *pvParameters){
	for(;;){
		turnOn(RED);
		vTaskDelay(250);
	}
}

static void blue_task(void *pvParameters){
	for(;;){
		toggle(GREEN);
		vTaskDelay(500);
	}
}

static void green_task(void *pvParameters){
	for(;;){
		toggle(BLUE);
		vTaskDelay(1000);
	}
}

static void sw2_task(void *pvParameters){
	unsigned char valAtual, valTemp, tempo;

	valTemp = GPIO_ReadPinInput(BOARD_SW2_GPIO, BOARD_SW2_GPIO_PIN);
	valAtual = valTemp;
	for(;;){
		do{
			vTaskDelay(100);
			valTemp = GPIO_ReadPinInput(BOARD_SW2_GPIO, BOARD_SW2_GPIO_PIN);
		}while(valAtual == valTemp);
		tempo = 10;
		while(tempo > 0){
			if(valTemp == GPIO_ReadPinInput(BOARD_SW2_GPIO, BOARD_SW2_GPIO_PIN))
				tempo--;
			else {
				valTemp = GPIO_ReadPinInput(BOARD_SW2_GPIO, BOARD_SW2_GPIO_PIN);
				tempo = 10;
			}
		}
		valAtual = valTemp;
		if(valAtual == 1U){
			delay++;
		}
	}
}

static void sw3_task(void *pvParameters){
	unsigned char valAtual, valTemp, tempo;

	valTemp = GPIO_ReadPinInput(BOARD_SW3_GPIO, BOARD_SW3_GPIO_PIN);
	valAtual = valTemp;
	for(;;){
		do{
			vTaskDelay(100);
			valTemp = GPIO_ReadPinInput(BOARD_SW3_GPIO, BOARD_SW3_GPIO_PIN);
		}while(valAtual == valTemp);
		tempo = 10;
		while(tempo > 0){
			if(valTemp == GPIO_ReadPinInput(BOARD_SW3_GPIO, BOARD_SW3_GPIO_PIN))
				tempo--;
			else {
				valTemp = GPIO_ReadPinInput(BOARD_SW3_GPIO, BOARD_SW3_GPIO_PIN);
				tempo = 10;
			}
		}
		valAtual = valTemp;
		if(valAtual == 1U){
			if(valAtual == 1U){
				delay--;
			}
		}
	}
}

static void uart_task(void *pvParameters){
	char c;
	eTaskState state;
	for(;;){
		c = GETCHAR();
		switch(c){
			case 'r':
				state = eTaskGetState(habRED);
				PRINTF("ENTROU VERMELHO");
				switch(state){
					case (eReady):
						turnOff(RED);
						vTaskSuspend(habRED);
						break;
					case(eRunning):
						turnOff(RED);
						vTaskSuspend(habRED);
						break;
					case (eSuspended):
						turnOn(RED);
						vTaskResume(habRED);
						break;
				}
				break;
			case 'g':
				state = eTaskGetState(habGREEN);
				PRINTF("ENTROU VERDE");
				switch(state){
					case (eReady):
						turnOff(GREEN);
						vTaskSuspend(habGREEN);
						break;
					case(eRunning):
						turnOff(GREEN);
						vTaskSuspend(habGREEN);
						break;
					case (eSuspended):
						turnOn(GREEN);
						vTaskResume(habGREEN);
						break;
				}
				break;
			case 'b':
				state = eTaskGetState(habBLUE);
				PRINTF("ENTROU AZUL");
				switch(state){
					case (eReady):
						turnOff(BLUE);
						vTaskSuspend(habBLUE);
						break;
					case(eRunning):
						turnOff(BLUE);
						vTaskSuspend(habBLUE);
						break;
					case (eSuspended):
						turnOn(BLUE);
						vTaskResume(habBLUE);
						break;
				}
				break;
			default:
				break;
		}
	}
}

static void lcd_task(void *pvParameters){
	int potReal;
	int tempReal;
	for(;;){
		lcdPosition(0,0);
		lcdString("Pot.: ");
		potReal = (pot * 100)/4095;
		lcdNumber(potReal);
		lcdPosition(1,0);
		lcdString("Luz: ");
		tempReal = (ldr * 100)/4095;
		lcdNumber(tempReal);
		//lcdString(" oC");
		vTaskDelay(pdMS_TO_TICKS(200));
	}
}

static void ad_task(void *pvParameters){
	int ad;
	for(;;){
		vTaskDelay(pdMS_TO_TICKS(100));
		temp = adRead(0);
		PRINTF("Temp:  %d", temp);

		vTaskDelay(pdMS_TO_TICKS(100));
		ldr = adRead(1);
		PRINTF("LDR: %d", ldr);

		vTaskDelay(pdMS_TO_TICKS(100));
		pot = adRead(2);
		PRINTF("Pot: %d", pot);
	}
}

static void timer_task(void *pvParameters){
	for(;;){
		PRINTF("\n entrou \r\n");
		timerDelay(1000);
		if(timerFinished()){
			LED_RED_TOGGLE();
		}
	}
}

static void ssd_task(void *pvParameters){
	for(;;){
		ssdDigit(0, 14);
		ssdDigit(1, 15);
		ssdDigit(2, 14);
		ssdDigit(3, 1);
		vTaskDelay(pdMS_TO_TICKS(5));
		ssdUpdate();
	}
}

int main(void) {
	/* Init board hardware. */
 	BOARD_InitPins();
	BOARD_BootClockRUN();
	BOARD_InitDebugConsole();

	lcdInit();
	adInit();
	rgbInit();

	xTaskCreate(lcd_task, "LCD_TASK", configMINIMAL_STACK_SIZE+50, NULL, task_PRIORITY, NULL);
	xTaskCreate(ad_task, "", configMINIMAL_STACK_SIZE, NULL, task_PRIORITY, NULL);
	xTaskCreate(red_task, "RED_TASK", configMINIMAL_STACK_SIZE+50, NULL, task_PRIORITY, NULL);
	xTaskCreate(blue_task, "BLUE_TASK", configMINIMAL_STACK_SIZE+50, NULL, task_PRIORITY, NULL);
	xTaskCreate(green_task, "GREEN_TASK", configMINIMAL_STACK_SIZE+50, NULL, task_PRIORITY, NULL);
	vTaskStartScheduler();

	for(;;) { /* Infinite loop to avoid leaving the main function */
		__asm("NOP"); /* something to use as a breakpoint stop while looping */
	}
}
