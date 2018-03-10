#include "WallFinder.h"
#include "RobotDrive.h"
#include "DistanceSensor.h"
#include <Arduino.h>

#define STOPPING_DISTANCE  6   // stop
#define CRAWLING_DISTANCE 16   // move  4.2 cm between distance mesurements
#define SLOWING_DISTANCE  30   // move  8.4 cm between distance mesurements
#define MOVING_DISTANCE  100   // 2 = x.tan(2) ::= x=2/tan(2) = 57-- move 16.9 below this move 16.9 cm between measurements, after this adjust position before moving 16.9 cm

int WallFinder::GetDistanceToWallSlightlyAdjustingPosition( DistanceSensor* eyes, LillyDrive* drive )
{
	int shortestDistance ;
	Handedness handedness = Centre ;
  shortestDistance = eyes->ReadModalDistanceInMM();
  Serial.print( "Centre: " ) ; Serial.print( shortestDistance );
	drive->TurnLeft01Degree();
  drive->TurnLeft01Degree();
  int leftDistance = eyes->ReadModalDistanceInMM();
  Serial.print( ", Left: " ) ; Serial.print( leftDistance );
  if ( leftDistance < shortestDistance )
  {
    handedness = Left;
    shortestDistance = leftDistance;
  }
  drive->TurnRight01Degree();
  drive->TurnRight01Degree();
  drive->TurnRight01Degree();
	drive->TurnRight01Degree();
	int rightDistance = eyes->ReadModalDistanceInMM();
  Serial.print( ", Right: " ) ; Serial.print( rightDistance );
	if ( rightDistance < shortestDistance )
	{
		handedness = Right;
		shortestDistance = rightDistance;
	}
	if ( handedness == Left ) 
	{
    Serial.println( " => Choosing left" );
		drive->TurnLeft01Degree();
		drive->TurnLeft01Degree();
    drive->TurnLeft01Degree();
    drive->TurnLeft01Degree();
	}
	else if ( handedness == Centre ) 
	{
    Serial.println( " => Choosing centre" );
    drive->TurnLeft01Degree();
		drive->TurnLeft01Degree();
	}	
  else
  {
    Serial.println( " => Choosing right" );
  }
  // read in MM for discerning which direction to point, 
  // return in CM the shortest distance read which is 
  // where coincidentelly we are pointing
	return shortestDistance/10;
}

int WallFinder::MoveToWall( DistanceSensor* eyes, LillyDrive* drive )
{
  Serial.println( "Move to Wall" );
  int distanceInCM = 0 ;
  int distanceInMM = 0 ;
  int distanceOfOneWheelInMM = 170; // half turn = 8.5
  int distance = WallFinder::GetDistanceToWallSlightlyAdjustingPosition(eyes, drive);
  Serial.println( distance );
  while ( distance > STOPPING_DISTANCE )
  {
    if ( distance < CRAWLING_DISTANCE )
    {
      drive->ForwardsQuarterTurn();
  	  distanceInCM += distanceOfOneWheelInMM/4;
      distance = eyes->ReadModalDistanceInCM();
    }
    else if ( distance < SLOWING_DISTANCE )
    {
      drive->ForwardsHalfTurn();
      distanceInCM += distanceOfOneWheelInMM/2;
      distance = eyes->ReadModalDistanceInCM();
    }
    else if ( distance < MOVING_DISTANCE)
    {
      drive->ForwardsOneTurn();
      distanceInCM += distanceOfOneWheelInMM;
      distance = eyes->ReadModalDistanceInCM();
    }
    else
    {
      drive->ForwardsOneTurn();       
	    distanceInCM += distanceOfOneWheelInMM;
      distance = WallFinder::GetDistanceToWallSlightlyAdjustingPosition(eyes, drive);
    }
    Serial.println( distance );
  }
  return distanceInCM/10;
}
