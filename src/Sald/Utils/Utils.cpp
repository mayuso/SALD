#include "saldpch.h"
#include "Sald/Utils/Utils.h"
#include "Sald/Core/Log.h"

GLenum Sald::Utils::GetFormat(int bitDepth)
{
    if (bitDepth == 1)
        return GL_RED;
    else if (bitDepth == 2) // grey + alpha; treating it as RGBA would read past the pixel data
        return GL_RG;
    else if (bitDepth == 3)
        return GL_RGB;
    else if (bitDepth == 4)
        return GL_RGBA;
    else
    {
        SALD_CORE_WARN("Can't detect the format of the image from the number of channels, defaulting to GL_RGBA");
        return GL_RGBA;
    }
}
