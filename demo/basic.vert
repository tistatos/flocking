#version 330 core

layout(location = 0) in vec3 vertexPosition_mdl;

uniform mat4 MVP;
out vec3 fragColor;


void main()
{
	gl_Position = MVP*vec4(vertexPosition_mdl, 1);
	fragColor = vec3(0.3, 0.3, 0.3);
}