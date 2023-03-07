#define STB_IMAGE_IMPLEMENTATION

#include "saldpch.h"
#include "Sald/Renderer/Texture.h"
#include "Sald/Utils/Utils.h"
#include "Sald/Core/Log.h"
#include "Sald/Core/Log.h"

Sald::Texture::Texture(const char *fileLocation)
{
    m_Width = 0;
    m_Height = 0;
    m_BitDepth = 0;
    if (!Load(fileLocation))
    {
        SALD_CORE_ERROR("Failed to load texture at: {0}", fileLocation);
    }
    glGenTextures(1, &m_TextureID);
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

    glBindTexture(GL_TEXTURE_2D, m_TextureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format = Utils::GetFormat(m_BitDepth);
    glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, texData);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(texData);
    return true;
}

void Sald::Texture::Use()
{
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Sald::Texture::Clear()
{
    glDeleteTextures(1, &m_TextureID);
}
