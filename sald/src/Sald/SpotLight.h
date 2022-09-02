#pragma once
#include "Core.h"
#include "PointLight.h"

#include "CommonValues.h"

namespace Sald
{
    class SpotLight : public PointLight
    {
    public:
        SALD_API SpotLight();
        SALD_API SpotLight(GLuint shadowWidth, GLuint shadowHeight,
                           GLfloat near, GLfloat far,
                           GLfloat red, GLfloat green, GLfloat blue,
                           GLfloat aIntensity, GLfloat dIntensity,
                           GLfloat xPos, GLfloat yPos, GLfloat zPos,
                           GLfloat xDir, GLfloat yDur, GLfloat zDir,
                           GLfloat con, GLfloat lin, GLfloat exp, GLfloat edg,
                           size_t id);
        SALD_API ~SpotLight();

        SALD_API void UseLight(Shader *shader, unsigned int lightCount, unsigned int textureUnit, unsigned int offset);

        SALD_API void Move(glm::vec3 pos, glm::vec3 dir);

    private:
        glm::vec3 m_Direction;
        GLfloat m_Edge, m_ProcEdge;
    };

}