

#ifndef DistanceSensorClass
#define DistanceSensorClass
#include "Arduino.h"


#define READING_COUNT 10

class DistanceSensor
{
	private:
    const int range = 15;
		int triggerPin;
		int sensorPin;
		void PrimeSensor();
		void SetSensorPin();
		void SetTriggerPin();
		long ReadDuration();
	public:
		DistanceSensor(int , int );
	  long ReadDistanceInMM();
    long ReadModalDistanceInMM();
	  long ReadDistanceInCM();
    long ReadAverageDistanceInCM();
    long ReadSlowAverageDistanceInCM();
    long ReadAverageFromModalDistanceInCM();
    long ReadModalDistanceInCM();
    boolean IsExit();
		boolean AtWall();
		
};

#endif 

