#version 330 core

// Position data
layout (location = 0) in vec3 aPos;

// Normals
layout (location = 1) in vec3 aNormal;

// Color data
layout (location = 2) in vec3 aColor;

// Texture coordinates
layout (location = 3) in vec2 aTex;



// Outputs the curreent position for the fragment shader 
out vec3 crntPos;
// Sending the color data out to the fragment shader
out vec3 color;
// Outputs the normal data to the fragment shader
out vec3 Normal;
// Outputes the textire coords to the fragment shader
out vec2 texCoord;

// Inputs the Camera matrix from the maiun function
uniform mat4 camMatrix;
// Imports the model matrix from the main funtion
uniform mat4 model;

void main()
{
	// Calculates the current pos 
	crntPos = vec3(model * vec4(aPos, 1.0f));
	// Outputs the position of vertices
	gl_Position = camMatrix * vec4(aPos, 1.0);


	// Assigns color from vertex data to color
	color = aColor;
	// Assigns the texture coords to the vertex data texCoord
	texCoord = aTex;
	// Assigns the normal from vertex data to Normal
	Normal = aNormal;
}