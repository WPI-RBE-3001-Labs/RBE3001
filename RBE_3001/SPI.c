/*
 * SPI.c
 *
 *  Created on: Feb 1, 2017
 *      Author: vargoal
 */
#include <RBELib/RBELib.h>

/**
 * @brief Initializes the SPI bus for communication with all of your
 * SPI devices.
 *
 * @todo Create the function that will allow you to initialize the SPI
 * in a mode compatible with all devices.  Do not forget to deassert all
 * of your SS lines!
 */
void initSPI() {
	//Setup SPI Pins
	setPinsDir('B',OUTPUT,3,4,5,7);
	setPinsDir('B',INPUT,1,6);
	//Setup SPI
	SPCR =  (0<<SPIE)| //Interrupt enable bit
			(1<<SPE) | //SPI enable bit
			(0<<DORD)| //1-LSB; 0-MSB
			(1<<MSTR)| //1-master;0-slave
			(0<<CPOL)| //clk polarity
			(0<<CPHA)| //clk phase
			(0<<SPR1)|(0<<SPR0); //div 4 prescaler pg 222
}

/**
 * @brief Send and receive a byte out of the MOSI line.
 *
 * Please note that even if you do not want to receive any data back
 * from a SPI device, the SPI standard requires you still receive something
 * back even if it is junk data. Assumes SS is handled externally
 *
 * @param data The byte to send down the SPI bus.
 * @return value The byte shifted in during transmit
 *
 */
unsigned char spiTransceive(BYTE data) {
	while((SPSR&(1<<WCOL)) == (1<<WCOL)) {} //wait til collision avoided
	SPDR = data;
	while((SPSR&(1<<SPIF)) != (1<<SPIF)) {} //waits til transfer complete
	return SPDR; //return received data*/
}

