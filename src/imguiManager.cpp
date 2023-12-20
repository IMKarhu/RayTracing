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
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGuiID dockspaceId = ImGui::GetID("dockingWindow");
		ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);*/
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
	void ImguiManager::imguiRender(std::vector<Object>& objects, PointLight& light, float deltatime)
	{
		//dockSpace(open);
		//viewport(open);
		ObjectSettings(objects,light, deltatime);
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
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
						   ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

			ImGui::Begin("DockSpace demo", &show, windowFlags);
			ImGui::PopStyleVar(3);

			ImGui::DockSpace(ImGui::GetID("DockSpace"));

			ImGui::End();
		}
	}

	void ImguiManager::viewport(bool& show)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::Begin("ViewPort", &show, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		ImGui::PopStyleVar(2);
		ImVec2 windowSize = viewportSize();
		ImVec2 windowPos = centeredviewport(windowSize);

		//ImGui::GetCursorPos()
		//int textureId = m_Renderer.getFrameBuffer();
		ImGui::SetCursorPos(windowPos);
		//ImTextureID texId = m_Window.getFrameBuffer();
		//ImGui::Image((void*)textureId, windowSize,ImVec2{0,1},ImVec2{1,0});
		ImGui::End();
	}

	void ImguiManager::ObjectSettings(std::vector<Object>& objects,PointLight& light, float deltatime)
	{
		ImGui::Begin("Settings");
		ImGui::Text("Render: %.3fms", deltatime);
		for (size_t i = 0; i < objects.size(); i++)
		{
			ImGui::PushID(i);

			ImGui::DragFloat3("Position", glm::value_ptr(objects[i].m_Position), 0.1f);
			ImGui::ColorEdit3("Albeido", glm::value_ptr(objects[i].m_Material.m_Albeido));
			ImGui::SliderFloat("Radius", &objects[i].m_Radius, 0.1f, 10.0f);

			ImGui::Separator();
			ImGui::PopID();
		}
		ImGui::DragFloat3("Position", glm::value_ptr(light.m_Position), 0.1f);
		ImGui::ColorEdit3("Albeido", glm::value_ptr(light.m_Color));
		ImGui::SliderFloat("Radius", &light.m_Radius, 0.1f, 10.0f);
		
		ImGui::End();
	}

	ImVec2 ImguiManager::viewportSize()
	{
		m_ViewportSize = ImGui::GetContentRegionAvail();
		/*windowSize.x -= ImGui::GetScrollX();
		windowSize.y -= ImGui::GetScrollY();
		float width = windowSize.x;
		float height = width / ((float)m_Window.getWidth() / (float)m_Window.getHeight());
		if (height > windowSize.y)
		{
			height = windowSize.y;
			width = height * ((float)m_Window.getWidth() / (float)m_Window.getHeight());
		}*/
		return ImVec2(m_ViewportSize);
	}
	ImVec2 ImguiManager::centeredviewport(ImVec2 aspect)
	{
		ImVec2 windowSize = ImVec2();
		windowSize = ImGui::GetContentRegionAvail();
		windowSize.x -= ImGui::GetScrollX();
		windowSize.y -= ImGui::GetScrollY();

		float viewportX = (windowSize.x / 2.0f) - (aspect.x / 2.0f);
		float viewportY = (windowSize.y / 2.0f) - (aspect.y / 2.0f);
		return ImVec2(viewportX, viewportY);
	}
}
