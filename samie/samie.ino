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

#define PIN_LIGHT_SENSOR A0
#define PIN_SONAR_SENSOR 11
#define SPEED 20

void setup()
{
  Serial.begin(9600);
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
      
      if (command == "Drive")
      {
        drive(Serial.readStringUntil(',').toInt());
        returnString = command + " Done";
      }
      else if(command == "Rotate")
      {
        //rotate command
        returnString = command + " Done";
      }
      else if(command == "")
      {
        returnString = command + " Done";
      }
      else if(command == "")
      {
        returnString = command + " Done";
      }
      else if(command == "")
      {
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

int drive(int x)
{
  //while less than x meters
  //drive
  MOTOR.setSpeedDir1(19,DIRF);
  MOTOR.setSpeedDir2(20,DIRF);
  return x;
} 

int rotate(int x){
 
 return x; 
}
