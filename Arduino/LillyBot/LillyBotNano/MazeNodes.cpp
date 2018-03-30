#include "MazeNodes.h"
#include "WaggleDance.h"
#include "WallFinder.h"
////////////////////////////////////////////////////////////////
// base node, nuff said
////////////////////////////////////////////////////////////////
BaseNode::BaseNode ( DistanceSensor* useEyes, LillyDrive* useDrive )
{
	this->drive = useDrive;
	this->eyes = useEyes; 
	entrance = Unknown;
}
//////////////////////////////////////////////////////////////////
// root maze node
//////////////////////////////////////////////////////////////////
boolean Maze::SolveMaze()
{
  boolean res = false;
  for( Direction d = North; d <= West; d=NextDirectionClockwise(d) )
  {
    if ( eyes->IsExit() )
    {
      WaggleDance::Yes( drive );
      int distance = WallFinder::MoveToWall( eyes, drive, new MoveToWallKeepingCentred( ) );
      res = SolveNode () ;
      if ( res )
      {
        return res;
      }
      else
      {
        drive->TurnRight90Degrees();          
      }
    }
    else
    {
      WaggleDance::No( drive );
      drive->TurnLeft90Degrees();          
    }
  }
  return res;  
}
boolean Maze::SolveNode () 
{
  Node* node = new Node( eyes, drive);
  boolean res = node -> SolveMaze() ;
  node -> ~Node();
  return res;   
}
//////////////////////////////////////////////////////////////////
boolean Node::SolveMaze()
{
  boolean res = false;
  // solve for left exit
  drive->TurnLeft90Degrees();
  if ( eyes->IsExit() )
  {
    WaggleDance::Yes( drive );
    int distance = WallFinder::MoveToWall( eyes, drive, new MoveToWallKeepingCentred( ) );
    res = SolveNode () ;
    if ( res )
    {
      WaggleDance::Jig(drive);
      return true;
    }
  }
  else
  {
    WaggleDance::No( drive );    
    drive->TurnRight90Degrees();
    drive->TurnRight90Degrees();
  }
  // else solve for right exit
  if ( eyes->IsExit() )
  {
    WaggleDance::Yes( drive );
    if (  SolveNode () )
    {
      WaggleDance::Jig(drive);
      return true;
    }
    else
    {
      drive->TurnLeft90Degrees();
    }
  }
  else
  {
    WaggleDance::No( drive );    
    drive->TurnRight90Degrees();
  }
  // return to the old nod
  WallFinder::MoveToWall( eyes, drive, new MoveToWallKeepingCentred( ) );
}
boolean Node::SolveNode () 
{
  Node* node = new Node( eyes, drive);
  boolean res = node -> SolveMaze() ;
  node -> ~Node();
  return res;   
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// path gets created 
// entrance is a direction, if east path runs east to west 
// distance calculated when Discover is called.
// Path
// Path.Discover
// Path.TravelInReverse
//////////////////////////////////////////////////////////
Path::Path( LillyDrive* useDrive, DistanceSensor* useEyes, Direction entrance, BaseNode* start ):BaseNode(useEyes,useDrive)
{
	this->entrance = entrance;
	this->start = start;
	this->travelled = false;
	this->distanceInCM=0;
  this->foundEndOfMaze = false;
}          
Path::~Path()
{
  if( end != NULL ) 
  { 
    ((MazeNode*)end)->~MazeNode() ; 
  }
}
BaseNode* Path::Discover ()
{
  Serial.println( "discover path" ) ;
  //TODO make move to wall fail, set foundEndOfMaze = true if it does
	this->distanceInCM=WallFinder::MoveToWall( eyes, drive, new MoveToWallKeepingCentred() );
	this->travelled = true;
	// if at end stop
	this->end = new MazeNode( this->drive, this->eyes, this->entrance, this );
	return this->end;
}
boolean Path::HasBeenTravelled(){ return this->travelled; }
boolean Path::HasNotBeenTravelled(){ return !this->HasBeenTravelled() ; }

BaseNode* Path::TravelInReverse()
{
	WallFinder::MoveToWall( this->eyes, this->drive, new MoveToWallKeepingCentred() );
	return this->start;
}

boolean Path::SolveMaze()
{
  Serial.println( "Path.solve maze" );
  if ( foundEndOfMaze )
  {
    return true ;
  }
  else
  {
    ((MazeNode*)(this->end))->DiscoverNode();
    return ((MazeNode*)(this->end))->SolveMaze();
  }
}

//////////////////////////////////////////////////////////
// StartingNode
// StartingNode.DiscoverNode checks for wall, if needed creates a path, 
// does a quarter turn. therefore discovers up to four paths and ends
// facing in the same direction as it started. 
//////////////////////////////////////////////////////////
StartingNode::StartingNode ( LillyDrive* useDrive, DistanceSensor* useEyes ):BaseNode(useEyes, useDrive){ entrance = North;}
StartingNode::~StartingNode ( )
{
  if ( northExit != NULL )
  {
    northExit->~Path();
  }
  if ( eastExit != NULL )
  {
    eastExit->~Path();
  }
  if ( southExit != NULL )
  {
    southExit->~Path();
  }
  if ( westExit != NULL )  
  {
    westExit->~Path();
  }
}
void StartingNode::DiscoverNode()
{
  Serial.println( "Discover starting node" ) ;
	// assume start is northExit-
	if ( eyes->IsExit() )
	{
    Serial.println( "yes north" ) ;
    WaggleDance::Yes(drive);
		northExit = new Path( drive, eyes, North, this );
	}
	else
	{
    Serial.println( "no north" ) ;
    WaggleDance::No(drive);
		northExit = NULL;
	}
	drive->TurnRight90Degrees();
  delay(100);
	if ( eyes->IsExit() )
	{
    Serial.println( "yes east" ) ;
    WaggleDance::Yes(drive);
		eastExit = new Path( drive, eyes, East, this );
	}
	else
	{
    Serial.println( "no east" ) ;
    WaggleDance::No(drive);
		eastExit = NULL;
	}
	drive->TurnRight90Degrees();
  delay(100);
	if ( eyes->IsExit() )
	{
    Serial.println( "yes south" ) ;
    WaggleDance::Yes(drive);
		southExit = new Path( drive, eyes, South, this );
	}
	else
	{
    Serial.println( "no south" ) ;
    WaggleDance::No(drive);
		southExit = NULL;
	}
	drive->TurnRight90Degrees();
  delay(100);
	if ( eyes->IsExit() )
	{
    Serial.println( "yes west" ) ;
    WaggleDance::Yes(drive);
		westExit = new Path( drive, eyes, West, this );
	}
	else
	{
    Serial.println( "no west" ) ;
    WaggleDance::No(drive);
		westExit = NULL;
	}
  delay(100);
	drive->TurnRight90Degrees();
  delay(100);
}
boolean StartingNode::NodeIsComplete()
{
	if( ( northExit == NULL || northExit->HasBeenTravelled() == true )&&
		  ( eastExit == NULL || eastExit->HasBeenTravelled() == true )&&
		  ( southExit == NULL || southExit->HasBeenTravelled() == true )&&
		  ( westExit == NULL || westExit->HasBeenTravelled() == true ) )	
	{
		return true;
	}
	else
	{
		return false;
	}
}
Direction StartingNode::NextDirectionToTry()
{
	if ( northExit != NULL && northExit->HasBeenTravelled() == false )
	{
		return North;
	}
	if ( eastExit != NULL && eastExit->HasBeenTravelled() == false )
	{
		return East;
	}
	if ( southExit != NULL && southExit->HasBeenTravelled() == false )
	{
		return South;
	}
	if ( westExit->HasBeenTravelled() == false )
	{
		return West;
	}
}

// assumes it will be facing north
boolean StartingNode::SolveMaze()
{
  Serial.println( "solve maze" ) ;
  delay(100);
  // TODO make this better
  boolean result = false;
  if ( northExit != NULL && northExit->HasNotBeenTravelled() )
  {
    WaggleDance::Yes(drive);
    Serial.println( "discover north" ) ;
    northExit->Discover();
    Serial.println( "north discovered" ) ;
    Serial.println( "Solve north" ) ;
    result = northExit->SolveMaze();
    Serial.println( "North solved" ) ;
  }
  else
  {    
    WaggleDance::No(drive);
    Serial.println( "skipping north" ) ;
    drive->TurnLeft90Degrees();
    drive->TurnLeft90Degrees();
    Serial.println( "north skipped" ) ;
  }
  // return facing south    Serial.println( "yes north" ) ;
  if ( result ) return result;
  if ( southExit != NULL && southExit->HasNotBeenTravelled() )
  {
    WaggleDance::Yes(drive);
    Serial.println( "discover south" ) ;
    southExit->Discover();
    Serial.println( "south discovered" ) ;
    Serial.println( "solving south" ) ;
    result = southExit->SolveMaze();
    if ( result ) return result;
    Serial.println( "south solved" ) ;
    drive->TurnRight90Degrees();
  }
  else
  {
    WaggleDance::No(drive);
    Serial.println( "skipping south" ) ;
    drive->TurnLeft90Degrees();
    Serial.println( "south skipped" ) ;
  }
  // returns facing east
  if ( eastExit != NULL && eastExit->HasNotBeenTravelled() )
  {
    WaggleDance::Yes(drive);
    Serial.println( "discover east" ) ;
    eastExit->Discover();
    Serial.println( "east discovered" ) ;
    Serial.println( "solving east" ) ;
    result = eastExit->SolveMaze();
    Serial.println( "east solved" ) ;
  }
  else
  {
    WaggleDance::No(drive);
    Serial.println( "Skipping east" ) ;
    drive->TurnLeft90Degrees();
    drive->TurnLeft90Degrees();
    Serial.println( "east skipped" ) ;
  }
  if ( result ) return result;
  if ( westExit != NULL && westExit->HasNotBeenTravelled() )
  {
    WaggleDance::Yes(drive);
    Serial.println( "discover west" ) ;
    westExit->Discover();
    Serial.println( "west discovered" ) ;
    Serial.println( "solving west" ) ;
    result = westExit->SolveMaze();
    Serial.println( "west solved" ) ;
  }
  else
  {
    WaggleDance::No(drive);
    Serial.println( "skipped west" ) ;
  }
  Serial.print( "Result: " ); Serial.println( result );
  return result;
  delay( 2000 );
}
//////////////////////////////////////////////////////////
// Maze mode entrance is the direction to exit. a maze node is always created by a path?
// DiscoverNode
//////////////////////////////////////////////////////////
MazeNode::MazeNode ( LillyDrive* useDrive, DistanceSensor* useEyes, Direction entrance, Path* entrancePath ):BaseNode( useEyes, useDrive )
{ 
	this->entrance = entrance;
  this->entrancePath = entrancePath;
}
MazeNode::~MazeNode()
{
  if ( leftExit != NULL )
  {
    leftExit->~Path();
  }
  if ( rightExit != NULL )
  {
    rightExit->~Path();
  }
}
void MazeNode::DiscoverNode()
{
  Serial.println( "Discover node" ) ;
	Direction right = NextDirectionClockwise( entrance ) ;
	Direction left = NextDirectionAntiClockwise( entrance ) ;
	drive->TurnLeft90Degrees();
  delay(200);
	if ( eyes->IsExit() )
	{
    Serial.println( "yes left" ) ;
    WaggleDance::Yes(drive);
	  leftExit = new Path( drive, eyes, left, this ) ;
	}
	else
	{
    Serial.println( "no left" ) ;
    WaggleDance::No(drive);
	  leftExit = NULL ;	
	}
	drive->TurnLeft90Degrees();
	drive->TurnLeft90Degrees();
  delay(200);
	if ( eyes->IsExit() )
	{
    Serial.println( "yes right" ) ;
    WaggleDance::Yes(drive);
	  rightExit = new Path( drive, eyes, right, this ) ;
	}
	else
	{
    Serial.println( "no right" ) ;
    WaggleDance::No(drive);
	  rightExit = NULL ;	
	}
	drive->TurnLeft90Degrees();
}
boolean MazeNode::NodeIsComplete()
{
	if( ( leftExit == NULL || leftExit->HasBeenTravelled() == true )&&
		  ( rightExit == NULL || rightExit->HasBeenTravelled() == true ) )	
	{
		return true;
	}
	else
	{
		return false;
	}
}
boolean MazeNode::SolveMaze()
{
  boolean foundExit = false ;
  // tries to solve left path
  if ( leftExit != NULL && leftExit->HasNotBeenTravelled() )
  {
    Serial.println( "Off to discover left path" ); 
    drive->TurnLeft90Degrees();
    leftExit->Discover();
    Serial.println( "discovered left path" ); 
    Serial.println( "solve left path" ); 
    foundExit = leftExit->SolveMaze();
    Serial.println( "left path solved" ); 
  }
  else
  {
    drive->TurnRight90Degrees();
  }
  // when returns will be facing west path
  if ( foundExit == false )
  {
    if ( rightExit != NULL && rightExit->HasNotBeenTravelled() )
    {
      Serial.println( "Off to discover right path" ); 
      rightExit->Discover();
      Serial.println( "discovered right path" ); 
      Serial.println( "solve right path" ); 
      foundExit = rightExit->SolveMaze();
      // will return facing left so will need one more left turn to face entrance point
      Serial.println( "Right path solved" ); 
      drive->TurnLeft90Degrees();
    }
    else
    {
      Serial.println( "No right exit, turning to face entrance" ) ;
      // here will be facing right and therefore need one more right turn to face entrance
      drive->TurnRight90Degrees();
    }
  }
  // else recover exit
  if ( foundExit )
  {
    return true;
  }
  else
  {
    entrancePath->TravelInReverse();
    return false ;
  }
}
boolean  MazeNode::ContinueSolving ( boolean result )
{
  return result == false ;
}
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
Direction NextDirectionClockwise( Direction direction )
{
	switch ( direction ){
		case Unknown : return Unknown;
		break;
		case North : return East ;
		break;
		case East  : return South;
		break;
		case South : return West;
		break;
		case West  : return North ;
		break;
	}
}
Direction NextDirectionAntiClockwise( Direction direction )
{
	switch ( direction ){
		case Unknown : return Unknown;
		break;
		case North : return West ;
		break;
		case East  : return North;
		break;
		case South : return East;
		break;
		case West  : return South ;
		break;
	}
}

Direction OppositeDirection( Direction direction )
{
	switch ( direction ){
		case Unknown : return Unknown;
		break;
		case North : return South ;
		break;
		case East  : return West;
		break;
		case South : return North;
		break;
		case West  : return East ;
		break;
	}
}

