#pragma once
#include "sald_api.h"

#include <GL/glew.h>

namespace Sald
{
    class Utils
    {
    public:
        SALD_API static void PrintInfo();
        SALD_API static GLenum GetFormat(int bitDepth);
    };
}