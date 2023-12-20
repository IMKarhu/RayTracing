#include "app.h"
#include "gameObject.h"



namespace KarhuRayTracer
{
	App::App()
	{
		m_Shaders.push_back(Shader{ "../shaders/VertexShader.vert","../shaders/FragmentShader.frag" });
		m_Shaders.push_back(Shader{ "../shaders/RayTracingKernel.comp" });
		m_Shaders.push_back(Shader{ "../shaders/SkyBox.vert", "../shaders/SkyBox.frag" });

		m_Materials.push_back({ glm::vec3(1.0, 0.75, 0.5), glm::vec3(0.0f),glm::vec3(0.0f)});
		m_Materials.push_back({ glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0f),glm::vec3(0.0f)});
		m_Materials.push_back({ glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.0f),glm::vec3(0.0f)});

		m_Objects.push_back({ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0, 0.0, 0.0), 1.0f, 0, m_Materials[0]});
		m_Objects.push_back({ glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(2.0, 0.0, 0.0), 2.0f, 0, m_Materials[1] });
		m_Objects.push_back({ glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(2.0, 1.0, 1.0), 2.0f, 1, m_Materials[2],
									glm::vec3(1.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f),glm::vec3(0.0f,0.0f,1.0f),-10,10,-10,10});

		m_PointLight.m_Position = glm::vec3(0.0f, 0.0f, -1.0f);
		m_PointLight.m_Color = glm::vec3(0.0f, 0.0f, 0.0f);
		m_PointLight.m_Radius = 1.0f;
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
			m_Renderer.render(m_Shaders,m_Camera, m_Objects,m_PointLight, m_DeltaTime);
			m_ImguiManager.begin();
			m_ImguiManager.imguiRender(m_Objects,m_PointLight, m_DeltaTime);
			m_ImguiManager.end();
			//m_Camera.update(m_DeltaTime);

			m_LastFrame = currentFrame;
			m_Window.pollEvents();
			m_Window.swapBuffers();
		}
		printf("Hello World!");
	}
}
