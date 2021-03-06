#include "MotorCont.h"
#include <RBELib/RBELib.h>
#include "Pinout.h"
#include "GlobalTiming.h"
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
	pwr = constrain(pwr,-4095,4095);
	int currentAngle = 0;
	switch(mtr)
	{
	case 0:
		currentAngle = potAngle(M0_POT_PIN);
//		printf("%i\n",currentAngle);
		if((currentAngle<0 && pwr<0)||(currentAngle>90 && pwr>0))
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
		break;
	}
}

int m0_target = 0;
int m1_target = 0;

void setAngles(int angZero,int angOne) {
	if(angZero>=0 && angZero<=90)
	{
		m0_target = angZero;
	}
	if(angOne<=0 && angOne>=-90)
	{
		m1_target = angOne;
	}
}

char atAngle() {
	int actZero = potAngle(M0_POT_PIN);
	int actOne = potAngle(M1_POT_PIN);
	int diffZero = actZero-m0_target;
	int diffOne = actOne-m1_target;
	//printf("%i,%i\n",diffZero,diffOne);
	if((diffZero >5) || (diffZero<-5))
	{
		return 0x0;
	}
	if((diffOne >5) || (diffOne<-5))
	{
		return 0x0;
	}
	return 0x1;

	//return ((abs(potAngle(M0_POT_PIN)-m0_target) < 3)&&(abs(potAngle(M1_POT_PIN)-m1_target) < 3));
}
int getMotorCurrent(int mtr) { //return mA
	switch(mtr)
	{
	case 0:
		return -1*((getADC(M0_CURRENT_PIN)-524)/1023.0)*5000;
	break;
	case 1:
		return -1*((getADC(M1_CURRENT_PIN)-524)/1023.0)*5000;
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
long lastErrorM0 = 0;
long lastErrorM1 = 0;
long sumErrorM0 = 0;
long sumErrorM1 = 0;
long M0_kp = 120;
long M0_ki = 0;
long M0_kd = 0;
long M1_kp = 120;
long M1_ki = 0;
long M1_kd = 0;


ISR(TIMER2_COMPA_vect) {
	//called at 100 hz
	//updatePIDConsts();
	/*printf("\n");
	printf("P: %f\n",M0_kp);
	printf("i: %f\n",M0_ki);
	printf("d: %f\n",M0_kd);*/
	int angleM0 = potAngle(M0_POT_PIN);
	int angleM1 = potAngle(M1_POT_PIN);
	long M0_ff = 0;//sin(angleM0*DEG_TO_RAD)*M0_GRAV_CONST;
	long M1_ff = 0;//sin((angleM0+angleM1)*DEG_TO_RAD)*M1_GRAV_CONST;
	long errorM0 = m0_target-angleM0;
	long errorM1 = m1_target-angleM1;
	long diffErrorM0 = lastErrorM0-errorM0;
	long diffErrorM1 = lastErrorM1-errorM1;
	lastErrorM0 = errorM0;
	lastErrorM1 = errorM1;
	sumErrorM0 += errorM0;
	sumErrorM1 += errorM1;
	long pidOutM0 = (M0_kp*errorM0)+(M0_ki*sumErrorM0)+(M0_kd*diffErrorM0)+M0_ff;
	long pidOutM1 = (M1_kp*errorM1)+(M1_ki*sumErrorM1)+(M1_kd*diffErrorM1)+M1_ff;
	pidOutM0 = constrain(pidOutM0,-4095,4095);
	pidOutM1 = constrain(pidOutM1,-4095,4095);
	setMotorPwr(0,pidOutM0);
	setMotorPwr(1,pidOutM1);
	//printf("%f,%i,%i,%f,%f,%f,%f,%i,%i\n",(float)getGlobalTime(),m0_target,m1_target,pidOutM0,pidOutM1,errorM0,errorM1,getMotorCurrent(0),getMotorCurrent(1));
	//printf("%i,%i\n",m0_target,m1_target);
	//printf("%i,%i\n",angleM0,angleM1);
	//printf("%f,%i,%i\n",(float)getGlobalTime(),angleM0,angleM1);
}

const float LINK_LENGTH_ZERO = 6*25.4; //mm
const float LINK_LENGTH_ONE = 5*25.4; //mm
const float PI = 3.141592654;
ArmPose getPoseFromXY(float x,float y) {
	float L3 = sqrt((x*x)+(y*y));
	//printf("%f\n",L3);
	float theta_three = acos(((LINK_LENGTH_ZERO*LINK_LENGTH_ZERO)+(LINK_LENGTH_ONE*LINK_LENGTH_ONE)-(L3*L3))/(2*LINK_LENGTH_ZERO*LINK_LENGTH_ONE));
	//printf("%f\n",theta_three);
	float theta_two = sin(theta_three)*(LINK_LENGTH_ONE/L3);
	float target_one = theta_two+atan(y/x);
	//printf("%f\n",target_one);
	float target_two = (PI-theta_three)*-1;
	//printf("%f\n",target_two);
	ArmPose result;
	target_one = (int)(target_one*(180/PI));
	target_two = (int)(target_two*(180/PI));
	result.thetaZero = target_one;
	result.thetaOne = target_two;
	//printf("%i\n",result.thetaZero);//result.thetaZero);
	//printf("%i\n",result.thetaOne);
	return result;
}

void goToXYWithLine(float x,float y) {
	float thetaOne = potAngle(M0_POT_PIN);
	float thetaTwo = potAngle(M1_POT_PIN);
	thetaOne = thetaOne*(PI/180.0f);
	thetaTwo = thetaTwo*(PI/180.0f);
	float yInit = (LINK_LENGTH_ZERO*sin(thetaOne))+(LINK_LENGTH_ONE*sin(thetaOne+thetaTwo));
	float xInit = (LINK_LENGTH_ZERO*cos(thetaOne))+(LINK_LENGTH_ONE*cos(thetaOne+thetaTwo));
	float diffX = x-xInit;
	float diffY = y-yInit;
	float length = sqrt((diffX*diffX)+(diffY*diffY));
	int numberOfPoints = length/2;
	//printf("xInit: %f\n",xInit);
	//printf("yInit: %f\n",yInit);
	//printf("diffX: %f\n",diffX);
	//printf("diffY: %f\n",diffY);
	//printf("Num Points: %i\n",numberOfPoints);
	_delay_ms(25);
	float deltaX = (x-xInit)/(float)numberOfPoints;
	float deltaY = (y-yInit)/(float)numberOfPoints;
	for(int i = 0; i<numberOfPoints;i++)
	{
		float xNew = xInit +(deltaX*(i+1));
		float yNew = yInit +(deltaY*(i+1));
		//printf("%f,%f\n",xNew,yNew);
		_delay_ms(5);
		ArmPose pose = getPoseFromXY(xNew,yNew);
		setAngles(pose.thetaZero,pose.thetaOne);
		//printf("%i,%i\n",pose.thetaZero,pose.thetaOne);
		//while(atAngle() != 0x1) {
			//printf("w\n");
			//printf("    %i,%i\n",potAngle(M0_POT_PIN),potAngle(M1_POT_PIN));
			//_delay_ms(2);
			//_delay_ms(5);
		//} //wait till at angle
		_delay_ms(2);
		//printf("d\n");
		//_delay_ms(5);
		//_delay_ms(5);
	}
	_delay_ms(500);
}

void updatePIDConsts() {
	float kp = ((getADC(ANALOG_4_PIN))/1023.0)*500;
	float ki = ((getADC(ANALOG_5_PIN))/1023.0)*10;
	float kd = ((getADC(ANALOG_6_PIN))/1023.0)*50;
	M0_kp = kp;
	M0_ki = ki;
	M0_kd = kd;
	M1_kp = kp;
	M1_ki = ki;
	M1_kd = kd;
}
