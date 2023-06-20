#version 330 core

// Position 
layout (location = 0) in vec3 aPos;
// Color
layout (location = 1) in vec3 aColor;
// Texture Coordinates
layout (location = 2) in vec2 aTex;
// Normals
layout (location = 3) in vec3 aNormal;

// Color for Fragment Shader
out vec3 color;
// Texture Coordinates for Fragment Shader
out vec2 texCoord;
// Normals for the Fragment Shader
out vec3 Normal;
// Current position for Fragment Shader
out vec3 crntPos;
out vec3 crntPos2;
// Camera Matrix
uniform mat4 camMatrix;
// Model Matrix
uniform mat4 model;
uniform mat4 model2;



void main()
{
	// Calculating current pos formula
	crntPos = vec3(model * vec4(aPos, 1.0f));
	crntPos2 = vec3(model2 * vec4(aPos, 1.0f));
	// Outputs positions of all vertices 
	gl_Position = camMatrix * vec4(aPos, 1.0f);

	// Color
	color = aColor;
	// Textures
	texCoord = aTex;
	// Normals
	Normal = aNormal;
}