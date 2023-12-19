#pragma once
#include <vector>
#include <glm/glm.hpp>

namespace KarhuRayTracer
{
	class Shader;

	struct Material
	{
		glm::vec3 m_Albeido;
		glm::vec3 m_Specular;
		glm::vec3 m_Emission;
		float m_Roughness = 0.5f;
	};

	struct Object
	{
		glm::vec3 m_Position;
		glm::vec3 m_Scale;
		float m_Radius;
		Material m_Material;

		/*Object();
		Object(glm::vec3& position, glm::vec3& scale, glm::vec3& colour, float radius, Material material);*/
	};

	struct PointLight
	{
		glm::vec3 m_Position;
		glm::vec3 m_Color;
		float m_Radius;
	};

	
	

	void bind(Shader& m_Shader, std::vector<Object> objects, PointLight light);
}