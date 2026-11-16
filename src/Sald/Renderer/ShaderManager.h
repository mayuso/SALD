#pragma once
#include "Sald/Core/Core.h"
#include "Sald/Renderer/Shader.h"

#include <map>
#include <string>

namespace Sald
{
    class ShaderManager
    {
    public:
        SALD_API ShaderManager();
        SALD_API ~ShaderManager();

        SALD_API static void NewShader(const std::string &id, const char *vertexFileName, const char *fragmentFileName);
        SALD_API static void NewShader(const std::string &id, const char *vertexFileName, const char *geometryFileName, const char *fragmentFileName);
        SALD_API static Shader *GetShader(const std::string &id);

    private:
        static std::map<std::string, Sald::Shader*> m_Shaders;
    };
}
