#include "ServoControl.h"
#include <Servo.h>
#include "pinNumbers.h"

Servo myServo;
int servoPosition = 0;

double timeMilliss;

bool toggle = true;

int getServoPos()
{
  return servoPosition;
}

void setupServo()
{
  myServo.attach(MY_SERVO_PIN);
}

void resetServo()
{
  if(!ServoTimeDelay(0.1)) return;

  myServo.write(0);
}

void Wack()
{
  myServo.write(180);

  ServoTimeDelay();
}

void StartupLoopStuff()
{
  myServo.write(servoPosition);

  if(!ServoTimeDelay(0.01)) return;

  if(toggle)
  {
    servoPosition += 5;

    if(servoPosition >= 180) 
    {
      toggle = !toggle;
    }
  }
  else
  {
    servoPosition -= 5;

    if(servoPosition <= 0) 
    {
      toggle = !toggle;
    }
  }
}

bool ServoTimeDelay(double timeSec) 
{
  if(millis() - timeMilliss > timeSec * 1000) //Has one second passed? //1000 is time in milliseconds
  {
    //wait one second
    timeMilliss = millis();
    
    return true; //and reset time.
  }

  return false;
}
