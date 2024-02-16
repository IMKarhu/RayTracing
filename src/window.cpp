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
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(static_cast<int>(m_Width), static_cast<int>(m_Height), m_Title, nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		

		if (!gladLoadGL())
		{
			printf("Failed to initialize OpenGL context!\n");
		}
		glEnable(GL_MULTISAMPLE);
		glViewport(0, 0, m_Width, m_Height);

		glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_callback);
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

	void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
	}
	
	void Window::mouse_callback(GLFWwindow* window, int button, int action, int mods) // int button = button, int action = press or release, int mods = modifiers like ctrl or shift
	{
		
		if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}

	/* Input class functions. */

	/*void Input::addBinding(int key, const Callback& callback, Input input)
	{
		input.m_Callbacks[key].push_back(callback);
	}

	void Input::onPress(int key, Input input)
	{
		for (Callback& callback : input.m_Callbacks[key])
		{
			callback();
		}
	}*/
}
