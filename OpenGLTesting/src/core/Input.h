#pragma once

#include <GLFW/glfw3.h>

#include "glm/glm.hpp"

#include "KeyCode.h"
#include "MouseCodes.h"

class Input
{
public:

	static bool IsKeyPressed(const KeyCode keycode);
	static bool IsMouseKeyPressed(const MouseCode mousecode);

	static glm::vec2 GetMousePos();

	static float GetMouseX();
	static float GetMouseY();

	static void SetWindow(GLFWwindow* window) { m_Window = window; }

private:

	static GLFWwindow* m_Window;

};

