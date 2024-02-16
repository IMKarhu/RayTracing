#include "renderer.h"
#include "window.h"
#include "shader.h"
#include "camera.h"
#include <iostream>
#include <glad.h>


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


		glNamedBufferData(m_VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);
		

		glNamedBufferData(m_EBO, sizeof(indices), indices, GL_STATIC_DRAW);
		

		glEnableVertexArrayAttrib(m_VAO, 0);
		glVertexArrayAttribBinding(m_VAO, 0, 0);
		glVertexArrayAttribFormat(m_VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
		

		glEnableVertexArrayAttrib(m_VAO, 1);
		glVertexArrayAttribBinding(m_VAO, 1, 0);
		glVertexArrayAttribFormat(m_VAO, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat));

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
	void Renderer::render(std::vector<Shader>& m_Shaders, Camera& m_Camera, std::vector<Object> objects, PointLight& light, unsigned int textureID, float dt)
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		m_Shaders[1].use_compute(ceil((float)m_Window.getWidth() / 8), ceil((float)m_Window.getHeight() / 4));
		bind(m_Shaders[1], objects, light, textureID);
		m_Camera.update(dt);
		m_Shaders[0].use();
		
		glBindTextureUnit(0, texture);
		m_Shaders[0].setUniformTexture("screen", 0);
		m_Shaders[0].setUniformMat4("view", m_Camera.getViewMatrix());
		m_Shaders[0].setUniformMat4("projection", m_Camera.getProjectionMatrix());
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);
	
	}
	
}
