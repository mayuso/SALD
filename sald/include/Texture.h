#pragma once
#include "sald_api.h"

#include "CommonValues.h"

#include <GL/glew.h>

namespace Sald
{
    class Texture
    {
    public:
        SALD_API Texture();
        SALD_API Texture(const char *fileLoc);
        SALD_API ~Texture();

        SALD_API bool LoadTexture();
        SALD_API void UseTexture();
        SALD_API void ClearTexture();

    private:
        GLenum GetFormat();

        GLuint m_TextureID;
        int m_Width, m_Height, m_BitDepth;

        const char *m_FileLocation;
    };

}