#pragma once
#include "Sald/Core/Core.h"
#include "Light.h"
#include "Sald/Utils/CommonValues.h"
#include "OmniShadowMap.h"

namespace Sald
{
    class PointLight : public Light
    {
    public:
        SALD_API PointLight();
        SALD_API PointLight(GLuint shadowWidth, GLuint shadowHeight,
                            GLfloat near, GLfloat far,
                            GLfloat red, GLfloat green, GLfloat blue,
                            GLfloat aIntensity, GLfloat dIntensity,
                            GLfloat xPos, GLfloat yPos, GLfloat zPos,
                            GLfloat con, GLfloat lin, GLfloat exp, size_t id);
        SALD_API ~PointLight();

        SALD_API void UseLight(Shader *shader, unsigned int lightCount, unsigned int textureUnit, unsigned int offset);

        SALD_API std::vector<glm::mat4> CalculateLightTransform();
        SALD_API GLfloat GetFarPlane();
        SALD_API glm::vec3 GetPosition();

    protected:
        glm::vec3 m_Position;
        GLfloat m_Constant, m_Linear, m_Exponent;
        GLfloat m_FarPlane;
        size_t m_Id;
    };

}