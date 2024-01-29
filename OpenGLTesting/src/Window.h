#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Logging.h"

class Window
{
public:

	Window();
	Window(int width, int height, const char* windowName);
	~Window();

	void updateWindow();

	static bool shouldClose(Window& window);

private:

	int init();
	void cleanUp();

public:

	inline GLFWwindow* getWindow() const { return m_window; }
	inline const int getWidth() const { return m_width; }
	inline const int getHeight() const { return m_height; }

private:

	// pointer to window
	GLFWwindow* m_window = nullptr;

	int m_width = 800;
	int m_height = 600;
	const char* m_windowName = nullptr;
};

