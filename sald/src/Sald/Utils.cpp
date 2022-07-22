#include "saldpch.h"
#include "Utils.h"
#include <stdio.h>
#include "GLFW/glfw3.h"

void Sald::Utils::PrintInfo()
{
    printf("\n--- RENDERER INFO: ---\n");
    printf("VENDOR: %s\n", glGetString(GL_VENDOR));
    printf("RENDERER: %s\n", glGetString(GL_RENDERER));
    printf("VERSION: %s\n", glGetString(GL_VERSION));
    printf("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    printf("----------------------\n\n");
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
        printf("Can't detected the format of the image from the number of channels, defaulting to GL_RGBA");
        return GL_RGBA;
    }
}
