#pragma once
#include "Sald/Core/Core.h"

#include "Sald/Core/Window.h"
#include "Sald/Core/KeyCodes.h"
#include "Sald/Core/MouseCodes.h"

#include <glm/glm.hpp>

namespace Sald
{
	class Input
	{
	public:

		SALD_API static bool IsKeyPressed(KeyCode key);
		SALD_API static bool IsMouseButtonPressed(MouseCode button);

		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}