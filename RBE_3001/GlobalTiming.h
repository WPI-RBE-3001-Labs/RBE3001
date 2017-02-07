/*
 * GloablTiming.h
 *
 *  Created on: Feb 7, 2017
 *      Author: vargoal
 */

#ifndef GLOBALTIMING_H_
#define GLOBALTIMING_H_

#include <RBELib/RBELib.h>
static void initGlobalTimer() {
	sei();
	OCR0A = 80;//225 hz; 18000 hz counting
	TCCR0A = (1<<WGM01)|(1<<COM0A0);
	TCCR0B = (1<<CS02)|(1<<CS00);
	TIMSK0 = 0x2; //OCIEA enable
}

unsigned long long globalCount;
ISR(TIMER0_COMPA_vect) {
	globalCount++;
}
const int MS_PER_TICK = 1000/225.0;
long getGlobalTime() {
	return globalCount*MS_PER_TICK;
}

#endif /* GLOBALTIMING_H_ */
