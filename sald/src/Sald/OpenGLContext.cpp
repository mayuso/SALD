#include "saldpch.h"
#include "OpenGLContext.h"

#include "Log.h"

#include <memory>
Sald::OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
    : m_WindowHandle(windowHandle)
{
}

std::unique_ptr<Sald::OpenGLContext> Sald::OpenGLContext::Create(void *window)
{

    return std::make_unique<OpenGLContext>(static_cast<GLFWwindow *>(window));
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
    SALD_CORE_LOG("  Vendor: {0}", glGetString(GL_VENDOR));
    SALD_CORE_LOG("  Renderer: {0}", glGetString(GL_RENDERER));
    SALD_CORE_LOG("  Version: {0}", glGetString(GL_VERSION));
    SALD_CORE_LOG("GLSL: {0}", glGetString(GL_SHADING_LANGUAGE_VERSION));
    SALD_CORE_LOG("----------------------");
}

void Sald::OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(m_WindowHandle);
}
