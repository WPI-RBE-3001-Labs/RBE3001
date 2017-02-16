/*
 * Periph.c
 *
 *  Created on: Feb 15, 2017
 *      Author: vargoal
 */

#include <RBELib/RBELib.h>

//Count modes
#define NQUAD 0x00 //non-quadrature mode
#define QUADRX1 0x01 //X1 quadrature mode
#define QUADRX2 0x02 //X2 quadrature mode
#define QUADRX4 0x03 //X4 quadrature mode
//Running modes
#define FREE_RUN 0x00
#define SINGE_CYCLE 0x04
#define RANGE_LIMIT 0x08
#define MODULO_N 0x0C
//Index modes
#define DISABLE_INDX 0x00 //index_disabled
#define INDX_LOADC 0x10
//index_load_CNTR
#define INDX_RESETC 0x20          //index_rest_CNTR
#define INDX_LOADO 0x30          //index_load_OL
#define ASYNCH_INDX 0x00        //asynchronous index
#define SYNCH_INDX 0x80          //synchronous index
//Clock filter modes
#define FILTER_1 0x00 //filter clock frequncy division factor 1
#define FILTER_2 0x80                 //filter clock frequncy division factor 2
//Flag modes
#define NO_FLAGS 0x00 //all flags disabled
#define IDX_FLAG 0x10 //IDX flag
#define CMP_FLAG 0x20 //CMP flag
#define BW_FLAG 0x40 //BW flag
#define CY_FLAG 0x80 //CY flag
//1 to 4 bytes data-width
#define BYTE_4 0x00 //four byte mode
#define BYTE_3 0x01 //three byte mode
#define BYTE_2 0x02 //two byte mode
#define BYTE_1 0x03 //one byte mode
//Enable/disable counter
#define EN_CNTR 0x00 //counting enabled
#define DIS_CNTR 0x04 //counting disabled
/* LS7366R op-code list */
#define CLR_MDR0 0x08
#define CLR_MDR1 0x10
#define CLR_CNTR 0x20
#define CLR_STR 0x30
#define READ_MDR0 0x48
#define READ_MDR1 0x50
#define READ_CNTR   0x60
#define READ_OTR    0x68
#define READ_STR    0x70
#define WRITE_MDR1 0x90
#define WRITE_MDR0 0x88
#define WRITE_DTR   0x98
#define LOAD_CNTR   0xE
#define LOAD_OTR    0xE

/*
 * @brief Find the acceleration in the given axis (X, Y, Z).
 * @param  axis The axis that you want to get the measurement of.
 * @return gVal Value of  acceleration.
 *
 * @todo Create a function that is able to find the acceleration of a given axis.
 */
signed int getAccel(int axis) {
	return -1;
}

/**
 * @brief Read an IR sensor and calculate the distance of the block.
 * @param  chan The port that the IR sensor is on.
 * @return value The distance the block is from the sensor.
 *
 * @todo Make a function that is able to get the ADC value of the IR sensor.
 */
int IRDist(int chan) {
	return -1;
}

/**
 * @brief Initialize the encoders with the desired settings.
 * @param chan Channel to initialize.
 *
 * @todo Make a function that can setup both encoder chips on the board.
 */
void encInit(int chan) {
	initSPI();
	setPinsDir('C',OUTPUT,2,4,5);
	setPinsVal('C',HIGH,2,4,5);//set to high to disable ss

	switch(chan)
	{
	case 0:
		setPinsVal('C',LOW,1,5); //ss enable
		spiTransceive(CLR_CNTR);
		setPinsVal('C',HIGH,1,5); //ss disable
		setPinsVal('C',LOW,1,5); //ss enable
		spiTransceive(WRITE_MDR0);
		spiTransceive(QUADRX1|FREE_RUN|DISABLE_INDX|ASYNCH_INDX|FILTER_1);
		setPinsVal('C',HIGH,1,5); //ss disable
	    setPinsVal('C',LOW,1,5); //ss enable
	    spiTransceive(WRITE_MDR1);
	    spiTransceive(NO_FLAGS|BYTE_2|EN_CNTR);
	    setPinsVal('C',HIGH,1,5); //ss disable
	break;
	case 1:
		setPinsVal('C',LOW,1,4); //ss enable
		spiTransceive(CLR_CNTR);
		setPinsVal('C',HIGH,1,4); //ss disable
		setPinsVal('C',LOW,1,4); //ss enable
		spiTransceive(WRITE_MDR0);
		spiTransceive(QUADRX1|FREE_RUN|DISABLE_INDX|ASYNCH_INDX|FILTER_1);
		setPinsVal('C',HIGH,1,4); //ss disable
		setPinsVal('C',LOW,1,4); //ss enable
		spiTransceive(WRITE_MDR1);
		spiTransceive(NO_FLAGS|BYTE_2|EN_CNTR);
		setPinsVal('C',HIGH,1,4); //ss disable
	break;
	default:
		printf("Error Enc init");
	break;
	}
}

/**
 * @brief Reset the current count of the encoder ticks.
 * @param chan The channel to clear.
 *
 * @todo Clear the encoder count (set to 0).
 */
void resetEncCount(int chan) {
	switch(chan)
	{
	case 0:
		setPinsVal('C',LOW,1,5); //ss enable
		spiTransceive(CLR_CNTR);
		setPinsVal('C',HIGH,1,5); //ss disable
	break;
	case 1:
		setPinsVal('C',LOW,1,4); //ss enable
		spiTransceive(CLR_CNTR);
		setPinsVal('C',HIGH,1,4); //ss disable
	break;
	default:
		printf("Error res enc");
	break;
	}
}

/**
 * @brief Finds the current count of one of the encoders.
 * @param  chan Channel that the encoder is on that you would like to read.
 * @return count The current count of the encoder.
 *
 * @todo Find the current encoder ticks on a given channel.
 */
signed long encCount(int chan) {
	int16_t count;
	switch(chan)
	{
	case 0:
		setPinsVal('C',LOW,1,5); //ss enable
		spiTransceive(READ_CNTR);
		count = spiTransceive(0xFF)<<8;
		count|= spiTransceive(0xFF);
		setPinsVal('C',HIGH,1,5); //ss disable
		return -1*count;
	break;
	case 1:
		setPinsVal('C',LOW,1,4); //ss enable
		spiTransceive(READ_CNTR);
		count = spiTransceive(0xFF)<<8;
		count|= spiTransceive(0xFF);
		setPinsVal('C',HIGH,1,4); //ss disable
		return -1*count;
	break;
	default:
		printf("Enc count error");
		return -1;
	break;
	}
}
