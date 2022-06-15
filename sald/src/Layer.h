#pragma once
#include "sald_api.h"

#include "Event.h"

#include <glad/glad.h>
#include <iostream>

namespace Sald
{
    class Layer
    {
    public:
        SALD_API Layer(const std ::string &name = " Layer ");
        SALD_API virtual ~Layer();
        SALD_API virtual void OnAttach();
        SALD_API virtual void OnDetach();
        SALD_API virtual void OnUpdate(GLfloat deltaTime);
        SALD_API virtual void OnEvent(Event &event);
        SALD_API std ::string &GetName();

    protected:
        std ::string m_DebugName;
        bool m_Enabled;
    };

}