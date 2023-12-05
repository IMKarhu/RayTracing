#version 460 core

in vec3 outColor; /* Needs to be same name than output in vertexShader. */

out vec4 FragColor;


void main()
{
	FragColor = vec4(outColor, 1.0);
}


/* Typical structure in shaders.

	in type variable_name.
	out type variable_name.
	uniform type variable_name.
	
	main function.
*/