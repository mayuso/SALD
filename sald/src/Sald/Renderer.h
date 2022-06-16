#pragma once
#include "Sald/sald_api.h"

#include <glad/glad.h>

#include <cstdint>

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