#ifndef __bufferObject_h__
#define __bufferObject_h__
/********************************************************************
* @file bufferObject.h
* @author Erik Larsson
* @version 1.0
* @section DESCRIPTION
*  
*********************************************************************/

#include "engineUtils.h"
#include "shape.h"

class BufferObject
{
public:
	BufferObject(Shape* s);
	~BufferObject();
	GLuint getVertexBuffer();
	Shape* getShape();
private:
	Shape* mShape;
	GLuint mVertexBuffer;


};


#endif // __bufferObject_h__
