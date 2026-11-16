#include "saldpch.h"
#include "TextureManager.h"

#include "Sald/Core/Log.h"

std::map<std::string, Sald::Texture *> Sald::TextureManager::m_Textures;

Sald::TextureManager::TextureManager()
{
}

Sald::TextureManager::~TextureManager()
{
}

void Sald::TextureManager::NewTexture(const std::string &id, const char *fileLocation)
{
    m_Textures[id] = new Texture(fileLocation);
}

Sald::Texture *Sald::TextureManager::GetTexture(const std::string &id)
{
    // find(), not operator[]: a lookup must not insert a null entry for an unknown id
    auto it = m_Textures.find(id);
    if (it == m_Textures.end())
    {
        SALD_CORE_ERROR("Texture '{0}' not found", id);
        return nullptr;
    }
    return it->second;
}
