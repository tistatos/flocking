#ifndef __flock_h__
#define __flock_h__

/********************************************************************
* @file flock.h
* @author Erik Larsson
* @version 1.0
* @section DESCRIPTION
*  Flocking demo - the entire flock
*********************************************************************/
#include "bird.h"
#include <glm.hpp>
#include <vector>
#include "engineUtils.h"

using namespace glm;

class Flock
{
public:
	Flock();
	void add(Bird *b);
	void update(double dt);


private:
	std::vector<Bird*> mBirds;

};

#endif // __flock_h__
