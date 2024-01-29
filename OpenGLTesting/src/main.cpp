/**
*		--<== Notes ==>--
*	So far I need to create a VAO (Vertex array object) And a VBO (Vertex buffer object). Done.
*	Now I want to create a cube in 3D Done
*	Next I want to add a camera for debugging purposes. Done
*	Next I wanna start abstracting away the rendering process, and maybe build some object via classes and such Done
*	Ok so I need to create a scene objecct that holds all of the meshes, and send that off to teh rendewr class Done
*	Now I wanna work on an event system that'll listen for the events, and dispatch messages to places that require the data
* 
*	Tex coords
*	0.0f, 0.0f // Indicates bottom left
*	0.0f, 1.0f // Inidicates top left
*	1.0f, 0.0f // Indicates bottom right
*	1.0f, 1.0f // Indicates top right
* 
*	Normals!
*	Normals act as the vector of movement that tells which direction light should be deflected as.
*	They work by listing values between 0-1 perpandicular (forming a 90 degree angle with) angle with the face itself
*	So lets say you have a face facing you. The normals would X: 0.0f, Y: 0.0f, Z -1.0f. Why? Because that's the direction
*	the light needs to bounce to look realistic
*	
*/

#define STB_IMAGE_IMPLEMENTATION

// STD
#include <iostream>
#include <filesystem>
#include <chrono>
#include <thread>
#include <Windows.h>

// Libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Native files
#include "Logging.h" // Custom logging class I made :3

#include "Renderer.h"

// Get true array size
#define arraySize(x) sizeof(x) / sizeof(x[0])

// Screen size
const uint32_t SCR_WIDTH = 1920;
const uint32_t SCR_HEIGHT = 1080;

#define MAX_FRAMES (1/144)

// Each vertex contains position, normals, color, texCoords
Vertex vertices[] =
{
	//		Position						Normals						Color						TexCoords
	// Front
	Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3( 0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3( 0.5f,  0.5f, 0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},

	// Back
	Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},

	// Top
	Vertex{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},

	// Bottom :3
	Vertex{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f,-1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f,-1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3(0.0f,-1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(0.0f,-1.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},

	// Left
	Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.0f, 0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f, 0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f, 0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},

	// Right
	Vertex{glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(1.0f, 0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(1.0f, 0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 0.0f,  0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},


};

// Element array buffer
GLuint indices[] =
{
	// Front face
	0, 1, 2, // Leftish triangle
	1, 3, 2, // Rightish triangle

	// Back face
	4, 5, 6,
	5, 7, 6,
	
	// Top face
	8, 9, 10,
	9, 11, 10,

	// Bottom face
	12, 13, 14,
	13, 15, 14,

	// Left face
	16, 17, 18,
	17, 19, 18,

	// Right face
	20, 21, 22,
	21, 23, 22
};

Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

Vertex grassVertices[] =
{
	Vertex{glm::vec3(-5.0f, -1.0f, -5.0f), glm::vec3(0.0f, 1.0f,  0.0f), glm::vec3(0.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-5.0f, -1.0f,  5.0f), glm::vec3(0.0f, 1.0f,  0.0f), glm::vec3(0.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3( 5.0f, -1.0f, -5.0f), glm::vec3(0.0f, 1.0f,  0.0f), glm::vec3(0.0f), glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3( 5.0f, -1.0f,  5.0f), glm::vec3(0.0f, 1.0f,  0.0f), glm::vec3(0.0f), glm::vec2(1.0f, 1.0f)}
};

GLuint grassIndices[] =
{
	0, 1, 2,
	1, 3, 2
};

int main()
{
	// Creates a window as well as a GLFW context
	Window window(SCR_WIDTH, SCR_HEIGHT, "OpenGL Window");

	// Outputs the GPU info into console
	Log::Info((const char*)glGetString(GL_RENDERER));

	// Generates shaders based on the file paths provided
	Shader shaderProgram("default.vert", "default.frag");
	
	// Texture
	Texture brickTexture("BrickWallNew.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTexture.texUnit(shaderProgram, "tex0", 0);

	Texture grassTexture("GrassHighQuality.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	grassTexture.texUnit(shaderProgram, "tex0", 0);


	// Creating data for cube
	std::vector<Vertex> cubeVert(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector<GLuint> cubeInd(indices, indices + sizeof(indices) / sizeof(GLuint));

	Mesh cubeObject(cubeVert, cubeInd, brickTexture);


	// Creating data for grass
	std::vector<Vertex> grassVert(grassVertices, grassVertices + sizeof(grassVertices) / sizeof(Vertex));
	std::vector<GLuint> grassInd(grassIndices, grassIndices + sizeof(grassIndices) / sizeof(GLuint));

	Mesh grassObject(grassVert, grassInd, grassTexture);


	// Creating data for light
	// Shader for the light cube
	Shader lightShader("light.vert", "light.frag");

	std::vector<Vertex> lightVert(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector<GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));

	Mesh lightObject(lightVert, lightInd, grassTexture);




	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(1.5f, -0.5f, 0.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 cubePos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 cubeModel = glm::mat4(1.0f);
	cubeModel = glm::translate(cubeModel, cubePos);


	lightShader.activate();
	glUniformMatrix4fv(lightShader.getUniform("model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(lightShader.getUniform("lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.activate();
	glUniformMatrix4fv(shaderProgram.getUniform("model"), 1, GL_FALSE, glm::value_ptr(cubeModel));
	glUniform4f(shaderProgram.getUniform("lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(shaderProgram.getUniform("lightPos"), lightPos.x, lightPos.y, lightPos.z);

	Scene defaultScene;

	defaultScene.AddMesh(cubeObject, shaderProgram);
	defaultScene.AddMesh(lightObject, lightShader);

	Scene grassScene;

	grassScene.AddMesh(grassObject, shaderProgram);

	Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));
	Camera camera2(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

	Renderer::get().set(&window, &camera, &defaultScene);

	while (!Window::shouldClose(window))
	{

		if (glfwGetKey(window.getWindow(), GLFW_KEY_M) == GLFW_PRESS)
		{
			Renderer::get().setScene(&grassScene);
			Renderer::get().setCamera(&camera2);
		}
		if (glfwGetKey(window.getWindow(), GLFW_KEY_N) == GLFW_PRESS)
		{
			Renderer::get().setScene(&defaultScene);
			Renderer::get().setCamera(&camera);
		}
	
		Renderer::get().renderLoop();

	}


	shaderProgram.deleteShader();
	lightShader.deleteShader();

	Log::Info("Program Completed");

	return 0;

}