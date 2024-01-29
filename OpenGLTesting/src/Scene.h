#pragma once

#include "Mesh.h"
#include <unordered_map>

/**
* 
* Notes:
*	This class is built to organize the actual scene of where this is taking place.
* 
*/

class Scene
{

public:

	// Adds a mesh to the scene	with appropriate shader
	void AddMesh(const Mesh& mesh, Shader& shader);

	// Removes a mesh from scene
	void RemoveMesh(const Mesh& mesh, Shader& shader);

	// Renders the meshes currently in the scene
	void Render(Camera& camera);

private:

	// holds all of the meshes in the scene
	std::unordered_map<Shader*, std::vector<Mesh>> m_meshes;

};

