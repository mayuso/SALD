#include "saldpch.h"
#include "Utils.h"
#include "Log.h"

#include "GLFW/glfw3.h"

GLenum Sald::Utils::GetFormat(int bitDepth)
{
    if (bitDepth == 1)
        return GL_RED;
    else if (bitDepth == 3)
        return GL_RGB;
    else if (bitDepth == 4)
        return GL_RGBA;
    else
    {
        SALD_CORE_WARN("Can't detected the format of the image from the number of channels, defaulting to GL_RGBA");
        return GL_RGBA;
    }
}
