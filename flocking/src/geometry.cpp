/********************************************************************
* @file geometry.cpp
* @author Erik Larsson
* @version 1.0
* @section DESCRIPTION
*  
*********************************************************************/

#include "geometry.h"

Geometry::Geometry(std::vector<glm::vec2> vertexList)
{
	mVertexList = vertexList;
}

int Geometry::getVertexCount() const
{
	return mVertexList.size();
}

std::vector<glm::vec2> Geometry::getVertices() const
{
	return mVertexList;
}