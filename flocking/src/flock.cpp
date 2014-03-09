/************************************************)********************
* @file flock.cpp
* @author Erik Larsson
* @version 1.0
* @section DESCRIPTION
*  
*********************************************************************/

#include "flock.h"

Flock::Flock()
{
}

void Flock::add(Bird *b)
{
	mBirds.push_back(b);
}

void Flock::update(double dt)
{
	std::vector<Bird*>::iterator iter;
	for(iter=mBirds.begin(); iter!=mBirds.end(); iter++)
	{
		std::vector<Bird*> neighbours;
		std::vector<Bird*>::iterator second;
		for(second=mBirds.begin(); second!=mBirds.end(); second++)
		{
			vec2 dist = vec2((*iter)->getPosition()-(*second)->getPosition());
			float distance = glm::length(dist);
			if( distance < NEIGHBOUR_RADIUS && distance > 0)
			{
				neighbours.push_back((*second));
			}
		}
		vec2 velocity = (*iter)->separate(neighbours)*(float)SEPARATION_WEIGHT; 
		velocity += (*iter)->aligment(neighbours)*(float)ALIGMENT_WEIGHT;
		velocity += (*iter)->cohesion(neighbours)*(float)COHESION_WEIGHT;
		
		velocity *= MAX_SPEED;
		(*iter)->update(dt, velocity);
	}
}
