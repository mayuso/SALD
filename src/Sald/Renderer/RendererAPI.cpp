#include "Sald/Renderer/RendererAPI.h"

#include "Sald/Core/Log.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

Sald::RendererAPI::API Sald::RendererAPI::s_API = RendererAPI::API::OpenGL;

std::unique_ptr<Sald::RendererAPI> Sald::RendererAPI::Create()
{
    switch (s_API)
    {
        case Sald::RendererAPI::API::None:    SALD_CORE_WARN("RendererAPI::None is currently not supported!");
        case Sald::RendererAPI::API::OpenGL:  return std::make_unique<OpenGLRendererAPI>();
    }
    SALD_CORE_WARN("Unknown RendererAPI!");
    return nullptr;
}
