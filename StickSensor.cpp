#include <Arduino.h>
#include "pinNumbers.h"
#include "AsyncDelay.h"

int sensorVal;
const double restTime = 0.75;

AsyncDelay restDelay;

int getSensorVal()
{
  sensorVal = analogRead(IR_SENSOR_1 );

  return sensorVal;
}

void setupStickSensor()
{
  pinMode(IR_SENSOR_1 , INPUT);
}

bool checkThreshhold(int threshhold)
{
  if(!restDelay.DelayComplete()) return false;
    
  sensorVal = analogRead(IR_SENSOR_1 );

  return(sensorVal <= threshhold);
}

void StartSensorRest()
{
  restDelay = AsyncDelay(restTime);
}