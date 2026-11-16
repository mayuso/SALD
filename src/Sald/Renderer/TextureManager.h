#pragma once
#include "Sald/Core/Core.h"
#include "Sald/Renderer/Texture.h"

#include <map>
#include <string>

namespace Sald
{
    class TextureManager
    {
    public:
        SALD_API TextureManager();
        SALD_API ~TextureManager();

        SALD_API static void NewTexture(const std::string &id, const char *fileLoc);
        SALD_API static Texture *GetTexture(const std::string &id);

    private:
        static std::map<std::string, Texture*> m_Textures;
    };
}
