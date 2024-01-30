#include "Input.h"

GLFWwindow* Input::m_Window = nullptr;

bool Input::IsKeyPressed(const KeyCode keycode)
{
    return glfwGetKey(m_Window, static_cast<int32_t>(keycode)) == GLFW_PRESS;
}

bool Input::IsMouseKeyPressed(const MouseCode mousecode)
{
    return glfwGetKey(m_Window, static_cast<int32_t>(mousecode)) == GLFW_PRESS;
}

glm::vec2 Input::GetMousePos()
{
    double x, y;
    glfwGetCursorPos(m_Window, &x, &y);
    return { (float)x, (float)y };
}

float Input::GetMouseX()
{
    return GetMousePos().x;
}

float Input::GetMouseY()
{
    return GetMousePos().y;
}
