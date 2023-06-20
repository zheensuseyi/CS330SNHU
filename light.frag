#version 330 core

out vec4 FragColor;

// Importing color for our lighting
uniform vec4 lightColor;

void main()
{
	// Color for our lighting
	FragColor = lightColor;
}