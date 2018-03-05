

#include "RobotDrive.h"
#define DELAY 100
#define QUARTER_TURN_STEPS 2548  //2498;
#define DEGREE_TURN_STEPS QUARTER_TURN_STEPS/90  //2498;
////////////////////////////////////////////////////////////////////////////////////////////////////////

LillyDrive::LillyDrive()
{
  leftMotor = new StepperMotor( 8,7,6,5 );
  rightMotor = new StepperMotor ( A1, A2, A3, A4 );
}
void LillyDrive::ForwardsOneTurn()
{
  Serial.println( "Forwards one rotation" ) ;
  Forwards(this->maxSteps);
}
void LillyDrive::ForwardsHalfTurn()
{
  Serial.println( "Forwards one half rotation" ) ;
  Forwards(this->maxSteps/2);
}
void LillyDrive::ForwardsQuarterTurn()
{
  Serial.println( "Forwards one quarter rotation" ) ;
  Forwards(this->maxSteps/4);  
}
void LillyDrive::Forwards( int steps )
{
  unsigned long lastTime; 
  unsigned long currentMillis;
  for(int i=0; i<=steps; )
  {
    currentMillis = micros();
    if (currentMillis < lastTime ) { lastTime = currentMillis; } 
    if(currentMillis-lastTime>=this->speedDelay)
    {
      leftMotor->MoveForwardsOneStep();
      rightMotor->MoveForwardsOneStep();
      lastTime = micros(); //currentMillis;
      i++;
    }
  }
}
void LillyDrive::Backwards( int steps )
{
  unsigned long lastTime; 
  unsigned long currentMillis;
  for(int i=0; i<=steps; )
  {
    currentMillis = micros();
    if (currentMillis < lastTime ) { lastTime = currentMillis; } 
    if(currentMillis-lastTime>=this->speedDelay)
    {
      leftMotor->MoveBackwardsOneStep();
      rightMotor->MoveBackwardsOneStep();
      lastTime = micros(); //currentMillis;
      i++;
    }
  }
}
void LillyDrive::BackwardsQuarterTurn()
{
  Backwards(this->maxSteps/4);  
}
void LillyDrive::BackwardsOneMM()
{
  int steps = 24;
  this->Backwards(steps);
}

void LillyDrive::TestLeftMotor()
{
  unsigned long steps = 1500;
  unsigned long lastTime; 
  unsigned long currentMillis;
Serial.println( "backwards" );
  for(int i=0; i<=steps; )
  {
    currentMillis = micros();
    if (currentMillis < lastTime ) { lastTime = currentMillis; } 
    if(currentMillis-lastTime>=this->speedDelay)
    {
      leftMotor->MoveBackwardsOneStep();
      lastTime = micros(); //currentMillis;
      i++;
    }
//Serial.println( i );
  }
Serial.println( "forwards" );
  for(int i=0; i<=steps; )
  {
    currentMillis = micros();
    if (currentMillis < lastTime ) { lastTime = currentMillis; } 
    if(currentMillis-lastTime>=this->speedDelay)
    {
      leftMotor->MoveForwardsOneStep();
      lastTime = micros(); //currentMillis;
      i++;
    }
  }  
}
void LillyDrive::TestRightMotor()
{
  unsigned long steps = 1500;
  unsigned long lastTime; 
  unsigned long currentMillis;
Serial.println( "backwards" );
  for(int i=0; i<=steps; )
  {
    currentMillis = micros();
    if (currentMillis < lastTime ) { lastTime = currentMillis; } 
    if(currentMillis-lastTime>=this->speedDelay)
    {
      rightMotor->MoveBackwardsOneStep();
      lastTime = micros(); //currentMillis;
      i++;
    }
//Serial.println( i );
  }
Serial.println( "forwards" );
  for(int i=0; i<=steps; )
  {
    currentMillis = micros();
    if (currentMillis < lastTime ) { lastTime = currentMillis; } 
    if(currentMillis-lastTime>=this->speedDelay)
    {
      rightMotor->MoveForwardsOneStep();
      lastTime = micros(); //currentMillis;
      i++;
    }
//Serial.println( i );
  }
}
    
