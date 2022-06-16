#pragma once
#include "Sald/sald_api.h"

#include "Sald/Model.h"

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