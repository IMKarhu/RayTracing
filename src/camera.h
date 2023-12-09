#pragma once
#include <glm/glm.hpp>

namespace KarhuRayTracer
{
	class Camera
	{
	public:
		Camera(float width, float height);
		~Camera();

		void update(float deltatime);
		const glm::mat4& getProjection() const { return m_ProjectionMatrix; }
		const glm::mat4& getViewMatrix() const { return m_ViewMatrix; }
	private:
		glm::vec3 m_Position;    /* Cameras position. */
		glm::vec3 m_Target;      /* */
		glm::vec3 m_Direction;   /* */
		glm::vec3 m_Up;			 /* Points upwards in world space. */
		glm::vec3 m_CameraRight; /* Points Cameras positive x-axis. */
		glm::vec3 m_CameraUp;	 /* Points Cameras positive y-axis. */

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		float m_Width;
		float m_Height;
	};
}