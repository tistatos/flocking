/********************************************************************
* @file bufferObject.cpp
* @author Erik Larsson
* @version 1.0
* @section DESCRIPTION
*  flocking 
********************************************************************/
#include "bufferObject.h"

BufferObject::BufferObject(Shape* s)
{
	GLfloat* glBuffer = new GLfloat[s->getGeometry()->getVertexCount()*3];
	for(int i = 0; i < s->getGeometry()->getVertices().size(); i++ )
	{
		glBuffer[i*3+0] = s->getGeometry()->getVertices()[i].x;
		glBuffer[i*3+1] = s->getGeometry()->getVertices()[i].y;
		glBuffer[i*3+2] = 0;
	}

	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(glBuffer)*s->getGeometry()->getVertexCount()*3,glBuffer, GL_STATIC_DRAW);

	delete[] glBuffer;
	
	mShape = s;
}

BufferObject::~BufferObject()
{
	glDeleteBuffers(1, &mVertexBuffer);
}

GLuint BufferObject::getVertexBuffer()
{
	return mVertexBuffer;
}

Shape* BufferObject::getShape()
{
	return mShape;
}
