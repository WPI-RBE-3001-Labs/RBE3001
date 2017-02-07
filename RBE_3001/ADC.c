/*
 * ADC.c
 *
 *  Created on: Feb 1, 2017
 *      Author: vargoal
 */
#include <RBELib/RBELib.h>

/**
 * @brief Initializes the ADC and make one channel active.
 * You can choose to use either interrupts or polling to read
 * the desired channel.
 *
 * @param channel The ADC channel to initialize.
 *
 * @todo Create the corresponding function to initialize the ADC
 * using the channel parameter.
 */
void initADC(int channel) {
	//SETUP ADC
	DIDR0 = 0xFF; //disable digital buffer for ADC pins
	ADMUX   = (1<<REFS1)|(unsigned int)channel; //AVcc; Mux pin = channel single pole
	ADCSRA  = (0<<ADATE)|(0<<ADIE); //Disable auto trigger and interrupt
	ADCSRA |= (1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2); //Set prescaler to 128 because it's only valid setting for setup
	ADCSRB  = (1<<ADTS0)|(1<<ADTS1); //set trigger source to timer0 Comp A
	ADCSRA |= (1<<ADEN)|(0<<ADSC); //Enable ADC and don't start conversion
}

/**
 * @brief Disables ADC functionality and clears any saved values (globals).
 *
 * @param channel  The ADC channel to disable.
 *
 * @todo Create the corresponding function to clear the last ADC
 * calculation register and disconnect the input to the ADC if desired.
 */
void clearADC(int channel) {
	DIDR0 |= (1<<channel); //reenable dio
}

/**
 * @brief Run a conversion on and get the analog value from one ADC
 * channel if using polling.
 *
 * @param channel  The ADC channel to run a conversion on.
 * @return adcVal The 8-10 bit value returned by the ADC
 * conversion.  The precision depends on your settings and
 * how much accuracy you desire.
 *
 * @todo Create the corresponding function to obtain the value of the
 * last calculation if you are using polling.
 */
unsigned short getADC(int channel) {
	changeADC(channel);
	ADCSRA |= (1<<ADSC);
	while((ADCSRA&(1<<ADIF))==0) {} //wait for conversion to end
	ADCSRA |= (0<<ADIF);
	return ADC;
}

/**
 * @brief Change the channel the ADC is sampling if using interrupts.
 *
 * @param channel  The ADC channel to switch to.
 *
 * @todo Create a way to switch ADC channels if you are using interrupts.
 */
void changeADC(int channel) {
	unsigned int val = (unsigned int) channel;
	if(val>7)
		printf("ADC Channel Error");
	ADMUX = (1<<REFS1)|(BYTE)val;
}

