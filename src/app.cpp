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
			m_Window.swapBuffers();
		}
		printf("Hello World!");
	}
}
