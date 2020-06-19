/*
 * ssd.c
 *
 *  Created on: 16/01/2018
 *      Author: fabio
 */

#include "ssd.h"

//vetor para armazenar a conversao do display
//ed0cgafb
static const char valor[] = {0xD7, 0x11, 0xCD, 0x5D, 0x1B, 0x5E, 0xDE, 0x15, 0xDF, 0x5F,
							 0x9F, 0xDA, 0xC6, 0xD9, 0xCE, 0x8E, 0xD1, 0xD5, 0xDC};
//armazena qual e o display disponivel
static char display;
//armazena o valor a ser enviado ao display
static char v0=0, v1=0, v2=0, v3=0;

void ssdDigit(char position, char value){
    if (position == 0){ v0 = value; }
    if (position == 1){ v1 = value; }
    if (position == 2){ v2 = value; }
    if (position == 3){ v3 = value; }
}

void ssdOff(void){
    //DISP1_PIN = 0;
	GPIO_ClearPinsOutput(DISP1_GPIO, 1U << DISP1_PIN);
    //DISP2_PIN = 0;
	GPIO_ClearPinsOutput(DISP2_GPIO, 1U << DISP2_PIN);
    //DISP3_PIN = 0;
	GPIO_ClearPinsOutput(DISP3_GPIO, 1U << DISP3_PIN);
    //DISP4_PIN = 0;
	GPIO_ClearPinsOutput(DISP4_GPIO, 1U << DISP4_PIN);
}

void ssdUpdate(void){
    //DISP1_PIN = 0;
	GPIO_ClearPinsOutput(DISP1_GPIO, 1U << DISP1_PIN);
    //DISP2_PIN = 0;
	GPIO_ClearPinsOutput(DISP2_GPIO, 1U << DISP2_PIN);
    //DISP3_PIN = 0;
	GPIO_ClearPinsOutput(DISP3_GPIO, 1U << DISP3_PIN);
    //DISP4_PIN = 0;
	GPIO_ClearPinsOutput(DISP4_GPIO, 1U << DISP4_PIN);


    switch(display){ //liga apenas o display da vez
    case 0:
        soWrite(valor[v0]);
        GPIO_SetPinsOutput(DISP1_GPIO, 1U << DISP1_PIN);
        display = 1;
        break;
    case 1:
        soWrite(valor[v1]);
        GPIO_SetPinsOutput(DISP2_GPIO, 1U << DISP2_PIN);
        display = 2;
        break;
    case 2:
        soWrite(valor[v2]);
        GPIO_SetPinsOutput(DISP3_GPIO, 1U << DISP3_PIN);
        display = 3;
        break;
    case 3:
        soWrite(valor[v3]);
        GPIO_SetPinsOutput(DISP4_GPIO, 1U << DISP4_PIN);
        display = 0;
        break;
    default:
        display = 0;
        break;
    }
}

void ssdInit(void){
    soInit();
    //configurao dos pinos de controle

    CLOCK_EnableClock(kCLOCK_PortA);
    CLOCK_EnableClock(kCLOCK_PortB);

    PORT_SetPinMux(DISP1_PORT, DISP1_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(DISP2_PORT, DISP2_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(DISP3_PORT, DISP3_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(DISP4_PORT, DISP4_PIN, kPORT_MuxAsGpio);

    DISP1_GPIO->PDDR |= (1U << DISP1_PIN);
    DISP2_GPIO->PDDR |= (1U << DISP2_PIN);
    DISP3_GPIO->PDDR |= (1U << DISP3_PIN);
    DISP4_GPIO->PDDR |= (1U << DISP4_PIN);

    v0 = 0;
    v1 = 0;
    v2 = 0;
    v3 = 0;
}






