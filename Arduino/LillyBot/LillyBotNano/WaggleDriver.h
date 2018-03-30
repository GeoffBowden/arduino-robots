#ifndef WAGGLE_DRIVER
#define WAGGLE_DRIVER

class WaggleDriver
{
	public:
		~WaggleDriver(){};
		virtual void SmallGestureLeft()=0;
		virtual void SmallGestureRight()=0;
		virtual void SmallGestureForward()=0;
		virtual void SmallGestureBackward()=0;
		virtual void GestureLeft()=0;
		virtual void GestureRight()=0;
		virtual void GestureForward()=0;
		virtual void GestureBackward()=0;
};

#endif



