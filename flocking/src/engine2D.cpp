/********************************************************************
* @file engine2D.cpp
* @author Erik Larsson
* @version 1.0
* @section DESCRIPTION
*  Flocking demo - 2D engine class
*********************************************************************/

#include "engineUtils.h"
#include "engine2D.h"

using namespace glm;

Engine2D::Engine2D()
{
	
}

bool Engine2D::init(GLFWwindow *window)
{
	mWindow = window;

	glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
	glEnable(GL_DEPTH_TEST); 
	glDepthFunc(GL_LESS);

	mProgramID = loadShader("basic.vert", "basic.frag");
	mModelMatrixID = glGetUniformLocation(mProgramID, "MVP");

	GLuint vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	setCamera(vec3(0.2f));
	return true;
}

void Engine2D::destroy()
{
	deleteBuffers();
	mWindow = NULL;
}

void Engine2D::setView(mat4 view)
{
	mViewMatrix = view;
}

void Engine2D::setCamera(vec3 camera)
{
	setView(mat4(
		camera.x,	0.0f,		0.0f,		0.0f,
		0.0f,		camera.y,	0.0f,		0.0f,
		0.0f,		0.0f,		camera.z,	0.0f,
		0.0f,		0.0f,		0.0f,		1.0f
		));
}

void Engine2D::add(Shape *s)
{
	mShapes.push_back(s);
}

void Engine2D::bindBuffers()
{
	for (int i = 0; i < mShapes.size(); i++)
	{
		mBuffers.push_back(new BufferObject(mShapes[i]));
	}
}

void Engine2D::deleteBuffers()
{
	for(std::vector<BufferObject*>::iterator iter = mBuffers.begin(); iter!=mBuffers.end(); iter++)
	{
		delete (*iter);
	}
	mBuffers.clear();
}

void Engine2D::update(double dt)
{
	//Not used in this demo
}

void Engine2D::render(double dt)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	std::vector<BufferObject*>::iterator iter;
	for(iter = mBuffers.begin(); iter != mBuffers.end(); iter++)
	{
		glUseProgram(mProgramID);

		glUniformMatrix4fv(mModelMatrixID, 1, GL_FALSE, &(mViewMatrix*(*iter)->getShape()->getModelMatrix())[0][0]);
		glBindBuffer(GL_ARRAY_BUFFER, (*iter)->getVertexBuffer());
	
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
			);

		glDrawArrays(GL_TRIANGLE_FAN, 0, (*iter)->getShape()->getGeometry()->getVertices().size());
		glDisableVertexAttribArray(0);

		glUseProgram(0);

	}

	glfwSwapBuffers(mWindow);
}

GLFWwindow *Engine2D::getWindow()
{
	return mWindow;
}


