#include "saldpch.h"
#include "Sald/Renderer/RenderCommand.h"
#include "Sald/Renderer/GraphicsContext.h"

namespace Sald
{
    std::unique_ptr<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}