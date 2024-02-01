#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
	:m_width(width), m_height(height), m_Position(position)
{
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	// inits matrices since otherwise they will null matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Makes camera look in the right direction from the right position
	view = glm::lookAt(m_Position, m_Position + m_Orientation, m_Up);
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)m_width / m_height, nearPlane, farPlane);

	// Sets new camera matrix
	m_cameraMatrix = projection * view;
}

void Camera::matrix(Shader& shader, const char* uniform)
{
	// Exports the camera matrix
	glUniformMatrix4fv(shader.getUniform(uniform), 1, GL_FALSE, glm::value_ptr(m_cameraMatrix));
}

void Camera::inputs(GLFWwindow* window)
{
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_Position += m_speed * m_Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_Position += m_speed * -glm::normalize(glm::cross(m_Orientation, m_Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_Position += m_speed * -m_Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_Position += m_speed * glm::normalize(glm::cross(m_Orientation, m_Up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		m_Position += m_speed * m_Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		m_Position += m_speed * -m_Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		m_speed = 0.4f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		m_speed = 0.1f;
	}


	// Handles mouse imputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on first click
		if (m_firstClick)
		{
			glfwSetCursorPos(window, (m_width / 2), (m_height / 2));
			m_firstClick = false;
		}

		// Stores the coordinates of the cursor
		double mouseX, mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalizes and shift the coordinates of the cursor such that they behind in the middle of the screen
		float rotX = m_sensistivity * (float)(mouseY - (m_height / 2)) / m_height;
		float rotY = m_sensistivity * (float)(mouseX - (m_width / 2)) / m_width;

		// Calculates ipcoming verical change in orientation
		glm::vec3 newOrientation = glm::rotate(m_Orientation, glm::radians(-rotX), glm::normalize(glm::cross(m_Orientation, m_Up)));

		// Decives whether or not the next vertical orientation is legal or not
		if (abs(glm::angle(newOrientation, m_Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			m_Orientation = newOrientation;
		}

		// Rotates the orientation left and right
		m_Orientation = glm::rotate(m_Orientation, glm::radians(-rotY), m_Up);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (m_width / 2), (m_height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides the cursor since camera isn't moving
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the enxt time the camera looks aroudn, it doesn't jump
		m_firstClick = true;
	}
}
