#include "Layer.h"

Sald::Layer::Layer(const std ::string &name) : m_DebugName(name)
{
}

Sald::Layer::~Layer()
{
}

void Sald::Layer::OnAttach()
{
}

void Sald::Layer::OnDetach()
{
}

void Sald::Layer::OnUpdate(GLfloat deltaTime)
{
}

void Sald::Layer::OnEvent(Event &e)
{
}

std ::string &Sald::Layer::GetName()
{
    return m_DebugName;
}