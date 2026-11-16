#include "LayerStack.h"
#include "saldpch.h"
#include <algorithm>

Sald::LayerStack::LayerStack() {}

Sald::LayerStack::~LayerStack() {
  for (Layer *layer : m_Layers) {
    delete layer;
  }
}

void Sald::LayerStack::PushLayer(Layer *layer) {
  m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
  m_LayerInsertIndex++;
}

void Sald::LayerStack::PushOverlay(Layer *overlay) {
  m_Layers.emplace_back(overlay);
}

void Sald::LayerStack::PopLayer(Layer *layer) {
  auto layersEnd = m_Layers.begin() + m_LayerInsertIndex;
  auto it = std::find(m_Layers.begin(), layersEnd, layer);
  if (it != layersEnd) {
    m_Layers.erase(it);
    m_LayerInsertIndex--;
  }
}

void Sald::LayerStack::PopOverlay(Layer *overlay) {
  auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(),
                      overlay);
  if (it != m_Layers.end()) {
    m_Layers.erase(it);
  }
}