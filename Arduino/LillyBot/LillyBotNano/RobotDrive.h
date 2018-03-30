#ifndef LillyBotDrive
#define LillyBotDrive
#include <Arduino.h>
#include "StepperForLilly.h"
#include "WaggleDriver.h"

class LillyDrive : public WaggleDriver
{
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
    void ForwardsXMMs(int X);
    void Backwards( int steps );
    void BackwardsQuarterTurn(); // 4.25 cm
    void BackwardsOneMM();
    void BackwardsXMMs(int X);
    // from WaggleDriver
    void SmallGestureLeft();
    void SmallGestureRight();
    void SmallGestureForward();
    void SmallGestureBackward();
    void GestureLeft();
    void GestureRight();
    void GestureForward();
    void GestureBackward();

	private:
		const int maxSteps = 4096;
    const int speedDelay = 1200;
		StepperMotor * leftMotor;
		StepperMotor * rightMotor;
		void Forwards( int steps );
		void doDelay( long startMicros, long endMicros ) ;	
};

#endif

