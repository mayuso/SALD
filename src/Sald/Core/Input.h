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

		SALD_API static glm::vec2 GetMousePosition();
		SALD_API static float GetMouseX();
		SALD_API static float GetMouseY();
	};
}