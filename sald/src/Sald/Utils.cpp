#include "saldpch.h"
#include "Utils.h"
#include "Log.h"

#include "GLFW/glfw3.h"

#include <stdio.h>

void Sald::Utils::PrintInfo()
{
    SALD_CORE_LOG("--- RENDERER INFO: ---");
    SALD_CORE_LOG("VENDOR: {0}", glGetString(GL_VENDOR));
    SALD_CORE_LOG("RENDERER: {0}", glGetString(GL_RENDERER));
    SALD_CORE_LOG("VERSION: {0}", glGetString(GL_VERSION));
    SALD_CORE_LOG("GLSL: {0}", glGetString(GL_SHADING_LANGUAGE_VERSION));
    SALD_CORE_LOG("----------------------");
}

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
