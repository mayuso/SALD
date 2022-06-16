#include "Light.h"

Sald::Light::Light()
{
    m_Color = glm::vec3(1.0f, 1.0f, 1.0f);
    m_AmbientIntensity = 1.0f;

    m_DiffuseIntensity = 0.0f;
    _isOn = true;
}

Sald::Light::Light(GLuint shadowWidth, GLuint shadowHeight,
                   GLfloat red, GLfloat green, GLfloat blue,
                   GLfloat aIntensity, GLfloat dIntensity)
{
    m_ShadowMap = new ShadowMap();
    m_ShadowMap->Init(shadowWidth, shadowHeight);

    m_Color = glm::vec3(red, green, blue);
    m_AmbientIntensity = aIntensity;

    m_DiffuseIntensity = dIntensity;
    _isOn = true;
}

void Sald::Light::Toggle()
{
    _isOn = !_isOn;
}

Sald::Light::~Light()
{
}

Sald::ShadowMap *Sald::Light::GetShadowMap()
{
    return m_ShadowMap;
}