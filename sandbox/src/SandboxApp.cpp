#include "SandboxApp.h"
#include "SandboxLayer.h"

SandboxApp::SandboxApp() : Sald::Application(1280, 720)
{
    PushLayer(new SandboxLayer());
}

SandboxApp::~SandboxApp()
{
}
