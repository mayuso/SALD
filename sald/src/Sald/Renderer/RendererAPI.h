#pragma once
#include "saldpch.h"
#include "Sald/Core/Core.h"

#include <glm/glm.hpp>

namespace Sald
{

    class RendererAPI
    {
    public:
        virtual ~RendererAPI() = default;

        SALD_API virtual void Init() = 0;
        SALD_API virtual void SetClearColor(float r, float g, float b, float a) = 0;
        SALD_API virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
        SALD_API virtual void Clear() = 0;

        enum class API
        {
            None = 0,
            OpenGL = 1
        };
        static API GetAPI() { return s_API; }
        static std::unique_ptr<RendererAPI> Create();

    private:
        static API s_API;
    };

}