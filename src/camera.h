#pragma once
#include <vector>
#include <glm/glm.hpp>

namespace KarhuRayTracer
{
	class Shader;
	class Window;

	class Camera
	{
	public:
		Camera(std::vector<Shader>& shaders, Window& m_Window, glm::vec3 position, glm::vec3 eulers, float fov);
		~Camera();

		void update(float deltatime);
		
		const glm::mat4 getViewMatrix();
		const glm::mat3 getProjectionMatrix();
	private:
		std::vector<Shader>& m_Shaders;
		Window& m_Window;
		glm::vec3 m_Position;    /* Cameras position. */
		//glm::vec3 m_Target;      /* */
		glm::vec3 m_Forward;     /* */
		glm::vec3 m_Up = glm::vec3(0.0f,0.0f,1.0f);			 /* Points upwards in world space. */
		glm::vec3 m_CameraRight; /* Points Cameras positive x-axis. */
		glm::vec3 m_CameraUp;	 /* Points Cameras positive y-axis. */
		glm::vec3 m_Eulers;

		glm::mat4 m_ViewMatrix;
		glm::mat4 m_Projection = glm::mat4(1.0f);
		float m_Fov;
		float m_CameraSpeed;
		float m_Sensitivity;
		float m_Yaw;
		float m_Pitch;

		void MouseInput(float xoffset, float yoffset, bool constrainPitch = true);
		void reCalculateProjection();
		void reCalculateviewMatrix();
	};
}