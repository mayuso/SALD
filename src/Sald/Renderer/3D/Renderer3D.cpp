#include "saldpch.h"
#include "Renderer3D.h"

#include <glad/glad.h>

Sald::Renderer3D::Renderer3D() : Sald::Renderer()
{
}

Sald::Renderer3D::~Renderer3D()
{
}

void Sald::Renderer3D::Init()
{
    Sald::Renderer::Init();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); // Fragments with lower depth values are drawn
}
