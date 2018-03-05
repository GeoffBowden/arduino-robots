#ifndef WAGGLE_DANCE
#define WAGGLE_DANCE

#include "RobotDrive.h"

class WaggleDance
{
  private:
    WaggleDance(){};
  public:
	  static void Yes( LillyDrive* drive );
	  static void No ( LillyDrive* drive );
    static void Jig( LillyDrive* drive );
    static void JigLeft( LillyDrive* drive );
    static void JigLeftXtimes( LillyDrive* drive, int xTimes );
    static void JigRight( LillyDrive* drive );
    static void JigRightXtimes( LillyDrive* drive, int xTimes );
};

#endif
