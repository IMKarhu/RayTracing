#include "app.h"

namespace KarhuRayTracer
{
	App::App()
	{
		

		
	}
	App::~App()
	{
		
	}
	void App::run()
	{
		while (!m_Window.shouldClose())
		{
			m_Window.pollEvents();
			
			m_ImguiManager.begin();
			m_ImguiManager.imguiRender();
			m_ImguiManager.end();
			m_Shader.use();
			m_Renderer.render();
			
			m_Window.swapBuffers();
		}
		printf("Hello World!");
	}
}
