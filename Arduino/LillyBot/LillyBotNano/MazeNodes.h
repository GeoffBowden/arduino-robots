#ifndef NODETYPESOFMAZE
#define NODETYPESOFMAZE
#include "RobotDrive.h"
#include "DistanceSensor.h"


enum Direction { Unknown, North, East, South, West };
Direction NextDirectionClockwise( Direction direction );
Direction NextDirectionAntiClockwise( Direction direction );
Direction OppositeDirection( Direction direction );

class BaseNode
{
	protected:
		LillyDrive* drive;
		DistanceSensor* eyes;
		Direction entrance ;
	public:
	  BaseNode ( DistanceSensor*, LillyDrive* );
    virtual boolean SolveMaze() = 0;
};


class Maze:public BaseNode
{
  private:
    boolean SolveNode () ;
  public:
    Maze ( DistanceSensor* eyes, LillyDrive* drive ):BaseNode ( eyes, drive ){}
    boolean SolveMaze();
};

class Node:public BaseNode
{
  private:
    boolean SolveNode () ;
  public :
    Node ( DistanceSensor* eyes, LillyDrive* drive ):BaseNode ( eyes, drive ){}
    boolean SolveMaze();
};

class Path:public BaseNode
{
	private:
		int distanceInCM;
		BaseNode* start;
		BaseNode* end;
		boolean travelled;
    boolean foundEndOfMaze;
	public:
		Path( LillyDrive* useDrive, DistanceSensor* useEyes, Direction entrance, BaseNode* start  );
    ~Path();
		BaseNode* Discover ();
		boolean HasBeenTravelled();
    boolean HasNotBeenTravelled();
		BaseNode* TravelInReverse();
    boolean SolveMaze(); 
};

class StartingNode:public BaseNode
{
	private:
		Path* northExit;
		Path* southExit;
		Path* eastExit;
		Path* westExit;
	public:
		StartingNode ( LillyDrive* , DistanceSensor* );//
    ~StartingNode ( );//
		void DiscoverNode();//
		boolean NodeIsComplete();//
		Direction NextDirectionToTry();//
    boolean SolveMaze(); 
};

class MazeNode:public BaseNode
{
	private:
		Path* leftExit;
		Path* rightExit;
    Path* entrancePath;
    boolean ContinueSolving ( boolean result );
	public:
		MazeNode( LillyDrive* , DistanceSensor*, Direction, Path* );
    ~MazeNode ( );
    void DiscoverNode();//
		boolean NodeIsComplete();//
    boolean SolveMaze(); 
};

#endif 


