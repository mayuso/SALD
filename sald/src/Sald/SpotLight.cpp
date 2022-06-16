#include "SpotLight.h"

Sald::SpotLight::SpotLight() : PointLight()
{
    m_Direction = glm::vec3(0.0f, -1.0f, 0.0f);
    m_Edge = 0.0f;
}

Sald::SpotLight::SpotLight(GLuint shadowWidth, GLuint shadowHeight,
                           GLfloat near, GLfloat far,
                           GLfloat red, GLfloat green, GLfloat blue,
                           GLfloat aIntensity, GLfloat dIntensity,
                           GLfloat xPos, GLfloat yPos, GLfloat zPos,
                           GLfloat xDir, GLfloat yDir, GLfloat zDir,
                           GLfloat con, GLfloat lin, GLfloat exp, GLfloat edg,
                           size_t id) : PointLight(shadowWidth, shadowHeight, near, far, red, green, blue, aIntensity, dIntensity, xPos, yPos, zPos, con, lin, exp, id)
{
    m_Direction = glm::normalize(glm::vec3(xDir, yDir, zDir));
    m_Edge = edg;
    m_ProcEdge = cosf(glm::radians(m_Edge));
}

Sald::SpotLight::~SpotLight()
{
}

void Sald::SpotLight::UseLight(Shader *shader, unsigned int lightCount, unsigned int textureUnit, unsigned int offset)
{
    if (lightCount > MAX_SPOT_LIGHTS)
        lightCount = MAX_SPOT_LIGHTS;
    shader->SetInt("spotLightCount", lightCount);

    char locBuff[100] = {'\0'};

    snprintf(locBuff, sizeof(locBuff), "spotLights[%zu].base.base.color", m_Id);
    shader->SetFloat3(locBuff, m_Color.x, m_Color.y, m_Color.z);

    if (_isOn)
    {
        snprintf(locBuff, sizeof(locBuff), "spotLights[%zu].base.base.ambientIntensity", m_Id);
        shader->SetFloat(locBuff, m_AmbientIntensity);

        snprintf(locBuff, sizeof(locBuff), "spotLights[%zu].base.base.diffuseIntensity", m_Id);
        shader->SetFloat(locBuff, m_DiffuseIntensity);
    }
    else
    {
        snprintf(locBuff, sizeof(locBuff), "spotLights[%zu].base.base.ambientIntensity", m_Id);
        shader->SetFloat(locBuff, 0.0f);

        snprintf(locBuff, sizeof(locBuff), "spotLights[%zu].base.base.diffuseIntensity", m_Id);
        shader->SetFloat(locBuff, 0.0f);
    }

    snprintf(locBuff, sizeof(locBuff), "spotLights[%zu].base.position", m_Id);
    shader->SetFloat3(locBuff, m_Position.x, m_Position.y, m_Position.z);

    snprintf(locBuff, sizeof(locBuff), "spotLights[%zu].base.constant", m_Id);
    shader->SetFloat(locBuff, m_Constant);

    snprintf(locBuff, sizeof(locBuff), "spotLights[%zu].base.linear", m_Id);
    shader->SetFloat(locBuff, m_Linear);

    snprintf(locBuff, sizeof(locBuff), "spotLights[%zu].base.exponent", m_Id);
    shader->SetFloat(locBuff, m_Exponent);

    snprintf(locBuff, sizeof(locBuff), "spotLights[%zu].direction", m_Id);
    shader->SetFloat3(locBuff, m_Direction.x, m_Direction.y, m_Direction.z);

    snprintf(locBuff, sizeof(locBuff), "spotLights[%zu].edge", m_Id);
    shader->SetFloat(locBuff, m_ProcEdge);

    GetShadowMap()->Read(GL_TEXTURE0 + textureUnit + m_Id);

    snprintf(locBuff, sizeof(locBuff), "omniShadowMaps[%zu].shadowMap", m_Id + offset);
    shader->SetInt(locBuff, textureUnit + m_Id);

    snprintf(locBuff, sizeof(locBuff), "omniShadowMaps[%zu].farPlane", m_Id + offset);
    shader->SetFloat(locBuff, GetFarPlane());
}

void Sald::SpotLight::Move(glm::vec3 pos, glm::vec3 dir)
{
    m_Position = pos;
    m_Direction = dir;
}
