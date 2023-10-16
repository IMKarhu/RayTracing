#pragma once
#include <glm/glm.hpp>

namespace KarhuRayTracer
{
	struct GameObject
	{
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

		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;
	};

	struct Sphere : public GameObject
	{

		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;
	};
}