/*
 * Lab2A.c
 *
 *  Created on: Feb 1, 2017
 *      Author: vargoal
 */
#include "Lab2A.h"

void setup() {
	//Testing ports setup
	initRBELib();
	initSPI(); //Initalizes SPI bus
	initADC(4);
}

void loop() {
	unsigned int val =getADC(4);
	printf("%i\n",val);
	_delay_ms(250); //Delay .25 sec
}

