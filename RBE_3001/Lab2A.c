/*
 * Lab2A.c
 *
 *  Created on: Feb 1, 2017
 *      Author: vargoal
 */
#include "Lab2A.h"
#include "Pinout.h"
#include "GlobalTiming.h"

void setup() {
	//Testing ports setup
	initRBELib();
	initSPI(); //Initalizes SPI bus
	initADC(4);
	initGlobalTimer();
}

void loop() {
	long time = getGlobalTime();
	unsigned int val =getADC(M0_POT_PIN);
	unsigned int valTwo =getADC(M1_POT_PIN);
	int angleOne = potAngle(M0_POT_PIN);
	int angleTwo = potAngle(M1_POT_PIN);
	int mVOne = potVolts(M0_POT_PIN);
	int mVTwo = potVolts(M1_POT_PIN);
	printf("%i,%i,%i,%i,%i,%i,%i\n",time,val,valTwo,angleOne,angleTwo,mVOne,mVTwo);
	_delay_ms(75);
}

