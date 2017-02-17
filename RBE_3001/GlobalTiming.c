#include "GlobalTiming.h"
void initGlobalTimer() {
	sei();
	OCR0A = 36;//500 hz; 18000 hz counting
	TCCR0A = (1<<WGM01)|(1<<COM0A0);
	TCCR0B = (1<<CS02)|(1<<CS00);
	TIMSK0 = 0x2; //OCIEA enable
}

unsigned long long globalCount;
ISR(TIMER0_COMPA_vect) {
	globalCount++;
	signed int a = getAccel(0);
	signed int b = getAccel(1);
	signed int c = getAccel(2);
	printf("%i,%i,%i\n",a,b,c);
}
const int MS_PER_TICK = 1000/500.0;
long getGlobalTime() {
	return globalCount*MS_PER_TICK;
}
