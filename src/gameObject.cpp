#include "gameObject.h"
#include "shader.h"
#include <glad.h>


//m_Sphere.Center = vec3(3.0, 0.0, 0.0);
//m_Sphere.Radius = 1.0;
//m_Sphere.Colour = vec3(1.0, 0.75, 0.5);

namespace KarhuRayTracer
{
	Material m_Material;
	extern Object m_Object;
	
	Object::Object() = default;
	Object::Object(glm::vec3& position, glm::vec3& scale, glm::vec3& colour, float radius, Material material)
	{
		m_Position = position;
		m_Scale = scale;
		m_Material = material;
		m_Colour = colour;
		m_Radius = radius;
	}

	void bind(Shader& m_Shader, Object object)
	{
		m_Shader.setCUniformVec3("u_Objects.position", object.m_Position);
		m_Shader.setCUniformVec3("u_Objects.scale", object.m_Scale);
		m_Shader.setCUniformVec3("u_Objects.colour", object.m_Colour);
		m_Shader.setCUniformfloat("u_Objects.radius", object.m_Radius);
	}
}