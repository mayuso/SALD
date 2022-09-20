#include "SaldGuiApp.h"
#include "SaldGuiLayer.h"


SaldGuiApp::SaldGuiApp() : Sald::Application(1280, 720)
{
    PushLayer(new SaldGuiLayer(GetWindow()));
}

SaldGuiApp::~SaldGuiApp()
{
}
