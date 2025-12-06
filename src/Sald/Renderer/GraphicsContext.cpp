#include "saldpch.h"
#include "Sald/Renderer/GraphicsContext.h"

#include "Sald/Core/Log.h"

#include "Sald/Renderer/Renderer.h"
#include "Sald/Renderer/RendererAPI.h"

#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>

std::unique_ptr<Sald::GraphicsContext> Sald::GraphicsContext::Create(void* window)
{
    switch (Sald::RendererAPI::GetAPI())
    {
        case Sald::RendererAPI::API::None:    SALD_CORE_WARN("RendererAPI::None is currently not supported!");
        case Sald::RendererAPI::API::OpenGL:  return std::make_unique<Sald::OpenGLContext>(static_cast<GLFWwindow*>(window));
    }

    SALD_CORE_ERROR("Unknown RendererAPI!");
    return nullptr;
}


