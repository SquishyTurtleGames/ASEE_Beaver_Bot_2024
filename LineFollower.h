#ifndef LineFollower_h
#define LineFollower_h

void LineSetup();
void ReadLine();
double CalculateFinalMultiplier(int start, int end);
void FindLargestChunk(int values[8]);
void CalcSteeringValues();
int* GetSensor();
int* GetSteeringValues();
int GetLargestChunkStart();
int GetLargestChunkEnd();
double GetFinalMultiplier();
void ChangeSpeed(int newSpeed);
void ReadButtons();
int GetWheelSpeed();
#endif