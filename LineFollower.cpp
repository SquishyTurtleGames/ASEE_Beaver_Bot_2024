
#include <Arduino.h>
#include "LineFollower.h"
#include "pinNumbers.h"
#include "ScreenControl.h"

int amountSeen = 0;
//int lastLineIndex = 0;
int firstLineIndex = 0;
int sensorCounter = 0;
int leftSteeringValue = 0;
int rightSteeringValue = 0;

int wheelSpeed = 100;


int sensors[8];
int steeringValues[2];


bool lineCounted = false;
int linesPassed = 0;


void LineSetup() {
for (int i=7; i >= 0; --i) {
  pinMode(LINE_SENSOR[i],INPUT);
}
//Servo steering;

}
int* GetSensor() {
  ReadLine();
  return sensors;
}

int* GetSteeringValues() {
  ReadLine();
  LineFollow(3);
  steeringValues[0] = leftSteeringValue;
  steeringValues[1] = rightSteeringValue;
  return steeringValues;
}


void ReadLine() {
  amountSeen = 0;
  //double averageSensor = 0;
  firstLineIndex = -1;
  for(int i = 7; i >= 0; i--) {
    sensors[i] = (digitalRead(LINE_SENSOR[i]) == HIGH) ? 1 : 0;
    //Serial.print(sensors[i]);
    if(sensors[i] == 1) {
       if(firstLineIndex == -1) {
        firstLineIndex = i;
      }
      //averageSensor += i;
      ++amountSeen;
    }
    //if(amountSeen == 2) {

    //}
    
  }
  
  Serial.println(" ");
  //averageSensor /= amountSeen;
  sensorCounter = 0;
  for (int i = 0; i < 8; i++ ){
    sensorCounter += sensors[i] << i;
  }
  
}

void LineFollow(int center = 3) {
  if (amountSeen == 0) {
    //floor it and pray? Consider Circling 
    //digitalWrite(LEDG, LOW);
  }
  else if (amountSeen >= 7) {
  }
  else {
    firstLineIndex--;
    if (firstLineIndex != -1) {
      rightSteeringValue = (wheelSpeed + 15*((wheelSpeed - 90)/10.0)*(firstLineIndex - center)); //10.0 is a double by design
      leftSteeringValue = (wheelSpeed - 15*((wheelSpeed - 90)/10.0)*(firstLineIndex - center)); 
    
    }
    Serial.println(firstLineIndex - center);
  }
}

void ChangeSpeed(int newSpeed) {
  wheelSpeed = newSpeed;
}

String GetWheelSpeed() {
  return String(wheelSpeed);
}
