#include "pinNumbers.h"
#include "ScreenSettings.h"
#include "ScreenControl.h"
#include "LineFollower.h"
#include "Drive.h"
#include "UserInput.h"
#include "ServoControl.h"
#include "StickSensor.h"


//State Variables
enum State {Startup, Running};
State presentState = Startup;

//Parameters
const int stickSensorThreshhold = 60;
const int startSpeed = 50;


void setup() 
{
  Serial.begin(9600);

  if(!Init_Screen())
  { for(;;); } 

  //Various Setup
  LineSetup();
  WheelsSetup();
  UserInputSetup();
  setupStickSensor();
  setupServo();

  //Initializing Encoder
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
  //Addition States should be called here
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
  //Check Yellow button
  if(getYellowState()) presentState = State::Running;

  //Check Encoder
  UpdateOpticalEncoder();
  if(getEncoderButtonState() == LOW)
  {
    ChangeSpeed(getEncoderValue());
  }

  //Display Error Handling
  Display(getEncoderValue());
  DisplayLineBreak();
}

void RunningLoop()
{
  //Steering Control
  UseSteeringValues(GetSteeringValues()[0], GetSteeringValues()[1]);

  //Servo Control
  resetServo();
  if(checkThreshhold(stickSensorThreshhold)) Wack();

  //Display Error Handling
  DisplaySensorReadings(GetSensor());
  DisplayLineBreak();
  Display(GetFinalMultiplier());
  DisplayLineBreak();
  Display(getSensorVal());
}