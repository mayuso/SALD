#include "saldpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include "Sald/Core/Log.h"

Sald::OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
    : m_WindowHandle(windowHandle)
{
}

void Sald::OpenGLContext::Init()
{
    // Set context for GLAD to use
    glfwMakeContextCurrent(m_WindowHandle);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        SALD_CORE_ERROR("Failed to initialize GLAD");
        return;
    }

    SALD_CORE_LOG("----------------------");
    SALD_CORE_LOG("OpenGL Info:");
    SALD_CORE_LOG("Vendor: {0}", glGetString(GL_VENDOR));
    SALD_CORE_LOG("Renderer: {0}", glGetString(GL_RENDERER));
    SALD_CORE_LOG("Version: {0}", glGetString(GL_VERSION));
    SALD_CORE_LOG("GLSL: {0}", glGetString(GL_SHADING_LANGUAGE_VERSION));
    SALD_CORE_LOG("----------------------");
}

void Sald::OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(m_WindowHandle);
}
