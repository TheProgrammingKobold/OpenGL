#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	// Assigns the type
	type = texType;

	// Stores width high and number of color channels
	int widthImg, heightImg, numColCh;
	// Flips the image so it appears right side up
	stbi_set_flip_vertically_on_load(true);

	// Gets currnet path
	std::string paraentDir = (std::filesystem::current_path().std::filesystem::path::parent_path()).string();
	std::string texPath = "\\OpenGLTesting\\extern\\textures\\";

	if (image != NULL && image[0] == '\0')
	{
		image = "Default.png";
	}

	std::string filePath = (paraentDir + texPath + image);

	// Validates that path given is correct
	if (!std::filesystem::is_directory(filePath) && !std::filesystem::exists(filePath))
	{
		std::cerr << "[Error loading file]: PATH: " << filePath << '\n';
		image = "Default.png";
	}

	filePath = (paraentDir + texPath + image);

	// Reads the image from a file and sstores it in bytes
	uint8_t* bytes = stbi_load(filePath.c_str(), &widthImg, &heightImg, &numColCh, 0);

	// Generates an OpenGL texture object
	glGenTextures(1, &ID);
	// Assigns the texture to a Texture unit
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configures the way the texture repeats (if it does at all)
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Assigns the image to an OpenGL TExture object
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	// Generates MipMaps
	glGenerateMipmap(texType);

	// Deletes the image data as it is already in the OpenGL TExture object
	stbi_image_free(bytes);

	// Unbinds the OPenGL TExture object so that it can't accidently be modified
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.getID(), uniform);
	// Shader needs to be activated before changing the value of a uniform
	shader.activate();
	// Sets the value of the uniform
	glUniform1i(texUni, unit);
}

void Texture::bind()
{
	glBindTexture(type, ID);
}

void Texture::unbind()
{
	glBindTexture(type, 0);
}

void Texture::deleteObject()
{
	glDeleteTextures(1, &ID);
}
