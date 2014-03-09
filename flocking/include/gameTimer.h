#ifndef __gameTimer_h__
#define __gameTimer_h__
/********************************************************************
* @file gameTimer.h
* @author Erik Larsson
* @version 1.0
* @section DESCRIPTION
*  
*********************************************************************/

#include "engineUtils.h"

class GameTimer
{
public:
	GameTimer();
	void tick();
	const float getDeltaTime();
	const float getFPS();
private:
	double mPrevious;
	double mCurrent;
	double mDeltaTime;
	double mFPS;
	double mFPSCount;
	int mFrames;
};


#endif // __gameTimer_h__
