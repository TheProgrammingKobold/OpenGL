#pragma once

#include <glad/glad.h>

#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:

	Shader(std::string filePathToVertex, std::string filePathToFragment);

	void activate();
	void deleteShader();

	inline const GLuint getID() const { return ID; }
	inline const GLint getUniform(std::string input) const { return glGetUniformLocation(ID, input.c_str()); }

private:

	static std::string parseFileToString(std::string filepath);
	static void validateShader(GLuint shader);

private:

	GLuint ID = 0;

};

