/*
 * MotorCont.h
 *
 *  Created on: Feb 7, 2017
 *      Author: vargoal
 */

#ifndef MOTORCONT_H_
#define MOTORCONT_H_

void setMotorPwr(unsigned int mtr, int pwr); //+- 4096
void initMotorControl();

void setAngles(int angZero,int AngOne);

typedef struct {
	int thetaZero;
	int thetaOne;
} ArmPose;
char atAngle();
ArmPose getPoseFromXY(float x,float y); //in mm

typedef struct {
	float x; //mm
	float y; //mm
} XYTarget;

void goToXYWithLine(float x,float y);

void updatePIDConsts();


#endif /* MOTORCONT_H_ */
