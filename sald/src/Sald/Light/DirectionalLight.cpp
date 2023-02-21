#include "saldpch.h"
#include "Sald/Light/DirectionalLight.h"

Sald::DirectionalLight::DirectionalLight() : Light()
{
    m_Direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

Sald::DirectionalLight::DirectionalLight(GLuint shadowWidth, GLuint shadowHeight,
                                         GLfloat red, GLfloat green, GLfloat blue,
                                         GLfloat aIntensity, GLfloat dIntensity,
                                         GLfloat xDir, GLfloat yDir, GLfloat zDir) : Light(shadowWidth, shadowHeight, red, green, blue, aIntensity, dIntensity)
{
    m_Direction = glm::vec3(xDir, yDir, zDir);
    m_LightProj = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
}

Sald::DirectionalLight::~DirectionalLight()
{
}

void Sald::DirectionalLight::UseLight(Shader *shader)
{
    shader->SetFloat3("directionalLight.base.color", m_Color.x, m_Color.y, m_Color.z);
    shader->SetFloat("directionalLight.base.ambientIntensity", m_AmbientIntensity);
    shader->SetFloat3("directionalLight.direction", m_Direction.x, m_Direction.y, m_Direction.z);
    shader->SetFloat("directionalLight.base.diffuseIntensity", m_DiffuseIntensity);
}

glm::mat4 Sald::DirectionalLight::CalculateLightTransform()
{
    return m_LightProj * glm::lookAt(-m_Direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}