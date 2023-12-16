
#include <Arduino.h>
#include "LineFollower.h"
#include "pinNumbers.h"
#include "ScreenControl.h"

int amountSeen = 0;
//int lastLineIndex = 0;
int firstLineIndex = 0;
int leftSteeringValue = 0;
int rightSteeringValue = 0;

int wheelSpeed = 100;


int sensors[8];
int steeringValues[2];

double finalMultiplier;

bool lineCounted = false;
int linesPassed = 0;

int largestChunkStart = -1;
int largestChunkEnd = -1;


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

int GetLargestChunkStart()
{
  return largestChunkStart;
}

int GetLargestChunkEnd()
{
  return largestChunkEnd;
}

double GetFinalMultiplier()
{
  return finalMultiplier;
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
  }
  
  FindLargestChunk(sensors);

  finalMultiplier = CalculateFinalMultiplier(largestChunkStart, largestChunkEnd);
}

void FindLargestChunk(int values[8])
{
  int currentChunkStart = -1;
  int currentChunkEnd = -1;
  int currentChunksize = 0;
  int largestChunksize = 0;

  for(int i = 0; i < 8; i++)
  {
    if(values[i] == 1)
    {
      if(currentChunkStart == -1)
      {
        currentChunkStart = i;
      }
      currentChunkEnd = i;

      currentChunksize++;

      if(currentChunksize > largestChunksize)
      {
        largestChunksize = currentChunksize;
        largestChunkStart = currentChunkStart;
        largestChunkEnd = currentChunkEnd;
      }
    }

    if(values[i] == 0)
    {
      currentChunksize = 0;
      currentChunkStart = -1;
      currentChunkEnd = -1;
    }
  }
}

double CalculateFinalMultiplier(int start, int end)
{
  int chunkSize = end - start + 1;

  int indexTotal = 0;
  for(int i = start; i < end + 1; i++)
  {
    indexTotal += i;
  }

  double averageIndex = (double)indexTotal / (double)chunkSize;

  double output = 0;
  if(averageIndex >= 3.5)
  {
    output = averageIndex - 3.0; 
  }
  else if(averageIndex < 3.5)
  {
    output = averageIndex - 4.0;
  }

  return output;
}

void LineFollow(int center = 3) {
  if (amountSeen == 0) {
    //floor it and pray? Consider Circling 
    //digitalWrite(LEDG, LOW);
  }
  else {
    firstLineIndex--;
    if (firstLineIndex != -1) {
      rightSteeringValue = (wheelSpeed + 15*((wheelSpeed - 90)/10.0)*(firstLineIndex - center)); //10.0 is a double by design
      leftSteeringValue = (wheelSpeed - 15*((wheelSpeed - 90)/10.0)*(firstLineIndex - center)); 
    
    }
  }
}

void ChangeSpeed(int newSpeed) {
  wheelSpeed = newSpeed;
}

String GetWheelSpeed() {
  return String(wheelSpeed);
}
