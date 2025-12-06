#include "saldpch.h"
#include "Sald/Light/PointLight.h"

Sald::PointLight::PointLight() : Light()
{
    m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_Constant = 1.0f;
    m_Linear = 0.0f;
    m_Exponent = 0.0f;
    m_Id = 0;
}

Sald::PointLight::PointLight(GLuint shadowWidth, GLuint shadowHeight,
                             GLfloat near, GLfloat far,
                             GLfloat red, GLfloat green, GLfloat blue,
                             GLfloat aIntensity, GLfloat dIntensity,
                             GLfloat xPos, GLfloat yPos, GLfloat zPos,
                             GLfloat con, GLfloat lin, GLfloat exp, size_t id) : Light(shadowWidth, shadowHeight, red, green, blue, aIntensity, dIntensity)
{
    m_Position = glm::vec3(xPos, yPos, zPos);
    m_Constant = con;
    m_Linear = lin;
    m_Exponent = exp;

    m_Id = id;
    m_FarPlane = far;

    float aspect = (float)shadowWidth / (float)shadowHeight;
    m_LightProj = glm::perspective(glm::radians(90.f), aspect, near, far);

    m_ShadowMap = new OmniShadowMap();
    m_ShadowMap->Init(shadowWidth, shadowHeight);
}

Sald::PointLight::~PointLight()
{
}

void Sald::PointLight::UseLight(Shader *shader, unsigned int lightCount, unsigned int textureUnit, unsigned int offset)
{
    if (lightCount > MAX_POINT_LIGHTS)
        lightCount = MAX_POINT_LIGHTS;
    shader->SetInt("pointLightCount", lightCount);

    char locBuff[100] = {'\0'};

    snprintf(locBuff, sizeof(locBuff), "pointLights[%zu].base.color", m_Id);
    shader->SetFloat3(locBuff, m_Color.x, m_Color.y, m_Color.z);

    snprintf(locBuff, sizeof(locBuff), "pointLights[%zu].base.ambientIntensity", m_Id);
    shader->SetFloat(locBuff, m_AmbientIntensity);

    snprintf(locBuff, sizeof(locBuff), "pointLights[%zu].base.diffuseIntensity", m_Id);
    shader->SetFloat(locBuff, m_DiffuseIntensity);

    snprintf(locBuff, sizeof(locBuff), "pointLights[%zu].position", m_Id);
    shader->SetFloat3(locBuff, m_Position.x, m_Position.y, m_Position.z);

    snprintf(locBuff, sizeof(locBuff), "pointLights[%zu].constant", m_Id);
    shader->SetFloat(locBuff, m_Constant);

    snprintf(locBuff, sizeof(locBuff), "pointLights[%zu].linear", m_Id);
    shader->SetFloat(locBuff, m_Linear);

    snprintf(locBuff, sizeof(locBuff), "pointLights[%zu].exponent", m_Id);
    shader->SetFloat(locBuff, m_Exponent);

    GetShadowMap()->Read(GL_TEXTURE0 + textureUnit + m_Id);

    snprintf(locBuff, sizeof(locBuff), "omniShadowMaps[%zu].shadowMap", m_Id + offset);
    shader->SetInt(locBuff, textureUnit + m_Id);

    snprintf(locBuff, sizeof(locBuff), "omniShadowMaps[%zu].farPlane", m_Id + offset);
    shader->SetFloat(locBuff, GetFarPlane());
}

std::vector<glm::mat4> Sald::PointLight::CalculateLightTransform()
{
    std::vector<glm::mat4> lightTransforms;
    lightTransforms.push_back(m_LightProj *
                              glm::lookAt(m_Position, m_Position + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
    lightTransforms.push_back(m_LightProj *
                              glm::lookAt(m_Position, m_Position + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
    lightTransforms.push_back(m_LightProj *
                              glm::lookAt(m_Position, m_Position + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
    lightTransforms.push_back(m_LightProj *
                              glm::lookAt(m_Position, m_Position + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
    lightTransforms.push_back(m_LightProj *
                              glm::lookAt(m_Position, m_Position + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
    lightTransforms.push_back(m_LightProj *
                              glm::lookAt(m_Position, m_Position + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));

    return lightTransforms;
}

GLfloat Sald::PointLight::GetFarPlane()
{
    return m_FarPlane;
}

glm::vec3 Sald::PointLight::GetPosition()
{
    return m_Position;
}