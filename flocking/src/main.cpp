/********************************************************************
* @file main.cpp
* @author Erik Larsson
* @version 1.0
* @section DESCRIPTION
*  Flocking demo main file
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "engine2D.h"
#include "gameTimer.h"
#include "birdGeometry.h"
#include "flock.h"
#define GLM_FORCE_RADIANS

#define FLOCK_SIZE 100

int main()
{
	Engine2D engine; //Graphics Engine
	Flock flock; //Flocking logic

	//Setup window with glfw and Glew
	const GLFWvidmode *vidmode;
	GLFWwindow *window;
	char titlestring[64] = "Flocking Demo";
	GameTimer timer;
	double dt;
	double fps;

	srand(time(NULL));

	//initiate GLFW
	if(!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	//Create window
	vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(vidmode->width/2, vidmode->width/2,titlestring , NULL, NULL);

	//exit if we cant create window
	if(!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	//Some information about GL
	printf("GL vendor:       %s\n", glGetString(GL_VENDOR));
	printf("GL renderer:     %s\n", glGetString(GL_RENDERER));
	printf("GL version:      %s\n", glGetString(GL_VERSION));
	printf("Desktop size:    %d x %d pixels\n", vidmode->width, vidmode->height);


	//Start GLEW
	glewExperimental = true;
	GLenum err = glewInit();

	if (err != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n Error:%s\n", glewGetErrorString(err) );
		return -1;
	}

	//initiate engine
	engine.init(window);

	//create geometry for birds
	Geometry bird = BirdGeometry();

	//Add birds to engine and flocking system
	for(int i = 0; i < FLOCK_SIZE; i++)
	{
		Shape *b = new Shape(&bird);
		flock.add(new Bird(b));
		engine.add(b);
	}
	//bind buffers of birds
	engine.bindBuffers();

	//limit to 60fps
	glfwSwapInterval(1);

	while(!glfwWindowShouldClose(window))
	{
		//Game loop
		timer.tick();
		dt = timer.getDeltaTime();
		fps = timer.getFPS();
		sprintf(titlestring, "Flocking Demo, %.4f ms/frame (%.1f FPS)", dt, fps);
		glfwSetWindowTitle(window, titlestring);

		//get keyboard events
		glfwPollEvents();
		//update flock
		flock.update(dt);

		//draw flock
		engine.render(dt);


		if(glfwGetKey(window, GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(window, GL_TRUE);
	}

	//Cleanup
	engine.destroy();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}