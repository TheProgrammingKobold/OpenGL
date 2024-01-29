#version 330 core

// Outputs the colors
out vec4 FragColor;


// IMports currnet pos
in vec3 crntPos;
// Imports the normal from the vertex shader
in vec3 Normal;
// Inputs color data from vertex shader
in vec3 color;
// Inputs the texture coords from the vertex shader
in vec2 texCoord;

// Gets the texture unit from the main function
uniform sampler2D tex0;
// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of thje light from the main function
uniform vec3 lightPos;
// Gets the position of the cmera from the main function
uniform vec3 camPos;

void main()
{
	// ambient lighting
	float ambient = 0.1f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighing
	float specularLight = 0.2f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;


	FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient + specular);
}
