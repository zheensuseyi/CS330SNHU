#version 330 core

layout (location = 0) in vec3 aPos;
// Model and camera matrix
uniform mat4 model2;
uniform mat4 camMatrix;

void main()
{
	// Calculating position for our light source
	gl_Position = camMatrix * model2 * vec4(aPos, 1.0f);
}