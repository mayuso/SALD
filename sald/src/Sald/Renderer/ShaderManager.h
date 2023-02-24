#pragma once
#include "Sald/Core/Core.h"

#include "Sald/Renderer/Shader.h"

namespace Sald
{
    class ShaderManager
    {
    public:
        SALD_API ShaderManager();
        SALD_API ~ShaderManager();

        SALD_API enum ShaderType
        {
            COLOR,
            DIRECTIONALLIGHT, 
            OMNIDIRECTIONALSHADOWMAP,
            SKYBOX,
            COUNT
        };
        SALD_API void Initialize();
        SALD_API static void NewShader(ShaderType type, const char* vertexFileName, const char* fragmentFileName);
        SALD_API static void NewShader(ShaderType type, const char* vertexFileName, const char* geometryFileName, const char* fragmentFileName);
        SALD_API static Shader* GetShader(ShaderType type);

    private:
        static Shader** m_Shaders;
        
    };
}
