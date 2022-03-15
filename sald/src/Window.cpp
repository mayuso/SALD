#include "Window.h"
#include "Utils.h"
#include "TimeManager.h"

#include <string>

Sald::Window::Window()
{
	m_Width = 1280;
	m_Height = 720;

	m_XChange = 0.0f;
	m_YChange = 0.0f;

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

	// Handle key + Mmouse input
	CreateCallbacks();

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initialization failed!");
		glfwDestroyWindow(m_MainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	// Setup Viewport size
	glViewport(0, 0, m_BufferWidth, m_BufferHeight);

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

GLfloat Sald::Window::GetXChange()
{
	// Might be better to just return the value, without resetting it to 0; In case that is better, implement the getter in the header directly.
	GLfloat theChange = m_XChange;
	m_XChange = 0.0f;
	return theChange;
}
GLfloat Sald::Window::GetYChange()
{
	// Might be better to just return the value, without resetting it to 0; In case that is better, implement the getter in the header directly.
	GLfloat theChange = m_YChange;
	m_YChange = 0.0f;
	return theChange;
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

void Sald::Window::CreateCallbacks()
{
	glfwSetFramebufferSizeCallback(m_MainWindow, HandleResize);
	glfwSetKeyCallback(m_MainWindow, HandleKeys);
	glfwSetCursorPosCallback(m_MainWindow, HandleMouse);
}

void Sald::Window::HandleResize(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Sald::Window::HandleKeys(GLFWwindow *window, int key, int code, int action, int mode)
{
	Sald::Window *auxWindow = static_cast<Sald::Window *>(glfwGetWindowUserPointer(window));

	if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key >= 0 && key < (int)sizeof(m_Keys))
	{
		if (action == GLFW_PRESS)
		{
			auxWindow->m_Keys[key] = true;
			printf("Pressed: %d\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			auxWindow->m_Keys[key] = false;
			printf("Released: %d\n", key);
		}
	}
}
void Sald::Window::HandleMouse(GLFWwindow *window, double xPos, double yPos)
{
	Sald::Window *auxWindow = static_cast<Sald::Window *>(glfwGetWindowUserPointer(window));

	if (auxWindow->m_MouseFirstMoved)
	{
		auxWindow->m_LastX = xPos;
		auxWindow->m_LastY = yPos;
		auxWindow->m_MouseFirstMoved = false;
	}

	auxWindow->m_XChange = xPos - auxWindow->m_LastX;
	auxWindow->m_YChange = auxWindow->m_LastY - yPos;

	auxWindow->m_LastX = xPos;
	auxWindow->m_LastY = yPos;
}