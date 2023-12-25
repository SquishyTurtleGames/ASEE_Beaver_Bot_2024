#include "pinNumbers.h"
#include <Arduino.h>

  int numLeftBools = 0;
  int numRightBools = 0;


void WheelsSetup() {

  pinMode(RIGHT_MOTOR_PIN_ONE, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN_TWO, OUTPUT);
  pinMode(LEFT_MOTOR_PIN_ONE, OUTPUT);
  pinMode(LEFT_MOTOR_PIN_TWO, OUTPUT);

  analogWrite(RIGHT_MOTOR_PIN_ONE, 255);
  analogWrite(RIGHT_MOTOR_PIN_TWO, 255);
  analogWrite(LEFT_MOTOR_PIN_ONE, 255);
  analogWrite(LEFT_MOTOR_PIN_TWO, 255);
}

void UseSteeringValues(int leftSteeringValue, int rightSteeringValue) 
{
  rightSteeringValue = (double)rightSteeringValue * 0.01 * 255;
  leftSteeringValue = (double)leftSteeringValue * 0.01 * 255;

  analogWrite(RIGHT_MOTOR_PIN_ONE, 255 - (int)constrain(rightSteeringValue, 0, 255));
  analogWrite(LEFT_MOTOR_PIN_ONE, 255 - (int)constrain(leftSteeringValue, 0, 255));
}

void HaltMotors(){
  UseSteeringValues(0, 0);
}
  
