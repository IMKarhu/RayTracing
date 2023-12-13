#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad.h>


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
		void getFrameBuffer() { return glfwGetFramebufferSize(m_Window, (int*)m_Width, (int*)m_Height); }
		const float getGlfwTime() const { return glfwGetTime(); }
		GLFWwindow* getContext() { return glfwGetCurrentContext(); }
		GLFWwindow* getWindow() const { return m_Window; }
		uint32_t getWidth() const { return m_Width; }
		uint32_t getHeight() const { return m_Height; }
	private:
		GLFWwindow* m_Window = nullptr;
		uint32_t m_Width;
		uint32_t m_Height;
		const char* m_Title;

		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	};
}
