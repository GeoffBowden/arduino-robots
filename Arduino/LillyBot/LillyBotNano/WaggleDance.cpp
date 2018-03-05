
#include "WaggleDance.h"
#include <Arduino.h>

void WaggleDance::Yes( LillyDrive* drive )
{
  drive->ForwardsOneMM();
  drive->ForwardsOneMM();
  drive->BackwardsOneMM();
  drive->BackwardsOneMM();
  drive->BackwardsOneMM();
  drive->BackwardsOneMM();
  drive->ForwardsOneMM();
  drive->ForwardsOneMM();
}
void WaggleDance::No (  LillyDrive* drive )
{
  JigLeft(drive);
  JigRight(drive);
  JigRight(drive);
  JigLeft(drive);
}
void WaggleDance::Jig( LillyDrive* drive )
{
  No(drive);  
  Yes(drive);  
  No(drive);  
  Yes(drive);  
}
void WaggleDance::JigLeft( LillyDrive* drive )
{
  drive->TurnLeft01Degree();
  drive->TurnLeft01Degree();
  drive->TurnRight01Degree();
  drive->TurnRight01Degree();
}
void WaggleDance::JigLeftXtimes( LillyDrive* drive, int xTimes )
{
  for( int i = 1; i <= xTimes; ++i )
  {
    JigLeft( drive );
  }
}
void WaggleDance::JigRight( LillyDrive* drive )
{
  drive->TurnRight01Degree();
  drive->TurnRight01Degree();
  drive->TurnLeft01Degree();
  drive->TurnLeft01Degree();
}
void WaggleDance::JigRightXtimes( LillyDrive* drive, int xTimes )
{
  for( int i = 1; i <= xTimes; ++i )
  {
    JigRight( drive );
  }
}

