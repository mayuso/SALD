#include "Sandbox2DApp.h"
#include "Sandbox2DLayer.h"

#include "Sald/Core/Log.h"

Sandbox2DApp::Sandbox2DApp() : Sald::Application(800, 600)
{
    PushLayer(new Sandbox2DLayer());
}


Sandbox2DApp::~Sandbox2DApp()
{
}
