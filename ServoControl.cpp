#include "ServoControl.h"
#include <Servo.h>
#include "pinNumbers.h"
#include "AsyncDelay.h"

Servo myServo;
AsyncDelay currentDelay;

const int servoRestAngle = 0;
const int servoWackAngle = 180;

const double servoActuationTime = 0.4;

void setupServo()
{
  myServo.attach(MY_SERVO_PIN);
}

void resetServo()
{
  if(!currentDelay.DelayComplete()) return;

  myServo.write(servoRestAngle);
}

void Wack()
{
  myServo.write(servoWackAngle);

  currentDelay = AsyncDelay(servoActuationTime);
}

