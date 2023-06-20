#version 330 core

out vec4 FragColor2;

// Importing color for our lighting
uniform vec4 lightColor2;

void main()
{
	// Color for our lighting
	FragColor2 = lightColor2;
}