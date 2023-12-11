#include "pinNumbers.h"
#include "ScreenSettings.h"
#include "ScreenControl.h"
#include "LineFollower.h"
#include "Drive.h"
#include "UserInput.h"


enum State {Startup, Running};
State presentState = Startup;

const int startSpeed = 100;

int testSensorValues1[8] = {0 ,1, 1, 0, 1, 0, 1, 0} ;
int testSensorValues2[8] = {0 ,0, 1, 1, 1, 1, 0, 0} ;

double testVal = 0;

void setup() 
{
  Serial.begin(9600);

  if(!Init_Screen())
  { for(;;); } 

  LineSetup();
  WheelsSetup();
  UserInputSetup();

  ChangeSpeed(startSpeed);
  setEncoderValue(startSpeed);
}

void loop() 
{
  SwitchState(presentState);

  TickDisplay();
}

void SwitchState(State currentState)
{
  switch(currentState)
  {
    case State::Startup:
      StartupLoop();
      break;

    case State::Running:
      RunningLoop();
      break;

    default:
      break;
  }
}

void StartupLoop()
{
  if(getYellowState() == LOW) presentState = State::Running;

  UpdateOpticalEncoder();
  if(getEncoderButtonState() == LOW)
  {
    ChangeSpeed(getEncoderValue());
  }

  //For Testing
  AppendStringLoopSafe(String(getEncoderValue()));
}

void RunningLoop()
{
  DisplaySensorReadings(GetSensor());

  ReadLine();

  //Real code
  //UseSteeringValues(GetSteeringValues()[0], GetSteeringValues()[1]);

  //Testing Code
  UseSteeringValues((int)testVal, (int)testVal);
  testVal += 0.01;

  AppendStringLoopSafe(String(testVal));
}