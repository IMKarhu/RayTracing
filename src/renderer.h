#pragma once
#include "gameObject.h"
#include <memory>

namespace KarhuRayTracer
{
	class Window;
	class Shader;
	class Renderer
	{
	public:
		Renderer(Window& window);
		~Renderer();

		void render(Shader& m_Shader, float dt);
		void update(float dt);
		void rescaleFrameBuffer(float width, float height);

		unsigned int getFrameBuffer() { return fbotex; }
	private:
		Window& m_Window;
		std::shared_ptr<Box> m_Box;
		unsigned int m_VAO;
		unsigned int m_VBO; /* Vertex buffer object. */
		unsigned int m_EBO; /* Element buffer object. */
		unsigned int m_FBO;
		unsigned int m_RBO;
		unsigned int fbotex;
		unsigned int texture;
	};
}