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
}

void loop() {
	//_delay_ms(500);
	spiTransceive('A');
}

