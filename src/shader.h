#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace KarhuRayTracer
{
	class Shader
	{
	public:
		Shader(const char* vertexShader, const char* fragmentShader);
		Shader(const char* computeShader);
		~Shader();
		void use();
		void use_compute(float width, float height);

		void setUniformVec4(const std::string& name, const glm::vec4& vec4);
		void setUniformMat4(const std::string& name, const glm::mat4& mat4);
		void setUniformTexture(const std::string& name, int value);
		void setUniformInt(const std::string& name, const int& value);

		/* Compute. */
		void setCUniformVec3(const std::string& name, const glm::vec3& vec3);
		void setCUniformfloat(const std::string& name, const float& value);
		void setCUniformInt(const std::string& name, const int& value);

	private:
		unsigned int m_VertexShader;
		unsigned int m_FragmentShader;
		unsigned int m_ComputeShader;

		unsigned int m_ShaderProgram;
		unsigned int m_ComputeProgram;
	};
}