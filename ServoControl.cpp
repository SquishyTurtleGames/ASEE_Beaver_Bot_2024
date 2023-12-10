/*
#include <Servo.h>

Servo myServo;
int servoPosition = 0;

void setupServo()
{
  myServo.attach(MY_SERVO_PIN);
}

void StartupLoopStuff()
{
  for (servoPosition = 0; servoPosition <= 180; servoPosition += 1) {
    myServo.write(servoPosition);
    ServoTimeDelay();
  }
  for (servoPosition = 180; servoPosition >= 0; servoPosition -= 1) {
    myServo.write(servoPosition);
    ServoTimeDelay();
  }
}

void ServoTimeDelay() {
  if(millis() - timeMilliss > 1000) //Has one second passed? //1000 is time in milliseconds
  {
    //wait one second
    timeMilliss = millis(); //and reset time.
  }
}

*/