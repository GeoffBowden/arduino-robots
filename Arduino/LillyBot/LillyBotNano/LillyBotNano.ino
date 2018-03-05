#include "RobotDrive.h"
#include "DistanceSensor.h"
#include "MazeNodes.h"
#include "RobotMaths.h"
#include "WaggleDance.h"

LillyDrive *drive ;
DistanceSensor *distanceSensor; // ( 4, 3 );


void setup() 
{
  Serial.begin(9600);
  drive = new LillyDrive();
  distanceSensor = new DistanceSensor( 4, 3 ) ;
}

void loop() 
{
//  ArrayTest();
//  MathsTest();
//  ExitCheck();
//  DistanceCheck();
//  TestWallFinding();
//  TestCircling();
//  TestNodeDiscovery();
  SolveMaze();
}

void SolveMaze()
{
  delay( 1000 ) ;  
  StartingNode* maze = new StartingNode(drive, distanceSensor);
  maze->DiscoverNode();
  maze->SolveMaze();
  maze->~StartingNode();
  delay( 1000 ) ;
  WaggleDance::Jig(drive);  
  delay( 2000 ) ;
}


void ArrayTest()
{
  Serial.println( "10, 5, 3, 0, 1, 0, 9, 1, 1, 10" );
  long readings2[10] = { 10, 5, 3, 0, 1, 0, 9, 1, 1, 10 };
  int count = 0;
  count = MathsFunctions::GetCountOfXInArrayFromIndex( 10, readings2, 5 );
  Serial.print( "count of 10 from readings from index 5 expected count 1 gives count = " ); Serial.println( count ) ;
  count = MathsFunctions::GetCountOfXInArrayFromIndex( 10, readings2, 0 );
  Serial.print( "count of 10 from readings from index 0 expected count 2 gives count = " ); Serial.println( count ) ;
  count = MathsFunctions::GetCountOfXInArrayFromIndex( 1, readings2, 4 );
  Serial.print( "count of 1 from readings from index 4 expected count 3 gives count = " ); Serial.println( count ) ;
  count = MathsFunctions::GetCountOfXInArrayFromIndex( 1, readings2, 5 );
  Serial.print( "count of 1 from readings from index 5 expected count 2 gives count = " ); Serial.println( count ) ;
}
void MathsTest()
{
  Serial.println( "___________________________________________________________");
  Serial.println( "{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 }" );
  long readings1[10] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
  long modal = MathsFunctions::GetModal( readings1 ) ;
  Serial.print( "TEST 1 Expected: 10 Actual: " ) + Serial.println( modal ) ;
  Serial.println( "___________________________________________________________");
  Serial.println( "{ 10, 5, 3, 0, 1, 0, 9, 1, 1, 10 }" );
  long readings2[10] = { 10, 5, 3, 0, 1, 0, 9, 1, 1, 10 };
  modal = MathsFunctions::GetModal( readings2 ) ;
  Serial.print( "TEST 2 Expected: 1 Actual: " ) + Serial.println( modal ) ;
  Serial.println( "___________________________________________________________");
  Serial.println( "{ 9, 5, 3, 0, 1, 0, 9, 1, 1, 9 }" );
  long readings3[10] = { 9, 5, 3, 0, 1, 0, 9, 1, 1, 9 };
  modal = MathsFunctions::GetModal( readings3 ) ;
  Serial.print( "TEST 3 Expected: 5 Actual: " ) + Serial.println( modal ) ;
  Serial.println( "___________________________________________________________");
  Serial.println( "{ 10, 5, 3, 0, 1, 0, 10, 1, 1, 10 }" );
  long readings4[10] = { 10, 5, 3, 0, 1, 0, 10, 1, 1, 10 };
  modal = MathsFunctions::GetModal( readings4 ) ;
  Serial.print( "TEST 4 Expected: 5 Actual: " ) + Serial.println( modal ) ;
  Serial.println( "___________________________________________________________");
  Serial.println( "{ 10, 11, 9, 9, 11, 0, 10, 11, 9, 10 }" );
  long readings5[10] = { 10, 11, 9, 9, 11, 0, 10, 11, 9, 10 };
  modal = MathsFunctions::GetModal( readings5 ) ;
  Serial.print( "TEST 5 Expected: 10 Actual: " ) + Serial.println( modal ) ;
  Serial.println( "___________________________________________________________");
  delay(10000) ;
}

void ExitCheck()
{
  if ( distanceSensor->IsExit() )
  {
    WaggleDance::Yes(drive);
  }
  else
  {
    WaggleDance::No(drive);
  }
  delay( 3000 );  
}

void DistanceCheck()
{
  int cm = distanceSensor->ReadDistanceInCM();
  Serial.println( cm );
  delay( 500 );  
}

void TestNodeDiscovery()
{
  MazeNode* node = new MazeNode( drive, distanceSensor, North, NULL ) ;
  node->DiscoverNode();
}

void TestWallFinding()
{
  delay( 1000 );
  drive->MoveToWall( distanceSensor );
  drive->TurnLeft90Degrees();
  delay( 1000 );
  drive->TurnLeft90Degrees();
  drive->MoveToWall( distanceSensor );
}

void TestCircling()
{
  Serial.println( "Test back and forth" );
  for( int i = 1; i <= 3; i++ )
  {
    TurnLeft();
    TurnRight();
  }
  Serial.println( "Test left turn" );
  for( int i = 1; i <= 5; i++ )
  {
    TurnLeft();
  }
}
void TurnLeft()
{
    Serial.println( "Turning left" );
    drive->TurnLeft90Degrees();
    delay( 200 );
    drive->TurnLeft90Degrees();
    delay( 200 );
    drive->TurnLeft90Degrees();
    delay( 200 );
    drive->TurnLeft90Degrees();
    delay( 1500 );
}
void TurnRight()
{
    Serial.println( "Turning Right" );
    drive->TurnRight90Degrees();
    delay( 200 );
    drive->TurnRight90Degrees();
    delay( 200 );
    drive->TurnRight90Degrees();
    delay( 200 );
    drive->TurnRight90Degrees();
    delay( 1500 );
}


