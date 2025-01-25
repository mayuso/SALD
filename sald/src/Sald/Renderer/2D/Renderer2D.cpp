#include "saldpch.h"
#include "Renderer2D.h"

#include <glad/glad.h>

Sald::Renderer2D::Renderer2D() : Sald::Renderer()
{

}

Sald::Renderer2D::~Renderer2D()
{
}

void Sald::Renderer2D::Init()
{
    Sald::Renderer::Init();
    glDisable(GL_DEPTH_TEST);
}

