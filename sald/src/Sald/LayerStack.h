#pragma once
#include "Core.h"

#include "Layer.h"

namespace Sald
{
    class LayerStack
    {
    public:
        SALD_API LayerStack();
        SALD_API ~LayerStack();
        SALD_API void PushLayer(Layer *layer);
        SALD_API void PushOverlay(Layer *overlay);
        SALD_API void PopLayer(Layer *layer);
        SALD_API void PopOverlay(Layer *overlay);
        std ::vector<Layer *>::iterator begin() { return m_Layers.begin(); }
        std ::vector<Layer *>::iterator end() { return m_Layers.end(); }

    private:
        std ::vector<Layer *> m_Layers;
        std ::vector<Layer *>::iterator m_LayerInsert;
    };

}
