/*
 * pot.c
 *
 *  Created on: Feb 1, 2017
 *      Author: vargoal
 */
#include <RBELib/RBELib.h>
#include "Pinout.h"

//TODO: Move cal values to struct
const float POT_M0_FACTOR  = (90)/(float)(785-383);
const int POT_M0_OFFSET = 383;
const float POT_M1_FACTOR  = (90)/(float)(617-244);
const int POT_M1_OFFSET = 244;
const float VOLTAGE_CONVERSION_FACTOR = 5000/1023.0;

/**
 * @brief Find the angle of the given potentiometer.
 * @param  pot The pot to check.
 * @return angle Angle of the potentiometer.
 *
 * @todo Calculate the angle using the ADC reading.
 */
int potAngle(int pot) {
	int val = 0;
	switch(pot)
	{
	case M0_POT_PIN:
		val = getADC(pot);
		return (val-POT_M0_OFFSET)*POT_M0_FACTOR;
	break;
	case M1_POT_PIN:
		val = getADC(pot);
		return ((val-POT_M1_OFFSET)*POT_M1_FACTOR)-90;
	break;
	default:
		printf("Pot Angle Error");
		return -1;
	break;
	}
}

/**
 * @brief Find the voltage value of the given potentiometer.
 * @param  pot The pot to get the value of.
 * @return volts Voltage of  potentiometer.
 *
 * @todo Convert the ADC value into a voltage in mV (so no floats needed).
 */
int potVolts(int pot) {
	unsigned int val = 1;
	switch(pot)
		{
		case M0_POT_PIN:
			val = getADC(pot);
			return val*VOLTAGE_CONVERSION_FACTOR;
		break;
		case M1_POT_PIN:
			val = getADC(pot);
			return val*VOLTAGE_CONVERSION_FACTOR;
		break;
		default:
			printf("Pot Volts Error");
			return -1;
		break;
		}
}
