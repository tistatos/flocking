/********************************************************************
* @file shape.cpp
* @author Erik Larsson
* @version 1.0
* @section DESCRIPTION
*  
*********************************************************************/

#include "shape.h"

Shape::Shape(Geometry *g)
{
	mGeometry = g;
	mModelMatrix = glm::mat4();
	scale(glm::vec3(2,2,1));
}

Geometry* Shape::getGeometry()
{
	return mGeometry;
}



void Shape::translate(glm::vec3 translateVec)
{
	mModelMatrix = glm::translate(mModelMatrix, translateVec);
}

void Shape::rotateZ(double theta)
{
	mModelMatrix = glm::rotate<glm::lowp_float>(mModelMatrix,theta,glm::vec3(0,0,1));
}


void Shape::scale(glm::vec3 scalevec)
{
	mModelMatrix = glm::scale(mModelMatrix, scalevec);
}

glm::mat4 Shape::getModelMatrix()
{
	return mModelMatrix;
}
