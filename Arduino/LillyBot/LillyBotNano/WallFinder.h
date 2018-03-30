#ifndef WALL_FINDER
#define WALL_FINDER
#include "DistanceSensor.h"
#include "RobotDrive.h"
#include <String.h>

#define DIAMETER_OF_WHEEL_IN_MM 170

enum Handedness 
{
	Left   = 01,
	Centre = 02,
	Right  = 03
};

class MoveToWallAlgorithm
{
  public:
    virtual int MoveToWall( DistanceSensor* eyes, LillyDrive* drive ) = 0;
    int GetDistanceToWallInCMSlightlyAdjustingPosition( DistanceSensor* eyes, LillyDrive* drive );
};


class WallFinder
{
  public:
    // returns distance in cm
    static int MoveToWall( DistanceSensor* eyes, LillyDrive* drive, MoveToWallAlgorithm* Algorithm );
	private:
		WallFinder();
};

class MoveToWallWithoutNearMeasurements:public MoveToWallAlgorithm
{
  public: int MoveToWall( DistanceSensor* eyes, LillyDrive* drive );
};

class MoveToWallSimple:public MoveToWallAlgorithm
{
  public: int MoveToWall( DistanceSensor* eyes, LillyDrive* drive );
};

class MoveToWallKeepingCentred:public MoveToWallAlgorithm 
{
  public: 
    int MoveToWall( DistanceSensor* eyes, LillyDrive* drive );
  private: 
    void CentreInPath( DistanceSensor* eyes, LillyDrive* drive );
    int GetDistanceToTravelCM ( DistanceSensor* eyes );
};


    
    


#endif




