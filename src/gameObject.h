#pragma once
#include <glm/glm.hpp>

namespace KarhuRayTracer
{
	class Shader;

	struct Material
	{
		glm::vec3 m_Albeido;
		glm::vec3 m_Specular;
		glm::vec3 m_Emission;
		float m_Roughness;
	};
	struct Object
	{
		glm::vec3 m_Position;
		glm::vec3 m_Scale;
		glm::vec3 m_Colour;
		float m_Radius;
		Material m_Material;

		Object();
		Object(glm::vec3& position, glm::vec3& scale, glm::vec3& colour, float radius, Material material);
	};

	
	

	void bind(Shader& m_Shader, Object object);
}