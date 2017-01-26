/*
 * Lab1_ADC.c
 *
 *  Created on: Jan 24, 2017
 *      Author: vargoal
 */
#include "Lab1.h"

void setupADCTiming() {
	sei(); //enable interrupts
	//SETUP Timer 0 to 225 hz CTC for ADC
	DDRB |= (1<<PB3); // set pin as output to diagnose timer
	DDRA = 0x00;
	PORTA = 0x00;
	DIDR0 = (1<<ADC0D); //disable digital buffer for ADC0 (PA0)
	OCR0A = 80;//225 hz; 18000 hz counting

	//PORTB = 0xFF;
	TCCR0A = (1<<WGM01)|(1<<COM0A0);
	TCCR0B = (1<<CS02)|(1<<CS00);
	TIMSK0 = 0x2; //OCIEA enable
	//SETUP ADC
	ADMUX   = (1<<REFS1); //AVcc; Mux pin = ADC0 single pole
	ADCSRA  = (1<<ADATE)|(1<<ADIE); //Enable auto trigger and interrupt
	ADCSRA |= (1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2); //Set prescaler to 128 because it's only valid setting for setup
	ADCSRB  = (1<<ADTS0)|(1<<ADTS1); //set trigger source to timer0 Comp A
	//TODO: add interrupt ISR to clear flag and store data
	ADCSRA |= (1<<ADEN)|(1<<ADSC); //Enable ADC
}
uint16_t lastADCVal = 0;
char newDataToSend = 0x00;
ISR(ADC_vect) { //Triggers on ADC conversion complete
	//ADIF auto clears on ISR call
	lastADCVal = 0;
	lastADCVal = ADCL;
	lastADCVal |= (ADCH<<8);
}
unsigned long globalCount;
ISR(TIMER0_COMPA_vect) {
	globalCount++;
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
	//Duty cycle 0-100
	OCR1A = 18000/newFreq;
	OCR1B = (unsigned int)((OCR1A*(unsigned long)dutyCycle)/100);
}

void setupSwitches() {
	DDRB = 0x00; //set port B as input
}
unsigned int freq = 10;
void readSwitches() {
	printf("Test %f",1.25); //example print out
	_delay_ms(500); //Delay .5 sec
	unsigned int dutyCycle = (unsigned int)(((unsigned long)lastADCVal*100)/1024);
	if((((~PINB)>>7)&0x01)==0x01)
	{
		freq = 1;
	}
	else if((((~PINB)>>6)&0x01)==0x01)
	{
		freq = 20;
	}
	else if((((~PINB)>>5)&0x01)==0x01)
	{
		freq = 100;
	}
	setPWM(freq,dutyCycle);
}

void setup() {
	debugUSARTInit(115200); //used
	initRBELib();
	setupPWMTiming();
	setPWM(150,50);
	setupSwitches();
	setupADCTiming();

	//startGlobalTiming();
	//setPWMFrew(140);
}

void loop() {
	//TODO: Check for BTN press for ADC start
	readSwitches();
}
