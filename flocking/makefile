#define compiler
CC = g++

CFLAGS = -Wfatal-errors
#define name of output file
TARGET = Flocking

#define include directories
INCLUDES = -I./include -I./include/glm

#define libraries to link to executable
LIBS = -lGL -lGLEW -lglfw3 -lGLU -lglut -lm -lX11 -lXxf86vm -lpthread -lXrandr -lXi

# define sourcefiles
SRCS = src/main.cpp src/bird.cpp src/birdGeometry.cpp src/bufferObject.cpp src/engine2D.cpp src/engineUtils.cpp src/flock.cpp src/gameTimer.cpp src/geometry.cpp src/shape.cpp

#define the C objects files
OBJS = $(SRCS:.c=.o)

MAIN = main.cpp

.PHONY: depend clean


all: $(MAIN)
	@echo Build successful

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) *.o *~ $(TARGET)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

