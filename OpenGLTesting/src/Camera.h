#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "Shader.h"

class Camera
{
public:

	// Setting up the camera
	Camera(int width, int height, glm::vec3 position);

	
	// Updates the camera matrix to the vertex shader
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	// Exports the camera matrix to the shader
	void matrix(Shader& shader, const char* uniform);
	// Handes camera inputs
	void inputs(GLFWwindow* window);


	// Getters
	inline const glm::vec3 getPosition() const { return m_Position; }

private:

	// Stores the main vectors of the camera
	glm::vec3 m_Position;
	glm::vec3 m_Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

	// Cam matrix
	glm::mat4 m_cameraMatrix = glm::mat4(1.0f);

	// Prevents the camera from jumping around when first clicking left click
	bool m_firstClick = true;

	// Stores teh width and height of window
	int m_width, m_height;

	// Adjusts the speed of the cmera and it's sensitivity when looking around
	float m_speed = 0.1f;
	float m_sensistivity = 100.0f;

};

