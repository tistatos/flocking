#version 330 core
#extension GL_ARB_separate_shader_objects : enable

out vec4 color;
in vec3 fragColor;


void main()
{
	color = vec4(fragColor,1.0);
}