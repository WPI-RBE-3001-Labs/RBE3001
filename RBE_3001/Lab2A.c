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
#include <RBELib/RBELib.h>
#include <RBELib/reg_structs.h>

void setup() {
	//Testing ports setup
	initRBELib();
	initADC(4);
	initGlobalTimer();
	initMotorControl();
	setAngles(30,-30);
	setPinsDir('C',INPUT,4,4,5,6,7);
	setPinsVal('C',HIGH,4,4,5,6,7);
}

void loop() {
	//BYTE val = getPinsVal('D',4,4,5,6,7);
	//printf("%x\t",PINC);
	if(((PINC>>4)&0x01)==0x00)
	{
		setAngles(0,0);
		//printf("0\n");
	}
	else if(((PINC>>5)&0x1)==0x00)
	{
		setAngles(30,0);
		//printf("3\n");
	}
	else if(((PINC>>6)&0x1)==0x00)
	{
		setAngles(60,0);
		//printf("6\n");
	}
	else if(((PINC>>7)&0x1)==0x00)
	{
		setAngles(90,0);
		//printf("9\n");
	}
	_delay_ms(25);
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

