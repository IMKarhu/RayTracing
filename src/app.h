#pragma once
#include "window.h"
#include "imguiManager.h"
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
		ImguiManager m_ImguiManager{ m_Window };
	};
}
