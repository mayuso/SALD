#pragma once
#include "Sald/Core/Core.h"

#include "Sald/Renderer/3D/Model.h"

namespace Sald
{
    class Object
    {
    public:
        SALD_API Object();
        SALD_API ~Object();

    private:
        Model *m_Model;
    };

}