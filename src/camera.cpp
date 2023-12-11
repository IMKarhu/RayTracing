#include "camera.h"
#include "shader.h"
#include "window.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

namespace KarhuRayTracer
{
    Camera::Camera(Shader& shader, Window& window, glm::vec3 position, glm::vec3 eulers)
        :m_Position(position),
         m_Eulers(eulers),
         m_Fov(45.0f),
         m_Shader(shader),
         m_Window(window)
    {
       
    }
    Camera::~Camera()
    {
    }
    void Camera::update(float deltatime)
    {
        float theta = glm::radians(m_Eulers.z);
        float phi = glm::radians(m_Eulers.y);

        m_Forward = {
            glm::cos(theta) * glm::cos(phi),
            glm::sin(theta) * glm::cos(phi),
            glm::sin(phi)
        };
        m_CameraRight = glm::normalize(glm::cross(m_Forward, m_Up));
        m_CameraUp = glm::cross(m_CameraRight, m_Forward);
        
        glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f);
        if (glfwGetKey(m_Window.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
        {
            position.x += 1.0f;
        }
        if (glfwGetKey(m_Window.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
        {
            position.x -= 1.0f;
        }
        if (glfwGetKey(m_Window.getWindow(), GLFW_KEY_A) == GLFW_PRESS)
        {
            position.y -= 1.0f;
        }
        if (glfwGetKey(m_Window.getWindow(), GLFW_KEY_D) == GLFW_PRESS)
        {
            position.y += 1.0f;
        }

        if (glm::length(position) > 0.1f) {
            position = glm::normalize(position);
            position += 1.0f * deltatime * position.x * m_Forward;
            position += 1.0f * deltatime * position.y * m_CameraRight;
        }
        m_Position = position;
        m_Shader.setCUniformVec3("CameraPosition", m_Position);
        m_Shader.setCUniformVec3("CameraForward", m_Forward);
        m_Shader.setCUniformVec3("CameraRight", m_CameraRight);
        m_Shader.setCUniformVec3("CameraUp", m_CameraUp);
        printf("pos: %f %f %f\r", m_Position.x, m_Position.y, m_Position.z);
    }
}