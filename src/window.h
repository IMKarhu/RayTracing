#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>


namespace KarhuRayTracer
{
	class Window
	{
	public:
		Window(const char* title, uint32_t width, uint32_t height);
		Window(const Window&) = delete;
		Window(Window&&) = delete;

		~Window();

		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;

		void initWindow();
		void pollEvents();
		bool shouldClose();
		void swapBuffers();
		GLFWwindow* getContext() { return glfwGetCurrentContext(); }
		GLFWwindow* getWindow() const { return m_Window; }
	private:
		GLFWwindow* m_Window = nullptr;
		uint32_t m_Width;
		uint32_t m_Height;
		const char* m_Title;

		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	};
}
