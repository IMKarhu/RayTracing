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
	
	/*Object::Object(){}
	Object::Object(glm::vec3& position, glm::vec3& scale, glm::vec3& colour, float radius, Material material)
	{
		m_Position = position;
		m_Scale = scale;
		m_Material = material;
		m_Colour = colour;
		m_Radius = radius;
	}*/

	void bind(Shader& m_Shader, std::vector<Object> objects)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			std::string index = std::to_string(i);
			m_Shader.setCUniformVec3(std::string("u_Objects[").append(index).append("].m_ObjPosition"), objects[i].m_Position);
			m_Shader.setCUniformVec3(std::string("u_Objects[").append(index).append("].m_ObjScale"), objects[i].m_Scale);
			m_Shader.setCUniformVec3(std::string("u_Objects[").append(index).append("].m_ObjColour"), objects[i].m_Colour);
			m_Shader.setCUniformfloat(std::string("u_Objects[").append(index).append("].m_ObjRadius"), objects[i].m_Radius);
		}
	}
	void bind1(Shader& m_Shader, Object object)
	{
		m_Shader.setCUniformVec3("u_Objects1.position", object.m_Position);
		m_Shader.setCUniformVec3("u_Objects1.scale", object.m_Scale);
		m_Shader.setCUniformVec3("u_Objects1.colour", object.m_Colour);
		m_Shader.setCUniformfloat("u_Objects1.radius", object.m_Radius);
	}
}