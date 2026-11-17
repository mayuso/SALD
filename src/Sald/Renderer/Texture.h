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

        // Binds to texture unit GL_TEXTURE0 + textureUnit (and leaves it active)
        SALD_API void Use(GLuint textureUnit = 0);
        SALD_API void Clear();

    private:
        bool Load(const char *fileLocation);

        GLuint m_TextureID = 0;
        int m_Width = 0, m_Height = 0, m_BitDepth = 0;
    };

}