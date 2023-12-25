#ifndef LineFollower_h
#define LineFollower_h

void LineSetup();
void ReadLine();
double CalculateFinalMultiplier(int start, int end);
void FindLargestChunk(int values[8]);
void CalcSteeringValues();
int* GetSensor();
int* GetSteeringValues();
double GetFinalMultiplier();
void ChangeSpeed(int newSpeed);
int GetWheelSpeed();
#endif