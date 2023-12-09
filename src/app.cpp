#include "app.h"


namespace KarhuRayTracer
{
	App::App()
	{
		/*glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

		m_Projection = glm::perspective(glm::radians(45.0f), (float)m_Window.getWidth() / (float)m_Window.getHeight(), 0.1f, 100.0f);
		m_Model = glm::rotate(m_Model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		m_View = glm::translate(m_View, glm::vec3(0.0f, 0.0f, -3.0f));
		glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
		trans = glm::mat4(1.0f);
		trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
		std::cout << vec.x << vec.y << vec.z << std::endl;*/
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
			
			
			
			/*m_DeltaTime**/
			//float greenvalue = (sin(m_DeltaTime) / 2.0f) + 0.5f;
			//m_Shader.setUniformVec4("uni_outColor", glm::vec4(0.0f, greenvalue, 0.0f, 1.0f));
			/*m_Shader.setUniformMat4("transform", trans);
			
			
			m_Shader.setUniformMat4("model", m_Model);*/
			m_Shader.setUniformMat4("view", m_Camera.getViewMatrix());
			m_Shader.setUniformMat4("projection", m_Camera.getProjection());
			m_Renderer.rescaleFrameBuffer(m_Window.getWidth(), m_Window.getHeight());
			//m_Shader.use();
			m_Renderer.render(m_Shader,m_DeltaTime);
			m_ImguiManager.begin();
			m_ImguiManager.imguiRender();
			m_ImguiManager.end();
			//m_Camera.update(m_DeltaTime);

			m_LastFrame = currentFrame;
			m_Window.pollEvents();
			m_Window.swapBuffers();
		}
		printf("Hello World!");
	}
}
