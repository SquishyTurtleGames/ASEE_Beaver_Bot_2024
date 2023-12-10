#include "pinNumbers.h"
#include <Arduino.h>

  int numLeftBools = 0;
  int numRightBools = 0;
  int timeMilliss = 0;


void WheelsSetup() {
  
  // initialize the LED pin as an output:
  //pinMode(ledPin, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN_ONE, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN_TWO, OUTPUT);
  pinMode(LEFT_MOTOR_PIN_ONE, OUTPUT);
  pinMode(LEFT_MOTOR_PIN_TWO, OUTPUT);
  // initialize the pushbutton pin as an input:
  //pinMode(greenButtonPin, INPUT_PULLUP);
  //pinMode(redButtonPin, INPUT_PULLUP);
  analogWrite(RIGHT_MOTOR_PIN_ONE, 255);
  analogWrite(RIGHT_MOTOR_PIN_TWO, 255);
  analogWrite(LEFT_MOTOR_PIN_ONE, 255);
  analogWrite(LEFT_MOTOR_PIN_TWO, 255);
}
/*
void loop() {
  // read the state of the pushbutton value:
  greenButtonState = digitalRead(greenButtonPin);
  redButtonState = digitalRead(redButtonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (greenButtonState == LOW) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    digitalWrite(rightMotorPinOne,HIGH);
    digitalWrite(rightMotorPinTwo,LOW);
    digitalWrite(leftMotorPinOne,HIGH);
    digitalWrite(leftMotorPinTwo,LOW);
    
  } else {
    digitalWrite(rightMotorPinOne,HIGH);
    digitalWrite(rightMotorPinTwo, HIGH);
    digitalWrite(leftMotorPinOne,HIGH);
    digitalWrite(leftMotorPinTwo, HIGH);
  }
  
  if (redButtonState == LOW) {
    // turn LED off:
    digitalWrite(ledPin, LOW);
    digitalWrite(ledPin, HIGH);
    digitalWrite(rightMotorPinOne,LOW);
    digitalWrite(rightMotorPinTwo,HIGH);
    digitalWrite(leftMotorPinOne,LOW);
    digitalWrite(leftMotorPinTwo,HIGH);
    
  } else {
    digitalWrite(rightMotorPinOne,HIGH);
    digitalWrite(rightMotorPinTwo, HIGH);
    digitalWrite(leftMotorPinOne,HIGH);
    digitalWrite(leftMotorPinTwo, HIGH);
  }*/

  void UseSteeringValues(int leftSteeringValue, int rightSteeringValue) {
    analogWrite(RIGHT_MOTOR_PIN_ONE, 255 - rightSteeringValue);
    analogWrite(LEFT_MOTOR_PIN_ONE, 255 - leftSteeringValue);
  }
  
