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
        SALD_API bool Init(unsigned int width, unsigned int height);
    };

}