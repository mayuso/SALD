#include "LayerStack.h"

Sald::LayerStack::LayerStack()
{
    m_LayerInsert = m_Layers.begin();
}

Sald::LayerStack::~LayerStack()
{
    for (Layer *layer : m_Layers)
    {
        delete layer;
    }
}

void Sald::LayerStack::PushLayer(Layer *layer)
{
    m_Layers.emplace(m_LayerInsert, layer);
}

void Sald::LayerStack::PushOverlay(Layer *overlay)
{
    m_Layers.emplace_back(overlay);
}

void Sald::LayerStack::PopLayer(Layer *layer)
{
    auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
    if (it != m_Layers.end())
    {
        m_Layers.erase(it);
    }
}

void Sald::LayerStack::PopOverlay(Layer *overlay)
{
    auto it = std ::find(m_Layers.begin(), m_Layers.end(), overlay);
    if (it != m_Layers.end())
    {
        m_Layers.erase(it);
    }
        
}