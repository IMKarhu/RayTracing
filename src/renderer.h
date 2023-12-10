#pragma once
#include "gameObject.h"
#include "frameBuffer.h"
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

		//unsigned int getFrameBuffer() { return fbotex; }
	private:
		Window& m_Window;
		//FrameBuffer m_FrameBuffer{};
		unsigned int m_VAO;
		unsigned int m_VBO; /* Vertex buffer object. */
		unsigned int m_EBO; /* Element buffer object. */
		
		unsigned int texture;
	};
}