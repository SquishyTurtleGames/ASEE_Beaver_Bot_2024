#include <Arduino.h>
#include "LineFollower.h"
#include "pinNumbers.h"
#include "ScreenControl.h"

int amountSeen = 0;

double adjustmentIncrement = 5.0;
int leftSteeringValue = 0;
int rightSteeringValue = 0;

int wheelSpeed;


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
  CalcSteeringValues();
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


void ReadLine() 
{
  amountSeen = 0;

  for(int i = 7; i >= 0; i--) 
  {
    sensors[i] = (digitalRead(LINE_SENSOR[i]) == HIGH) ? 1 : 0;

    if(sensors[i] == 1) 
    {
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
  if(averageIndex > 3.5)
  {
    output = averageIndex - 3.0; 
  }
  else if(averageIndex < 3.5)
  {
    output = averageIndex - 4.0;
  }
  else
  {
    output = 0;
  }

  return output;
}

void CalcSteeringValues() 
{
  double rightSteeringValueRaw;
  double leftSteeringValueRaw;

  if (amountSeen == 0) 
  {
    //floor it and pray? Consider Circling 
    //emergency code to go here
  }
  else 
  {
    double potentialMax = 100 + adjustmentIncrement * 4;

    rightSteeringValueRaw = wheelSpeed + (adjustmentIncrement * finalMultiplier);
    leftSteeringValueRaw = wheelSpeed - (adjustmentIncrement * finalMultiplier);

    rightSteeringValue = (rightSteeringValueRaw / potentialMax) * 100.0;
    leftSteeringValue = (leftSteeringValueRaw / potentialMax) * 100.0;
  }
}

void ChangeSpeed(int newSpeed) {
  wheelSpeed = constrain(newSpeed, 0, 100);
}

int GetWheelSpeed() {
  return wheelSpeed;
}
