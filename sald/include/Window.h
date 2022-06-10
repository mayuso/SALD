#pragma once
#include "sald_api.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

namespace Sald
{
	class Window
	{
	public:
		SALD_API Window();
		SALD_API Window(GLint windowWidth, GLint windowHeight);
		SALD_API ~Window();

		SALD_API int Initialize();
		SALD_API GLFWwindow *GetWindow();
		SALD_API GLfloat GetBufferWidth();
		SALD_API GLfloat GetBufferHeight();
		SALD_API bool GetShouldClose();

		SALD_API bool *GetKeys();
		SALD_API GLfloat GetXChange();
		SALD_API GLfloat GetYChange();
		SALD_API void SwapBuffers();

		SALD_API void PollEvents();

		SALD_API void ShowFPS();
		SALD_API void SetVSync(bool vSync);
		SALD_API void SetCursorEnabled(bool enabled);

		SALD_API void ResizeViewport(int width, int height);

	private:
		GLFWwindow *m_MainWindow;

		GLint m_Width, m_Height;
		GLint m_BufferWidth, m_BufferHeight;

		double m_LastFrameTime, m_FrameCount;

		bool m_Keys[1024];

		GLfloat m_LastX, m_LastY, m_XChange, m_YChange;
		bool m_MouseFirstMoved;

		void CreateCallbacks();
		static void HandleResize(GLFWwindow *window, int width, int height);
		static void HandleKeys(GLFWwindow *window, int key, int code, int action, int mode);
		static void HandleMouse(GLFWwindow *window, double xPos, double yPos);
	};
}
