#pragma once
#include "Sald/sald_api.h"

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
        SALD_API ~Camera();

        SALD_API void KeyControl(bool *keys, GLfloat deltaTime);
        SALD_API void MouseControl(GLfloat xChange, GLfloat yChange);

        SALD_API glm::vec3 GetCameraPosition();
        SALD_API glm::vec3 GetCameraDirection();

        SALD_API glm::mat4 CalculateViewMatrix();

    private:
        glm::vec3 m_Position, m_Front, m_Up, m_Right, m_WorldUp;

        GLfloat m_Yaw, m_Pitch;

        GLfloat m_MovementSpeed, m_TurnSpeed;

        void Update();
    };

}