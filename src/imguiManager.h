#pragma once
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "glm/glm.hpp"

namespace KarhuRayTracer
{
	class Window;
	class Renderer;

	class ImguiManager
	{
	public:
		ImguiManager(Window& window, Renderer& renderer);
		~ImguiManager();

		void begin();
		void end();
		void imguiRender();
		void dockSpace(bool &show);
		void viewport(bool& show);
	private:
		Window& m_Window;
		Renderer& m_Renderer;
		bool show_demo_window = true;
		bool open = true;
		bool show_another_window = false;
		glm::vec4 clear_color = glm::vec4(0.45f, 0.55f, 0.60f, 1.00f);
		ImGuiIO& io = ImGui::GetIO();
	};
}
