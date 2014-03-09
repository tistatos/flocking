#ifndef __bird_h__
#define __bird_h__
/********************************************************************
* @file bird.h
* @author Erik Larsson
* @version 1.0
* @section DESCRIPTION
*  Flocking Demo - bird with boid flocking
*********************************************************************/

#include "shape.h"
//Weights for behaviour
#define SEPARATION_WEIGHT 0.11 
#define ALIGMENT_WEIGHT 1
#define COHESION_WEIGHT 1

//radii for neighbours
#define NEIGHBOUR_RADIUS .6
#define DESIRED_SEPARATION 0.03

#define MAX_SPEED 0.004

using namespace glm;

class Bird
{
public:

	Bird(Shape* s);
	void update(double dt, glm::vec2 velocity);

	glm::vec2 getPosition();
	glm::vec2 getForward();
	glm::vec2 getVelocity();

	void addVelocity();

	vec2 separate(std::vector<Bird*> neighbours);
	vec2 aligment(std::vector<Bird*> neighbours);
	vec2 cohesion(std::vector<Bird*> neighbours);

private:
	Shape *mShape;
	vec2 mVelocity;
};
#endif // __bird_h__