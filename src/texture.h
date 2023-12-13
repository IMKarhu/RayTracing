#pragma once
#include <string>
#include <vector>

namespace KarhuRayTracer
{
	class Texture
	{
	public:
		Texture();

		void createTexture();
		void createCubeMap();
		void bind();
	private:
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;
		unsigned int m_TextureID;
		std::string m_FilePath;
	};

	
}

