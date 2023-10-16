#pragma once

namespace KarhuRayTracer
{
	class Window;
	class Renderer
	{
	public:
		Renderer(Window& window);
		~Renderer();

		void render();
		void update(float dt);
		unsigned int getFrameBUffer() { return fbotex; }
	private:
		Window& m_Window;
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;
		unsigned int m_FBO;
		unsigned int fbotex;
	};
}