#pragma once
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "glm/glm.hpp"

namespace KarhuRayTracer
{
	class Window;

	class ImguiManager
	{
	public:
		ImguiManager(Window& window);
		~ImguiManager();

		void begin();
		void end();
		void imguiRender();
	private:
		Window& m_Window;
		bool show_demo_window = false;
		bool show_another_window = false;
		glm::vec4 clear_color = glm::vec4(0.45f, 0.55f, 0.60f, 1.00f);
		ImGuiIO& io = ImGui::GetIO();
	};
}
