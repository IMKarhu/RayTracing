#pragma once
#include "gameObject.h"
#include <vector>

namespace KarhuRayTracer
{
	class Window;
	class Shader;
	class Camera;

	class Renderer
	{
	public:
		Renderer(Window& window);
		~Renderer();

		void render(std::vector<Shader>& shaders, Camera& camera, std::vector<Object> objects, PointLight& light, unsigned int textureID, float dt);

		unsigned int getTexture() { return m_Texture; }
	private:
		Window& m_Window;
		
		unsigned int m_VAO;
		unsigned int m_VBO; /* Vertex buffer object. */
		unsigned int m_EBO; /* Element buffer object. */
		unsigned int m_Texture;
	};
}