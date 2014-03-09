#ifndef __geometry_h__
#define __geometry_h__
/********************************************************************
* @file geometry.h
* @author Erik Larsson
* @version 1.0
* @section DESCRIPTION
*  
*********************************************************************/
#include <vector>
#include "glm.hpp"

class Geometry
{
public:
	Geometry(std::vector<glm::vec2> vertexList);
	~Geometry() {};

	std::vector<glm::vec2> getVertices() const;
	int getVertexCount() const;
protected:
	std::vector<glm::vec2> mVertexList;
};



#endif // __geometry_h__
