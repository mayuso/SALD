#include "saldpch.h"
#include "TextureManager.h"

std::map<std::string, Sald::Texture *> Sald::TextureManager::m_Textures;

Sald::TextureManager::TextureManager()
{
}

Sald::TextureManager::~TextureManager()
{
}

void Sald::TextureManager::NewTexture(std::string id, const char *fileLocation)
{
    m_Textures[id] = new Texture(fileLocation);
}

Sald::Texture *Sald::TextureManager::GetTexture(std::string id)
{
    return m_Textures[id];
}
