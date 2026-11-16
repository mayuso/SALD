#pragma once
#include "Sald/Core/Core.h"
#include "ShadowMap.h"

namespace Sald
{
    class OmniShadowMap : public ShadowMap
    {
    public:
        SALD_API OmniShadowMap();
        SALD_API ~OmniShadowMap();
        SALD_API bool Init(GLuint width, GLuint height) override;
        SALD_API void Read(GLenum textureUnit) override;
    };

}