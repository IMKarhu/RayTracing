#version 460 core

in vec3 texCoords;

out vec4 FragColor;

uniform samplerCube u_SkyBox;

void main()
{
	FragColor = texture(u_SkyBox, texCoords);
}

/* Typical structure in shaders.

	in type variable_name.
	out type variable_name.
	uniform type variable_name.
	
	main function.
*/
