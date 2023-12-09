#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace KarhuRayTracer
{
    Camera::Camera(float width, float height)
        :m_Position(glm::vec3(0.0f,0.0f,0.3f)), m_Target(glm::vec3(0.0f)), m_CameraUp(glm::vec3(0.0f,1.0f,0.0f)), m_Width(width), m_Height(height)
    {
        m_Direction = glm::normalize(m_Position - m_Target);
        m_CameraRight = glm::normalize(glm::cross(m_CameraUp, m_Direction));
        m_CameraUp = glm::cross(m_Direction, m_CameraRight);

        m_ViewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
                           glm::vec3(0.0f, 0.0f, 0.0f),
                              glm::vec3(0.0f, 1.0f, 0.0f));
        //constexpr float fov = glm::half_pi<float>();
        m_ProjectionMatrix = glm::perspectiveFov(glm::radians(45.0f), width, height, 0.1f, 100.0f);
    }
    Camera::~Camera()
    {
    }
    void Camera::update(float deltatime)
    {
        //TODO
    }
}