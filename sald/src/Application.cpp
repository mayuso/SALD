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
    while (!m_MainWindow->GetShouldClose())
    {
        GLfloat now = glfwGetTime(); // TODO: This fails here, do it inside Sald::Application when layers are implemented
        deltaTime = now - lastTime;
        lastTime = now;

        for (Layer *layer : m_LayerStack)
            layer->OnUpdate(deltaTime);

        // m_MainWindow->OnUpdate();
    }
}

void Sald::Application::OnEvent(Event &e)
{
    // EventDispatcher dispatcher(e);
    // dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

    // HZ_CORE_TRACE("{0}", e);

    /*
    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
    {
        (*--it)->OnEvent(e);
        if (e.Handled)
            break;
    }
    */
}

void Sald::Application::PushLayer(Layer *layer)
{
    m_LayerStack.PushLayer(layer);
}
void Sald::Application::PushOverlay(Layer *layer)
{
    m_LayerStack.PushOverlay(layer);
}