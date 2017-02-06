/*
 * Lab2A.c
 *
 *  Created on: Feb 1, 2017
 *      Author: vargoal
 */
#include "Lab2A.h"

void setup() {
	//Testing ports setup
	initRBELib();
	initSPI(); //Initalizes SPI bus
}

void loop() {
	for(int i = 0;i<4095;i++)
	{
		setDAC(0,i);
		setDAC(1,i);
		setDAC(2,i);
		setDAC(3,i);
	}
	for(int i = 4095;i>0;i--)
	{
		setDAC(0,i);
		setDAC(1,i);
		setDAC(2,i);
		setDAC(3,i);
	}
}

