#pragma once
#include "saldpch.h"
#include "Sald/Core/Core.h"

namespace Sald
{
    class GraphicsContext
    {
    public:
        virtual ~GraphicsContext() = default;
        SALD_API virtual void Init() = 0;
        SALD_API virtual void SwapBuffers() = 0;

        static std::unique_ptr<GraphicsContext> Create(void *window);
    };
}