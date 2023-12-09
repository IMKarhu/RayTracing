#include "gameObject.h"
#include <glad.h>


namespace KarhuRayTracer
{
	/* GameObject Functions. */
	void GameObject::setPosition(glm::vec3& position)
	{
	}
	void GameObject::setScale(glm::vec3& scale)
	{
	}

	/* Box functions. */
	Box::Box(float width, float height)
	{
		float vertices[] =
		{
			-1.0f,-1.0f, 0.0f, 0.0f,0.0f,
			 1.0f,-1.0f, 0.0f, 0.0f,1.0f,
			 1.0f, 1.0f, 0.0f, 1.0f,1.0f,
			 -1.0f,1.0f, 0.0f, 1.0f,0.0f
		};

		unsigned int indices[] =
		{
			0,1,2,
			2,3,0
		};

		glGenVertexArrays(1, &m_VAO); /* Create VertexArrayObject. */
		glGenBuffers(1, &m_VBO); /* Create VertexBufferObject. */
		glGenBuffers(1, &m_EBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		/* Position. */
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); /* Params: location in VertexShader, number of values we input, type, normalized, stride, offset. */
		glEnableVertexAttribArray(0);
		/* Color. */
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));

		/*glGenFramebuffers(1, &m_FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

		glGenTextures(1, &fbotex);
		glBindTexture(GL_TEXTURE_2D, fbotex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbotex, 0);

		glGenRenderbuffers(1, &m_RBO);
		glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RBO);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);*/

	}

	Box::~Box()
	{
		glDeleteBuffers(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);
		glDeleteBuffers(1, &m_FBO);
		glDeleteBuffers(1, &m_RBO);
	}

	void Box::resizeFramebuffer(float width, float height)
	{
		glBindTexture(GL_TEXTURE_2D, fbotex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbotex, 0);

		glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RBO);
		glViewport(0, 0, width, height);
	}

	void Box::render()
	{
		glBindVertexArray(m_VAO);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

}