#pragma once
#include "saldpch.h"
#include "Sald/Core/Core.h"

#include "Sald/Renderer/RendererAPI.h"

#include <glad/glad.h>

namespace Sald
{
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        SALD_API virtual void Init() override;
        SALD_API virtual void SetClearColor(float r, float g, float b, float a) override;
        SALD_API virtual void Clear() override;
        SALD_API virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
    };
}