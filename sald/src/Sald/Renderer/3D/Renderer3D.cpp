#include "saldpch.h"
#include "Renderer3D.h"

#include <glad/glad.h>

Sald::Renderer3D::Renderer3D() : Sald::Renderer()
{
    // TODO: 3D Depth ordering is broken because this line here is doing nothing.
    glEnable(GL_DEPTH_TEST);
}

Sald::Renderer3D::~Renderer3D()
{
}
