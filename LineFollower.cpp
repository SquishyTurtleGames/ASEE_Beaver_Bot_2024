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


void LineSetup() 
{
  for (int i=7; i >= 0; --i) 
  {
    pinMode(LINE_SENSOR[i],INPUT);
  }
}
int* GetSensor() 
{
  ReadLine();
  return sensors;
}

int* GetSteeringValues() {
  ReadLine();
  CalcSteeringValues();
  FindLargestChunk(sensors);
  finalMultiplier = CalculateFinalMultiplier(largestChunkStart, largestChunkEnd);
  steeringValues[0] = leftSteeringValue;
  steeringValues[1] = rightSteeringValue;
  return steeringValues;
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
      //check if we're not currently on a chunk
      if(currentChunkStart == -1)
      {
        currentChunkStart = i;
      }
      currentChunkEnd = i;

      currentChunksize++;

      //This is true when the current chunk is the largest chunk so far
      if(currentChunksize > largestChunksize)
      {
        largestChunksize = currentChunksize;
        largestChunkStart = currentChunkStart;
        largestChunkEnd = currentChunkEnd;
      }
    }

    if(values[i] == 0)
    {
      //resets values to the initial conditions
      currentChunksize = 0;
      currentChunkStart = -1;
      currentChunkEnd = -1;
    }
  }
}

double CalculateFinalMultiplier(int start, int end)
{
  /*
  this is a more complicated bit of logic. !! BE CAREFUL to undersand what it does before you change anything !!

  this method begins with the start and end indexs of the largest chunk of 1's in the line sensor date.

  This method does 2 main things:
  1. it calculates the average index of the chunk. It does this by adding up all the indexes in the chunk and 
    dividing by the number of 1's in the chunk

      example: if the data is 00001110. There are 1's on index 4, 5, and 6. The method adds up 4 + 5 + 6 = 15, then divides by 3, so the result is 5. 
      5 is the midpoint index of the chunk --> 00001(1)10. The method now treats that as the working location of the line.

  2. this method shifts the index so that it is better for calculating the wheel speed.
    by default the indexes map like this:

    X  X  X  X  |  X  X  X  X
    ^  ^  ^  ^  |  ^  ^  ^  ^
    0  1  2  3  |  4  5  6  7

    however, the data is easier to use of negative numbers represents that the line is on the left side of the sensor and positive the right.
    to do this we subtract 3 if the average index is above 3.5, and 4 if it is below 3.5
    The result is that the multiplier values map to the data like this:

    X  X  X  X  |  X  X  X  X
    ^  ^  ^  ^  |  ^  ^  ^  ^
   -4 -3 -2 -1  | +1 +2 +3 +4

      example: if the average index of the line is 5 (as in the previous example) the method subtracts 3 resulting in +2, which is the final multiplier

  */


  //this is the number of 1's in the chunk
  int chunkSize = end - start + 1;

  //adds each index in the largest chunk together
  int indexTotal = 0;
  for(int i = start; i < end + 1; i++)
  {
    indexTotal += i;
  }

  //gets the midpoint index of the chunk
  double averageIndex = (double)indexTotal / (double)chunkSize;

  //subtrancts the appropriate value so that the index range goes from 
  // 0 - 7
  //  to 
  //-4 - 4
  double multiplier = 0;
  if(averageIndex > 3.5)
  {
    multiplier = averageIndex - 3.0; 
  }
  else if(averageIndex < 3.5)
  {
    multiplier = averageIndex - 4.0;
  }

  return multiplier;
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

void ChangeSpeed(int newSpeed) 
{
  wheelSpeed = constrain(newSpeed, 0, 100);
}

int GetWheelSpeed() 
{
  return wheelSpeed;
}
