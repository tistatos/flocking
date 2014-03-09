#ifndef __birdGeometry_h__
#define __birdGeometry_h__
/********************************************************************
* @file birdGeometry.h
* @author Erik Larsson
* @version 1.0
* @section DESCRIPTION
*  
*********************************************************************/

#include "geometry.h"

class BirdGeometry : public Geometry
{
public:
	BirdGeometry();
private:
	std::vector<glm::vec2> createBird();
};

#endif // __birdGeometry_h__
