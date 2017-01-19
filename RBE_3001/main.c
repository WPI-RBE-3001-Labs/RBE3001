#include "RBELib/RBELib.h" //RBELib
/* Prelab - LED Switch Program
int main(void){
	DDRB = 0xFF; //Set LED Port as output
	DDRD = 0x00; //Set Switch Port as input
	while (1)
	{
		PORTB = PIND;//Set LED to Switch
	}
	return 0;
}
*/
/* Prelab - Send text to board and back
void debugUSARTInit(unsigned long baudrate) {
	UBRR1H = ((F_CPU / (16 * baudrate)) - 1) >> 8;
	UBRR1L = ((F_CPU / (16 * baudrate)) - 1);
	UCSR1B = (1 << RXEN1) | (1 << TXEN1);
	UCSR1C = (3 << UCSZ10);//(1 << USBS1)
}
void putCharDebug(char byteToSend) {
	while(!(UCSR1A & (1<<UDRE1))){}
	UDR1=byteToSend;
}
unsigned char getCharDebug(void) {
	while (!(UCSR1A & (1 << RXC1))){}
	return UDR1;
}
int main(void) {
	//initRBELib(); //Setup printf() and setServo()
	debugUSARTInit(115200); //Initialize UART
	//DDRB = 0xFF; //Set LED Port as output
	//DDRD = 0x00; //Set Switch Port as input
	while(1)
	{
		char tmp = getCharDebug();
		//_delay_ms(500); //Delay .5 sec
		_delay_ms(1000); //Delay .5 sec
		putCharDebug(tmp);
		//printf("Hello World\n\r");
		//PORTB = PIND;//Set LED to Switch

	}
}
*/

// Prelab - Blinking LED
int main(void) {
	TCCR1B |= (1<<CS12);
	TIMSK1 |=(1<<TOIE0);
	DDRB = 0xFF; //Set LED Port as output
	PORTB = 0xFF; //start with LEDs on
	sei();
	while(1)
	{}
}

ISR(TIMER1_OVF_vect)
{
	PORTB =~PORTB;
}
