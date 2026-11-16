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
        SALD_API virtual ~Window();

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
        GLFWwindow *m_MainWindow = nullptr;
        std::unique_ptr<GraphicsContext> m_Context;

        // Last value written to the window title, so it is only rewritten when it changes
        double m_DisplayedFPS = -1.0;

        bool m_Keys[1024] = {};

        struct WindowData
        {
            std::string Title;
            unsigned int Width = 0, Height = 0;
            // Framebuffer size in pixels; differs from Width/Height on HiDPI displays
            int BufferWidth = 0, BufferHeight = 0;
            bool VSync = false;

            EventCallbackFn eventCallback;
        };

        WindowData m_Data;
    };
}
