#pragma once
#include "window.h"
#include "imguiManager.h"
#include "renderer.h"
#include "shader.h"
#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace KarhuRayTracer
{
	class App
	{
	public:
		App();
		~App();

		void run();
	private:
		Window m_Window{ "Karhu RayTracer", 800, 600 };
		Shader m_Shader{ "../shaders/VertexShader.vert","../shaders/FragmentShader.frag", "../shaders/RayTracingKernel.comp"};
		Camera m_Camera{ m_Shader, m_Window, glm::vec3(0.0f,0.0f,0.0), glm::vec3(0.0f,0.0f,1.0f) };
		Renderer m_Renderer{ m_Window };
		ImguiManager m_ImguiManager{ m_Window, m_Renderer };

		float m_DeltaTime = 0.0f;
		float m_LastFrame = 0.0f;
		glm::mat4 trans;
		glm::mat4 m_Projection;
		glm::mat4 m_Model = glm::mat4(1.0f);
		glm::mat4 m_View = glm::mat4(1.0f);
	};
}
