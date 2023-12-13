#version 460 core

layout(location = 0) in vec3 inPosition;

out vec3 texCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
	texCoords = inPosition;
	gl_Position = projection * view * vec4(inPosition, 1.0);
}

/* Typical structure in shaders.

	in type variable_name.
	out type variable_name.
	uniform type variable_name.
	
	main function.
*/
