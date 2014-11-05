#ifndef __engineUtils_h__
#define __engineUtils_h__
/********************************************************************
* @file engineUtils.h
* @author Erik Larsson
* @version 1.0
* @section DESCRIPTION
*
*********************************************************************/
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>


const float PI = 3.14159265358979323f;

GLuint loadShader(const char* vertexFile, const char* fragmentFile);
double getRand();

#endif // __engineUtils_h__
