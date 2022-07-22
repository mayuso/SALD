#include "saldpch.h"
#include "Window.h"
#include "Utils.h"
#include "TimeManager.h"

#include "Sald/Events/ApplicationEvent.h"
#include "Sald/Events/KeyEvent.h"
#include "Sald/Events/MouseEvent.h"

Sald::Window::Window()
    : m_Width(1280), m_Height(720), m_XChange(0.0f), m_YChange(0.0f)
{
    for (size_t i = 0; i < sizeof(m_Keys); ++i)
    {
        m_Keys[i] = 0;
    }
}

Sald::Window::Window(GLint windowWidth, GLint windowHeight)
    : m_Width(windowWidth), m_Height(windowHeight), m_XChange(0.0f), m_YChange(0.0f)
{
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

int Sald::Window::Initialize()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        printf("GLFW Initialization failed!");
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
    m_MainWindow = glfwCreateWindow(m_Width, m_Height, "SALD - Main window", NULL, NULL);
    if (!m_MainWindow)
    {
        printf("GLFW Window creation failed!");
        glfwTerminate();
        return 1;
    }

    // Get Buffer size information
    glfwGetFramebufferSize(m_MainWindow, &m_BufferWidth, &m_BufferHeight);

    // Set context for GLEW to use
    glfwMakeContextCurrent(m_MainWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        return 1;
    }

    glEnable(GL_DEPTH_TEST);

    // Set GLFW callbacks
    glfwSetWindowSizeCallback(m_MainWindow, [](GLFWwindow *window, int width, int height)
                              {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        
        data.Width = width;
        data.Height = height;

        WindowResizeEvent event(width, height);
        data.EventCallback(event); });

    glfwSetWindowCloseCallback(m_MainWindow, [](GLFWwindow *window)
                               {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data.EventCallback(event); });

    glfwSetKeyCallback(m_MainWindow, [](GLFWwindow *window, int key, int scancode, int action, int mods)
                       {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        switch (action)
        {
            case GLFW_PRESS:
            {
                KeyPressedEvent event(key, 0);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleasedEvent event(key);
                data.EventCallback(event);
                break;
            }
            case GLFW_REPEAT:
            {
                KeyPressedEvent event(key, true);
                data.EventCallback(event);
                break;
            }
        } });

    glfwSetCharCallback(m_MainWindow, [](GLFWwindow *window, unsigned int keycode)
                        {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        KeyTypedEvent event(keycode);
        data.EventCallback(event); });

    glfwSetMouseButtonCallback(m_MainWindow, [](GLFWwindow *window, int button, int action, int mods)
                               {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        switch (action)
        {
            case GLFW_PRESS:
            {
                MouseButtonPressedEvent event(button);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                MouseButtonReleasedEvent event(button);
                data.EventCallback(event);
                break;
            }
        } });

    glfwSetScrollCallback(m_MainWindow, [](GLFWwindow *window, double xOffset, double yOffset)
                          {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.EventCallback(event); });

    glfwSetCursorPosCallback(m_MainWindow, [](GLFWwindow *window, double xPos, double yPos)
                             {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        MouseMovedEvent event((float)xPos, (float)yPos);
        data.EventCallback(event); });

    // Setup Viewport size
    // HandleResize(m_MainWindow, m_BufferWidth, m_BufferHeight);

    glfwSetWindowUserPointer(m_MainWindow, this);

    Sald::Utils::PrintInfo();

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

void Sald::Window::SwapBuffers() { glfwSwapBuffers(m_MainWindow); }

void Sald::Window::PollEvents()
{
    glfwPollEvents();
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
    EventCallback = callback;
}

void Sald::Window::OnUpdate()
{
}
