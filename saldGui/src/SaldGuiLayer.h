#pragma once
#include "Sald/Core.h"
#include "Sald/Layer.h"
#include "Sald/Window.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <memory>

class SaldGuiLayer : public Sald::Layer
{
public:
    SaldGuiLayer(std::shared_ptr<Sald::Window> window);
    ~SaldGuiLayer();

    void OnUpdate(GLfloat deltaTime) override;
    void OnEvent(Sald::Event& event) override;
private:
    bool show_demo_window;
    bool show_another_window;
    ImVec4 clear_color;
    ImGuiConfigFlags configFlags;
};