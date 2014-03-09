#ifndef __engineUtils_h__
#define __engineUtils_h__
/********************************************************************
* @file engineUtils.h
* @author Erik Larsson
* @version 1.0
* @section DESCRIPTION
*  
*********************************************************************/
#include <glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <vector>
#include <iostream>
#include <fstream>

const float PI = 3.14159265358979323f;

GLuint loadShader(const char* vertexFile, const char* fragmentFile);
double getRand();

#endif // __engineUtils_h__
