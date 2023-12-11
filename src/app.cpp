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
			
			float currentFrame = m_Window.getGlfwTime();
			m_DeltaTime = currentFrame - m_LastFrame;

			m_Camera.update(m_DeltaTime);
			m_Renderer.render(m_Shader,m_DeltaTime);
			/*m_ImguiManager.begin();
			m_ImguiManager.imguiRender();
			m_ImguiManager.end();*/
			//m_Camera.update(m_DeltaTime);

			m_LastFrame = currentFrame;
			m_Window.pollEvents();
			m_Window.swapBuffers();
		}
		printf("Hello World!");
	}
}
