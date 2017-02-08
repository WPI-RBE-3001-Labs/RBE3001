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


	// Setup PID timer(100 hz)
	sei(); //enable interrupts
	OCR2A = 180; //set to make 100 hz interrupt
	TCCR2A = (0<<COM2A1)|
			 (0<<COM2A0)|
			 (0<<COM2B1)|
			 (0<<COM2B0)|
			 (1<<WGM21)| //configure for CTC mode
			 (0<<WGM20);
	TCCR2B = (0<<FOC2A)|
			 (0<<FOC2B)|
			 (0<<WGM22)|
			 (1<<CS22)| //set prescaler to 1024
			 (1<<CS21)|
			 (1<<CS20);
	TIMSK2 = (0<<OCIE2B)|
			 (1<<OCIE2A)|
			 (0<<TOIE2);//enable interrupt on max
}
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt))) //copied from arduino
void setMotorPwr(unsigned int mtr, int pwr) {
	constrain(pwr,-4096,4096);
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

int m0_target = 0;
int m1_target = 0;

void setAngles(int angZero,int angOne) {
	if(angZero>0 && angZero<=90)
	{
		m0_target = angZero;
	}
	if(angOne<0 && angOne>=-90)
	{
		m1_target = angOne;
	}
}


int getMotorCurrent(int mtr) { //return mA
	switch(mtr)
	{
	case 0:
		return ((getADC(M0_CURRENT_PIN)-524)/1023.0)*1000;
	break;
	case 1:
		return ((getADC(M1_CURRENT_PIN)-524)/1023.0)*1000;
	break;
	default:
		printf("getMtrCur error");
		return 0;
	break;
	}
}

const float DEG_TO_RAD = 180/3.141592654;
const float M0_GRAV_CONST = 0;
const float M1_GRAV_CONST = 0;
float lastErrorM0 = 0;
float lastErrorM1 = 0;
float sumErrorM0 = 0;
float sumErrorM1 = 0;
float KP_MAX = 4;
float KI_MAX = 0;
float KD_MAX = 0;
float M0_kp = 4;
float M0_ki = 0;
float M0_kd = 0;
float M1_kp = 4;
float M1_ki = 0;
float M1_kd = 0;


ISR(TIMER2_COMPA_vect) {
	//called at 100 hz
	int angleM0 = potAngle(0);
	int angleM1 = potAngle(1);
	float M0_ff = cos(angleM0*DEG_TO_RAD)*M0_GRAV_CONST;
	float M1_ff = cos(angleM1*DEG_TO_RAD)*M1_GRAV_CONST;
	float errorM0 = m0_target-angleM0;
	float errorM1 = m1_target-angleM1;
	float diffErrorM0 = lastErrorM0-errorM0;
	float diffErrorM1 = lastErrorM1-errorM1;
	lastErrorM0 = errorM0;
	lastErrorM1 = errorM1;
	sumErrorM0 += errorM0;
	sumErrorM1 += errorM1;
	float pidOutM0 = (M0_kp*errorM0)+(M0_ki*sumErrorM0)+(M0_kd*diffErrorM0)+M0_ff;
	float pidOutM1 = (M1_kp*errorM1)+(M1_ki*sumErrorM1)+(M1_kd*diffErrorM1)+M1_ff;
	setMotorPwr(0,pidOutM0);
	setMotorPwr(1,pidOutM1);
	printf("%f,%f,%f,%f\n",pidOutM0,pidOutM1,errorM0,errorM1);
}
