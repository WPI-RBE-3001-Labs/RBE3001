/*
 * Lab1_ADC.c
 *
 *  Created on: Jan 24, 2017
 *      Author: vargoal
 */
#include "Lab1.h"

void setupADCTiming() {

}

void startADCOutput() {

}

void setupPWMTiming() {
	//puts timer one in fast PWM mode
	DDRD |= (1<<PD4); // set PWM pin as output
	TCCR1A = (1<<COM1B1)|(1<<WGM11)|(1<<WGM10);
	TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS12)|(1<<CS10);
	OCR1A = 200; //default values -IDK doesn't matter
	OCR1B = 100;
}

void setPWM(unsigned int newFreq,unsigned int dutyCycle) {
	OCR1A = 18000/newFreq;
	OCR1B = (OCR1A*dutyCycle)/100;
}

void startGlobalTiming() {

}

unsigned long getGlobalTime() {
	return 1;
}

void setup() {
	//setupADCTiming();
	//startADCOutput();
	setupPWMTiming();
	setPWM(150,50);
	//startGlobalTiming();
	//setPWMFrew(140);
}

void loop() {
	//TODO: Check for BTN press for ADC start
	//TODO: check PWM freq BTNS to switch freq; Could do with interrupts but why
}
