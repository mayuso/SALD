#pragma once
#include "Core.h"

#include "Window.h"
#include "KeyCodes.h"
#include "MouseCodes.h"

#include <glm/glm.hpp>

namespace Sald
{
	class Input
	{
	public:

		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}