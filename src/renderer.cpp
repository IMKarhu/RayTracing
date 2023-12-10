#include "renderer.h"
#include "window.h"
#include "shader.h"
#include <iostream>
#include <glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace KarhuRayTracer
{
	unsigned int indices[] =
	{
		0,1,2,
		2,3,0
	};
	Renderer::Renderer(Window& window)
		:m_Window(window)
	{
		float vertices[] =
		{
			-1.0f,-1.0f, 0.0f,  0.0f, 0.0f,
			 1.0f,-1.0f, 0.0f,  1.0f, 0.0f,
			 1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
			-1.0f, 1.0f, 0.0f,  0.0f, 1.0f
		};
		

		glCreateVertexArrays(1, &m_VAO);
		glCreateBuffers(1, &m_VBO);
		glCreateBuffers(1, &m_EBO);

		//glBindVertexArray(m_VAO);

		glNamedBufferData(m_VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);
		//glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glNamedBufferData(m_EBO, sizeof(indices), indices, GL_STATIC_DRAW);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glEnableVertexArrayAttrib(m_VAO, 0);
		glVertexArrayAttribBinding(m_VAO, 0, 0);
		glVertexArrayAttribFormat(m_VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		//glEnableVertexAttribArray(0);

		glEnableVertexArrayAttrib(m_VAO, 1);
		glVertexArrayAttribBinding(m_VAO, 1, 0);
		glVertexArrayAttribFormat(m_VAO, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat));
		//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		//glEnableVertexAttribArray(1);

		glVertexArrayVertexBuffer(m_VAO, 0, m_VBO, 0, 5 * sizeof(GLfloat));
		glVertexArrayElementBuffer(m_VAO, m_EBO);

		glCreateTextures(GL_TEXTURE_2D, 1, &texture);
		glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureStorage2D(texture, 1, GL_RGBA32F, m_Window.getWidth(), m_Window.getHeight());
		glBindImageTexture(0, texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

	}
	Renderer::~Renderer()
	{
		glDeleteBuffers(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);
	}
	void Renderer::render(Shader& m_Shader, float dt)
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_Shader.use_compute(ceil(m_Window.getWidth()/8), ceil(m_Window.getHeight()/4));
		m_Shader.use();
		
		glBindTextureUnit(0, texture);
		m_Shader.setUniformTexture("screen", 0);
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);
	}
	
}
