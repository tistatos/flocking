#ifndef __SHAPE_H__
#define __SHAPE_H__
/********************************************************************
* @file shape.h
* @author Erik Larsson
* @version 1.0
* @section DESCRIPTION
*  Flocking demo - shape class
*********************************************************************/

#include "geometry.h"
#include <gtc/matrix_transform.hpp>
class Shape 
{
public:
	Shape(Geometry *g);
	~Shape();
	Geometry* getGeometry();
	glm::mat4 getModelMatrix();
	void scale(glm::vec3 scaleVec);
	void translate(glm::vec3 translateVec);
	void rotateZ(double theta);
private:
	Geometry* mGeometry;
	glm::mat4 mModelMatrix;
	static double maxSpeed;

};
#endif // __SHAPE_H__
