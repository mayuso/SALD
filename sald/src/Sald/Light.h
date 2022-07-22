#pragma once
#include "Core.h"

#include "Shader.h"
#include "ShadowMap.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace Sald
{
    class Light
    {
    public:
        SALD_API Light();
        SALD_API Light(GLuint shadowWidth, GLuint shadowHeight,
                       GLfloat red, GLfloat green, GLfloat blue,
                       GLfloat aIntensity, GLfloat dIntensity);
        SALD_API ~Light();

        SALD_API ShadowMap *GetShadowMap();

        SALD_API void UseLight(Shader *shader);
        SALD_API void Toggle();

    protected:
        glm::vec3 m_Color;
        GLfloat m_AmbientIntensity;
        GLfloat m_DiffuseIntensity;

        glm::mat4 m_LightProj;
        ShadowMap *m_ShadowMap;
        bool _isOn;
    };

}