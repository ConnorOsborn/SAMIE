/*
Connor Osborn
Maddy Henderson
Lab 4 Task 1
*/

#include <Hercules.h>
#include <Hercules_dfs.h>
#include <Hercules_Stepper.h>
#include <seeed_pwm.h>
#include <Ultrasonic.h>

#define PIN_LIGHT_SENSOR A0
#define PIN_SONAR_SENSOR 11
#define SPEED 20

int getLightIntensity();
void rotate90(int times);
void rotate45();
float getDistance();
void blindSearch(int time);
void safeDrive(int time);

Ultrasonic ultrasonic(PIN_SONAR_SENSOR);

int lightValue = 0;
int topLightValue = 500;
int timeRotating = 0;
int threshold = 0;

void setup()
{
	Serial.begin(9600);
	MOTOR.begin();

	MOTOR.setSpeedDir1((SPEED - 1), DIRF);
	MOTOR.setSpeedDir2((SPEED), DIRR);
}

void loop()
{
	if (timeRotating > 1000)
	{
		timeRotating = 0;
		topLightValue /= 1.5;
		blindSearch(750);
	}

	lightValue = getLightIntensity();
	if ((topLightValue - 5) < lightValue)
	{
		topLightValue = lightValue;
		MOTOR.setSpeedDir(0, DIRF);
		rotate45();
		safeDrive(2000);
	}

	if (getDistance() < 8.00) rotate90(1);

	delay(15);
	timeRotating++;
	Serial.println();

	if (lightValue > 800) while(1) {}

	MOTOR.setSpeedDir1((SPEED - 1), DIRF);
	MOTOR.setSpeedDir2((SPEED), DIRR);
}

int getLightIntensity()
{
	return (1024 - analogRead(PIN_LIGHT_SENSOR));
}

void rotate45()
{
	Serial.println("rotate45");
	int intensity = -1;

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

void rotate90(int times)
{
	Serial.println("rotate90");
	while (times--)
	{
		for (int speed = 0; speed < 30; speed++)
		{
			MOTOR.setSpeedDir1(speed, DIRF);
			MOTOR.setSpeedDir2(speed, DIRR);
			delay(10);
		}

		delay(310);

		for (int speed = 30; speed > 0; --speed)
		{
			MOTOR.setSpeedDir1(speed, DIRF);
			MOTOR.setSpeedDir2(speed, DIRR);
			delay(10);
		}
	}
	MOTOR.setSpeedDir(0, DIRF);
}

float getDistance()
{
	//m = 1.0026
	//b = 0.6087
	// (measured - b) / m = true distance

	return (ultrasonic.MeasureInCentimeters() - 0.6087) / 1.0026;
}

void blindSearch(int time)
{
	while (time--)
	{
		if (getDistance() > 9.00)
		{
			MOTOR.setSpeedDir1((SPEED - 1), DIRF);
			MOTOR.setSpeedDir2((SPEED), DIRF);
		}
		else
		{
			MOTOR.setSpeedDir(0, DIRF);
			rotate90(1);
		}

		delay(15);
	}
}

void safeDrive(int time)
{
	MOTOR.setSpeedDir1((SPEED - 1), DIRF);
	MOTOR.setSpeedDir2((SPEED), DIRF);

	time /= 5;
	while (time--)
	{
		if (getDistance() < 8.00)
		{
			MOTOR.setSpeedDir(0, DIRF);
			break;
		}
		delay(5);
	}
	MOTOR.setSpeedDir(0, DIRF);
}