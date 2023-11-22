#version 460 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec2 inTexCoord;

out vec3 outColor;
out vec2 outTexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	gl_Position = vec4(inPosition, 1.0);
	outColor =  inColor;
	outTexCoord = inTexCoord;

}

/* Typical structure in shaders.

	in type variable_name.
	out type variable_name.
	uniform type variable_name.
	
	main function.
*/