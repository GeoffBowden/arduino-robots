

#define LM1 8
#define LM2 7
#define LM3 6
#define LM4 5

#define RM1 A4
#define RM2 A3
#define RM3 A2
#define RM4 A1

int steps = 0;
boolean heading = true; 
unsigned long lastTime;
unsigned long currentMillis;
const int steps_max = 4095;
int stepsLeft = steps_max;
long timeTaken;

void setup() {
  // put your setup code here, to run once:
  Serial.begin( 9600 );
  pinMode ( LM1, OUTPUT );
  pinMode ( LM2, OUTPUT );
  pinMode ( LM3, OUTPUT );
  pinMode ( LM4, OUTPUT );

  pinMode ( RM1, OUTPUT );
  pinMode ( RM2, OUTPUT );
  pinMode ( RM3, OUTPUT );
  pinMode ( RM4, OUTPUT );

}

void loop() {
  // put your main code here, to run repeatedly:
  while(stepsLeft>0)
  {
    currentMillis = micros();
    if (currentMillis < lastTime ) { lastTime = currentMillis; } 
    if(currentMillis-lastTime>=1500)
    {
      stepper(1);
      timeTaken = timeTaken+currentMillis-lastTime;
      lastTime = micros(); //currentMillis;
      stepsLeft--;
    }
  }
  Serial.println(timeTaken);
  Serial.println("Wait...");
  delay(200);
  stepsLeft = steps_max;
}


void stepper(int xw)
{
  for(int x=0;x<xw;x++)
  {
    switch(steps)
    {
      case 0:
        digitalWrite(LM1, LOW);
        digitalWrite(LM2, LOW);
        digitalWrite(LM3, LOW);
        digitalWrite(LM4, HIGH);
        //////////////////////////////
        digitalWrite(RM1, LOW);
        digitalWrite(RM2, LOW);
        digitalWrite(RM3, LOW);
        digitalWrite(RM4, HIGH);
       
       break;
      case 1:
        digitalWrite(LM1, LOW);
        digitalWrite(LM2, LOW);
        digitalWrite(LM3, HIGH);
        digitalWrite(LM4, HIGH);
        //////////////////////////////
        digitalWrite(RM1, LOW);
        digitalWrite(RM2, LOW);
        digitalWrite(RM3, HIGH);
        digitalWrite(RM4, HIGH);
       break;
      case 2:
        digitalWrite(LM1, LOW);
        digitalWrite(LM2, LOW);
        digitalWrite(LM3, HIGH);
        digitalWrite(LM4, LOW);
        //////////////////////////////
        digitalWrite(RM1, LOW);
        digitalWrite(RM2, LOW);
        digitalWrite(RM3, HIGH);
        digitalWrite(RM4, LOW);
       break;
      case 3:
        digitalWrite(LM1, LOW);
        digitalWrite(LM2, HIGH);
        digitalWrite(LM3, HIGH);
        digitalWrite(LM4, LOW);
        //////////////////////////////
        digitalWrite(RM1, LOW);
        digitalWrite(RM2, HIGH);
        digitalWrite(RM3, HIGH);
        digitalWrite(RM4, LOW);
       break;
      case 4:
        digitalWrite(LM1, LOW);
        digitalWrite(LM2, HIGH);
        digitalWrite(LM3, LOW);
        digitalWrite(LM4, LOW);
        //////////////////////////////
        digitalWrite(RM1, LOW);
        digitalWrite(RM2, HIGH);
        digitalWrite(RM3, LOW);
        digitalWrite(RM4, LOW);
       break;
      case 5:
        digitalWrite(LM1, HIGH);
        digitalWrite(LM2, HIGH);
        digitalWrite(LM3, LOW);
        digitalWrite(LM4, LOW);
        //////////////////////////////
        digitalWrite(RM1, HIGH);
        digitalWrite(RM2, HIGH);
        digitalWrite(RM3, LOW);
        digitalWrite(RM4, LOW);
       break;
      case 6:
        digitalWrite(LM1, HIGH);
        digitalWrite(LM2, LOW);
        digitalWrite(LM3, LOW);
        digitalWrite(LM4, LOW);
        //////////////////////////////
        digitalWrite(RM1, HIGH);
        digitalWrite(RM2, LOW);
        digitalWrite(RM3, LOW);
        digitalWrite(RM4, LOW);
       break;
      case 7:
        digitalWrite(LM1, HIGH);
        digitalWrite(LM2, LOW);
        digitalWrite(LM3, LOW);
        digitalWrite(LM4, HIGH);
        //////////////////////////////
        digitalWrite(RM1, HIGH);
        digitalWrite(RM2, LOW);
        digitalWrite(RM3, LOW);
        digitalWrite(RM4, HIGH);
       break;
      default:
        digitalWrite(LM1, LOW);
        digitalWrite(LM2, LOW);
        digitalWrite(LM3, LOW);
        digitalWrite(LM4, LOW);
        //////////////////////////////
        digitalWrite(RM1, LOW);
        digitalWrite(RM2, LOW);
        digitalWrite(RM3, LOW);
        digitalWrite(RM4, LOW);
       break;
    }
    moveToNextStep();
    //delay(10);
  }
}
void moveToNextStep()
{
  //if(heading==1){steps++;}else{steps--;}
  steps = (heading==1)?steps+1:steps-1;
  if(steps>7){steps=0;}
  if(steps<0){steps=7;}
}

