#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace KarhuRayTracer
{
    Camera::Camera(float width, float height)
        :m_Position(glm::vec3(0)), m_Width(width), m_Height(height)
    {
        constexpr float fov = glm::half_pi<float>();
        m_Projection = glm::perspectiveFov(fov, m_Width, m_Height, 0.1f, 1000.0f);
    }
    Camera::~Camera()
    {
    }
}