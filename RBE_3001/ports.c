/*
 * ports.c
 *
 *  Created on: Feb 1, 2017
 *      Author: vargoal
 */
#include <RBELib/ports.h>
/**
 * @brief Sets the direction (Input/Output) of the specified pins.
 *
 * @param port Port to set (A/B/C/D).
 * @param dir The pin on PORTA to set the direction of.
 * @param numPins The number of pins that you are setting the
 * direction of.
 * @param ... Pins one after another
 *
 * @todo Create a way to set a port's pins to inputs or outputs.
 */
void setPinsDir(char port, int dir, char numPins, ...) {

}

/**
 * @brief Gets the value on the specified pins of a port.
 *
 * @param port Port to read (A/B/C/D).
 * @param numPins The number of pins that you are reading.
 * @param ... The pins one after another.
 *
 * @return value The value of the specified pins on the port.
 *
 * @todo Create a way to read all given pins on a port.
 */
unsigned char getPinsVal(char port, int numPins, ...) {
	return 'A';
}

/**
 * @brief Sets the value on the specified pins of a port.
 *
 * @param port Port to set (A/B/C/D).
 * @param numPins The number of pins that you are setting.
 * @param val The value (high/low) to set the pin to.
 * @param ... The pins one after another.
 *
 * @todo Create a way to set all given pins on a port.
 */
void setPinsVal(char port, int val, int numPins, ...) {

}


