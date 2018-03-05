#ifndef LillyBotDrive
#define LillyBotDrive
#include <Arduino.h>
#include "StepperForLilly.h"
#include "DistanceSensor.h"
class LillyDrive
{
	private:
		const int maxSteps = 4096;
    const int speedDelay = 1200;
		StepperMotor * leftMotor;
		StepperMotor * rightMotor;
		void Forwards( int steps );
		void doDelay( long startMicros, long endMicros ) ;
	public:
		LillyDrive();
		void ForwardsOneTurn();     //17.00 cm 
		void ForwardsHalfTurn();    // 8.50 cm
    void ForwardsQuarterTurn(); // 4.25 cm
		void TurnLeft90Degrees();
    void TurnRight90Degrees();
    void TurnLeft01Degree();
    void TurnRight01Degree();
    void TestLeftMotor();
    void TestRightMotor();
    void ForwardsOneMM();
		int MoveToWall( DistanceSensor* eyes );
    void Backwards( int steps );
    void BackwardsQuarterTurn(); // 4.25 cm
    void BackwardsOneMM();
    void WaggleDanceYes();
    void WaggleDanceNo();
};

#endif

