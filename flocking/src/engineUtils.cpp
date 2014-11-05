/********************************************************************
* @file engineUtils.cpp
* @author Erik Larsson
* @version 1.0
* @section DESCRIPTION
*
*********************************************************************/
#include "engineUtils.h"

using namespace std;

GLuint loadShader(const char* vertexFile, const char* fragmentFile)
{
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexCode;
	std::ifstream vertexShaderStream(vertexFile, std::ios::in);

	if(vertexShaderStream.is_open())
	{
		std::string line = "";
		while(getline(vertexShaderStream, line))
		{
			vertexCode += "\n" + line;
		}
		vertexShaderStream.close();
	}
	else
	{
		printf("Could not read Vertex shader file");
		return 0;
	}

	std::string fragmentCode;
	std::ifstream fragmentShaderStream (fragmentFile, std::ios::in);

	if(fragmentShaderStream.is_open())
	{
		std::string line = "";
		while(getline(fragmentShaderStream, line))
		{
			fragmentCode += "\n" + line;
		}
		fragmentShaderStream.close();
	}
	else
	{
		printf("Could not read Fragment shader file");
		return 0;
	}

	GLint result = GL_FALSE;
	int infoLog;
	printf("Compiling Shader file");
	char const *vertexSource = vertexCode.c_str();
	glShaderSource(vertexShaderID, 1, &vertexSource, NULL);
	glCompileShader(vertexShaderID);

	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLog);

	if(infoLog > 0)
	{
		std::vector<char> vertexError(infoLog+1);
		glGetShaderInfoLog(vertexShaderID, infoLog, NULL, &vertexError[0]);
		//printf("%s\n", vertexError);
	}

	printf("Compiling Fragment file");
	char const *fragmentSource = fragmentCode.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShaderID);

	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLog);

	if(infoLog > 0)
	{
		std::vector<char> fragmentError(infoLog+1);
		glGetShaderInfoLog(fragmentShaderID, infoLog, NULL, &fragmentError[0]);
		//printf("%s\n", fragmentError);
	}

	printf("Linking program\n");
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);

	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLog);

	if(infoLog > 0)
	{
		std::vector<char> linkingError(infoLog+1);
		glGetProgramInfoLog(programID, infoLog, NULL, &linkingError[0]);
		printf("%s\n", &linkingError[0]);
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return programID;

}

double getRand()
{
	return rand()/(double)RAND_MAX;
}