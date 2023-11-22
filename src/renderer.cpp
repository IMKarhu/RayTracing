#include "renderer.h"
#include "window.h"
#include <glad/gl.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace KarhuRayTracer
{



	Renderer::Renderer(Window& window)
		:m_Window(window)
	{
		float vertices[] =
		{
			//position		   //color		      //texture coords
			0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, //top right
			0.5f,-0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, //bottom right
		   -0.5f,-0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, //bottom left
		   -0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f  //top left
		};
		
		unsigned int indices[] =
		{
			0,1,3,
			1,2,3
		};
		
		float texCoords[] =
		{
			0.0f,0.0f,
			1.0f,0.0f,
			0.5f,1.0f
		};
		

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);
		

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		
		/* Position. */
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		/* Color. */
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		/* Texture. */
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;
		unsigned char* data = stbi_load("../textures/container.jpg", &width, &height, &nrChannels, 0);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			printf("Failed to load texture");
		}
		stbi_image_free(data);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}
	Renderer::~Renderer()
	{
		glDeleteBuffers(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);
	}
	void Renderer::render()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*glGenFramebuffers(1, &m_FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

		glGenTextures(1, &fbotex);
		glBindTexture(GL_TEXTURE_2D, fbotex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Window.getWidth(), m_Window.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbotex, 0);*/
		//glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}
