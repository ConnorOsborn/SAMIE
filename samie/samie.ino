/*
S.A.M.I.E. (SLAM Automated Mobie Intelegent Explorer)
Arduino Serial Code/API - Created by Connor Osborn
Arduino Control Code - Created by Maddy Henderson
*/

#include <Hercules.h>
#include <Hercules_dfs.h>
#include <Hercules_Stepper.h>
#include <seeed_pwm.h>
#include <Ultrasonic.h>

#define PIN_SONAR_SENSOR 11
#define SPEED 20

Ultrasonic ultrasonic(PIN_SONAR_SENSOR);

void setup()
{
  Serial.begin(9600);
  MOTOR.begin();
}

void loop()
{
  String command;
  String returnString;
  
  while(true)
  {
    if (Serial.available())
    {
      command = Serial.readStringUntil(',');
      
      if (command == "DriveForward")
      {
        safeDrive(Serial.readStringUntil(',').toInt());
        returnString = command + " Done";
      }
      else if(command == "DriveBackward"){
	safeDrive(((Serial.readStringUntil(',').toInt())*-1));   
      }
      else if(command == "RotateRight")
      {
        rotate45(Serial.readStringUntil(',').toInt());
        returnString = command + " Done";
      }
      else if(command == "RotateLeft")
      {
	rotate45(((Serial.readStringUntil(',').toInt())*-1));
        returnString = command + " Done";
      }
      else
      {
        returnString = "Fail";
      }
      
      Serial.println(returnString);
    }
    
    while (Serial.available() > 0) char t = Serial.read(); // Clear Buffer
    delay(10);
  }
}

float getDistance()
{
	//m = 1.0026
	//b = 0.6087
	// (measured - b) / m = true distance

	return (ultrasonic.MeasureInCentimeters() - 0.6087) / 1.0026;
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

void rotate45(int times)
{
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
