/*
  somefunctions. I'm not finished.
  Some code has been copied and pasted from lab 4
*/

#include <Hercules.h>
#include <Hercules_dfs.h>
#include <Hercules_Stepper.h>
#include <seeed_pwm.h>
#include <Ultrasonic.h>

#define PIN_LIGHT_SENSOR A0
#define PIN_SONAR_SENSOR 11
#define SPEED 20


void drive(void);
void rotate45(void);
void CWorCCW(void);
void ForR(void);
void getDirection(void);

void drive(void){
  Serial.begin(9600);
	MOTOR.begin();

	MOTOR.setSpeedDir1((SPEED - 1), DIRF);
	MOTOR.setSpeedDir2((SPEED), DIRR);
  return;
}
void rotate45(void){
 //it rotates 45 degrees
  for (int speed = 0; speed < 30; speed++)
	{
		MOTOR.setSpeedDir1(speed, DIRF);
		MOTOR.setSpeedDir2(speed, DIRR);
		delay(10);
	}

	delay(160);

	for (int speed = 30; speed > 0; --speed)
	{
		MOTOR.setSpeedDir1(speed, DIRF);
		MOTOR.setSpeedDir2(speed, DIRR);
		delay(10);
	}
	MOTOR.setSpeedDir(0, DIRF);
}
void CWorCCW(void){
 //clockwise vs counter-clockwise 
}
void ForR(void){
 //Forward vs. Reverse 
}
void getDirection(void){
  ForR();
  CWorCCW();
}
