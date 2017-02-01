/*
 * DAC.c
 *
 *  Created on: Feb 1, 2017
 *      Author: vargoal
 */
#include <RBELib/DAC.h>

#define DAC_WRITE_N_UPDATE_ALL 0b0010
#define DAC_WRITE_N_UPDATE_N 0b0011
#define DAC_PWR_DOWN_N 0b0100
#define DAC_PWR_DOWN_ALL 0b0101
#define DAC_SEL_INT_REF 0b0110
#define DAC_SEL_EXT_REF 0b0111

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
	//set cs low
	/*The 4-bit command, C3-C0, is loaded first; then the 4-bit
	DAC address, A3-A0; and finally the 16-bit data word.
	The data word comprises the 12-bit input code,
	ordered MSB to LSB, followed by 4 don’t-care
	bits.*/
}