void LillyDrive::doDelay( long startMicros, long endMicros ) 
{
    if ( endMicros < startMicros )
    {
      delay( DELAY );
    }
    else
    {
      long diff = endMicros - startMicros ;
      if( diff < DELAY ) 
      {
        delay( DELAY - diff );
      }
    }
}

void LillyDrive::ForwardsOneMM()
{
  int steps = 24;
  this->Forwards(steps);
}
void LillyDrive::TurnLeft01Degree()
{
  int steps = DEGREE_TURN_STEPS;
  unsigned long lastTime; 
  unsigned long currentMillis;
  for(int i=0; i<=steps; )
  {
    currentMillis = micros();
    if (currentMillis < lastTime ) { lastTime = currentMillis; } 
    if(currentMillis-lastTime>=this->speedDelay)
    {
      leftMotor->MoveBackwardsOneStep();
      rightMotor->MoveForwardsOneStep();
      lastTime = micros(); //currentMillis;
      i++;
    }
  }
}
void LillyDrive::TurnLeft90Degrees()
{
  Serial.println( "Turn left 90 degrees" ) ;
  int steps = QUARTER_TURN_STEPS;
  unsigned long lastTime; 
  unsigned long currentMillis;
  for(int i=0; i<=steps; )
  {
    currentMillis = micros();
    if (currentMillis < lastTime ) { lastTime = currentMillis; } 
    if(currentMillis-lastTime>=this->speedDelay)
    {
      leftMotor->MoveBackwardsOneStep();
      rightMotor->MoveForwardsOneStep();
      lastTime = micros(); //currentMillis;
      i++;
    }
  }
}

void LillyDrive::TurnRight01Degree()
{
  int steps = DEGREE_TURN_STEPS;
  unsigned long lastTime; 
  unsigned long currentMillis;
  for(int i=0; i<=steps; )
  {
    currentMillis = micros();
    if (currentMillis < lastTime ) { lastTime = currentMillis; } 
    if(currentMillis-lastTime>=this->speedDelay)
    {
      rightMotor->MoveBackwardsOneStep();
      leftMotor->MoveForwardsOneStep();
      lastTime = micros(); //currentMillis;
      i++;
    }
  }
}
void LillyDrive::TurnRight90Degrees()
{
  Serial.println( "Turn right 90 degrees" ) ;
  int steps = QUARTER_TURN_STEPS;
  unsigned long lastTime; 
  unsigned long currentMillis;
  for(int i=0; i<=steps; )
  {
    currentMillis = micros();
    if (currentMillis < lastTime ) { lastTime = currentMillis; } 
    if(currentMillis-lastTime>=this->speedDelay)
    {
      rightMotor->MoveBackwardsOneStep();
      leftMotor->MoveForwardsOneStep();
      lastTime = micros(); //currentMillis;
      i++;
    }
  }
}
//////////////////////////////////////////////////////////////////
//  This will take one measurement and try to move towards the wall
//  when an object is a long way away if it has a gap underneath it
//  it will still register a good distance. When we get near the 
//  distance sensor will not be able see the object, just the gap.
//  This was discovered approaching the sofa.
//////////////////////////////////////////////////////////////////
int LillyDrive::MoveToWall( DistanceSensor* eyes )
{
  Serial.println( "Move to Wall" );
  int distanceInWheelRevolutions = 0 ;
  int distanceOfOneWheelInCm = 17; // half turn = 8.5
  int distance = eyes->ReadDistanceInCM();
  while ( distance > 5 )
  {
    if ( distance < 20 )
    {
      this->ForwardsQuarterTurn(); 
    }
    else
    {
      this->ForwardsOneTurn();       
    }
    distance = eyes->ReadDistanceInCM();
  }
}

