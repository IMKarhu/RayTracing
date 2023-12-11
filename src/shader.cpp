#include "shader.h"
#include <glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

namespace KarhuRayTracer
{
	Shader::Shader(const char* vertexShader, const char* fragmentShader, const char* computeShader)
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::string computeCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		std::ifstream cShaderFile;
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		cShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			vShaderFile.open(vertexShader);
			fShaderFile.open(fragmentShader);
			cShaderFile.open(computeShader);
			std::stringstream vShaderStream, fShaderStream, cShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			cShaderStream << cShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			cShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
			computeCode = cShaderStream.str();
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << e.code() << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		const char* cShaderCode = computeCode.c_str();

		m_VertexShader = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(m_VertexShader, 1, &vShaderCode, nullptr);
		glCompileShader(m_VertexShader);

		int success;
		char infoLog[512];
		glGetShaderiv(m_VertexShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(m_VertexShader, 512, nullptr, infoLog);
			std::cout << "Error Shader Vertex compilation failed!\n" << infoLog << std::endl;
		}

		m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(m_FragmentShader, 1, &fShaderCode, nullptr);
		glCompileShader(m_FragmentShader);

		glGetShaderiv(m_FragmentShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(m_FragmentShader, 512, nullptr, infoLog);
			std::cout << "Error Shader fragment compilation failed!\n" << infoLog << std::endl;
		}

		m_ComputeShader = glCreateShader(GL_COMPUTE_SHADER);
		glShaderSource(m_ComputeShader, 1, &cShaderCode, nullptr);
		glCompileShader(m_ComputeShader);
		
		m_ShaderProgram = glCreateProgram();

		glAttachShader(m_ShaderProgram, m_VertexShader);
		glAttachShader(m_ShaderProgram, m_FragmentShader);
		glLinkProgram(m_ShaderProgram);

		glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_ShaderProgram, 512, NULL, infoLog);
		}

		m_ComputeProgram = glCreateProgram();

		glAttachShader(m_ComputeProgram, m_ComputeShader);
		glLinkProgram(m_ComputeProgram);

		glGetProgramiv(m_ComputeProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_ComputeProgram, 512, NULL, infoLog);
		}

		//glUseProgram(m_ShaderProgram); // move this to render function

		glDeleteShader(m_VertexShader);
		glDeleteShader(m_FragmentShader);
	}

	Shader::~Shader()
	{
	}

	void Shader::use()
	{
		glUseProgram(m_ShaderProgram);
	}

	void Shader::use_compute(float width, float height)
	{
		glUseProgram(m_ComputeProgram);
		glDispatchCompute(width, height, 1);
		glMemoryBarrier(GL_ALL_BARRIER_BITS);
	}

	void Shader::setUniformVec4(const std::string& name, const glm::vec4& vec4)
	{
		int location = glGetUniformLocation(m_ShaderProgram, name.c_str());
		if (location < 0)
		{
			return;
		}
		glUniform4f(location, vec4.x,vec4.y,vec4.z,vec4.w);
	}

	void Shader::setUniformMat4(const std::string& name, const glm::mat4& mat4)
	{
		int location = glGetUniformLocation(m_ShaderProgram, name.c_str());
		if (location < 0)
		{
			return;
		}
		glUniformMatrix4fv(location, 1, GL_FALSE, &mat4[0][0]);
	}
	void Shader::setUniformTexture(const std::string& name, int value)
	{
		int location = glGetUniformLocation(m_ShaderProgram, name.c_str());
		if (location < 0)
		{
			return;
		}
		glUniform1i(location, value);
	}

	void Shader::setCUniformVec3(const std::string& name, const glm::vec3& vec3)
	{
		int location = glGetUniformLocation(m_ComputeProgram, name.c_str());
		if (location < 0)
		{
			return;
		}
		glUniform3fv(location, 1, glm::value_ptr(vec3));
	}
}