#pragma once
#include "Sald/Core/Core.h"
#include "Sald/Events/Event.h"

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

        SALD_API void KeyControl(GLfloat deltaTime);
        SALD_API void MouseControl(glm::vec2 mouseMoveDelta);

        SALD_API glm::vec3 GetCameraPosition();
        SALD_API glm::vec3 GetCameraDirection();

        SALD_API glm::mat4 CalculateViewMatrix();

        SALD_API float GetAspectRatio();

        SALD_API ~Camera();

    private:
        glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
        glm::vec3 m_Front = {0.0f, 0.0f, -1.0f};
        glm::vec3 m_Up = {0.0f, 1.0f, 0.0f};
        glm::vec3 m_Right = {1.0f, 0.0f, 0.0f};
        glm::vec3 m_WorldUp = {0.0f, 1.0f, 0.0f};

        GLfloat m_Yaw = -90.0f, m_Pitch = 0.0f; // looks down -Z, matching m_Front

        GLfloat m_MovementSpeed = 0.0f, m_TurnSpeed = 0.0f;

        glm::vec2 m_InitialMousePosition = {0.0f, 0.0f};
        // False until the first update has sampled the cursor
        bool m_HasMousePosition = false;

        void MoveCamera();

        float m_ViewportWidth = 1280, m_ViewportHeight = 720;
    };

}