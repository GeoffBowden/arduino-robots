#include "RobotMaths.h"

#include <Arduino.h>

long MathsFunctions::GetModal(long readings[READING_COUNT])
{
  long modalReading = readings[0];
  int modalCount = 1 + GetCountOfXInArrayFromIndex( modalReading, readings, 1 );
  //Serial.print( "modalReading " ) ; Serial.print( modalReading ) ; Serial.print( " modal Count " ) ; Serial.println( modalCount ) ;
  long nextReading = 0;
  int nextCount = 0;
  int actualReadingCount = 1;
  for( int i = 1; i < READING_COUNT; i++ )
  {
		nextReading = readings[i];
	  nextCount = 1 + GetCountOfXInArrayFromIndex( nextReading, readings, i+1 );
    //Serial.print( "nextReading " ) ; Serial.print( nextReading ) ; Serial.print( " nextCount " ) ; Serial.println( nextCount ) ;  
	  if ( nextCount > modalCount )
	  {
    	modalCount = nextCount;
      modalReading = nextReading;
      actualReadingCount = 1;
    }
    if ( nextCount == modalCount )
    {
	    modalReading += nextReading;
	    actualReadingCount ++;
    }
  }      
  //Serial.print( "modalReading " ) ; Serial.print( modalReading ) ; Serial.print( " actualReadingCount " ) ; Serial.println( actualReadingCount ) ;
  return modalReading / actualReadingCount;
}

int MathsFunctions::GetCountOfXInArrayFromIndex( long x, long theArray[READING_COUNT], long index )
{
//  Serial.println( "GetCountOfXInArrayFromIndex" );
//  Serial.print( "Off to find: " ); 
//  Serial.println( x );
//  Serial.println( index );
  int count = 0 ;
//  Serial.println( "Searching..." );
  for( index; index < READING_COUNT; index++ )
  {
//    Serial.println( theArray[index] ) ;
	  if ( theArray[index] == x )
	  {
	    count++;
	  }
//    Serial.print( theArray[index] ); Serial.print( " " );
  }
//  Serial.println( " " );
//  Serial.println( count );
  return count;
} 


