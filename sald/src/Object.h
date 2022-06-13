#pragma once
#include "sald_api.h"

#include "Model.h"

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