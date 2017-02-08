#include "MotorCont.h"
#include <RBELib/RBELib.h>
#include "Pinout.h"
void initMotorControl() {
	initSPI(); //Initalizes SPI bus
	initADC(4);
	setDAC(0,0);
	setDAC(1,0);
	setDAC(2,0);
	setDAC(3,0);
}
void setMotorPwr(unsigned int mtr, int pwr) {
	int currentAngle = 0;
	switch(mtr)
	{
	case 0:
		currentAngle = potAngle(M0_POT_PIN);
		if((currentAngle<0 && pwr<0)||((currentAngle>90 && pwr>0)))
		{
			//don't move because at bound of motion
			setDAC(0,0);
			setDAC(1,0);
		}
		else
		{
			if(pwr>0)
			{
				setDAC(0,pwr);
				setDAC(1,0);
			}
			else
			{
				setDAC(0,0);
				setDAC(1,-1*pwr);
			}
		}
		break;
	case 1:
		currentAngle = potAngle(M1_POT_PIN);
		if((currentAngle<-90 && pwr<0)||((currentAngle>0 && pwr>0)))
		{
			//don't move because at bound of motion
			setDAC(2,0);
			setDAC(3,0);
		}
		else
		{
			if(pwr>0)
			{
				setDAC(3,pwr);
				setDAC(2,0);
			}
			else
			{
				setDAC(3,0);
				setDAC(2,-1*pwr);
			}
		}
		break;
	default:
		printf("setMtr error");
	}
}
