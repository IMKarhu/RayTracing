#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad.h>
#include <glm/glm.hpp>
#include <functional>
#include <map>


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
		const float getGlfwTime() const { return (float)glfwGetTime(); }
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
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouse_callback(GLFWwindow* window, int button, int action, int mods);
	};

	/*class Input
	{
	public:
		using Callback = std::function<void()>;

		Input() {}

		static void addBinding(int key, const Callback& callback, Input input);

		void onPress(int key, Input input);
	private:
		std::map<int, std::vector<Callback>> m_Callbacks;
	};*/
}
