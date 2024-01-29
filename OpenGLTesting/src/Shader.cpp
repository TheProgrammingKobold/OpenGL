#include "Shader.h"

Shader::Shader(std::string filePathToVertex, std::string filePathToFragment)
{
	// Reading the shaders from the file
	std::string vertexString = parseFileToString("shaders/" + filePathToVertex);
	std::string fragmentString = parseFileToString("shaders/" + filePathToFragment);

	if (vertexString == "ERROR" || fragmentString == "ERROR")
	{
		std::cerr << "[ERROR]: VERTEXSTRING: " << vertexString << '\n' << "FRAGMENTSTRING: " << fragmentString << '\n';
		return;
	}

	// Converts them into const char pointers
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	// Creates and ID for the shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attaches the vertex shader source to a vertex object
	glShaderSource(vertexShader, 1, &vertexCode, NULL);
	// Compiles the shader into machine code
	glCompileShader(vertexShader);
	// Validates the shader
	validateShader(vertexShader);


	// Creates ID for fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attaches the fragment shader to a fragment object
	glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
	// Compiling the shader into machine code
	glCompileShader(fragmentShader);
	// Validates the shader
	validateShader(fragmentShader);


	// Creates a shader program and the ID to it
	ID = glCreateProgram();
	// Attaches both shaders to the shader program
	// MISTAKE! Was accidently attatching the fragment shader twice :c
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Links everything
	glLinkProgram(ID);
	// Checks if the shaders linked properly

	GLint hasCompiled;
	char infoLog[1024];
	glGetProgramiv(ID, GL_LINK_STATUS, &hasCompiled);
	if (!hasCompiled)
	{
		glGetProgramInfoLog(ID, 1024, NULL, infoLog);
		std::cerr << "[Shader Linking Error]: " << infoLog << '\n';
	}


	// Deletes the shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::activate()
{
	glUseProgram(ID);
}

void Shader::deleteShader()
{
	glDeleteProgram(ID);
}

std::string Shader::parseFileToString(std::string filepath)
{
	// Setting the result
	std::string result;

	// Setting the main file path object from filepath parameter
	std::filesystem::path filePath = filepath;

	// Checking if the file actually exists or not
	if (std::filesystem::exists(filePath) && std::filesystem::is_regular_file(filePath))
	{
		// Opens the file for reading
		std::ifstream inputFile(filePath);

		// Checks if the file opened properly
		if (inputFile.is_open())
		{
			// Reads the entire content of the file and then puts that into a string
			std::ostringstream contentStream;
			contentStream << inputFile.rdbuf();
			result = contentStream.str();

			inputFile.close();
		} else {
			std::cerr << "Unable to open file \"" + filepath + "\"" << '\n';
			result = "ERROR";
		}
	} else {
		std::cerr << "File at \"" + filepath + "\" was unable to be reached" << '\n';
		result = "ERROR";
	}

	return result;
}

void Shader::validateShader(GLuint shader)
{
	int status;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (!status) // Status works like a bool here
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "[Shader Compilation Error]: " << infoLog << '\n';
	}
}
