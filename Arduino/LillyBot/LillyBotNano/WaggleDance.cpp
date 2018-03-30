
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
void WaggleDance::ShowNumber( WaggleDriver* drive, int Number )
{
  boolean negative = (Number < 0) ;
  Number = abs( Number ) ;
  int thousands = Number / 1000 ;
  int hundreds = (Number - (thousands*1000))/100;
  int tens = (Number - ((thousands*1000)+(hundreds*100)))/10;
  int units = (Number - ((thousands*1000)+(hundreds*100)+(tens*10)));
  // start the number
  delay( 200 ) ;  
  JigLeft(drive );
  delay( 200 ) ;  
  if( negative ) 
  {
    drive->SmallGestureRight();
    drive->SmallGestureLeft();
    drive->SmallGestureLeft();
    drive->SmallGestureRight();
    drive->SmallGestureRight();
    drive->SmallGestureLeft();
    delay( 100 ) ;
  }
  // jig forwards for each thousand in number than jig right as the divider
  if ( thousands > 0 ) { ShowDigit( drive, thousands ); }
  if (( thousands > 0 )&&( hundreds > 0 )) { ShowDigit( drive, hundreds ); }
  if (( thousands > 0 )&&( hundreds > 0 )&&(tens>0)) { ShowDigit( drive, tens ); } 
  ShowDigit( drive, units ); 
  // end the number 
  JigLeft( drive );
}
void WaggleDance::ShowDigit( WaggleDriver* drive, int Digit )
{
  if ( Digit > 0 ) 
  {
    for( int j=1; j<=Digit; j++ ) 
    {
      drive->GestureForward();
      delay( 10 ) ;
      drive->GestureBackward();
      delay( 90 ) ;  
    }
  }  
  else
  {
    drive->SmallGestureForward();
    No( drive ) ;
    drive->SmallGestureBackward();
  }
  delay( 200 );
  JigRight( drive );
  delay( 200 ) ;  
}

