#pragma once
#include "Sald/Core/Core.h"

#include "Sald/Renderer/Shader.h"
#include "ShadowMap.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <memory>

namespace Sald
{
    class Light
    {
    public:
        SALD_API Light();
        SALD_API Light(GLuint shadowWidth, GLuint shadowHeight,
                       GLfloat red, GLfloat green, GLfloat blue,
                       GLfloat aIntensity, GLfloat dIntensity);
        SALD_API virtual ~Light();

        // Owns its shadow map (GL framebuffer + texture), so lights move but do not copy
        Light(const Light &) = delete;
        Light &operator=(const Light &) = delete;
        Light(Light &&) noexcept = default;
        Light &operator=(Light &&) noexcept = default;

        SALD_API ShadowMap *GetShadowMap();

        SALD_API void Toggle();

    protected:
        glm::vec3 m_Color;
        GLfloat m_AmbientIntensity;
        GLfloat m_DiffuseIntensity;

        glm::mat4 m_LightProj = glm::mat4(1.0f);
        std::unique_ptr<ShadowMap> m_ShadowMap;
        bool _isOn = true;
    };

}