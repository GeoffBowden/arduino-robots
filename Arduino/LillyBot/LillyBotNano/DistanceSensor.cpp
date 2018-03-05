#include "DistanceSensor.h"
#include "RobotMaths.h"

DistanceSensor::DistanceSensor( int triggerPin, int listenerPin )
{
  this->triggerPin = triggerPin;
  this->sensorPin = listenerPin;
  if ( this->triggerPin != this->sensorPin )
  {
    pinMode(this->triggerPin, OUTPUT);
    pinMode(this->sensorPin, INPUT);
  }
}

long DistanceSensor::ReadDuration()
{
  long duration = 0;
  PrimeSensor();
  this->SetSensorPin();
  duration = pulseIn(this->sensorPin, HIGH);
  return duration;  
}

long DistanceSensor::ReadDistanceInMM()
{
  long duration = 0 ;
  delay ( 20 );
  for ( int i = 1; i<=5; i++ )
  {
    duration += ReadDuration();
  }
  duration /= 5;
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance traveled.
  //return (( duration * 100 ) / 29 / 2) ;
  return ( ( duration * 10 ) / 58 ) ;
}
long DistanceSensor::ReadDistanceInCM()
{
  long duration = 0 ;
//  delay ( 20 );
  for ( int i = 1; i<=READING_COUNT; i++ )
  {
    int reading = ReadDuration();
//    Serial.print( reading/58 ) ; Serial.print( " " ) ; 
    duration += reading/58;  
  }
//  Serial.println( duration );
  duration /= READING_COUNT;
//  Serial.print( "Distance read = " ) ; Serial.println( duration ) ;
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  //return (( duration * 100 ) / 29 / 2) ;
  return ( ( duration ) ) ;
}
long DistanceSensor::ReadAverageDistanceInCM()
{
  long readings[READING_COUNT];
  long sum = 0;
  for( int i = 0; i < READING_COUNT; i ++ )
  {
    long reading = ReadDistanceInCM();
    readings[i] = reading;
    sum += reading;
  } 
  long ave = sum/READING_COUNT;
  return ave;
}
long DistanceSensor::ReadModalDistanceInCM()
{
  long readings[READING_COUNT];
  long sum = 0;
  for( int i = 0; i < READING_COUNT; i ++ )
  {
    long reading = ReadDistanceInCM();
    readings[i] = reading;
  } 
  long ave = MathsFunctions::GetModal( readings );
  return ave;
}
long DistanceSensor::ReadSlowAverageDistanceInCM()
{
  long duration = 0 ;
  int reading = 0 ;
  for ( int i = 1; i<=READING_COUNT; i++ )
  {
    delay( 100 );
    duration = ReadDuration();
    reading += duration/58;
  }
  reading /= READING_COUNT;
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  //return (( duration * 100 ) / 29 / 2) ;
  return ( reading ) ;
}
long DistanceSensor::ReadAverageFromModalDistanceInCM()
{
  long sum = 0;
  for( int i = 0; i < READING_COUNT; i ++ )
  {
    sum += ReadModalDistanceInCM();
  } 
  long ave = sum/READING_COUNT ;
  return ave;
}
void DistanceSensor::PrimeSensor()
{
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  this->SetTriggerPin();
  digitalWrite(this->triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(this->triggerPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(this->triggerPin, LOW);
}

void DistanceSensor::SetSensorPin()
{
  if ( this->triggerPin == this->sensorPin )
  {
    pinMode(this->sensorPin, INPUT);
  }
}

void DistanceSensor::SetTriggerPin()
{
  if ( this->triggerPin == this->sensorPin )
  {
    pinMode(this->sensorPin, OUTPUT);
  }
}

boolean DistanceSensor::IsExit()
{
  int dist = ReadAverageFromModalDistanceInCM(); //ReadModalDistanceInCM();
  Serial.print( "distance: " );
  Serial.println(dist);
	if( dist > range )
	{
    Serial.println( "Is an exit" );
		return true;
	}
  Serial.println( "Is not an exit" );
	return false;
}
boolean DistanceSensor::AtWall()
{
	if( IsExit() )
	{
    return false ;
	}
  return true ;
}

