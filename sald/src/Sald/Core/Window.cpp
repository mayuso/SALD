#include "saldpch.h"
#include "Sald/Core/Window.h"
#include "Sald/Utils/Utils.h"
#include "Sald/Utils/TimeManager.h"

#include "Sald/Core/Log.h"

#include "Sald/Events/ApplicationEvent.h"
#include "Sald/Events/KeyEvent.h"
#include "Sald/Events/MouseEvent.h"

Sald::Window::Window()
    : m_XChange(0.0f), m_YChange(0.0f)
{
    m_Data.Width = 1280;
    m_Data.Height = 720;
    for (size_t i = 0; i < sizeof(m_Keys); ++i)
    {
        m_Keys[i] = 0;
    }
}

Sald::Window::Window(GLint windowWidth, GLint windowHeight)
    : m_XChange(0.0f), m_YChange(0.0f)
{
    m_Data.Width = windowWidth;
    m_Data.Height = windowHeight;
    for (size_t i = 0; i < sizeof(m_Keys); ++i)
    {
        m_Keys[i] = 0;
    }
}

Sald::Window::~Window()
{
    glfwDestroyWindow(m_MainWindow);
    glfwTerminate();
}

int Sald::Window::Init()
{
    m_Data.Title = "SALD - Main window";

    // Initialize GLFW
    if (!glfwInit())
    {
        SALD_CORE_ERROR("GLFW Initialization failed!");
        glfwTerminate();
        return 1;
    }

    // Setup GLFW window properties
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Core profile = No backwards compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Allow forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    m_MainWindow = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), NULL, NULL);
    if (!m_MainWindow)
    {
        SALD_CORE_ERROR("GLFW Window creation failed!");
        glfwTerminate();
        return 1;
    }

    m_Context = GraphicsContext::Create(m_MainWindow);
    m_Context->Init();

    // Get Buffer size information
    glfwGetFramebufferSize(m_MainWindow, &m_BufferWidth, &m_BufferHeight);

    glfwSetWindowUserPointer(m_MainWindow, &m_Data);

    // Set GLFW callbacks
    glfwSetWindowSizeCallback(m_MainWindow, [](GLFWwindow *window, int width, int height)
                              {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        data.Width = width;
        data.Height = height;

        WindowResizeEvent event(width, height);
        data.eventCallback(event); });

    glfwSetWindowCloseCallback(m_MainWindow, [](GLFWwindow *window)
                               {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data.eventCallback(event); });

    glfwSetKeyCallback(m_MainWindow, [](GLFWwindow *window, int key, int scancode, int action, int mods)
                       {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        switch (action)
        {
            case GLFW_PRESS:
            {
                KeyPressedEvent event(key, 0);
                data.eventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleasedEvent event(key);
                data.eventCallback(event);
                break;
            }
            case GLFW_REPEAT:
            {
                KeyPressedEvent event(key, true);
                data.eventCallback(event);
                break;
            }
        } });

    glfwSetCharCallback(m_MainWindow, [](GLFWwindow *window, unsigned int keycode)
                        {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        KeyTypedEvent event(keycode);
        data.eventCallback(event); });

    glfwSetMouseButtonCallback(m_MainWindow, [](GLFWwindow *window, int button, int action, int mods)
                               {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        switch (action)
        {
            case GLFW_PRESS:
            {
                MouseButtonPressedEvent event(button);
                data.eventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                MouseButtonReleasedEvent event(button);
                data.eventCallback(event);
                break;
            }
        } });

    glfwSetScrollCallback(m_MainWindow, [](GLFWwindow *window, double xOffset, double yOffset)
                          {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.eventCallback(event); });

    glfwSetCursorPosCallback(m_MainWindow, [](GLFWwindow *window, double xPos, double yPos)
                             {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        MouseMovedEvent event((float)xPos, (float)yPos);
        data.eventCallback(event); });

    return 0;
}

GLFWwindow *Sald::Window::GetWindow()
{
    return m_MainWindow;
}
GLfloat Sald::Window::GetBufferWidth() { return m_BufferWidth; }
GLfloat Sald::Window::GetBufferHeight() { return m_BufferHeight; }
bool Sald::Window::GetShouldClose() { return glfwWindowShouldClose(m_MainWindow); }

bool *Sald::Window::GetKeys()
{
    return m_Keys;
}

void Sald::Window::ShowFPS()
{
    double fpsCount = TimeManager::Instance().CalculateFrameRate(false);
    std::string titleString = "SALD - Main window - " + std::to_string(fpsCount) + " FPS";
    glfwSetWindowTitle(m_MainWindow, titleString.c_str());
}
void Sald::Window::SetVSync(bool vSync)
{
    if (vSync)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

    m_Data.VSync = vSync;
}

bool Sald::Window::GetVSync()
{
    return m_Data.VSync;
}

void Sald::Window::SetCursorEnabled(bool enabled)
{
    if (enabled)
    {
        glfwSetInputMode(m_MainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else
    {
        glfwSetInputMode(m_MainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}

void Sald::Window::SetEventCallback(const EventCallbackFn &callback)
{
    m_Data.eventCallback = callback;
}

void Sald::Window::OnUpdate()
{
    glfwPollEvents();
    m_Context->SwapBuffers();
    ShowFPS();
}
