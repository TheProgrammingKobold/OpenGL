#include "VAO.h"

// Vertex Array Object
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// Links the VBO to the VAO using a certain layout. Layout also being used in shader under "location"
void VAO::linkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.unbind();
}

// Binds the VAO
void VAO::bind()
{
	glBindVertexArray(ID);
}

// Unbinds the VAO
void VAO::unbind()
{
	glBindVertexArray(0);
}

// Deletes the vertex array object
void VAO::deleteObject() const
{
	glDeleteVertexArrays(1, &ID);
}
