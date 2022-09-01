#include "saldpch.h"
#include "Application.h"
#include "Input.h"

#include "Log.h"

Sald::Application *Sald::Application::m_Instance = nullptr;

Sald::Application::Application()
{
    Log::Init();
    m_MainWindow = std::make_shared<Window>();
    m_MainWindow->Initialize();
    m_MainWindow->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
    m_MainWindow->SetCursorEnabled(true);
    m_MainWindow->SetVSync(true);
}

Sald::Application::Application(GLint windowWidth, GLint windowHeight)
{
    Log::Init();
    m_MainWindow = std::make_shared<Window>(windowWidth, windowHeight);
    m_MainWindow->Initialize();
    m_MainWindow->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
    m_MainWindow->SetCursorEnabled(true);
    m_MainWindow->SetVSync(true);
}

Sald::Application::~Application()
{
}

void Sald::Application::Run()
{
    while (m_Running)
    {

        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        if (!m_Minimized)
        {
            for (Layer *layer : m_LayerStack)
                layer->OnUpdate(deltaTime);
        }
        m_MainWindow->OnUpdate();
    }
}

void Sald::Application::OnEvent(Event &e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<Sald::WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
    dispatcher.Dispatch<Sald::WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
    {
        (*--it)->OnEvent(e);
        if (e.Handled)
            break;
    }
}

bool Sald::Application::OnWindowClose(Sald::WindowCloseEvent &e)
{
    m_Running = false;
    return true;
}

bool Sald::Application::OnWindowResize(Sald::WindowResizeEvent &e)
{

    if (e.GetWidth() == 0 || e.GetHeight() == 0)
    {
        m_Minimized = true;
        return false;
    }
    m_Minimized = false;
    Renderer::SetViewport(0, 0, e.GetWidth(), e.GetHeight());
    return false;
}

std::shared_ptr<Sald::Window> Sald::Application::GetWindow()
{
    return m_MainWindow;
}

void Sald::Application::PushLayer(Layer *layer)
{
    m_LayerStack.PushLayer(layer);
}
void Sald::Application::PushOverlay(Layer *layer)
{
    m_LayerStack.PushOverlay(layer);
}