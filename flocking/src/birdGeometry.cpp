/********************************************************************
* @file birdGeometry.cpp
* @author Erik Larsson
* @version 1.0
* @section DESCRIPTION
*  Geometry for birds
*********************************************************************/

#include "birdGeometry.h"

BirdGeometry::BirdGeometry() : Geometry(createBird()) {}

std::vector<glm::vec2> BirdGeometry::createBird()
{
	std::vector<glm::vec2> vec;
	vec.push_back(glm::vec2(0.0f,0.0f));
	vec.push_back(glm::vec2(.05f,-.05f));
	vec.push_back(glm::vec2(0.0f,0.1f));
	vec.push_back(glm::vec2(-0.05f,-0.05f));
	return vec;

}