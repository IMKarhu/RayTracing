#pragma once
#include <glm/glm.hpp>

namespace KarhuRayTracer
{
	struct GameObject
	{
		//virtual ~GameObject() = 0;
		/* Setters. */
		void setPosition(glm::vec3& position);
		void setScale(glm::vec3& scale);

		/* Getters. */
		glm::vec3 getPosition() { return m_Position; }
		glm::vec3 getScale() { return m_Scale; }

	private:
		/* Member variables. */
		glm::vec3 m_Position;
		glm::vec3 m_Scale;
		glm::mat4 m_ModelMatrix;
		glm::mat4 m_ViewMatrix;
	};

	struct Box : public GameObject
	{
		Box(float width, float height);
		~Box();
		void resizeFramebuffer(float width, float height);
		void render();
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;
		unsigned int m_FBO;
		unsigned int m_RBO;
		unsigned int fbotex;
	};

	struct Sphere : public GameObject
	{

		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;
	};
}