/********************************************************************
* @file bird.cpp
* @author Erik Larsson
* @version 1.0
* @section DESCRIPTION
*  
*********************************************************************/

#include "bird.h"
#include "engineUtils.h"
Bird::Bird(Shape* s)
{
	mShape = s;
	//Calculate random velocity
	mVelocity = glm::vec2((getRand())*MAX_SPEED,(getRand())*MAX_SPEED);
	addVelocity();

}

void Bird::update(double dt, glm::vec2 velocity)
{
	mVelocity += velocity;
	if(length(mVelocity) > MAX_SPEED)
	{
		mVelocity = normalize(mVelocity)*(float)MAX_SPEED;
	}
	addVelocity();
	vec2 pos = getPosition();
	if(pos.y > 5.0f)
	{
		mVelocity.y = -mVelocity.y;
	}
	else if(pos.y < -5.0f)
	{
		mVelocity.y = -mVelocity.y;
	}
	if(pos.x > 5.0f)
	{
		mVelocity.x = -mVelocity.x;
	}
	else if(pos.x < -5.0f)
	{
		mVelocity.x = -mVelocity.x;
	}
}

glm::vec2 Bird::getPosition()
{
	glm::mat4 matrix = mShape->getModelMatrix();
	return glm::vec2(matrix[3].x, matrix[3].y);
}

glm::vec2 Bird::getForward()
{
	glm::mat4 matrix = mShape->getModelMatrix();
	return glm::vec2(matrix[1].x, matrix[1].y);

}

void Bird::addVelocity()
{
	//rotate bird to face velocity
	vec2 fwd = getForward();
	fwd /= length(fwd);
	if(length(mVelocity) >0)
	{
		vec2 velo = mVelocity/length(mVelocity);
		float dotprod = dot(fwd,velo);
		vec3 crossprod = cross(vec3(fwd,1),vec3(velo,1));
		if(crossprod.z <0)
		{
			crossprod.z = -1;
		}
		else
		{
			crossprod.z = 1;
		}
		mShape->rotateZ((1-dotprod)*90*crossprod.z);
		//add velocity to position
		mShape->translate(glm::vec3(0,length(mVelocity),0));
	}



}


vec2 Bird::cohesion(std::vector<Bird*> neighbours)
{
	vec2 sum = vec2(0,0);
	int count = 0;
	vec2 myPos = getPosition();
	std::vector<Bird*>::iterator iter;
	for(iter=neighbours.begin(); iter!=neighbours.end(); iter++)
	{
		sum = (*iter)->getPosition();
		count ++;
	}
	
	if(count > 0)
	{
		sum /= (float)count;
		vec2 desired = myPos-sum;

		float d = length(desired);
		if(d > 0.0f)
		{
			desired /= d;
			if(d < 0.3f)
			{
				desired *=(float)MAX_SPEED*(d/0.3f);

			}
			else
			{
				desired *=(float)MAX_SPEED;
			}
			return desired-mVelocity;
		}
		else
		{
			return vec2(0,0);
		}
	}
	else
	{
		return vec2(0,0);
	}
}

vec2 Bird::aligment(std::vector<Bird*> neighbours)
{
	vec2 mean(0,0);
	int count = 0;

	std::vector<Bird*>::iterator iter;
	for(iter=neighbours.begin(); iter!=neighbours.end(); iter++)
	{
		mean += (*iter)->getVelocity();
		count ++;
	}
	if(count)
	{
		mean /= (float)count;
	}

	return mean;
}

vec2 Bird::separate(std::vector<Bird*> neighbours)
{
	vec2 mean(0,0);
	vec2 myPos = getPosition();

	int count = 0;

	std::vector<Bird*>::iterator iter;
	for(iter=neighbours.begin(); iter!=neighbours.end(); iter++)
	{
		vec2 neighbourPos = (*iter)->getPosition();
		vec2 distance = myPos-neighbourPos;
		if(length(distance) < DESIRED_SEPARATION)
		{
			mean += distance/length(distance);
			count ++;
		}
	}
	if(count)
	{
		mean /= (float)count;
	}
	return mean;
}

vec2 Bird::getVelocity()
{
	return mVelocity;
}