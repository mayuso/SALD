#pragma once
#include "Sald/Core/Core.h"

#include "Sald/Renderer/Renderer.h"

namespace Sald
{
    class Renderer3D : public Renderer
    {
    public:
        SALD_API Renderer3D();
        SALD_API ~Renderer3D();

        SALD_API static void Init();
    };
}