#include "app.h"
#include "gameObject.h"



namespace KarhuRayTracer
{
	App::App()
	{
		m_Shaders.push_back(Shader{ "../shaders/VertexShader.vert","../shaders/FragmentShader.frag" });
		m_Shaders.push_back(Shader{ "../shaders/RayTracingKernel.comp" });
		m_Shaders.push_back(Shader{ "../shaders/SkyBox.vert", "../shaders/SkyBox.frag" });

		m_Object.m_Position = glm::vec3(3.0f, 0.0f, 0.0f);
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

			//m_Camera.update(m_DeltaTime);
			m_Renderer.render(m_Shaders,m_Camera, m_Object, m_DeltaTime);
			m_ImguiManager.begin();
			m_ImguiManager.imguiRender(m_Object.m_Position);
			m_ImguiManager.end();
			//m_Camera.update(m_DeltaTime);

			m_LastFrame = currentFrame;
			m_Window.pollEvents();
			m_Window.swapBuffers();
		}
		printf("Hello World!");
	}
}
