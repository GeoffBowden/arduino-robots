#include "StepperForLilly.h"

////////////////////////////////////////////////////////////////

StepperMotor::StepperMotor(int pin1, int pin2, int pin3, int pin4 )
{
	this->outPin1 = pin1;
	this->outPin2 = pin2;
	this->outPin3 = pin3;
	this->outPin4 = pin4;
	pinMode(this->outPin1, OUTPUT);
	pinMode(this->outPin2, OUTPUT);
	pinMode(this->outPin3, OUTPUT);
	pinMode(this->outPin4, OUTPUT);
}

void StepperMotor::MoveForwardsOneStep()
{
  //Serial.println(this->currentStep);
	ExecuteStep();
	this->currentStep++;
	if ( this->currentStep > 7 ) { this->currentStep=0 ; }
}

void StepperMotor::MoveBackwardsOneStep()
{
  this->currentStep--;
  if ( this->currentStep < 0 ) { this->currentStep=7 ; }
	ExecuteStep();
}

void StepperMotor::ExecuteStep()
{
    switch(currentStep)
    {
      case 0:
        digitalWrite(this->outPin1, LOW);
        digitalWrite(this->outPin2, LOW);
        digitalWrite(this->outPin3, LOW);
        digitalWrite(this->outPin4, HIGH);
       break;
      case 1:
        digitalWrite(this->outPin1, LOW);
        digitalWrite(this->outPin2, LOW);
        digitalWrite(this->outPin3, HIGH);
        digitalWrite(this->outPin4, HIGH);
       break;
      case 2:
        digitalWrite(this->outPin1, LOW);
        digitalWrite(this->outPin2, LOW);
        digitalWrite(this->outPin3, HIGH);
        digitalWrite(this->outPin4, LOW);
       break;
      case 3:
        digitalWrite(this->outPin1, LOW);
        digitalWrite(this->outPin2, HIGH);
        digitalWrite(this->outPin3, HIGH);
        digitalWrite(this->outPin4, LOW);
       break;
      case 4:
        digitalWrite(this->outPin1, LOW);
        digitalWrite(this->outPin2, HIGH);
        digitalWrite(this->outPin3, LOW);
        digitalWrite(this->outPin4, LOW);
       break;
      case 5:
        digitalWrite(this->outPin1, HIGH);
        digitalWrite(this->outPin2, HIGH);
        digitalWrite(this->outPin3, LOW);
        digitalWrite(this->outPin4, LOW);
       break;
      case 6:
        digitalWrite(this->outPin1, HIGH);
        digitalWrite(this->outPin2, LOW);
        digitalWrite(this->outPin3, LOW);
        digitalWrite(this->outPin4, LOW);
       break;
      case 7:
        digitalWrite(this->outPin1, HIGH);
        digitalWrite(this->outPin2, LOW);
        digitalWrite(this->outPin3, LOW);
        digitalWrite(this->outPin4, HIGH);
       break;
      default:
        digitalWrite(this->outPin1, LOW);
        digitalWrite(this->outPin2, LOW);
        digitalWrite(this->outPin3, LOW);
        digitalWrite(this->outPin4, LOW);
       break;
    }	
}


