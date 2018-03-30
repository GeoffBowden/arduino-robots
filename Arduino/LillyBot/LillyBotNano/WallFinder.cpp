#include "WallFinder.h"
#include "RobotDrive.h"
#include "DistanceSensor.h"
#include "WaggleDance.h"
#include <Arduino.h>

#define STOPPING_DISTANCE  6   // stop
#define CRAWLING_DISTANCE 16   // move  4.2 cm between distance mesurements
#define SLOWING_DISTANCE  30   // move  8.4 cm between distance mesurements
#define MOVING_DISTANCE  100   // 2 = x.tan(2) ::= x=2/tan(2) = 57-- move 16.9 below this move 16.9 cm between measurements, after this adjust position before moving 16.9 cm
#define SHOW_RESULT_IN_WAGGLEDANCE 


int WallFinder::MoveToWall( DistanceSensor* eyes, LillyDrive* drive, MoveToWallAlgorithm* Algorithm )
{
  Algorithm->MoveToWall( eyes, drive );
}

int MoveToWallSimple::MoveToWall( DistanceSensor* eyes, LillyDrive* drive )
{
  Serial.println( "Move to Wall Simple" );
  int distanceInMM = 0 ;
  int distanceOfOneWheelInMM = DIAMETER_OF_WHEEL_IN_MM; // half turn = 8.5
  int distance = GetDistanceToWallInCMSlightlyAdjustingPosition(eyes, drive);
  #ifdef SHOW_RESULT_IN_WAGGLEDANCE
    WaggleDance::ShowNumber( drive, distance ) ;
  #endif
  Serial.println( distance );
  while ( distance > STOPPING_DISTANCE )
  {
    if ( distance < CRAWLING_DISTANCE )
    {
      drive->ForwardsQuarterTurn();
  	  distanceInMM += distanceOfOneWheelInMM/4;
      distance = eyes->ReadModalDistanceInCM();
      #ifdef SHOW_RESULT_IN_WAGGLEDANCE
        WaggleDance::ShowNumber( drive, distance ) ;
      #endif
      Serial.println( distance );
    }
    else if ( distance < SLOWING_DISTANCE )
    {
      drive->ForwardsHalfTurn();
      distanceInMM += distanceOfOneWheelInMM/2;
      distance = eyes->ReadModalDistanceInCM();
      #ifdef SHOW_RESULT_IN_WAGGLEDANCE
        WaggleDance::ShowNumber( drive, distance ) ;
      #endif
      Serial.println( distance );
    }
    else if ( distance < MOVING_DISTANCE)
    {
      drive->ForwardsOneTurn();
      distanceInMM += distanceOfOneWheelInMM;
      distance = eyes->ReadModalDistanceInCM();
      #ifdef SHOW_RESULT_IN_WAGGLEDANCE
        WaggleDance::ShowNumber( drive, distance ) ;
      #endif
      Serial.println( distance );
    }
    else
    {
      drive->ForwardsOneTurn();       
	    distanceInMM += distanceOfOneWheelInMM;
      distance = GetDistanceToWallInCMSlightlyAdjustingPosition(eyes, drive);
    }
    Serial.println( distance );
  }
  // actually make distance in CM
  int distanceInCM = distanceInMM/10 ;
  return distanceInCM;
}


