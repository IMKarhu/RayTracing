#pragma once
#include "window.h"
#include "imguiManager.h"
#include "renderer.h"
#include "shader.h"
#include "glm/glm.hpp"
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
		Renderer m_Renderer{ m_Window };
		ImguiManager m_ImguiManager{ m_Window, m_Renderer };
		Shader m_Shader{ "../shaders/VertexShader.vert","../shaders/FragmentShader.frag" };

		float timer;
	};
}
