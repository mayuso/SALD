#include "BreakoutApp.h"
#include "GameLayer.h"

BreakoutApp::BreakoutApp() : Sald::Application(1280, 720, Sald::Application::Dimensions::Two)
{
    PushLayer(new GameLayer());
}

BreakoutApp::~BreakoutApp()
{
}
