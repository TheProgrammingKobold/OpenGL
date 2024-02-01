#pragma once

#include <vector>
#include <glad/glad.h>

class EBO
{
public:

	EBO(std::vector<GLuint>& indices);

	// Binds EBO
	void bind();
	// Unbinds EBO
	void unbind();
	// Deltes EBO
	void deleteObject();

private:
	GLuint ID;
};

