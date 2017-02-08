/*
 * Lab2A.c
 *
 *  Created on: Feb 1, 2017
 *      Author: vargoal
 */
#include "Lab2A.h"
#include "Pinout.h"
#include "GlobalTiming.h"
#include "MotorCont.h"
void setup() {
	//Testing ports setup
	initRBELib();
	initADC(4);
	initGlobalTimer();
	initMotorControl();
	setAngles(45,-45);
}

void loop() {
	/*long time = getGlobalTime();
	unsigned int val = getADC(M0_POT_PIN);
	unsigned int valTwo = getADC(M1_POT_PIN);
	int angleOne = potAngle(M0_POT_PIN);
	int angleTwo = potAngle(M1_POT_PIN);
	int mVOne = potVolts(M0_POT_PIN);
	int mVTwo = potVolts(M1_POT_PIN);
	printf("%f,%i,%i,%i,%i,%i,%i\n",(float)time,val,valTwo,angleOne,angleTwo,mVOne,mVTwo);
	setMotorPwr(0,30*(4096/100));
	setMotorPwr(1,30*(4096/100));
	_delay_ms(75);*/

}

