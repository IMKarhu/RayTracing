#include "gameObject.h"
#include "shader.h"
#include <glad.h>
#include <string>


//m_Sphere.Center = vec3(3.0, 0.0, 0.0);
//m_Sphere.Radius = 1.0;
//m_Sphere.Colour = vec3(1.0, 0.75, 0.5);

namespace KarhuRayTracer
{
	Material m_Material;
	extern Object m_Object;

	void bind(Shader& m_Shader, std::vector<Object> objects, PointLight light)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			std::string index = std::to_string(i);
			m_Shader.setCUniformVec3(std::string("u_Objects[").append(index).append("].m_ObjPosition"), objects[i].m_Position);
			m_Shader.setCUniformVec3(std::string("u_Objects[").append(index).append("].m_ObjScale"), objects[i].m_Scale);
			m_Shader.setCUniformfloat(std::string("u_Objects[").append(index).append("].m_ObjRadius"), objects[i].m_Radius);
			m_Shader.setCUniformVec3(std::string("u_Objects[").append(index).append("].m_ObjMaterial.m_Albeido"), objects[i].m_Material.m_Albeido);
			m_Shader.setCUniformfloat(std::string("u_Objects[").append(index).append("].m_ObjMaterial.m_Roughness"), objects[i].m_Material.m_Roughness);
		}

		m_Shader.setCUniformVec3("u_PointLight.m_LightPosition", light.m_Position);
		m_Shader.setCUniformVec3("u_PointLight.m_LightColor", light.m_Color);
		m_Shader.setCUniformfloat("u_PointLight.m_LightRadius", light.m_Radius);
	}
}