int MoveToWallAlgorithm::GetDistanceToWallInCMSlightlyAdjustingPosition( DistanceSensor* eyes, LillyDrive* drive )
{
  int shortestDistance ;
  Handedness handedness = Centre ;
  shortestDistance = eyes->ReadModalDistanceInMM();
  #ifdef SHOW_RESULT_IN_WAGGLEDANCE
    WaggleDance::ShowNumber( drive, shortestDistance ) ;
  #endif
  Serial.print( "Centre: " ) ; Serial.print( shortestDistance );
  drive->TurnLeft01Degree();
  drive->TurnLeft01Degree();
  int leftDistance = eyes->ReadModalDistanceInMM();
  #ifdef SHOW_RESULT_IN_WAGGLEDANCE
    WaggleDance::ShowNumber( drive, leftDistance ) ;
  #endif
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
  #ifdef SHOW_RESULT_IN_WAGGLEDANCE
    WaggleDance::ShowNumber( drive, rightDistance ) ;
  #endif
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

int MoveToWallWithoutNearMeasurements::MoveToWall( DistanceSensor* eyes, LillyDrive* drive )
{
  int distanceInMM = 0;
  int diameterOfWheelInCM = DIAMETER_OF_WHEEL_IN_MM / 10;
  int distance = GetDistanceToWallInCMSlightlyAdjustingPosition(eyes, drive);
  #ifdef SHOW_RESULT_IN_WAGGLEDANCE
    WaggleDance::ShowNumber( drive, distance ) ;
  #endif
  Serial.println( distance );
  int CrawlCutOffCount = 3;
  while ( distance > 3 )
  {
    //long distance
    if ( distance > ( 5 * diameterOfWheelInCM ) ) 
    {
      drive->ForwardsOneTurn();       
      distanceInMM += DIAMETER_OF_WHEEL_IN_MM;
      distance = GetDistanceToWallInCMSlightlyAdjustingPosition(eyes, drive);       
      #ifdef SHOW_RESULT_IN_WAGGLEDANCE
        WaggleDance::ShowNumber( drive, distance ) ;
      #endif
      Serial.println( distance );
    }
    // homing in
    else if ( distance > ( diameterOfWheelInCM + 3 ) ) 
    {
      drive->ForwardsOneTurn();       
      distanceInMM += DIAMETER_OF_WHEEL_IN_MM;
      distance = eyes->ReadModalDistanceInCM();
      #ifdef SHOW_RESULT_IN_WAGGLEDANCE
        WaggleDance::ShowNumber( drive, distance ) ;
      #endif
      Serial.println( distance );
    }
    // gonna hit
    else if ( distance >= diameterOfWheelInCM && distance <= diameterOfWheelInCM + 3 ) 
    {
      drive->ForwardsHalfTurn();
      distanceInMM += DIAMETER_OF_WHEEL_IN_MM/2;
      drive->ForwardsQuarterTurn();
      distanceInMM += DIAMETER_OF_WHEEL_IN_MM/4;
      for ( int j = 0; j<((diameterOfWheelInCM+3)-distance); j++ )
      { 
        for( int i = 1; i <= 10; i++ )
        {
          drive->ForwardsOneMM();
          distanceInMM += 1;
        }        
      }
      distance = eyes->ReadModalDistanceInCM();
      #ifdef SHOW_RESULT_IN_WAGGLEDANCE
        WaggleDance::ShowNumber( drive, distance ) ;
      #endif
      Serial.println( distance );
    }
    else if ( distance > 8 )
    {
      drive->ForwardsQuarterTurn();
      distanceInMM += DIAMETER_OF_WHEEL_IN_MM/4;
      distance = eyes->ReadModalDistanceInCM();
      #ifdef SHOW_RESULT_IN_WAGGLEDANCE
        WaggleDance::ShowNumber( drive, distance ) ;
      #endif
      Serial.println( distance );
    }
    else
    {
      for( int i = 1; i <= 10; i++ )
      {
        drive->ForwardsOneMM();
        distanceInMM += 1;
      }
      if ( CrawlCutOffCount <= 0 )
      {
        int distanceInCM = distanceInMM/10 ;
        return distanceInCM;
      }
      else
      {
        CrawlCutOffCount --;
      }
      distance = eyes->ReadModalDistanceInCM();
      #ifdef SHOW_RESULT_IN_WAGGLEDANCE
        WaggleDance::ShowNumber( drive, distance ) ;
      #endif
      Serial.println( distance );
    }
  }
  int distanceInCM = distanceInMM/10 ;
  return distanceInCM;
}


void MoveToWallKeepingCentred::CentreInPath( DistanceSensor* eyes, LillyDrive* drive )
{
  drive->TurnLeft90Degrees();
  int leftDistanceMM = eyes->ReadModalDistanceInMM();
  drive->TurnRight90Degrees();
  drive->TurnRight90Degrees();
  int rightDistanceMM = eyes->ReadModalDistanceInMM();
  int moveMM = abs( leftDistanceMM - rightDistanceMM ) / 2 ;
  // if we have to move and the move is not more than a small correction
  if ( moveMM > 0 && moveMM < 100 ) 
  {
    // facing the right
    // need to move left so reverse
    if ( leftDistanceMM > rightDistanceMM )
    {
      drive->BackwardsXMMs( moveMM ) ;
    }
    //need to move right so forwareds
    else if ( rightDistanceMM > leftDistanceMM )
    {
      drive->ForwardsXMMs( moveMM ) ;
    }
  }
  drive->TurnLeft90Degrees();    
}

int MoveToWallKeepingCentred::GetDistanceToTravelCM ( DistanceSensor* eyes )
{
  return eyes->ReadModalDistanceInCM() - 4;
}

int MoveToWallKeepingCentred::MoveToWall( DistanceSensor* eyes, LillyDrive* drive )
{
  int distanceToTravelCM = GetDistanceToTravelCM ( eyes );
  int distanceTravelledCM = 0;

  while ( distanceToTravelCM > 0 )
  {
    drive->ForwardsXMMs( 10 );
    distanceTravelledCM ++ ;
    if ( distanceTravelledCM % 20 == 0 ) 
    {
      CentreInPath( eyes, drive ) ;
      distanceToTravelCM = GetDistanceToTravelCM ( eyes );
    }
    else
    {
      distanceToTravelCM -- ;
    }
  }

  return distanceTravelledCM ;
}



