#version 460 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inUV;

out vec2 outUV;

uniform mat4 projection;
uniform mat4 view;

void main()
{
	gl_Position = vec4(inPosition, 1.0);
	outUV =  inUV;
}

/* Typical structure in shaders.

	in type variable_name.
	out type variable_name.
	uniform type variable_name.
	
	main function.
*/