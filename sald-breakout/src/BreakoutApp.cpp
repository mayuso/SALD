#include "BreakoutApp.h"
#include "GameLayer.h"

BreakoutApp::BreakoutApp() : Sald::Application(1280, 720)
{
    PushLayer(new GameLayer());
}

BreakoutApp::~BreakoutApp()
{
}
