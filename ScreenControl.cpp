#include "ScreenControl.h"
#include "LineFollower.h"
#include <Arduino.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define DEF_TEXT_SIZE 2
#define TICK_PER_UPDATE 100
int currentTick = 0;

bool loopSafe = true;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String mainString;
String appendString;
bool updated = true;

int currentTextSize = 1;

//ScreenSettings screenSetting = new ScreenSettings();

bool Init_Screen()
{
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    return false; // Don't proceed, loop forever
  }

  display.clearDisplay();
  currentTextSize = DEF_TEXT_SIZE;
  display.setTextSize(currentTextSize); 
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);
  display.cp437(true);

  return true;
}

void NewText(String text)
{
  mainString = text;
  updated = true;
}

void AppendString(String string) {
  appendString += " " + string;
  updated = true;
}

void AppendStringLoopSafe(String string) {
  Serial.println("Append called");

  if(!loopSafe) return;

  appendString += " " + string;
  updated = true;
}

void DisplaySensorReadings(int sensorRead[8])
{
  String output = "";

  for(int i = 0; i < 8; i++)
  {
    output += String(sensorRead[i]);
  }

  output += "\n";

  output += GetWheelSpeed();

  mainString = output;

  updated = true;
}

void TickDisplay()
{
  Serial.println("false");
    loopSafe = false;

    currentTick++;
    if(currentTick >= TICK_PER_UPDATE && updated)
    {
      UpdateDisplay();
      currentTick = 0;
      updated = false;
    }
}

void UpdateDisplay()
{
  display.setCursor(0, 0);
  display.setTextSize(currentTextSize);
  display.clearDisplay();
  display.print(mainString + appendString);
  display.display();

  mainString = "";
  appendString = "";

  Serial.println("true");
  loopSafe = true;
}