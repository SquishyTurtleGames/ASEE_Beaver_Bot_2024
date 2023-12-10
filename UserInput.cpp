#include <Arduino.h>
#include "pinNumbers.h"
#include "LineFollower.h"

int yellowButtonState = HIGH;
int whiteButtonState = HIGH;

int encoderValue;
const int defaultEncoderStartVal = 100;
int oldClockState = LOW;

void SetupUserInput()
{
  pinMode(YELLOW_BUTTON_PIN, INPUT_PULLUP);
  pinMode(WHITE_BUTTON_PIN, INPUT_PULLUP);
  pinMode(DIAL_SWITCH_PIN, INPUT_PULLUP);
  pinMode(DIAL_CLOCK_PIN, INPUT);
  pinMode(DIAL_DATA_PIN, INPUT);

  encoderValue = defaultEncoderStartVal;
  oldClockState = digitalRead(DIAL_CLOCK_PIN);
}

void ReadButtons() 
{
  yellowButtonState = digitalRead(YELLOW_BUTTON_PIN);
  whiteButtonState = digitalRead(WHITE_BUTTON_PIN);
}

int getYellowState()
{
  ReadButtons();
  return yellowButtonState;
}

int getWhiteState()
{
  ReadButtons();
  return whiteButtonState;
}

void ReadOpticalEncoder()
{
    int dialClockState = digitalRead(DIAL_CLOCK_PIN);
    int dialDataState = digitalRead(DIAL_DATA_PIN);

    if (dialClockState != oldClockState && dialClockState == HIGH) {
      //Something happened OOOOOOOOH
      if (dialDataState == LOW) {
        encoderValue -= 1;
      }
      else {
        encoderValue += 1;
      }
    }

    oldClockState = dialClockState;
}

int getEncoderButtonState() 
{
  return digitalRead(DIAL_SWITCH_PIN);
}

int getEncoderValue()
{
  return encoderValue;  
}

void setEncoderValue(int val)
{
  encoderValue = val;
}