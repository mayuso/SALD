#pragma once
#include "Sald/Core/Core.h"

#include "Sald/Renderer/Renderer.h"
#include "Sald/Events/Event.h"

#include "Sald/Renderer/GraphicsContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>



namespace Sald
{
    class Window
    {
    public:
        SALD_API Window();
        SALD_API Window(GLint windowWidth, GLint windowHeight);
        SALD_API ~Window();

        SALD_API int Init();
        SALD_API GLFWwindow *GetWindow();
        SALD_API GLfloat GetBufferWidth();
        SALD_API GLfloat GetBufferHeight();
        SALD_API bool GetShouldClose();

        SALD_API bool *GetKeys();

        SALD_API void ShowFPS();
        SALD_API void SetVSync(bool vSync);
        SALD_API bool GetVSync();
        SALD_API void SetCursorEnabled(bool enabled);

        using EventCallbackFn = std::function<void(Event &)>;
        SALD_API void SetEventCallback(const EventCallbackFn &callback);
        SALD_API virtual void OnUpdate();

    private:
        GLFWwindow *m_MainWindow;
        std::unique_ptr<GraphicsContext> m_Context;

        GLint m_BufferWidth, m_BufferHeight;

        double m_LastFrameTime, m_FrameCount;

        bool m_Keys[1024];

        GLfloat m_LastX, m_LastY, m_XChange, m_YChange;
        bool m_MouseFirstMoved;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn eventCallback;
        };

        WindowData m_Data;
    };
}
