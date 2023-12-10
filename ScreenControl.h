#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "LineFollower.h"

void SetDisplay();

bool Init_Screen();
void NewText(const char* text);
void AppendText(const char* text);
void AppendString(String string);
void DisplaySensorReadings(int sensorRead[8]);

void TickDisplay();
void UpdateDisplay();

