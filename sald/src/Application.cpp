#include "Application.h"

Sald::Application::Application()
{
    m_MainWindow = std::make_unique<Window>();
    m_MainWindow->Initialize();
}

Sald::Application::Application(GLint windowWidth, GLint windowHeight)
{
    m_MainWindow = std::make_unique<Window>(windowWidth, windowHeight);
    m_MainWindow->Initialize();
}

Sald::Application::~Application()
{
}

void Sald::Application::Run()
{
}