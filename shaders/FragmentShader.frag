#version 460 core

in vec2 outUV; /* Needs to be same name than output in vertexShader. */

out vec4 FragColor;

uniform sampler2D screen;


void main()
{
	FragColor = texture(screen, outUV);
}


/* Typical structure in shaders.

	in type variable_name.
	out type variable_name.
	uniform type variable_name.
	
	main function.
*/