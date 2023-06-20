#include"Camera.h"
float speed = 0.1f;
bool isPerspective;
// Camera object
Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
	isPerspective = true;
}
// Toggle for projection view for our main loop
void Camera::ToggleProjectionMode()
{
	isPerspective = !isPerspective;
}
// Camera Matrix
void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{

	// Initializes matrices since otherwise they will be the null matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	// Makes camera look in the right direction from the right position
	view = glm::lookAt(Position, Position + Orientation, Up);
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	// Adding our toggle for projection view
	if (isPerspective)
	{
		// Perspective projection
		projection = glm::perspective(glm::radians(FOVdeg), (float)width / (float)height, nearPlane, farPlane);
	}
	else
	{
		// Orthographic projection
		float aspect = (float)width / (float)height;
		float left = -1.0f * aspect;
		float right = 1.0f * aspect;
		float bottom = -1.0f;
		float top = 1.0f;
		projection = glm::ortho(left, right, bottom, top, nearPlane, farPlane);
	}
	// Exports the camera matrix to the Vertex Shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));

}

void Camera::Inputs(GLFWwindow* window)
{

	// Making our keybinds

	// Press/hold W to go forward
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Orientation;
	}

	// Press/hold A to go left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
	}

	// Press/hold S to go backwards
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -Orientation;
	}

	// Press/hold D to go right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	}

	// Press/hold Q to go up
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		Position += speed * Up;
	}

	// Press/hold S to go down
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		Position += speed * -Up;
	}


	
	double scrollY = 0.0;
	// Making our keybinds for mouse wheel up and down
	// Mouse scroll up, camera speed goes up, Mouse scroll down, camera speed goes down
	glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
		Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
		camera->speed += static_cast<float>(yoffset) * 0.1f;
		camera->speed = std::max(camera->speed, 0.1f);
		camera->speed = std::min(camera->speed, 5.0f);
	});

	// Mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Hides our cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Camera won't jump on the first click
		if (firstClick)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		// Storing cursor coordinates
		double mouseX;
		double mouseY;
		// Getting cursor coordinates
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Transforms and normalizes the cursors so they start at the middle of the screen
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		// Verticle Orientation change
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		// Checks to see if Orientation is within the window 
		if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			Orientation = newOrientation;
		}

		// Rotating orientation left and right
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		// Sets cursor to middle of screen
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides mouse once its released
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Making sure camera won't jump first time its clicked.
		firstClick = true;
	}
}