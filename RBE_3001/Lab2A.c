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
	targets[0].x = 8.5*25.4;
	targets[0].y = 5*25.4;
	targets[1].x = 10.5*25.4;
	targets[1].y = 0*25.4;
	targets[2].x = 8.5*25.4;
	targets[2].y = 0*25.4;
	targets[3].x = 8.5*25.4;
	targets[3].y = 5*25.4;

	//init everything
	initRBELib();
	initADC(4);
	initGlobalTimer();
	initMotorControl();
	//setAngles(30,-30);
	setPinsDir('C',INPUT,3,4,6,7);
	setPinsVal('C',HIGH,3,4,6,7);
	encInit(0);
	encInit(1);
	setPinsDir('D',INPUT,7,1,2,3,4,5,6,7);
	setPinsVal('D',HIGH,7,1,2,3,4,5,6,7);
	//setPinsVAL('D',INPUT,6,2,3,4,5,6,7);
	//ArmPose pose = getPoseFromXY(7.5*25.4,6*25.4);
	//setAngles(pose.thetaZero,pose.thetaOne);
	//printf("%i,%i\n",pose.thetaZero,pose.thetaOne);
	//_delay_ms(3000);
	//printf("Start\n");
	/*for(int i = 0;i<3;i++)
	{
		ArmPose pose = getPoseFromXY(targets[i].x,targets[i].y);
		setAngles(pose.thetaZero,pose.thetaOne);
		while(atAngle() != 0x1) {_delay_ms(50);} //wait till at angle
		printf("Done\n");
		_delay_ms(1000);
	}*/
	//_delay_ms(3000);
	setAngles(90,0);
	//_delay_ms(1000);
	//resetEncCount(0);
	//resetEncCount(1);
	//setAngles(89,0);


	//setMotorPwr(0,0);
	//setMotorPwr(1,0);
}

void loop() {
	/*if((getPinsVal('D',1,3)==0x00))
	{
		//Btn 3 pressed
		setAngles(89,0);
		printf("btn 3\n");
	}
	if((getPinsVal('D',1,2)==0x00))
	{
		//Btn 2 pressed
		setAngles(1,0);
		printf("btn 2\n");
	}
	if((getPinsVal('D',1,1)==0x00))
	{
		//Btn 1 pressed
		resetEncCount(0);
		resetEncCount(1);
		printf("btn 1\n");
	}*/
	_delay_ms(25);
}

