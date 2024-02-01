#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, Texture& textures)
	: m_vertices(vertices), m_indices(indices), m_textures(textures)
{
	m_VAO.bind();
	// Gens a vertex buffer object and links it
	VBO VBO(vertices);
	// Generates element buffer object and links indices
	EBO EBO(indices);
	// Links the VBO
	m_VAO.linkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);					// Position
	m_VAO.linkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));  // Normals
	m_VAO.linkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));  // Color
	m_VAO.linkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));  // TexCoords

	// Unbinds all to prevent accidental changes
	m_VAO.unbind();
	VBO.unbind();
	EBO.unbind();
}

void Mesh::Draw(Shader& shader, Camera& camera)
{
	// Binds shader to access uniforms
	shader.activate();
	m_VAO.bind();

	m_textures.bind();

	// Taking care of camera matrix
	glUniform3f(shader.getUniform("camMatrix"), camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
	camera.matrix(shader, "camMatrix");

	// Draw call
	glDrawElements(GL_TRIANGLES, (GLsizei)m_indices.size(), GL_UNSIGNED_INT, 0);
}
