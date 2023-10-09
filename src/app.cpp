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
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_ImguiManager.begin();
			m_ImguiManager.imguiRender();
			m_ImguiManager.end();
			m_Window.swapBuffers();
		}
		printf("Hello World!");
	}
}
