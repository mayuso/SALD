#include "Renderer.h"

Sald::Renderer::Renderer()
{
}
Sald::Renderer::~Renderer()
{
}

void Sald::Renderer::SetClearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void Sald::Renderer::Clear(GLbitfield mask)
{
    glClear(mask);
}
