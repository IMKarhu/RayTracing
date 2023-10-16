#include "imguiManager.h"
#include "window.h"
#include "renderer.h"

namespace KarhuRayTracer
{
	ImguiManager::ImguiManager(Window& window, Renderer& renderer)
		:m_Window(window), m_Renderer(renderer)
	{
		(void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
		
		ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 460 core");
	}
	ImguiManager::~ImguiManager()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
	void ImguiManager::begin()
	{
		/*ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);*/
		//ImGuiID dockspaceId = ImGui::GetID("dockingWindow");
		//ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
	void ImguiManager::end()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = m_Window.getContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}
	void ImguiManager::imguiRender()
	{
		//dockSpace(open);
		//viewport(open);
		ImGui::ShowDemoWindow(&show_demo_window);
	}
	void ImguiManager::dockSpace(bool& show)
	{
		static bool optFullSreenPersistant = true;
		bool optFullScreen = optFullSreenPersistant;

		static ImGuiDockNodeFlags dockSpaceFlags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (optFullScreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
						   ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

			ImGui::Begin("DockSpace demo", &show, windowFlags);
			ImGui::PopStyleVar(2);

			ImGui::DockSpace(ImGui::GetID("DockSpace"));

			ImGui::End();
		}
	}
	void ImguiManager::viewport(bool& show)
	{
		ImGui::Begin("ViewPort", &show, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		ImVec2 windowSize = ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight());/* make a proper size for this. */
		ImVec2 windowPos = ImVec2(0.0f, 0.0f);/* make a proper position for this. */

		//ImGui::GetCursorPos()
		int textureId = m_Renderer.getFrameBUffer();
		//ImTextureID texId = m_Window.getFrameBuffer();
		ImGui::Image((void*)textureId, windowSize);
		ImGui::End();
	}
}


//if (show_demo_window)
//{
//	ImGui::ShowDemoWindow(&show_demo_window);
//}
//
//{
//	static float f = 0.0f;
//	static int counter = 0;
//
//	ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
//
//	ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
//	ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
//	ImGui::Checkbox("Another Window", &show_another_window);
//
//	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);          // Edit 1 float using a slider from 0.0f to 1.0f
//	//ImGui::SliderFloat3("translation", &rectangle.getPosition().x, 0.0f, 800.0f);
//	//ImGui::SliderFloat3("scale", &rectangle.getScale().x, 0.0f, 800.0f);
//	ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
//
//	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
//		counter++;
//	ImGui::SameLine();
//	ImGui::Text("counter = %d", counter);
//
//	//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
//	ImGui::End();
//}
//if (show_another_window)
//{
//	ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
//	ImGui::Text("Hello from another window!");
//	if (ImGui::Button("Close Me"))
//		show_another_window = false;
//	ImGui::End();
//}