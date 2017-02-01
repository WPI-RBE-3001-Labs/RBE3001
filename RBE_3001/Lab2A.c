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
	setPinsDir('A',1,3,1,2,3);
	setPinsDir('A',0,1,0);
	setPinsVal('A',1,1,0);

}

void loop() {
	uint8_t output = getPinsVal('A',3,1,2,3);
	printf("%d\n",output);
	_delay_ms(1000); //Delay 1 sec
}

