#pragma once
#include "Core.h"

#include <glad/glad.h>

namespace Sald
{
    class Utils
    {
    public:
        SALD_API static GLenum GetFormat(int bitDepth);
    };
}