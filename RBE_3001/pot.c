/*
 * pot.c
 *
 *  Created on: Feb 1, 2017
 *      Author: vargoal
 */
#include <RBELib/pot.h>

typedef struct{
	int ADC_Channel;
	float valOffset;
	float scaleVal;
} POT;

//Constants
const POT potVals1 = {1,0,1};
const POT potVals2 = {2,0,1};
const POT potVals3 = {3,0,1};


/**
 * @brief Find the angle of the given potentiometer.
 * @param  pot The pot to check.
 * @return angle Angle of the potentiometer.
 *
 * @todo Calculate the angle using the ADC reading.
 */
int potAngle(int pot);

/**
 * @brief Find the voltage value of the given potentiometer.
 * @param  pot The pot to get the value of.
 * @return volts Voltage of  potentiometer.
 *
 * @todo Convert the ADC value into a voltage in mV (so no floats needed).
 */
int potVolts(int pot);
