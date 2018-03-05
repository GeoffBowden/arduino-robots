#ifndef StepperForLilly
#define StepperForLilly
#include <arduino.h>

class StepperMotor
{
	private:
		int outPin1=1;
		int outPin2=2;
		int outPin3=3;
		int outPin4=4;
		int currentStep = 0; // 0..7
		void ExecuteStep();
	public:
		StepperMotor( int, int, int, int );
		void MoveForwardsOneStep();
		void MoveBackwardsOneStep();
};

#endif

