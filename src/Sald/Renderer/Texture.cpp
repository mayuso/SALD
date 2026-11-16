#define STB_IMAGE_IMPLEMENTATION

#include "saldpch.h"
#include "Sald/Renderer/Texture.h"
#include "Sald/Utils/Utils.h"
#include "Sald/Core/Log.h"

Sald::Texture::Texture()
{
}

Sald::Texture::Texture(const char *fileLocation)
{
    if (!Load(fileLocation))
    {
        SALD_CORE_ERROR("Failed to load texture at: {0}", fileLocation);
    }
}

Sald::Texture::~Texture()
{
    Clear();
}

bool Sald::Texture::Load(const char *fileLocation)
{
    unsigned char *texData = stbi_load(fileLocation, &m_Width, &m_Height, &m_BitDepth, 0);
    if (!texData)
    {
        SALD_CORE_ERROR("Failed to find: {0}", fileLocation);
        return false;
    }
    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);

    GLenum format = Utils::GetFormat(m_BitDepth);
    // stb rows are tightly packed; the default alignment of 4 skews (or reads
    // past the end of) images whose row size is not a multiple of 4 bytes
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, texData);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(texData);
    return true;
}

void Sald::Texture::Use()
{
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Sald::Texture::Clear()
{
    if (m_TextureID != 0)
    {
        glDeleteTextures(1, &m_TextureID);
        m_TextureID = 0;
    }
}
