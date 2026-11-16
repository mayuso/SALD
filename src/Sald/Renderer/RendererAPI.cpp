#include "Sald/Renderer/RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

Sald::RendererAPI::API Sald::RendererAPI::s_API = RendererAPI::API::OpenGL;

std::unique_ptr<Sald::RendererAPI> Sald::RendererAPI::Create()
{
    switch (s_API)
    {
        case Sald::RendererAPI::API::None:    return nullptr; // runs during static init, before Log::Init, so it must not log
        case Sald::RendererAPI::API::OpenGL:  return std::make_unique<OpenGLRendererAPI>();
    }
    return nullptr;
}
