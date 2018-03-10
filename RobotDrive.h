#ifndef LillyBotDrive
#define LillyBotDrive
#include <Arduino.h>
#include "StepperForLilly.h"
#include "WaggleDriver.h"

class LillyDrive : public WaggleDriver
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
    void Backwards( int steps );
    void BackwardsQuarterTurn(); // 4.25 cm
    void BackwardsOneMM();
	
	// from WaggleDriver
	void SmallGestureLeft();
	void SmallGestureRight();
	void SmallGestureForward();
	void SmallGestureBackward();
	void GestureLeft();
	void GestureRight();
	void GestureForward();
	void GestureBackward();
	
};

#endif

