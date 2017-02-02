/*
 * ports.c
 *
 *  Created on: Feb 1, 2017
 *      Author: vargoal
 */
#include <RBELib/RBELib.h>
#include <RBELib/reg_structs.h>

// Port functionality tested


/**
 * @brief Sets the direction (Input/Output) of the specified pins.
 *
 * @param port Port to set (A/B/C/D).
 * @param dir The pin on PORTA to set the direction of.
 * @param numPins The number of pins that you are setting the
 * direction of.
 * @param ... Pins one after another
 *
 */
void setPinsDir(char port, int dir, int numPins, ...) {
	va_list pinPointers; //var args pointer list
	va_start(pinPointers, numPins);
	__8bitreg_t* portPointer; //Byte type defined in RBELib
	//Note DDRAbits-DDRDbits defined in RBELib
	switch(port)
	{
	case 'A':
		portPointer = &DDRAbits;
		break;
	case 'B':
		portPointer = &DDRBbits;
		break;
	case 'C':
		portPointer = &DDRCbits;
		break;
	case 'D':
		portPointer = &DDRDbits;
		break;
	default: //invalid input port so print error to serial
		printf("Invalid port in setPinsDir");
		break;
	}
	for(uint8_t i = 0;i<numPins;i++)
	{
		uint8_t pin = va_arg(pinPointers,int);
		switch(pin)
		{
		case 0:
			portPointer->_P0 = dir;
			break;
		case 1:
			portPointer->_P1 = dir;
			break;
		case 2:
			portPointer->_P2 = dir;
			break;
		case 3:
			portPointer->_P3 = dir;
			break;
		case 4:
			portPointer->_P4 = dir;
			break;
		case 5:
			portPointer->_P5 = dir;
			break;
		case 6:
			portPointer->_P6 = dir;
			break;
		case 7:
			portPointer->_P7 = dir;
			break;
		default: //invalid pin number given
			printf("Invalid pin in setPinsDir");
			break;
		}
	}
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
 */
unsigned char getPinsVal(char port, int numPins, ...) {
	va_list pinPointers; //var args pointer list
	va_start(pinPointers, numPins);
	unsigned char result;
	__8bitreg_t* portPointer; //Byte type defined in RBELib
	//Note DDRAbits-DDRDbits defined in RBELib
	switch(port)
	{
	case 'A':
		portPointer = &PINA;
		break;
	case 'B':
		portPointer = &PINB;
		break;
	case 'C':
		portPointer = &PINC;
		break;
	case 'D':
		portPointer = &PIND;
		break;
	default: //invalid input port so print error to serial
		printf("Invalid port in getPinsVal");
		break;
	}
	for(uint8_t i = 0;i<numPins;i++)
	{
		uint8_t pin = va_arg(pinPointers,int);
		switch(pin)
		{
		case 0:
			result|= (portPointer->_P0)<<0;
			break;
		case 1:
			result|= (portPointer->_P1)<<1;
			break;
		case 2:
			result|= (portPointer->_P2)<<2;
			break;
		case 3:
			result|= (portPointer->_P3)<<3;
			break;
		case 4:
			result|= (portPointer->_P4)<<4;
			break;
		case 5:
			result|= (portPointer->_P5)<<5;
			break;
		case 6:
			result|= (portPointer->_P6)<<6;
			break;
		case 7:
			result|= (portPointer->_P7)<<7;
			break;
		default: //invalid pin number given
			printf("Invalid pin in getPinsVal");
			break;
		}
	}
	return result;
}

/**
 * @brief Sets the value on the specified pins of a port.
 *
 * @param port Port to set (A/B/C/D).
 * @param numPins The number of pins that you are setting.
 * @param val The value (high/low) to set the pin to.
 * @param ... The pins one after another.
 *
 */
void setPinsVal(char port, int val, int numPins, ...) {
	va_list pinPointers; //var args pointer list
	va_start(pinPointers, numPins);
	__8bitreg_t* portPointer; //Byte type defined in RBELib
	//Note DDRAbits-DDRDbits defined in RBELib
	switch(port)
	{
	case 'A':
		portPointer = &PORTAbits;
		break;
	case 'B':
		portPointer = &PORTBbits;
		break;
	case 'C':
		portPointer = &PORTCbits;
		break;
	case 'D':
		portPointer = &PORTDbits;
		break;
	default: //invalid input port so print error to serial
		printf("Invalid port in setPinsVal");
		break;
	}
	for(uint8_t i = 0;i<numPins;i++)
	{
		uint8_t pin = va_arg(pinPointers,int);
		switch(pin)
		{
		case 0:
			portPointer->_P0 = val;
			break;
		case 1:
			portPointer->_P1 = val;
			break;
		case 2:
			portPointer->_P2 = val;
			break;
		case 3:
			portPointer->_P3 = val;
			break;
		case 4:
			portPointer->_P4 = val;
			break;
		case 5:
			portPointer->_P5 = val;
			break;
		case 6:
			portPointer->_P6 = val;
			break;
		case 7:
			portPointer->_P7 = val;
			break;
		default: //invalid pin number given
			printf("Invalid pin in setPinsVal");
			break;
		}
	}
}


