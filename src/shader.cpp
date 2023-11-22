#include "shader.h"
#include <glad/gl.h>
#include <iostream>
#include <fstream>
#include <sstream>

namespace KarhuRayTracer
{
	Shader::Shader(const char* vertexShader, const char* fragmentShader)
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			vShaderFile.open(vertexShader);
			fShaderFile.open(fragmentShader);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << e.code() << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

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

		m_ShaderProgram = glCreateProgram();

		glAttachShader(m_ShaderProgram, m_VertexShader);
		glAttachShader(m_ShaderProgram, m_FragmentShader);
		glLinkProgram(m_ShaderProgram);

		glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_ShaderProgram, 512, NULL, infoLog);
		}

		glUseProgram(m_ShaderProgram); // move this to render function

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
	void Shader::setUniformVec4(const std::string& name, const glm::vec4& vec4)
	{
		int location = glGetUniformLocation(m_ShaderProgram, name.c_str());
		if (location < 0)
		{
			return;
		}
		glUniform4f(location, vec4.x,vec4.y,vec4.z,vec4.w);
	}
}