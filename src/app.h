#pragma once
#include "window.h"
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
	};
}
