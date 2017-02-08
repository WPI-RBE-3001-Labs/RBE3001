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


#endif /* MOTORCONT_H_ */
