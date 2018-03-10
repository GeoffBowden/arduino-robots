#ifndef WALL_FINDER
#define WALL_FINDER
#include "DistanceSensor.h"
#include "RobotDrive.h"

enum Handedness 
{
	Left   = 01,
	Centre = 02,
	Right  = 03
};

class WallFinder
{
	private:
		WallFinder();
		static int GetDistanceToWallSlightlyAdjustingPosition( DistanceSensor* eyes, LillyDrive* drive ); 
	public:
		static int MoveToWall( DistanceSensor* eyes, LillyDrive* drive );
};



#endif




