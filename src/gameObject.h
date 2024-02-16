#pragma once
#include <vector>
#include <string>
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
		int m_Type;
		Material m_Material;

		/* Plane only. */

		glm::vec3 m_Tangent;
		glm::vec3 m_BiTangent;
		glm::vec3 m_Normal;
		float m_Umin, m_Umax;
		float m_Vmin, m_Vmax;
	};

	struct PointLight
	{
		glm::vec3 m_Position;
		glm::vec3 m_Color;
		float m_Radius;
	};

	class CubeMaterial
	{
	public:
		CubeMaterial();
		~CubeMaterial();

		unsigned int createCubeMap(std::vector<std::string> faces);
	private:
		
	};
	

	void bind(Shader& m_Shader, std::vector<Object> objects, PointLight light, unsigned int TextureID);
}