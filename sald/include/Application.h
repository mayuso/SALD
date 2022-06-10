#pragma once
#include "sald_api.h"

namespace Sald
{
    class Application
    {
    public:
        SALD_API Application();
        SALD_API ~Application();

        SALD_API virtual void Update();
    };

}