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
       m_Projection = glm::perspective(glm::radians(m_Fov), (float)m_Window.getWidth() / (float)m_Window.getHeight(), 0.1f, 100.0f);
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
        
        double mouse_x, mouse_y;
        glfwGetCursorPos(m_Window.getWindow(), &mouse_x, &mouse_y);
        glm::vec3 position = m_Position;
        if (glfwGetKey(m_Window.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
        {
            position.x += 1.0f * deltatime;
        }
        if (glfwGetKey(m_Window.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
        {
            position.x -= 1.0f * deltatime;
        }
        if (glfwGetKey(m_Window.getWindow(), GLFW_KEY_A) == GLFW_PRESS)
        {
            position.y += 1.0f * deltatime;
        }
        if (glfwGetKey(m_Window.getWindow(), GLFW_KEY_D) == GLFW_PRESS)
        {
            position.y -= 1.0f * deltatime;
        }
        if (glfwGetKey(m_Window.getWindow(), GLFW_KEY_0) == GLFW_PRESS)
        {
            glfwSetCursorPos(m_Window.getWindow(), m_Window.getWidth() / 2, m_Window.getHeight() / 2);
            glm::vec3 dEulers = { 0.0f, 0.0f, 0.0f };
            dEulers.z = -0.1f * static_cast<float>(mouse_x - m_Window.getWidth() / 2);
            dEulers.y = -0.1f * static_cast<float>(mouse_y - m_Window.getHeight() / 2);

            m_Eulers.y = fminf(89.0f, fmaxf(-89.0f, m_Eulers.y + dEulers.y));

            m_Eulers.z += dEulers.z;
            if (m_Eulers.z > 360) {
                m_Eulers.z -= 360;
            }
            else if (m_Eulers.z < 0) {
                m_Eulers.z += 360;
            }
        }

       
       /* if (glm::length(position) > 0.1f) {
            position = glm::normalize(position);
            position += 1.0f * deltatime * position.x * m_Forward;
            position += 1.0f * deltatime * position.y * m_CameraRight;
        }*/
        m_Position = position;

        
        m_Shaders[1].setCUniformVec3("CameraPosition", m_Position);
        m_Shaders[1].setCUniformVec3("CameraForward", m_Forward);
        m_Shaders[1].setCUniformVec3("CameraRight", m_CameraRight);
        m_Shaders[1].setCUniformVec3("CameraUp", m_CameraUp);
        printf("pos: %f %f %f\r", m_Position.x, m_Position.y, m_Position.z);
    }
    const glm::mat4 Camera::getViewMatrix()
    {
        reCalculateviewMatrix();
        return m_ViewMatrix;
    }
    const glm::mat3 Camera::getProjectionMatrix()
    {
        reCalculateProjection();
        return m_Projection;
    }
    void Camera::MouseInput(float xoffset, float yoffset, bool constrainPitch)
    {
        xoffset *= m_Sensitivity;
        yoffset *= m_Sensitivity;

        m_Yaw += xoffset;
        m_Pitch += yoffset;

        if (constrainPitch)
        {
            if (m_Pitch > 89.0f)
                m_Pitch = 89.0f;
            if (m_Pitch < -89.0f)
                m_Pitch = -89.0f;
        }
    }
    void Camera::reCalculateProjection()
    {
        m_Projection = glm::perspective(glm::radians(m_Fov), (float)m_Window.getWidth() / (float)m_Window.getHeight(), 0.1f, 100.0f);
    }
    void Camera::reCalculateviewMatrix()
    {
        m_ViewMatrix = glm::lookAt(m_Position, m_Position + glm::vec3(0.0f, 0.0f, -1.0f),m_CameraUp);
    }
}