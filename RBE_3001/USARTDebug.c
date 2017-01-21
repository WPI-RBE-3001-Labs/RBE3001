/*
 * USARTDebug.c
 *
 *  Created on: Jan 20, 2017
 *      Author: vargoal
 */
#include <RBELib/RBELib.h>
#include <RBELib/USARTDebug.h>

void debugUSARTInit(unsigned long baudrate) {
	/*
	 * Enables USART1 and sets the baud rate. Also sets 8 bit frame w/1 stop bit.
	 * TODO: Add check to make sure valid baudrates used(Datasheet pg. 241)
	 */
	UBRR1H = ((F_CPU / (16 * baudrate)) - 1) >> 8;
	UBRR1L = ((F_CPU / (16 * baudrate)) - 1);
	UCSR1B = (1 << RXEN1) | (1 << TXEN1);
	UCSR1C = (3 << UCSZ10);
}

void putCharDebug(char byteToSend) {
	/*
	 * Sends a single char using serial over USART 1
	 */
	while(!(UCSR1A & (1<<UDRE1))){}
	UDR1=byteToSend;
}

unsigned char getCharDebug(void) {
	/*
	 * Reads a single character from USART1
	 */
	while (!(UCSR1A & (1 << RXC1))){}
	return UDR1;
}

