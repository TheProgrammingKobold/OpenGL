#pragma once


#include "VAO.h"
#include "EBO.h"
#include "Camera.h"
#include "Texture.h"

#include <vector>

/**
* 
* Notes:
* 
* A dynamic object that gets created leleeleeleeeeleleeel
* 
*/

enum MeshType
{
	TEXTURED_MESH,
	LIGHT_MESH
};

class Mesh
{
public:

	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, Texture& textures);


	void Draw(Shader& shader, Camera& camera);

private:

	std::vector<Vertex> m_vertices;
	std::vector<GLuint> m_indices;
	Texture m_textures;

	VAO m_VAO;

};

