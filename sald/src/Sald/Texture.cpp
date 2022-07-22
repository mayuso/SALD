#define STB_IMAGE_IMPLEMENTATION

#include "saldpch.h"
#include "Texture.h"
#include "Utils.h"

#include <cstring>

Sald::Texture::Texture()
{
    m_TextureID = 0;
    m_Width = 0;
    m_Height = 0;
    m_BitDepth = 0;
    m_FileLocation = const_cast<char *>("");
}
Sald::Texture::Texture(const char *fileLoc)
{
    m_TextureID = 0;
    m_Width = 0;
    m_Height = 0;
    m_BitDepth = 0;
    m_FileLocation = fileLoc;
}
Sald::Texture::~Texture()
{
    ClearTexture();
}

bool Sald::Texture::LoadTexture()
{
    unsigned char *texData = stbi_load(m_FileLocation, &m_Width, &m_Height, &m_BitDepth, 0);
    if (!texData)
    {
        printf("Failed to find: %s\n", m_FileLocation);
        return false;
    }

    glGenTextures(1, &m_TextureID);
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

void Sald::Texture::UseTexture()
{
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Sald::Texture::ClearTexture()
{
    glDeleteTextures(1, &m_TextureID);
    m_TextureID = 0;
    m_Width = 0;
    m_Height = 0;
    m_BitDepth = 0;
    m_FileLocation = const_cast<char *>("");
}
