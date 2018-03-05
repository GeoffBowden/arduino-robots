#ifndef ROBOT_MATHS
#define ROBOT_MATHS

#define READING_COUNT 10

class MathsFunctions
{
  public:
    static long GetModal(long readings[READING_COUNT]);	
    static int GetCountOfXInArrayFromIndex( long x, long theArray[READING_COUNT], long index );
}	;



#endif

