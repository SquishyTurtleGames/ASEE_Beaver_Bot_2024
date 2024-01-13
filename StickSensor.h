#include <Arduino.h>
#include "pinNumbers.h"
#include "AsyncDelay.h"

void setupStickSensor();

bool checkThreshhold(int threshhold);

int getSensorVal();

void StartSensorRest();