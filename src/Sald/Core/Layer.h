#pragma once
#include "Sald/Core/Core.h"
#include "Sald/Core/Timestep.h"

#include "Sald/Events/Event.h"

#include <glad/glad.h>

namespace Sald {
class Layer {
public:
  SALD_API Layer(const std ::string &name = " Layer ");
  SALD_API virtual ~Layer();
  SALD_API virtual void OnAttach();
  SALD_API virtual void OnDetach();
  SALD_API virtual void OnUpdate(Timestep ts);
  SALD_API virtual void OnEvent(Event &event);
  SALD_API std ::string &GetName();

protected:
  std ::string m_DebugName;
  bool m_Enabled;
};

} // namespace Sald