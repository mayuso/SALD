#pragma once
#include "Sald/Core/Core.h"

#include "Sald/Renderer/Shader.h"

#include <glad/glad.h>

namespace Sald
{
    class Material
    {
    public:
        SALD_API Material();
        SALD_API Material(GLfloat sIntensity, GLfloat shine);
        SALD_API ~Material();

        SALD_API void UseMaterial(Shader *shader);

    private:
        GLfloat m_SpecularIntensity;
        GLfloat m_Shininess; // A.K.A specular power
    };

}