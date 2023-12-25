#include "pinNumbers.h"
#include "ScreenSettings.h"
#include "ScreenControl.h"
#include "LineFollower.h"
#include "Drive.h"
#include "UserInput.h"
#include "ServoControl.h"


enum State {Startup, Running};
State presentState = Startup;

const int startSpeed = 50;

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

  pinMode(IRSensor1, INPUT);

  setupServo();
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
  if(getYellowState()) presentState = State::Running;

  UpdateOpticalEncoder();
  if(getEncoderButtonState() == LOW)
  {
    ChangeSpeed(getEncoderValue());
  }

  //For Testing
  Display(getEncoderValue());
  DisplayLineBreak();
  Display(getServoPos());
}

void RunningLoop()
{
  UseSteeringValues(GetSteeringValues()[0], GetSteeringValues()[1]);

  resetServo();
  if(getWhiteState()) Wack();

  int sensorVal = analogRead(IRSensor1);

  DisplaySensorReadings(GetSensor());
  DisplayLineBreak();
  Display(GetFinalMultiplier());
  DisplayLineBreak();
  Display(sensorVal);
}