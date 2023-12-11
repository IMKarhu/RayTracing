#pragma once
#include <glm/glm.hpp>

namespace KarhuRayTracer
{
	class Shader;
	class Window;

	class Camera
	{
	public:
		Camera(Shader& shader, Window& m_Window, glm::vec3 position, glm::vec3 eulers);
		~Camera();

		void update(float deltatime);
		
	private:
		Shader& m_Shader;
		Window& m_Window;
		glm::vec3 m_Position;    /* Cameras position. */
		//glm::vec3 m_Target;      /* */
		glm::vec3 m_Forward;     /* */
		glm::vec3 m_Up = glm::vec3(0.0f,0.0f,1.0f);			 /* Points upwards in world space. */
		glm::vec3 m_CameraRight; /* Points Cameras positive x-axis. */
		glm::vec3 m_CameraUp;	 /* Points Cameras positive y-axis. */
		glm::vec3 m_Eulers;

		float m_Fov;
	};
}