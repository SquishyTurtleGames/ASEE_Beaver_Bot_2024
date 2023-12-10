#ifndef LineFollower_h
#define LineFollower_h

void LineSetup();
void ReadLine();
void LineFollow(int center);
int* GetSensor();
int* GetSteeringValues();
void ChangeSpeed(int newSpeed);
void ReadButtons();
String GetWheelSpeed();
#endif