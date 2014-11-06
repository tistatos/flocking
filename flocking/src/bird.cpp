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

	glm::mat4 mMatrix = mShape->getModelMatrix();
	mMatrix[3].x = -5.0f + 2*5.0f*getRand();
	mMatrix[3].y = -5.0f + 2*5.0f*getRand();

	mShape->setModelMatrix(mMatrix);


}

void Bird::update(double dt, glm::vec2 velocity)
{
	mVelocity += velocity;
	if(glm::length(mVelocity) > MAX_SPEED)
	{
		mVelocity = glm::normalize(mVelocity)*(float)MAX_SPEED;
	}
	addVelocity();
	glm::vec2 pos = getPosition();
	if(pos.y > 5.0f)
	{
		pos.y = -5.0f;
	}
	else if(pos.y < -5.0f)
	{
		pos.y = 5.0f;
	}
	if(pos.x > 5.0f)
	{
		pos.x = -5.0f;
	}
	else if(pos.x < -5.0f)
	{
		pos.x = 5.0f;
	}

	glm::mat4 mMatrix = mShape->getModelMatrix();
	mMatrix[3].x = pos.x;
	mMatrix[3].y = pos.y;

	mShape->setModelMatrix(mMatrix);
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
	glm::vec2 fwd = getForward();
	fwd /= glm::length(fwd);
	if(glm::length(mVelocity) >0)
	{
		glm::vec2 velo = mVelocity/glm::length(mVelocity);
		float dotprod = glm::dot(fwd,velo);
		glm::vec3 crossprod = glm::cross(glm::vec3(fwd,1),glm::vec3(velo,1));
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
		mShape->translate(glm::vec3(0,glm::length(mVelocity),0));
	}



}


glm::vec2 Bird::cohesion(std::vector<Bird*> neighbours)
{
	int count = 0;
	glm::vec2 myPos = getPosition();
	glm::vec2 sum = myPos;
	std::vector<Bird*>::iterator iter;
	for(iter=neighbours.begin(); iter!=neighbours.end(); iter++)
	{
		sum += (*iter)->getPosition();
		count ++;
	}

	if(count > 0)
	{
		sum /= (float)count;
		glm::vec2 desired = sum-myPos;

		float d = glm::length(desired);
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
			return glm::vec2(0,0);
		}
	}
	else
	{
		return glm::vec2(0,0);
	}
}

glm::vec2 Bird::aligment(std::vector<Bird*> neighbours)
{
	glm::vec2 mean(0,0);
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

glm::vec2 Bird::separate(std::vector<Bird*> neighbours)
{
	glm::vec2 mean(0,0);
	glm::vec2 myPos = getPosition();

	int count = 0;

	std::vector<Bird*>::iterator iter;
	for(iter=neighbours.begin(); iter!=neighbours.end(); iter++)
	{
		glm::vec2 neighbourPos = (*iter)->getPosition();
		glm::vec2 distance = myPos-neighbourPos;
		if(glm::length(distance) < DESIRED_SEPARATION)
		{
			mean += distance/glm::length(distance);
			count ++;
		}
	}

	if(count)
	{
		mean /= (float)count;
	}
	return mean;
}

glm::vec2 Bird::getVelocity()
{
	return mVelocity;
}