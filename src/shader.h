#pragma once
#include <glm/glm.hpp>
#include <iostream>

namespace KarhuRayTracer
{
	class Shader
	{
	public:
		Shader(const char* vertexShader, const char* fragmentShader, const char* computeShader);
		~Shader();
		void use();
		void use_compute(float width, float height);

		void setUniformVec4(const std::string& name, const glm::vec4& vec4);
		void setUniformMat4(const std::string& name, const glm::mat4& mat4);
		void setUniformTexture(const std::string& name, int value);

	private:
		unsigned int m_VertexShader;
		unsigned int m_FragmentShader;
		unsigned int m_ComputeShader;

		unsigned int m_ShaderProgram;
		unsigned int m_ComputeProgram;
	};
}