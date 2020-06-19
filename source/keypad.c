/*
 * keypad.c
 *
 *  Created on: 10/01/2018
 *      Author: fabio
 */

#include "keypad.h"

#define bitSet(arg,bit) ((arg) |= (1<<bit))
#define bitClr(arg,bit) ((arg) &= ~(1<<bit))
#define bitFlp(arg,bit) ((arg) ^= (1<<bit))
#define bitTst(arg,bit) ((arg) & (1<<bit))

static unsigned int keys;

//vetor com o "nome" dos botões
//U -> up, L -> left, D -> down, R -> right
//S -> start, s -> select
//a ordem é referente a posição dos botões
static const char charKey[] = {'U','L','D','R','S','X','Y','A','B','s'};

unsigned int kpRead(void){
	return keys;
}

char kpReadKey(void){
	int i;
	for(i = 0; i < 10; i++){
		if(keys & (1<<i)){
			return charKey[i];
		}
	}
	//nenhuma tecla pressionada
	return 0;
}

void kpDebounce(void){

}
