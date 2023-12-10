#include "pinNumbers.h"
#include "ScreenSettings.h"
#include "ScreenControl.h"
#include "LineFollower.h"
#include "Drive.h"
#include "UserInput.h"


enum State {Startup, Running};
State presentState = Startup;

const int startSpeed = 100;

unsigned long timeMillis = millis();
bool toggle = false;
int testSensorValues1[8] = {0 ,1, 1, 0, 1, 0, 1, 0} ;
int testSensorValues2[8] = {0 ,0, 1, 1, 1, 1, 0, 0} ;

void setup() 
{
  Serial.begin(9600);

  if(!Init_Screen())
  { for(;;); } 

  LineSetup();
  WheelsSetup();

  ChangeSpeed(startSpeed);
  setEncoderValue(startSpeed);

  SetupUserInput();
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
    case State::Running:
      RunningLoop();
      break;

    case State::Startup:
      StartupLoop();
      break;

    default:
      break;
  }
}

void RunningLoop()
{
  DisplaySensorReadings(GetSensor());

  ReadLine();

  //Real code
  //UseSteeringValues(GetSteeringValues()[0], GetSteeringValues()[1]);

  //Testing Code
  UseSteeringValues(200, 200);
}

void StartupLoop()
{
  if(getYellowState() == LOW) presentState = State::Running;

  ReadOpticalEncoder();
  if(getEncoderButtonState() == LOW)
  {
    ChangeSpeed(getEncoderValue());
  }

  //For Testing
  AppendString(String(getEncoderValue()));
}

