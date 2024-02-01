#pragma once

#include "Shader.h"

#include <glad/glad.h>
#include <filesystem>
#include <stb_image.h>

class Texture
{
public:

	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	// Assians a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	// Binds the texture
	void bind();
	// Unbinds the texture
	void unbind();
	// Deletes the texture
	void deleteObject();

private:
	
	GLuint ID;
	GLenum type;

};

