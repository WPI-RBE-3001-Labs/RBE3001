/*
 * DAC.c
 *
 *  Created on: Feb 1, 2017
 *      Author: vargoal
 */
#include <RBELib/RBELib.h>

#define DAC_WRITE_N_UPDATE_ALL 0b0010
#define DAC_WRITE_N_UPDATE_N 0b0011
#define DAC_PWR_DOWN_N 0b0100
#define DAC_PWR_DOWN_ALL 0b0101
#define DAC_SEL_INT_REF 0b0110
#define DAC_SEL_EXT_REF 0b0111

#define DACA 0b0000
#define DACB 0b0001
#define DACC 0b0010
#define DACD 0b0011
#define DACALL 0b1111

//http://cds.linear.com/docs/en/datasheet/2634fc.pdf
//Max SPI freq = 50 MHz

/**
 * @brief Set the DAC to the given value on the chosen channel.
 * @param  DACn The channel that you want to set.
 * @param SPIVal The value you want to set it to.
 *
 * @todo Make the function that is able to set the DAC to a given value
 * from 0 - 4095.
 */
void setDAC(int DACn, int SPIVal) {
	setPinsDir('D',OUTPUT,1,4);
	setPinsVal('D',LOW,1,4); //set cs low
	/*The 4-bit command, C3-C0, is loaded first; then the 4-bit
	DAC address, A3-A0; and finally the 16-bit data word.
	The data word comprises the 12-bit input code,
	ordered MSB to LSB, followed by 4 don’t-care
	bits.*/
	// SPI sends MSB first
	BYTE word = DAC_WRITE_N_UPDATE_N<<4;//change 1111 to dac number
	switch(DACn){
	case 0:
		word |= DACA;
	break;
	case 1:
		word |= DACB;
	break;
	case 2:
		word |= DACC;
	break;
	case 3:
		word |= DACD;
	break;
	default:
		word = ( DAC_WRITE_N_UPDATE_ALL<<4)|DACALL;
		printf("DAC Error");
	break;
	};
	//D - 3
	//C - 2
	//B - 1
	//A - 0
	//word |= DACC;
	spiTransceive(word);
	unsigned int val = (unsigned int)SPIVal;
	val = val<<4;
	BYTE wordTwo = (unsigned short)(val>>8);
	BYTE wordThree = ((val<<4)&0b11110000);
	spiTransceive(word);
	spiTransceive(wordTwo);
	spiTransceive(wordThree);
	setPinsVal('D',HIGH,1,4); //set cs low
}

