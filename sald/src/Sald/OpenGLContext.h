#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Sald
{
    class OpenGLContext
    {
    public:
        OpenGLContext(GLFWwindow *windowHandle);

        virtual void Init();
        virtual void SwapBuffers();
        static std::unique_ptr<Sald::OpenGLContext> Create(void *window);

    private:
        GLFWwindow *m_WindowHandle;
    };

}