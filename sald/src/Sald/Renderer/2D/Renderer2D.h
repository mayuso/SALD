#pragma once
#include "Sald/Core/Core.h"

#include "Sald/Renderer/Renderer.h"

namespace Sald
{
    class Renderer2D : public Renderer
    {
    public:
        SALD_API Renderer2D();
        SALD_API ~Renderer2D();
    };
}