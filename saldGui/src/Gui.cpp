#include "Gui.h"
#include "Dockspace.h"

#include "imgui.h"

namespace Application
{
    void RenderUI()
    {

        Dockspace::RenderUI();

        ImGui::Begin("Settings");
        ImGui::Button("Hello");
        static float value = 0.0f;
        ImGui::DragFloat("Value", &value);
        ImGui::End();

        ImGui::Begin("Viewport");
        ImGui::End();
    }
}