#pragma once

namespace KarhuRayTracer
{
	class Shader
	{
	public:
		Shader(const char* vertexShader, const char* fragmentShader);
		~Shader();
		void use();
	private:
		unsigned int m_VertexShader;
		unsigned int m_FragmentShader;

		unsigned int m_ShaderProgram;
	};
}