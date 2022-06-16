#pragma once
#include "Sald/sald_api.h"

#include "Sald/Window.h"
#include "Sald/Layer.h"
#include "Sald/LayerStack.h"
#include "Sald/Event.h"

#include <memory>

namespace Sald
{
    class Application
    {
    public:
        SALD_API Application();
        SALD_API Application(GLint windowWidth, GLint windowHeight);
        SALD_API ~Application();

        SALD_API void Run();


        void OnEvent(Event& e);

        SALD_API void PushLayer(Layer *layer);
        SALD_API void PushOverlay(Layer *layer);

        std::unique_ptr<Window> m_MainWindow;

    private:
        LayerStack m_LayerStack;
        bool m_Running = true;
        GLfloat deltaTime = 0.0f, lastTime = 0.0f;
    };

}