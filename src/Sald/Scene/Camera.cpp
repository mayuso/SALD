#include "saldpch.h"
#include "Sald/Scene/Camera.h"

#include "Sald/Core/Input.h"

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

    MoveCamera();
}

Sald::Camera::~Camera()
{
}

void Sald::Camera::OnUpdate(GLfloat deltaTime)
{
    const glm::vec2 &mouse{Input::GetMouseX(), Input::GetMouseY()};
    glm::vec2 mouseMoveDelta = (mouse - m_InitialMousePosition) * 0.01f;
    m_InitialMousePosition = mouse;

    KeyControl(deltaTime);
    MouseControl(mouseMoveDelta);
}

void Sald::Camera::KeyControl(GLfloat deltaTime)
{
    GLfloat velocity = m_MovementSpeed * deltaTime;
    if (Input::IsKeyPressed(Key::W) || Input::IsKeyPressed(Key::Up))
    {
        m_Position += m_Front * velocity;
    }
    if (Input::IsKeyPressed(Key::S) || Input::IsKeyPressed(Key::Down))
    {
        m_Position -= m_Front * velocity;
    }
    if (Input::IsKeyPressed(Key::A) || Input::IsKeyPressed(Key::Left))
    {
        m_Position -= m_Right * velocity;
    }
    if (Input::IsKeyPressed(Key::D) || Input::IsKeyPressed(Key::Right))
    {
        m_Position += m_Right * velocity;
    }
}
void Sald::Camera::MouseControl(glm::vec2 mouseMoveDelta)
{
    mouseMoveDelta.x *= m_TurnSpeed;
    // This makes vertical mouse movement less sensitive. Still not sure if it feels right.
    // mouseMoveDelta.y *= -m_TurnSpeed * (m_ViewportHeight / m_ViewportWidth);
    mouseMoveDelta.y *= -m_TurnSpeed;
    m_Yaw += mouseMoveDelta.x;
    m_Pitch += mouseMoveDelta.y;

    if (m_Pitch > 89.9f)
    {
        m_Pitch = 89.9f;
    }
    else if (m_Pitch < -89.9f)
    {
        m_Pitch = -89.9f;
    }

    MoveCamera();
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
    // return glm::lookAt(m_Position, <object to look at>, m_Up); // Look at an object, AKA: third person camera
}

void Sald::Camera::MoveCamera()
{
    m_Front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front.y = sin(glm::radians(m_Pitch));
    m_Front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(m_Front);

    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

float Sald::Camera::GetAspectRatio()
{
    return m_ViewportWidth / m_ViewportHeight;
}
