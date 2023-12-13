#include "texture.h"
#include "glad.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace KarhuRayTracer
{
	Texture::Texture()
	{
		float skyBox[] =
		{
			-1.0,-1.0,1.0,
			 1.0,-1.0, 1.0,
			 1.0,-1.0,-1.0,
			-1.0,-1.0,-1.0,
			-1.0, 1.0, 1.0,
			 1.0, 1.0, 1.0,
			 1.0, 1.0,-1.0,
			-1.0, 1.0,-1.0
		};

		unsigned int skyboxIndices[] =
		{
			1,2,6,
			6,5,1,

			0,4,7,
			7,3,0,

			4,5,6,
			6,7,4,

			0,3,2,
			2,1,0,

			0,1,5,
			5,4,0,

			3,7,6,
			6,2,3
		};

		

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);
		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyBox), skyBox, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), skyboxIndices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_VERTEX_ARRAY, 0);

		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	void Texture::createTexture()
	{
		
	}
	void Texture::createCubeMap()
	{
		std::vector<std::string> CubeMapFaces =
		{
			"../textures/skybox/right.jpg",
			"../textures/skybox/left.jpg",
			"../textures/skybox/top.jpg",
			"../textures/skybox/bottom.jpg",
			"../textures/skybox/front.jpg",
			"../textures/skybox/back.jpg"
		};

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID);

		int width, height, nrChannels;
		for (unsigned int i = 0; i < CubeMapFaces.size(); i++)
		{
			unsigned char* data = stbi_load(CubeMapFaces[i].c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
				);
				stbi_image_free(data);
			}
			else
			{
				std::cout << "Cubemap tex failed to load at path: " << CubeMapFaces[i] << std::endl;
				stbi_image_free(data);
			}
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}
	void Texture::bind()
	{
		glBindVertexArray(m_VAO);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
}
