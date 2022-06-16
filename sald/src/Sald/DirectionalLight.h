#pragma once
#include "Sald/sald_api.h"
#include "Sald/Light.h"

namespace Sald
{
    class DirectionalLight : public Light
    {
    public:
        SALD_API DirectionalLight();
        SALD_API DirectionalLight(GLuint shadowWidth, GLuint shadowHeight,
                                     GLfloat red, GLfloat green, GLfloat blue,
                                     GLfloat aIntensity, GLfloat dIntensity,
                                     GLfloat xDir, GLfloat yDir, GLfloat zDir);
        SALD_API ~DirectionalLight();

        SALD_API void UseLight(Shader *shader);

        SALD_API glm::mat4 CalculateLightTransform();

    private:
        glm::vec3 m_Direction;
    };

}