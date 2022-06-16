#pragma once
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