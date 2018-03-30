#ifndef WAGGLE_DANCE
#define WAGGLE_DANCE

#include "RobotDrive.h"
#include "WaggleDriver.h"

class WaggleDance
{
  private:
    WaggleDance(){};
    static void ShowDigit( WaggleDriver* drive, int Digit );
  public:
	  static void Yes( WaggleDriver* drive );
	  static void No ( WaggleDriver* drive );
    static void Jig( WaggleDriver* drive );
    static void JigLeft( WaggleDriver* drive );
    static void JigLeftXtimes( WaggleDriver* drive, int xTimes );
    static void JigRight( WaggleDriver* drive );
    static void JigRightXtimes( WaggleDriver* drive, int xTimes );
    static void ShowNumber( WaggleDriver* drive, int Number );
};

#endif
