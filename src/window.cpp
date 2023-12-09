#include "window.h"
#include "imgui.h"
#include <stdexcept>


namespace KarhuRayTracer
{
	Window::Window(const char* title, uint32_t width, uint32_t height)
		:m_Title(title),
		m_Width(width),
		m_Height(height)
	{
		initWindow();
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Window::initWindow()
	{
		
		if (!glfwInit())
		{
			throw std::runtime_error("Failed to initialize GLFW!\n");
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(static_cast<int>(m_Width), static_cast<int>(m_Height), m_Title, nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		if (!gladLoadGL())
		{
			printf("Failed to initialize OpenGL context!\n");
		}

		glViewport(0, 0, m_Width, m_Height);

		glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		
		printf("%s\n", glGetString(GL_VERSION));
	}

	void Window::pollEvents()
	{
		glfwPollEvents();
	}

	bool Window::shouldClose()
	{
		return glfwWindowShouldClose(m_Window);
	}
	void Window::swapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
	void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}
