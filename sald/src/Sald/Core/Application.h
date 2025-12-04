#pragma once
#include "Sald/Core/Core.h"
#include "Sald/Core/Timestep.h"

#include "Sald/Core/Layer.h"
#include "Sald/Core/LayerStack.h"
#include "Sald/Core/Window.h"
#include "Sald/Events/ApplicationEvent.h"
#include "Sald/Events/Event.h"

#include "Sald/Renderer/ShaderManager.h"

namespace Sald {

class Application {
public:
  enum class Dimensions { Two = 2, Three = 3 };
  SALD_API Application(GLint windowWidth, GLint windowHeight,
                       Dimensions dimensionNumber);
  SALD_API ~Application();

  static Application &GetInstance() { return *s_Instance; }

  SALD_API void Run();

  void OnEvent(Event &e);

  SALD_API void PushLayer(Layer *layer);
  SALD_API void PushOverlay(Layer *layer);

  SALD_API bool OnWindowClose(WindowCloseEvent &e);
  SALD_API bool OnWindowResize(WindowResizeEvent &e);

  SALD_API std::shared_ptr<Window> GetWindow();

private:
  Application();
  static Application *s_Instance;
  std::shared_ptr<Window> m_MainWindow;
  LayerStack m_LayerStack;

  ShaderManager *m_ShaderManager;

  bool m_Running = true;
  bool m_Minimized = false;
  GLfloat m_LastFrameTime = 0.0f;
};

}