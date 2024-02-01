#include "Scene.h"

void Scene::AddMesh(const Mesh& mesh, Shader& shader)
{
	// Adds a mesh to the scene along with the shader
	m_meshes[&shader].push_back(mesh);
}

void Scene::RemoveMesh(const Mesh& mesh, Shader& shader)
{
	// Idk how tf this works. Shitty cpp syntax
	auto& meshList = m_meshes[&shader];
	meshList.erase(std::remove_if(meshList.begin(), meshList.end(),
		[&mesh](const Mesh& m) {return &m == &mesh; }),
		meshList.end());
}

void Scene::Render(Camera& camera)
{
	// Gets all the shader and meshes inside the unordered map
	for (auto& [shader, meshList] : m_meshes)
	{
		// Goes through the each mesh and calls the draw method
		for (auto& mesh : meshList)
		{
			mesh.Draw(*shader, camera);
		}
	}
}
