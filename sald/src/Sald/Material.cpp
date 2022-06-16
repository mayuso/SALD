#include "Material.h"

Sald::Material::Material()
{
    m_SpecularIntensity = 0;
    m_Shininess = 0;
}

Sald::Material::Material(GLfloat sIntensity, GLfloat shine)
{
    m_SpecularIntensity = sIntensity;
    m_Shininess = shine;
}

Sald::Material::~Material()
{
}

void Sald::Material::UseMaterial(Shader *shader)
{
    shader->SetFloat("material.specularIntensity", m_SpecularIntensity);
    shader->SetFloat("material.shininess", m_Shininess);
}