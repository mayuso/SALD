#pragma once
#include "sald_api.h"

#include "Window.h"

#include <memory>

namespace Sald
{
    class Application
    {
    public:
        SALD_API Application();
        SALD_API Application(GLint windowWidth, GLint windowHeight);
        SALD_API ~Application();

        SALD_API virtual void Run();

        std::unique_ptr<Window> m_MainWindow;
    };

}