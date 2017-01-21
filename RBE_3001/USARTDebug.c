/*
 * USARTDebug.c
 *
 *  Created on: Jan 20, 2017
 *      Author: vargoal
 */
#include <RBELib/RBELib.h>
#include <RBELib/USARTDebug.h>

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

