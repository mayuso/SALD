#include "Platform/OpenGL/OpenGLRendererAPI.h"

void Sald::OpenGLRendererAPI::Init()
{
}

void Sald::OpenGLRendererAPI::SetClearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void Sald::OpenGLRendererAPI::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Sald::OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    glViewport(x, y, width, height);
}