#pragma once
#include "Core.h"
#include "Events/Event.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Sald
{
    class Camera
    {
    public:
        SALD_API Camera();
        SALD_API Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

        SALD_API void OnUpdate(GLfloat deltaTime);
        SALD_API void OnEvent(Event &e);

        SALD_API void KeyControl(GLfloat deltaTime);
        SALD_API void MouseControl(glm::vec2 mouseMoveDelta);

        SALD_API glm::vec3 GetCameraPosition();
        SALD_API glm::vec3 GetCameraDirection();

        SALD_API glm::mat4 CalculateViewMatrix();

        SALD_API ~Camera();

    private:
        glm::vec3 m_Position, m_Front, m_Up, m_Right, m_WorldUp;

        GLfloat m_Yaw, m_Pitch;

        GLfloat m_MovementSpeed, m_TurnSpeed;

        glm::vec2 m_InitialMousePosition = {0.0f, 0.0f};

        void MoveCamera();
    };

}