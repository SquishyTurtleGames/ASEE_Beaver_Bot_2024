#ifndef AsyncDelay_h
#define AsyncDelay_h
#include "Arduino.h" 

class AsyncDelay 
{
public:
  AsyncDelay();
	AsyncDelay(double timeSec);
	bool DelayComplete();
  
private:
  double delayTime;
  double timeMillis;
};

#endif