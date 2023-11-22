#version 460 core

in vec3 outColor;
in vec2 outTexCoord;

out vec4 FragColor;

uniform vec4 uni_outColor;
uniform sampler2D uni_Texture;

void main()
{
	FragColor = texture(uni_Texture, outTexCoord) * vec4(outColor, 1.0);
}


/* Typical structure in shaders.

	in type variable_name.
	out type variable_name.
	uniform type variable_name.
	
	main function.
*/