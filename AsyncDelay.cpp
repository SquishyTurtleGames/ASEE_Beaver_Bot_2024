#include "Arduino.h"
#include "AsyncDelay.h"

double timeMillis = 0;
double delayTime = 0;

AsyncDelay::AsyncDelay() {}

AsyncDelay::AsyncDelay(double timeSec) 
{
  delayTime = timeSec;

	timeMillis = millis();
}

bool AsyncDelay::DelayComplete()
{
  return(millis() - timeMillis > delayTime * 1000);
}