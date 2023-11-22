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
			timer = m_Window.getGlfwTime();
			float greenvalue = (sin(timer) / 2.0f) + 0.5f;
			m_Shader.setUniformVec4("uni_outColor", glm::vec4(0.0f, greenvalue, 0.0f, 1.0f));
			m_Renderer.render();
			
			m_Window.swapBuffers();
		}
		printf("Hello World!");
	}
}
