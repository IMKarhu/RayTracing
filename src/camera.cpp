#include "camera.h"
#include "shader.h"
#include "window.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

namespace KarhuRayTracer
{
    Camera::Camera(std::vector<Shader>& shaders, Window& window, glm::vec3 position, glm::vec3 eulers, float fov)
        :m_Position(position),
         m_Eulers(eulers),
         m_Fov(fov),
         m_Shaders(shaders),
         m_Window(window)
    {
        m_Yaw = 0.0f;
        m_Pitch = 0.0f;
        m_CameraSpeed = 2.0f;
        m_Forward = glm::vec3(0.0f, 0.0f, 0.0f);
        m_CameraRight = glm::vec3(0.0f, 0.0f, 0.0f);
        m_CameraUp = glm::vec3(0.0f, 0.0f, 0.0f);

        m_Projection = glm::perspective(glm::radians(m_Fov), (float)m_Window.getWidth() / (float)m_Window.getHeight(), 0.1f, 100.0f);
         
    }
    Camera::~Camera()
    {
    }
    void Camera::update(float deltatime)
    {
        float yaw = glm::radians(m_Eulers.y); //yaw -90
        float pitch = glm::radians(m_Eulers.z); // pitch 0


        m_Forward = {
            glm::cos(yaw) * glm::cos(pitch),
            glm::sin(pitch),
            glm::sin(yaw) * glm::cos(pitch)  
        };
        m_CameraRight = glm::normalize(glm::cross(m_Forward, m_Up));
        m_CameraUp = glm::cross(m_CameraRight, m_Forward);
        
        double mouse_x, mouse_y;
        glfwGetCursorPos(m_Window.getWindow(), &mouse_x, &mouse_y);
        glm::vec3 position = m_Position;
        if (glfwGetKey(m_Window.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
        {
            position += m_Forward * m_CameraSpeed * deltatime;
        }
        if (glfwGetKey(m_Window.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
        {
            position -= m_Forward * m_CameraSpeed * deltatime;
        }
        if (glfwGetKey(m_Window.getWindow(), GLFW_KEY_A) == GLFW_PRESS)
        {
            position -= m_CameraRight * m_CameraSpeed * deltatime;
        }
        if (glfwGetKey(m_Window.getWindow(), GLFW_KEY_D) == GLFW_PRESS)
        {
            position += m_CameraRight * m_CameraSpeed * deltatime;
        }
        if (glfwGetMouseButton(m_Window.getWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
            glfwSetCursorPos(m_Window.getWindow(), m_Window.getWidth() / 2, m_Window.getHeight() / 2);
            glm::vec3 dEulers = { 0.0f, 0.0f, 0.0f };
            dEulers.y = 0.1f * static_cast<float>(mouse_x - m_Window.getWidth() / 2);
            dEulers.z = -0.1f * static_cast<float>(mouse_y - m_Window.getHeight() / 2);

            m_Eulers.z = fminf(89.0f, fmaxf(-89.0f, m_Eulers.z + dEulers.z));

            m_Eulers.y += dEulers.y;
            if (m_Eulers.y > 360) {
                m_Eulers.y -= 360;
            }
            else if (m_Eulers.y < 0) {
                m_Eulers.y += 360;
            }
        }
       
        m_Position = position;

        m_Shaders[1].setCUniformVec3("CameraPosition", m_Position);
        m_Shaders[1].setCUniformVec3("CameraForward", m_Forward);
        m_Shaders[1].setCUniformVec3("CameraRight", m_CameraRight);
        m_Shaders[1].setCUniformVec3("CameraUp", m_CameraUp);
    }
}