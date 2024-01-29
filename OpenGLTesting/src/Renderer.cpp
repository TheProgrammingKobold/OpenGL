#include "Renderer.h"

// Checks if OS is windows and includes windows.h
#ifdef _WIN32
#include <Windows.h>
void setConsoleTitle(std::wstring input)
{
	SetConsoleTitle(input.c_str());
}
#else

void setConsoleTitle(std::wstring input)
{}

#endif // _WIN32

// Definig the static variable for Renderer
Renderer Renderer::m_instance;


Renderer::Renderer(Window* window, Camera* camera, Scene* scene)
	: m_window(window), m_camera(camera), m_scene(scene)
{
	init();
}

Renderer::~Renderer()
{
	cleanUp();
}

int Renderer::init()
{
	if (!glfwInit())
	{
		Log::Error("GLFW failed to Init");
		return 0;
	}

	// Tells glfw what version of openGL we wanna use
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	

	// For frame limiting
	m_startTime = glfwGetTime();
	m_endTime = glfwGetTime();

	return 0;
}

void Renderer::cleanUp()
{
	glfwTerminate();
}

void Renderer::renderLoop()
{
	// Checks to see if escape key is pressed, and exits the program if so
	if (glfwGetKey(m_window->getWindow(), GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(m_window->getWindow(), true);
	}

	// Clears the background color, and depth buffer
	glClearColor(0.05f, 0.0f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Handles camera input
	m_camera->inputs(m_window->getWindow());
	// Updates camera matrix
	m_camera->updateMatrix(m_FOV, 0.1f, 100.0f);

	// Updates the scene
	m_scene->Render(*m_camera);

	// Updates frame buffer and polls events
	m_window->updateWindow();

	// Frame limits
	m_endTime = glfwGetTime();
	frameLimit(m_startTime, m_endTime);
	m_startTime = glfwGetTime();

	

}

void Renderer::frameLimit(double startTime, double endTime)
{
	// If the time is greater than FPS is tells the current thread to sleep
	if (endTime - startTime > (1.0 / m_maxFPS))
	{
		std::this_thread::sleep_for(std::chrono::duration<double>((1.0 / m_maxFPS)-(endTime - startTime)));
	}

	// Outputs FPS as console title to free up console room
	if (m_count > 100)
	{
		std::wstring FPS = L"FPS: " + std::to_wstring((int)(1 / (endTime - startTime)));
		setConsoleTitle(FPS.c_str());
		m_count = 0;
	}

	m_count++;
}

const void Renderer::set(Window* window, Camera* camera, Scene* scene)
{
	this->m_window = window;
	this->m_camera = camera;
	this->m_scene = scene;
}
