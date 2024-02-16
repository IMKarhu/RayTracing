#include "gameObject.h"
#include "shader.h"
#include <glad.h>
#include <stb_image.h>



namespace KarhuRayTracer
{

	CubeMaterial::CubeMaterial()
	{
		
	}
	CubeMaterial::~CubeMaterial()
	{
	}

	unsigned int CubeMaterial::createCubeMap(std::vector<std::string> faces)
	{
		unsigned int textureID;
		glGenTextures(1, &textureID);

		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		int width, height, nrChannels;
		for (int i = 0; i < faces.size(); i++)
		{
			unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
				);
				stbi_image_free(data);
			}
			else
			{
				std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
				stbi_image_free(data);
			}
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		return textureID;
	}

	/* This is rather dumb way to send data for shaders. Better way would be to use uniform buffers. */
	void bind(Shader& m_Shader, std::vector<Object> objects, PointLight light, unsigned int TextureID)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			std::string index = std::to_string(i);
			m_Shader.setCUniformVec3(std::string("u_Objects[").append(index).append("].m_ObjPosition"), objects[i].m_Position);
			m_Shader.setCUniformVec3(std::string("u_Objects[").append(index).append("].m_ObjScale"), objects[i].m_Scale);
			m_Shader.setCUniformfloat(std::string("u_Objects[").append(index).append("].m_ObjRadius"), objects[i].m_Radius);
			m_Shader.setCUniformInt(std::string("u_Objects[").append(index).append("].m_ObjType"), objects[i].m_Type);
			m_Shader.setCUniformVec3(std::string("u_Objects[").append(index).append("].m_ObjMaterial.m_Albeido"), objects[i].m_Material.m_Albeido);
			m_Shader.setCUniformfloat(std::string("u_Objects[").append(index).append("].m_ObjMaterial.m_Roughness"), objects[i].m_Material.m_Roughness);
			if (objects[i].m_Type == 1)
			{
				m_Shader.setCUniformVec3(std::string("u_Objects[").append(index).append("].m_ObjTangent"), objects[i].m_Tangent);
				m_Shader.setCUniformVec3(std::string("u_Objects[").append(index).append("].m_ObjBiTangent"), objects[i].m_BiTangent);
				m_Shader.setCUniformVec3(std::string("u_Objects[").append(index).append("].m_ObjNormal"), objects[i].m_Normal);
				m_Shader.setCUniformfloat(std::string("u_Objects[").append(index).append("].m_ObjUmin"), objects[i].m_Umin);
				m_Shader.setCUniformfloat(std::string("u_Objects[").append(index).append("].m_ObjUmax"), objects[i].m_Umax);
				m_Shader.setCUniformfloat(std::string("u_Objects[").append(index).append("].m_ObjVmin"), objects[i].m_Vmin);
				m_Shader.setCUniformfloat(std::string("u_Objects[").append(index).append("].m_ObjVmax"), objects[i].m_Vmax);
			}
		}

		m_Shader.setCUniformVec3("u_PointLight.m_LightPosition", light.m_Position);
		m_Shader.setCUniformVec3("u_PointLight.m_LightColor", light.m_Color);
		m_Shader.setCUniformfloat("u_PointLight.m_LightRadius", light.m_Radius);
		m_Shader.setUniformInt("u_SkyBox", TextureID);
	}
	
}