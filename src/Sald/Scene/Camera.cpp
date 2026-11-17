#include "saldpch.h"
#include "Sald/Scene/Camera.h"

#include "Sald/Core/Input.h"

#include <utility>

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
    if (m_MouseLookEnabled)
    {
        const glm::vec2 mouse = Input::GetMousePosition();
        // There is no previous position on the first update: measuring from (0, 0)
        // would swing the camera by wherever the cursor happens to be
        if (!m_HasMousePosition)
        {
            m_InitialMousePosition = mouse;
            m_HasMousePosition = true;
        }
        glm::vec2 mouseMoveDelta = (mouse - m_InitialMousePosition) * 0.01f;
        m_InitialMousePosition = mouse;
        MouseControl(mouseMoveDelta);
    }

    KeyControl(deltaTime);
}

void Sald::Camera::KeyControl(GLfloat deltaTime)
{
    GLfloat velocity = m_MovementSpeed * deltaTime;
    if (Input::IsKeyPressed(Key::LeftShift))
        velocity *= m_RunMultiplier;

    glm::vec3 forward = m_Front;
    glm::vec3 right = m_Right;
    if (m_Mode == Mode::Walk)
    {
        // Looking up or down must not lift the walker off the ground or slow them down
        forward = glm::vec3(m_Front.x, 0.0f, m_Front.z);
        forward = glm::length(forward) > 0.0f ? glm::normalize(forward) : glm::vec3(0.0f, 0.0f, -1.0f);
        right = glm::normalize(glm::cross(forward, m_WorldUp));
    }

    glm::vec3 move(0.0f);
    if (Input::IsKeyPressed(Key::W) || Input::IsKeyPressed(Key::Up))
        move += forward;
    if (Input::IsKeyPressed(Key::S) || Input::IsKeyPressed(Key::Down))
        move -= forward;
    if (Input::IsKeyPressed(Key::A) || Input::IsKeyPressed(Key::Left))
        move -= right;
    if (Input::IsKeyPressed(Key::D) || Input::IsKeyPressed(Key::Right))
        move += right;

    // Normalised so moving diagonally is not faster than moving straight
    if (glm::length(move) > 0.0f)
    {
        glm::vec3 target = m_Position + glm::normalize(move) * velocity;
        if (m_Mode == Mode::Walk && m_Collision)
            target = m_Collision(m_Position, target);
        m_Position = target;
    }

    if (m_Mode == Mode::Walk)
        SnapToGround();
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

void Sald::Camera::SetMode(Mode mode)
{
    m_Mode = mode;
    if (m_Mode == Mode::Walk)
        SnapToGround();
}

Sald::Camera::Mode Sald::Camera::GetMode() const
{
    return m_Mode;
}

void Sald::Camera::SetGroundHeightFunction(GroundHeightFn groundHeight)
{
    m_GroundHeight = std::move(groundHeight);
}

void Sald::Camera::SetCollisionFunction(CollisionFn collision)
{
    m_Collision = std::move(collision);
}

void Sald::Camera::SetEyeHeight(GLfloat eyeHeight)
{
    m_EyeHeight = eyeHeight;
}

void Sald::Camera::SetRunMultiplier(GLfloat multiplier)
{
    m_RunMultiplier = multiplier;
}

void Sald::Camera::SetMouseLookEnabled(bool enabled)
{
    m_MouseLookEnabled = enabled;
    // Re-sample on the next update, otherwise the cursor travel while look was
    // off would be applied as one big turn
    m_HasMousePosition = false;
}

void Sald::Camera::SetPosition(glm::vec3 position)
{
    m_Position = position;
    if (m_Mode == Mode::Walk)
        SnapToGround();
}

void Sald::Camera::SetRotation(GLfloat yaw, GLfloat pitch)
{
    m_Yaw = yaw;
    m_Pitch = glm::clamp(pitch, -89.9f, 89.9f);
    MoveCamera();
}

void Sald::Camera::SnapToGround()
{
    float ground = m_GroundHeight ? m_GroundHeight(m_Position.x, m_Position.z) : 0.0f;
    m_Position.y = ground + m_EyeHeight;
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
