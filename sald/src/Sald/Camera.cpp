#include "Camera.h"

Sald::Camera::Camera()
{

}
Sald::Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
    m_Position = startPosition;
    m_WorldUp = startUp;
    m_Yaw = startYaw;
    m_Pitch = startPitch;
    m_Front = glm::vec3(0.0f, 0.0f, -1.0f);

    m_MovementSpeed = startMoveSpeed;
    m_TurnSpeed = startTurnSpeed;

    Update();
}

Sald::Camera::~Camera()
{
}

void Sald::Camera::KeyControl(bool *keys, GLfloat deltaTime)
{
    GLfloat velocity = m_MovementSpeed * deltaTime;
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
    {
        m_Position += m_Front * velocity;
    }
    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
    {
        m_Position -= m_Front * velocity;
    }
    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        m_Position -= m_Right * velocity;
    }
    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        m_Position += m_Right * velocity;
    }
}
void Sald::Camera::MouseControl(GLfloat xChange, GLfloat yChange)
{
    xChange *= m_TurnSpeed;
    // TODO [MAR]: 0.5625 is 9/16, for 16:9 screens. If I wanna keep it: Make it configurable depending on the current window aspect ratio?
    yChange *= m_TurnSpeed * 0.5625;

    m_Yaw += xChange;
    m_Pitch += yChange;

    if (m_Pitch > 89.9f)
    {
        m_Pitch = 89.9f;
    }
    else if (m_Pitch < -89.9f)
    {
        m_Pitch = -89.9f;
    }

    Update();
}

glm::vec3 Sald::Camera::GetCameraPosition()
{
    return m_Position;
}
glm::vec3 Sald::Camera::GetCameraDirection()
{
    return glm::normalize(m_Front);
}

glm::mat4 Sald::Camera::CalculateViewMatrix()
{
    return glm::lookAt(m_Position, m_Position + m_Front, m_Up); // First person camera
    //return glm::lookAt(m_Position, <object to look at>, m_Up); // Look at an object, AKA: third person camera
}

void Sald::Camera::Update()
{
    m_Front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front.y = sin(glm::radians(m_Pitch));
    m_Front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(m_Front);

    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}