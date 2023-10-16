#pragma once
#include <glm/glm.hpp>

namespace KarhuRayTracer
{
	class Camera
	{
	public:
		Camera(float width, float height);
		~Camera();

		const glm::mat4& getProjection() const { return m_Projection; }
	private:
		glm::vec3 m_Position;
		glm::mat4 m_Projection;
		float m_Width;
		float m_Height;
	};
}