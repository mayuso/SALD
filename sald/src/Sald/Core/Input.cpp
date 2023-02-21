#include "saldpch.h"
#include "Sald/Core/Input.h"

#include "Sald/Core/Application.h"
#include <GLFW/glfw3.h>

bool Sald::Input::IsKeyPressed(const KeyCode key)
{
    auto *window = static_cast<GLFWwindow *>(Application::GetInstance().GetWindow()->GetWindow());
    auto state = glfwGetKey(window, static_cast<int32_t>(key));
    return state == GLFW_PRESS;
}

bool Sald::Input::IsMouseButtonPressed(const MouseCode button)
{
    auto *window = static_cast<GLFWwindow *>(Application::GetInstance().GetWindow()->GetWindow());
    auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
    return state == GLFW_PRESS;
}

glm::vec2 Sald::Input::GetMousePosition()
{
    auto *window = static_cast<GLFWwindow *>(Application::GetInstance().GetWindow()->GetWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    return {(float)xpos, (float)ypos};
}

float Sald::Input::GetMouseX()
{
    return GetMousePosition().x;
}

float Sald::Input::GetMouseY()
{
    return GetMousePosition().y;
}