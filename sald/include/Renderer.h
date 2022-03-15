#pragma once
#include "sald_api.h"

#include <GL/glew.h>

namespace Sald
{
    class Renderer
    {
    public:
        SALD_API static void SetClearColor(float r, float g, float b, float a);
        SALD_API static void Clear(GLbitfield mask);

    private:
        Renderer();
        ~Renderer();
    };
}