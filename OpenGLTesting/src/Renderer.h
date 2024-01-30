#pragma once


/**
* 
*	Renderer:
*		I'm not entirely sure how I'm supposed to impliment this. So Imma just guess and say this is supposed to be used as the memory
*		buffer for objects in the scene, and automatically calls the draw calls, and binds the proper VAOs and stuff.
*		As well as binding textures and such.
* 
*	Idea 1:
*		Gonna try making a scene class where you init all the data and then pass that data to the renderer to render out that scene. That way
*		It'll be easy to make multiple scenes.
* 
*	Note:
*		I probably need to keep the loop outside this method, but still have everything else in there. That way, it's more clear and you can
*		put more items in the loop iteself without having to modify the renderer
* 
*/

#include <thread>
#include <chrono>



#include "Window.h"
#include "Scene.h"
#include "Input.h"

class Renderer
{
public:

	

	Renderer(const Renderer&) = delete;

	~Renderer();

	// A method to be placed inside of a loop
	void renderLoop();

	// Getting the instance of the class
	inline static Renderer& get() { return m_instance; }

private:

	// Inits everything
	int init();
	// In case anythign needs to be cleaned up
	void cleanUp();
	// Limits the framerate
	void frameLimit(double startTime, double endTime);

public:

	// Setters
	inline const void setMaxFPS(int newFPS) { m_maxFPS = newFPS; }
	inline const void setFOV(float FOV) { m_FOV = FOV; }
	inline const void setScene(Scene* newScene) { m_scene = newScene; }
	inline const void setCamera(Camera* newCam) { m_camera = newCam; }
	inline const void setWindow(Window* newWindow) { m_window = newWindow; }

	const void set(Window* window, Camera* camera, Scene* scene);

private:

	Renderer() { init(); }
	Renderer(Window* window, Camera* camera, Scene* scene);

	// Storing an instance of this class
	static Renderer m_instance;

private:

	// Nessesary parts to render a full scene
	Window* m_window = nullptr;
	Camera* m_camera = nullptr;
	Scene* m_scene = nullptr;

	// For frame limiting
	double m_maxFPS = 144;
	double m_startTime = 0;
	double m_endTime = 0;
	

	// Other variables
	float m_FOV = 80.0f;
	int m_count = 0;
	bool m_Vsync = true;
};

