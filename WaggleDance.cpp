
#include "WaggleDance.h"
#include <Arduino.h>

void WaggleDance::Yes( WaggleDriver* drive )
{
  drive->GestureForward();
  drive->GestureBackward();
  drive->GestureBackward();
  drive->GestureForward();
}
void WaggleDance::No (  WaggleDriver* drive )
{
  JigLeft(drive);
  JigRight(drive);
  JigRight(drive);
  JigLeft(drive);
}
void WaggleDance::Jig( WaggleDriver* drive )
{
  No(drive);  
  Yes(drive);  
  No(drive);  
  Yes(drive);  
}
void WaggleDance::JigLeft( WaggleDriver* drive )
{
  drive->GestureLeft();
  drive->GestureRight();
}
void WaggleDance::JigLeftXtimes( WaggleDriver* drive, int xTimes )
{
  for( int i = 1; i <= xTimes; ++i )
  {
    JigLeft( drive );
  }
}
void WaggleDance::JigRight( WaggleDriver* drive )
{
  drive->GestureRight();
  drive->GestureLeft();
}
void WaggleDance::JigRightXtimes( WaggleDriver* drive, int xTimes )
{
  for( int i = 1; i <= xTimes; ++i )
  {
    JigRight( drive );
  }
}

