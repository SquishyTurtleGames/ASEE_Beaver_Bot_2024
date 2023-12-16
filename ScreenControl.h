#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "LineFollower.h"

bool Init_Screen();

void Display(String string);
void Display(int value);
void Display(double value);

void DisplayLineBreak();
void DisplaySensorReadings(int sensorRead[8]);

void TickDisplay();
void UpdateDisplay();

