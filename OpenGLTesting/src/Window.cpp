#include "Window.h"

#include <stdexcept>

Window::Window()
{
	m_windowName = "Window";
	init();
}

Window::Window(int width, int height, const char* windowName)
	: m_width(width), m_height(height), m_windowName(windowName)
{
	init();
}

Window::~Window()
{
	cleanUp();
}

void Window::updateWindow()
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

bool Window::shouldClose(Window& window)
{
	return glfwWindowShouldClose(window.m_window);
}

int Window::init()
{

	// Creates the window object
	m_window = glfwCreateWindow(m_width, m_height, m_windowName, NULL, NULL);

	// Validates the window object
	if (!m_window)
	{
		Log::Error("m_window isn't a valid pointer and failed to create window object");
		glfwTerminate();
		return 0;
	}

	glfwMakeContextCurrent(m_window);

	// Inits glad and checks for success
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Log::Error("Glad failed to initilize properly");
		glfwDestroyWindow(m_window);
		glfwTerminate();
		return 0;
	}

	// Starts the rendering at 0, 0. And ends it at the width and height of the screen.
	glViewport(0, 0, m_width, m_height);

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Sets a long ptr to be able to access data in lamda
	glfwSetWindowUserPointer(m_window, &m_data);

	glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			try
			{
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
				}
			}
			catch (const std::bad_function_call& e)
			{
				std::cerr << e.what() << '\n';
			}

		});

	Log::Info("Window created successfully");

	return 1;
}

void Window::cleanUp()
{
	glfwDestroyWindow(m_window);
}
