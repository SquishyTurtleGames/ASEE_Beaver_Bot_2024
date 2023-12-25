#include <Arduino.h>
#include "pinNumbers.h"

int sensorVal;

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
  sensorVal = analogRead(IR_SENSOR_1 );

  return(sensorVal <= threshhold);
}