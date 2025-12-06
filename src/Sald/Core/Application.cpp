#include "Sald/Core/Application.h"
#include "Sald/Core/Input.h"
#include "Sald/Core/Log.h"
#include "saldpch.h"

#include "Sald/Renderer/2D/Renderer2D.h"
#include "Sald/Renderer/3D/Renderer3D.h"

#include "Sald/Renderer/RenderCommand.h"

Sald::Application *Sald::Application::s_Instance = nullptr;

Sald::Application::Application(GLint windowWidth, GLint windowHeight,
                               Sald::Application::Dimensions dimensionNumber) {
  Log::Init();

  if (s_Instance)
    SALD_CORE_ERROR("Application already exists");
  s_Instance = this;

  m_MainWindow = std::make_shared<Window>(windowWidth, windowHeight);
  m_MainWindow->Init();
  m_MainWindow->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
  m_MainWindow->SetCursorEnabled(true);
  m_MainWindow->SetVSync(true);

  if (dimensionNumber == Sald::Application::Dimensions::Two) {
    Renderer2D::Init();
  } else {
    Renderer3D::Init();
  }
}

Sald::Application::~Application() {
  if (m_ShaderManager)
    delete m_ShaderManager;
}

void Sald::Application::Run() {
  while (m_Running) {
    GLfloat time = (GLfloat)glfwGetTime();
    Timestep timestep = time - m_LastFrameTime;
    m_LastFrameTime = time;

    if (!m_Minimized) {
      for (Layer *layer : m_LayerStack)
        layer->OnUpdate(timestep);
    }
    m_MainWindow->OnUpdate();
  }
}

void Sald::Application::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<Sald::WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
  dispatcher.Dispatch<Sald::WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

  for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
    (*--it)->OnEvent(e);
    if (e.Handled)
      break;
  }
}

bool Sald::Application::OnWindowClose(Sald::WindowCloseEvent &e) {
  m_Running = false;
  return true;
}

bool Sald::Application::OnWindowResize(Sald::WindowResizeEvent &e) {

  if (e.GetWidth() == 0 || e.GetHeight() == 0) {
    m_Minimized = true;
    return false;
  }
  m_Minimized = false;
  RenderCommand::SetViewport(0, 0, e.GetWidth(), e.GetHeight());
  return false;
}

std::shared_ptr<Sald::Window> Sald::Application::GetWindow() {
  return m_MainWindow;
}

void Sald::Application::PushLayer(Layer *layer) {
  m_LayerStack.PushLayer(layer);
}
void Sald::Application::PushOverlay(Layer *layer) {
  m_LayerStack.PushOverlay(layer);
}