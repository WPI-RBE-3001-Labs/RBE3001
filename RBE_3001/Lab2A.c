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

XYTarget targets[4];

void setup() {
	//setup targets
	targets[0].x = 7.5*25.4;
	targets[0].y = 6*25.4;
	targets[1].x = 7.5*25.4;
	targets[1].y = 8*25.4;
	targets[2].x = 5.5*25.4;
	targets[2].y = 7*25.4;
	targets[3].x = 7.5*25.4;
	targets[3].y = 6*25.4;

	//init everything
	initRBELib();
	initADC(4);
	initGlobalTimer();
	initMotorControl();
	setAngles(30,-30);
	setPinsDir('C',INPUT,4,4,5,6,7);
	setPinsVal('C',HIGH,4,4,5,6,7);
	ArmPose pose = getPoseFromXY(7.5*25.4,6*25.4);
	setAngles(pose.thetaZero,pose.thetaOne);
	printf("%i,%i\n",pose.thetaZero,pose.thetaOne);
	_delay_ms(3000);
	printf("Start\n");
	/*for(int i = 0;i<3;i++)
	{
		ArmPose pose = getPoseFromXY(targets[i].x,targets[i].y);
		setAngles(pose.thetaZero,pose.thetaOne);
		while(atAngle() != 0x1) {_delay_ms(50);} //wait till at angle
		printf("Done\n");
		_delay_ms(1000);
	}*/
	//_delay_ms(3000);
}

void loop() {
	//BYTE val = getPinsVal('D',4,4,5,6,7);
	//printf("%x\t",PINC);
	if(((PINC>>4)&0x01)==0x00)
	{
		//printf("Btn press");
		//_delay_ms(50);
		//setAngles(0,0);
		for(int i = 0;i<4;i++)
		{
			goToXYWithLine(targets[i].x,targets[i].y);
			//while(atAngle() != 0x1) {_delay_ms(20);} //wait till at angle
			printf("Done\n");
			//_delay_ms(1000);
		}
		printf("Seq Done\n");
		_delay_ms(1000);
		//printf("0\n");
	}
	else if(((PINC>>5)&0x1)==0x00)
	{
		setAngles(0,-30);
		//printf("3\n");
	}
	else if(((PINC>>6)&0x1)==0x00)
	{
		setAngles(0,-60);
		//printf("6\n");
	}
	else if(((PINC>>7)&0x1)==0x00)
	{
		setAngles(0,-89);
		//printf("9\n");
	}
	//_delay_ms(25);
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

