#pragma once
#include "saldpch.h"
#include "Sald/Core/Core.h"

#include <glad/glad.h>

namespace Sald
{
    class Renderer
    {
    public:
        SALD_API static void SetClearColor(float r, float g, float b, float a);
        SALD_API static void Clear();
        SALD_API static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    };
}