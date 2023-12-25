#include <Arduino.h>
#include "pinNumbers.h"
#include "LineFollower.h"
  
  void UserInputSetup();

  void ReadButtons();
  bool getYellowState();
  bool getWhiteState();

  void UpdateOpticalEncoder();
  int getEncoderButtonState();
  int getEncoderValue();

  void setEncoderValue(int val);        
