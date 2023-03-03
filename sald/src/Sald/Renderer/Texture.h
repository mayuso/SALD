#pragma once
#include "Sald/Core/Core.h"

#include "Sald/Utils/CommonValues.h"

#include <glad/glad.h>

namespace Sald
{
    class Texture
    {
    public:
        SALD_API Texture();
        SALD_API Texture(const char *fileLoc);
        SALD_API ~Texture();

        SALD_API void Use();
        SALD_API void Clear();

    private:
        GLenum GetFormat();
        bool Load(const char *fileLocation);

        GLuint m_TextureID;
        int m_Width, m_Height, m_BitDepth;
    };

}