#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"

class Camera
{
public:
	// Camera Vectors
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	// Making sure camera doesn't bug out with this command
	bool firstClick = true;
	bool isPerspective = true;

	// Width and Height of the window
	int width;
	int height;

	// Speed and Sensitivity of the Camera
	float speed = 0.1f;
	float sensitivity = 100.0f;

	// Constructor for inital values
	Camera(int width, int height, glm::vec3 position);
	// Passing Camera Matrix to Vertex Shader
	void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
	// Camera inputs
	void Inputs(GLFWwindow* window);
	// Projection toggle
	void ToggleProjectionMode();
	
};
#endif