#include "SaldGuiLayer.h"
#include "Dockspace.h"

#include "Sald/Renderer.h"



SaldGuiLayer::SaldGuiLayer(std::shared_ptr<Sald::Window> window)
    : Layer(" SaldGuiLayer ")
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking

    // TODO: Enabling ImGuiConfigFlags_ViewportsEnable crashes in: IM_ASSERT(g.PlatformIO.Monitors.Size > 0 && "Platform init didn't setup Monitors list?");
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows

    ImGui::StyleColorsDark();                        

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(window->GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    show_demo_window = true;
    show_another_window = false;
    clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    configFlags = io.ConfigFlags;
}

void SaldGuiLayer::OnUpdate(GLfloat deltaTime)
{

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    Dockspace::RenderUI();

    ImGui::Begin("Settings");
    ImGui::Button("Hello");
    static float value = 0.0f;
    ImGui::DragFloat("Value", &value);
    ImGui::End();

    ImGui::Begin("Viewport");
    ImGui::End();

    // Rendering
    ImGui::Render();
    uint32_t display_w, display_h;
    Sald::Renderer::SetViewport(0, 0, 0, 0);
    Sald::Renderer::SetClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    Sald::Renderer::Clear();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (configFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void SaldGuiLayer::OnEvent(Sald::Event& event)
{
}

SaldGuiLayer::~SaldGuiLayer()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}



