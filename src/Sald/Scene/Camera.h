#pragma once
#include "Sald/Core/Core.h"
#include "Sald/Events/Event.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <functional>

namespace Sald
{
    class Camera
    {
    public:
        // Fly: moves along the view direction (free camera).
        // Walk: moves on the ground plane and keeps the eye at a fixed height
        // above the ground returned by the ground height function.
        enum class Mode
        {
            Fly,
            Walk
        };

        // Ground height (world Y) at world position (x, z)
        using GroundHeightFn = std::function<float(float x, float z)>;
        // Where a move from `from` to `to` may end; return `to` when nothing is in the way
        using CollisionFn = std::function<glm::vec3(const glm::vec3 &from, const glm::vec3 &to)>;

        SALD_API Camera();
        SALD_API Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

        SALD_API void OnUpdate(GLfloat deltaTime);

        SALD_API void KeyControl(GLfloat deltaTime);
        SALD_API void MouseControl(glm::vec2 mouseMoveDelta);

        SALD_API void SetMode(Mode mode);
        SALD_API Mode GetMode() const;
        SALD_API void SetGroundHeightFunction(GroundHeightFn groundHeight);
        SALD_API void SetCollisionFunction(CollisionFn collision);
        SALD_API void SetEyeHeight(GLfloat eyeHeight);
        // Speed multiplier while Left Shift is held
        SALD_API void SetRunMultiplier(GLfloat multiplier);
        // Off while the cursor is free, so moving it over the window does not turn the camera
        SALD_API void SetMouseLookEnabled(bool enabled);
        SALD_API void SetPosition(glm::vec3 position);
        // Degrees; yaw -90 looks down -Z, pitch is clamped to +-89.9
        SALD_API void SetRotation(GLfloat yaw, GLfloat pitch);

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
        GLfloat m_RunMultiplier = 2.0f;

        Mode m_Mode = Mode::Fly;
        GroundHeightFn m_GroundHeight;
        CollisionFn m_Collision;
        GLfloat m_EyeHeight = 1.7f;

        bool m_MouseLookEnabled = true;
        glm::vec2 m_InitialMousePosition = {0.0f, 0.0f};
        // False until the first update has sampled the cursor
        bool m_HasMousePosition = false;

        void MoveCamera();
        void SnapToGround();

        float m_ViewportWidth = 1280, m_ViewportHeight = 720;
    };

}
