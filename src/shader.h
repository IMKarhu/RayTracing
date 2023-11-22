#pragma once
#include <glm/glm.hpp>
#include <iostream>

namespace KarhuRayTracer
{
	class Shader
	{
	public:
		Shader(const char* vertexShader, const char* fragmentShader);
		~Shader();
		void use();

		void setUniformVec4(const std::string& name, const glm::vec4& vec4);

	private:
		unsigned int m_VertexShader;
		unsigned int m_FragmentShader;

		unsigned int m_ShaderProgram;
	};
}