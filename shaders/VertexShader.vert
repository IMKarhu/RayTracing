#version 460 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColor;

out vec3 outColor;


void main()
{
	outColor =  inColor;
	gl_Position = vec4(inPosition.x,inPosition.y,inPosition.z, 1.0);
	
}

/* Typical structure in shaders.

	in type variable_name.
	out type variable_name.
	uniform type variable_name.
	
	main function.
*/