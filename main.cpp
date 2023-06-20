// IMPORTANT: This program runs in x64 Release 
// Zheen H. Suseyi
// 06/15/2023
// CS330
// SNHU
// Note: I put my shaders, light shaders, shaderClass, VBO, EBO, VAO, Camera, Texture, into their own files and call them in my main function in order to keep the code tidy
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Controls for Camera: WASD to move around, Q to go up, E to go down, hold down left click to "hold" the camera in place,                        //
// Mousescroll up/down to increase or decrease camera speed while moving                                                                          //
// Press "P" to toggle projection view model, NOTE: IT MAY BUG OUT AND REQUIRE YOU TO PRESS IT A COUPLE TIMES BEFORE IT SWITCHES IM NOT SURE WHY  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"

// Setting our window size and initalizing it to variables
const unsigned int width = 800;
const unsigned int height = 800;
// Our y and z offsets in order to put the objects in their desired place
GLfloat yOffset = -0.035f;
GLfloat yOffset2 = 0.065f;
GLfloat yOffset3 = 0.26f;
GLfloat yOffset4 = 0.68f;
GLfloat zOffset = -0.6f;
GLfloat zOffset2 = 0.68f;


// Coordinates to make a Leafy Pyramid 
GLfloat points[] =
{	//                COORDINATES				/       COLORS	   /    TexCoord	/        NORMALS       //
	-0.09f, 0.0f + yOffset,	   0.09f + zOffset,      0.0f, 0.0f, 0.0f,  0.0f, 0.0f,      1.0f, 1.0f, 1.0f,
	-0.09f, 0.0f + yOffset,	  -0.09f + zOffset,      0.0f, 0.0f, 0.0f,  0.0f, 5.0f,      1.0f, 1.0f, 1.0f,
	 0.09f, 0.0f + yOffset,	  -0.09f + zOffset,      0.0f, 0.0f, 0.0f,  5.0f, 5.0f,      1.0f, 1.0f, 1.0f,
	 0.09f, 0.0f + yOffset,	   0.09f + zOffset,      0.0f, 0.0f, 0.0f,  5.0f, 0.0f,      1.0f, 1.0f, 1.0f,

	-0.09f, 0.0f + yOffset,	   0.09f + zOffset,      0.0f, 0.0f, 0.0f,  0.0f, 0.0f,	     1.0f, 1.0f, 1.0f,
	-0.09f, 0.0f + yOffset,	  -0.09f + zOffset,      0.0f, 0.0f, 0.0f,  5.0f, 0.0f,      1.0f, 1.0f, 1.0f,
	 0.0f,  0.1575f + yOffset, 0.0f + zOffset,	     0.0f, 0.0f, 0.0f,  2.5f, 5.0f,      1.0f, 1.0f, 1.0f,

	-0.09f, 0.0f + yOffset,   -0.09f + zOffset,      0.0f, 0.0f, 0.0f,  5.0f, 0.0f,      1.0f, 1.0f, 1.0f,
	 0.09f, 0.0f + yOffset,   -0.09f + zOffset,      0.0f, 0.0f, 0.0f,  0.0f, 0.0f,      1.0f, 1.0f, 1.0f,
	 0.0f,  0.1575f + yOffset, 0.0f + zOffset,       0.0f, 0.0f, 0.0f,  2.5f, 5.0f,	     1.0f, 1.0f, 1.0f,

	 0.09f, 0.0f + yOffset,   -0.09f + zOffset,      0.0f, 0.0f, 0.0f,  0.0f, 0.0f,	     1.0f, 1.0f, 1.0f,
	 0.09f, 0.0f + yOffset,    0.09f + zOffset,      0.0f, 0.0f, 0.0f,  5.0f, 0.0f,	     1.0f, 1.0f, 1.0f,
	 0.0f,  0.1575f + yOffset, 0.0f + zOffset,	     0.0f, 0.0f, 0.0f,  2.5f, 5.0f,	     1.0f, 1.0f, 1.0f,

	 0.09f, 0.0f + yOffset,    0.09f + zOffset,      0.0f, 0.0f, 0.0f,  5.0f, 0.0f,      1.0f, 1.0f, 1.0f,
	-0.09f, 0.0f + yOffset,    0.09f + zOffset,      0.0f, 0.0f, 0.0f,  0.0f, 0.0f,      1.0f, 1.0f, 1.0f,
	 0.0f,  0.1575f + yOffset, 0.0f + zOffset,	     0.0f, 0.0f, 0.0f,  2.5f, 5.0f,      1.0f, 1.0f, 1.0f,
};
// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	4, 6, 5,
	7, 9, 8,
	10, 12, 11,
	13, 15, 14
};
// Small Lemon Cube
GLfloat points2[] =
{ //     COORDINATES							 /        COLORS		/    TexCoord  //		 / normals //
	-0.10f, -0.10f + yOffset,  0.10f + zOffset,     1.0f, 1.0f, 0.0f,   0.25f, 0.66f,			1.0f, 1.0f, 1.0f,
	-0.10f, -0.10f + yOffset, -0.10f + zOffset,     1.0f, 1.0f, 0.0f,   0.25f, 0.33f,			1.0f, 1.0f, 1.0f,
	 0.10f, -0.10f + yOffset, -0.10f + zOffset,     1.0f, 1.0f, 0.0f,   0.75f, 0.33f,			1.0f, 1.0f, 1.0f,

	 0.10f, -0.10f + yOffset,  0.10f + zOffset,     1.0f, 1.0f, 0.0f,   0.75f, 0.66f,			1.0f, 1.0f, 1.0f,
	-0.10f,  0.10f + yOffset,  0.10f + zOffset,     1.0f, 1.0f, 0.0f,   0.75f, 1.0f,			1.0f, 1.0f, 1.0f,
	-0.10f,  0.10f + yOffset, -0.10f + zOffset,     1.0f, 1.0f, 0.0f,   0.75f, 0.66f,			1.0f, 1.0f, 1.0f,

	 0.10f,  0.10f + yOffset, -0.10f + zOffset,     1.0f, 1.0f, 0.0f,   0.25f, 0.66f,			1.0f, 1.0f, 1.0f,
	 0.10f,  0.10f + yOffset,  0.10f + zOffset,     1.0f, 1.0f, 0.0f,   0.25f, 1.0f,			1.0f, 1.0f, 1.0f
};

// Indices for Cube order
GLuint indices2[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 5,
	0, 5, 4,
	1, 2, 6,
	1, 6, 5,
	2, 3, 7,
	2, 7, 6,
	3, 0, 4,
	3, 4, 7,
	4, 5, 6,
	4, 6, 7
};

// Our Metal Desk Plane
GLfloat points3[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //	  / normals //
-1.0f, -0.14f, 1.0f,       0.5f, 0.5f, 0.5f,   0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
-1.0f, -0.14f, -1.0f,      0.5f, 0.5f, 0.5f,   0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
 1.0f, -0.14f, -1.0f,      0.5f, 0.5f, 0.5f,   1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
 1.0f, -0.14f, 1.0f,       0.5f, 0.5f, 0.5f,   1.0f, 0.0f,		0.0f, 1.0f, 0.0f

};
// Indices for Plane order
GLuint indices3[] =
{
	0, 1, 2,
	0, 2, 3
};

// Water Bottle 
GLfloat points4[] = {
	 //     COORDINATES							/        COLORS      /   TexCoord  //			/ normals //
	-0.1f, -0.2f + yOffset2,  0.1f + zOffset2,     1.0f, 1.0f, 0.0f,   0.25f, 0.66f,			1.0f, 1.0f, 1.0f,
	-0.1f, -0.2f + yOffset2, -0.1f + zOffset2,     1.0f, 1.0f, 0.0f,   0.25f, 0.33f,			1.0f, 1.0f, 1.0f,
	 0.1f, -0.2f + yOffset2, -0.1f + zOffset2,     1.0f, 1.0f, 0.0f,   0.75f, 0.33f,			1.0f, 1.0f, 1.0f,

	 0.1f, -0.2f + yOffset2,  0.1f + zOffset2,     1.0f, 1.0f, 0.0f,   0.75f, 0.66f,			1.0f, 1.0f, 1.0f,
	-0.1f,  0.2f + yOffset2,  0.1f + zOffset2,     1.0f, 1.0f, 0.0f,   0.75f, 1.0f,			    1.0f, 1.0f, 1.0f,
	-0.1f,  0.2f + yOffset2, -0.1f + zOffset2,     1.0f, 1.0f, 0.0f,   0.75f, 0.66f,			1.0f, 1.0f, 1.0f,

	 0.1f,  0.2f + yOffset2, -0.1f + zOffset2,     1.0f, 1.0f, 0.0f,   0.25f, 0.66f,			1.0f, 1.0f, 1.0f,
	 0.1f,  0.2f + yOffset2,  0.1f + zOffset2,     1.0f, 1.0f, 0.0f,   0.25f, 1.0f,			    1.0f, 1.0f, 1.0f
};
// Indices for Water Bottle 
GLuint indices4[] = {
	0, 1, 2,
	0, 2, 3,
	0, 1, 5,
	0, 5, 4,
	1, 2, 6,
	1, 6, 5,
	2, 3, 7,
	2, 7, 6,
	3, 0, 4,
	3, 4, 7,
	4, 5, 6,
	4, 6, 7
};

// Water Bottle Cap
GLfloat points5[] =
{ //                  COORDINATES             /          COLORS         /   TexCoord  //            / normals //
	-0.04f, -0.06f + yOffset3,  0.04f + zOffset2,     1.0f, 1.0f, 0.0f,   0.25f, 0.66f,			1.0f, 1.0f, 1.0f,
	-0.04f, -0.06f + yOffset3, -0.04f + zOffset2,     1.0f, 1.0f, 0.0f,   0.25f, 0.33f,			1.0f, 1.0f, 1.0f,
	 0.04f, -0.06f + yOffset3, -0.04f + zOffset2,     1.0f, 1.0f, 0.0f,   0.75f, 0.33f,			1.0f, 1.0f, 1.0f,

	 0.04f, -0.06f + yOffset3,  0.04f + zOffset2,     1.0f, 1.0f, 0.0f,   0.75f, 0.66f,			1.0f, 1.0f, 1.0f,
	-0.04f,  0.06f + yOffset3,  0.04f + zOffset2,     1.0f, 1.0f, 0.0f,   0.75f, 1.0f,			1.0f, 1.0f, 1.0f,
	-0.04f,  0.06f + yOffset3, -0.04f + zOffset2,     1.0f, 1.0f, 0.0f,   0.75f, 0.66f,			1.0f, 1.0f, 1.0f,

	 0.04f,  0.06f + yOffset3, -0.04f + zOffset2,     1.0f, 1.0f, 0.0f,   0.25f, 0.66f,			1.0f, 1.0f, 1.0f,
	 0.04f,  0.06f + yOffset3,  0.04f + zOffset2,     1.0f, 1.0f, 0.0f,   0.25f, 1.0f,			1.0f, 1.0f, 1.0f
};

// Indices for Water Bottle Cap order
GLuint indices5[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 5,
	0, 5, 4,
	1, 2, 6,
	1, 6, 5,
	2, 3, 7,
	2, 7, 6,
	3, 0, 4,
	3, 4, 7,
	4, 5, 6,
	4, 6, 7
};

// Long Wood Pole
GLfloat points6[] =
{ //     COORDINATES             /        COLORS             /   TexCoord  //       / normals //
	-0.02f, -0.8f + yOffset4,  0.02f,     1.0f, 1.0f, 0.0f,   0.0f, 0.0f,			1.0f, 1.0f, 1.0f,
	-0.02f, -0.8f + yOffset4, -0.02f,     1.0f, 1.0f, 0.0f,   0.0f, 0.0f,			1.0f, 1.0f, 1.0f,
	 0.02f, -0.8f + yOffset4, -0.02f,     1.0f, 1.0f, 0.0f,   0.0f, 0.0f,			1.0f, 1.0f, 1.0f,

	 0.02f, -0.8f + yOffset4,  0.02f,     1.0f, 1.0f, 0.0f,   0.0f, 0.0f,			1.0f, 1.0f, 1.0f,
	-0.02f,  0.8f + yOffset4,  0.02f,     1.0f, 1.0f, 0.0f,   0.0f, 0.0f,			1.0f, 1.0f, 1.0f,
	-0.02f,  0.8f + yOffset4, -0.02f,     1.0f, 1.0f, 0.0f,   0.0f, 0.0f,			1.0f, 1.0f, 1.0f,

	 0.02f,  0.8f + yOffset4, -0.02f,     1.0f, 1.0f, 0.0f,   0.0f, 0.0f,			1.0f, 1.0f, 1.0f,
	 0.02f,  0.8f + yOffset4,  0.02f,     1.0f, 1.0f, 0.0f,   0.0f, 0.0f,			1.0f, 1.0f, 1.0f
};

// Indices for Long Wood Pole order
GLuint indices6[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 5,
	0, 5, 4,
	1, 2, 6,
	1, 6, 5,
	2, 3, 7,
	2, 7, 6,
	3, 0, 4,
	3, 4, 7,
	4, 5, 6,
	4, 6, 7
};
// Points for light cube #1
GLfloat lightPoints[] =
{ //     COORDINATES     // 
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};
// Indices for light cube #1
GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

// Points for light cube #2
GLfloat lightPoints2[] =
{ //     COORDINATES     // 
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

// Indices for light cube #2
GLuint lightIndices2[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

// Main function
int main()
{
	// Initialize GLFW
	glfwInit();

	// Let GLFW what version of OpenGL we are using 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Telling GLFW we are using the CORE profile, not going to use outdated functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Making our window using GLFW
	GLFWwindow* window = glfwCreateWindow(width, height, "Some random items relaxing at a Starbucks Table during a nice sunny day", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Make the window the current context
	glfwMakeContextCurrent(window);

	// Load GLAD to configure OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	glViewport(0, 0, width, height);



	// Generates Shader object using our seperate files default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");


	// Moving our lemon object to the right
	for (int i = 0; i < sizeof(points) / sizeof(float); i += 11) {
		points[i] += 0.55f; // Move the Pyramid right by 0.5 units
	}
	for (int i = 0; i < sizeof(points2) / sizeof(float); i += 11) {
		points2[i] += 0.55f; // Move the Cube right by 0.5 units
	}

	// Moving our Water Bottle to the left
	for (int i = 0; i < sizeof(points4) / sizeof(float); i += 11) {
		points4[i] -= 0.57f; // Move the Water Bottle left by 0.5 units
	}
	// Moving our Water Cap to the left
	for (int i = 0; i < sizeof(points5) / sizeof(float); i += 11) {
		points5[i] -= 0.57f; // Move the Water Bottle left by 0.5 units
	}


	// Generates Vertex Array Object for our leafy pyramid using our seperate files and binds it
	VAO VAO1;
	VAO1.Bind();
	// Generates Vertex Buffer Object for our leafy pyramid using our seperate files and links it to vertices
	VBO VBO1(points, sizeof(points));
	// Generates Element Buffer Object for our leafy pyramid using our seperate files and links it to indices
	EBO EBO1(indices, sizeof(indices));
	// Links VBO attributes to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));


	// Generates Vertex Array Object for our small cube using our seperate files and binds it
	VAO VAO2;
	VAO2.Bind();
	// Generates Vertex Buffer Object for our small cube using our seperate files and links it to vertices
	VBO VBO2(points2, sizeof(points2));
	// Generates Element Buffer Object for our small cube using our seperate files and links it to indices
	EBO EBO2(indices2, sizeof(indices2));
	// Links VBO attributes to VAO
	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));


	// Generates Vertex Array Object for our desk plane using our seperate files and binds it
	VAO VAO3;
	VAO3.Bind();
	// Generates Vertex Buffer Object for our desk plane using our seperate files and links it to vertices
	VBO VBO3(points3, sizeof(points3));
	// Generates Element Buffer Object for our desk plane using our seperate files and links it to indices
	EBO EBO3(indices3, sizeof(indices2));
	// Links VBO attributes to VAO
	VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO3.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO3.LinkAttrib(VBO3, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO3.LinkAttrib(VBO3, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));


	// Generates Vertex Array Object for our Water Bottle using our seperate files and binds it
	VAO VAO4;
	VAO4.Bind();
	// Generates Vertex Buffer Object for our Water Bottle using our seperate files and links it to vertices
	VBO VBO4(points4, sizeof(points4));
	// Generates Element Buffer Object for our Water Bottle using our seperate files and links it to indices
	EBO EBO4(indices4, sizeof(indices4));
	// Links VBO attributes to VAO
	VAO4.LinkAttrib(VBO4, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO4.LinkAttrib(VBO4, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO4.LinkAttrib(VBO4, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO4.LinkAttrib(VBO4, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));


	// Generates Vertex Array Object for our Water Cap using our seperate files and binds it
	VAO VAO5;
	VAO5.Bind();
	// Generates Vertex Buffer Object for our Water Cap  using our seperate files and links it to vertices
	VBO VBO5(points5, sizeof(points5));
	// Generates Element Buffer Object for our Water Cap  using our seperate files and links it to indices
	EBO EBO5(indices5, sizeof(indices5));
	// Links VBO attributes to VAO
	VAO5.LinkAttrib(VBO5, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO5.LinkAttrib(VBO5, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO5.LinkAttrib(VBO5, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO5.LinkAttrib(VBO5, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	

	// Generates Vertex Array Object for our Wooden Pole using our seperate files and binds it
	VAO VAO6;
	VAO6.Bind();
	// Generates Vertex Buffer Object for our Wooden Pole using our seperate files and links it to vertices
	VBO VBO6(points6, sizeof(points6));
	// Generates Element Buffer Object for our Wooden Pole using our seperate files and links it to indices
	EBO EBO6(indices6, sizeof(indices6));
	// Links VBO attributes to VAO
	VAO6.LinkAttrib(VBO6, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO6.LinkAttrib(VBO6, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO6.LinkAttrib(VBO6, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO6.LinkAttrib(VBO6, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	
	// Light cube shader
	Shader lightShader("light.vert", "light.frag");
	Shader lightShader2("light2.vert", "light2.frag");

	// Generates Vertex Array Object for our light cube using our seperate files and binds it
	VAO lightVAO;
	lightVAO.Bind();
	// Generates Vertex Buffer Object for our light cube using our seperate files and links it to vertices
	VBO lightVBO(lightPoints, sizeof(lightPoints));
	// Generates Element Buffer Object for our light cube using our seperate files and links it to indices
	EBO lightEBO(lightIndices, sizeof(lightIndices));
	// Links VBO attributes to VAO
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	
	// Generates Vertex Array Object for our light cube2 using our seperate files and binds it
	VAO lightVAO2;
	lightVAO2.Bind();
	// Generates Vertex Buffer Object for our light cube2 using our seperate files and links it to vertices
	VBO lightVBO2(lightPoints2, sizeof(lightPoints2));
	// Generates Element Buffer Object for our light cube2 using our seperate files and links it to indices
	EBO lightEBO2(lightIndices2, sizeof(lightIndices2));
	// Links VBO attributes to VAO
	lightVAO2.LinkAttrib(lightVBO2, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();
	VAO3.Unbind();
	VBO3.Unbind();
	EBO3.Unbind();
	VAO4.Unbind();
	VBO4.Unbind();
	EBO4.Unbind();
	VAO5.Unbind();
	VBO5.Unbind();
	EBO5.Unbind();
	VAO6.Unbind();
	VBO6.Unbind();
	EBO6.Unbind();
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();
	lightVAO2.Unbind();
	lightVBO2.Unbind();
	lightEBO2.Unbind();
	

	// Color of our light which is natural sunlight
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	// Position of our light
	glm::vec3 lightPos = glm::vec3(-1.9f, 0.5f, -1.9f);
	// Light model 
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);
	// Activating our light shader
	lightShader.Activate();
	// Matrices for our light shader 
	// Model for lightShader, comment this line out to make the cube not show
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	// Color for lightShader
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	// Activating shader program
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	// Color for shaderProgram
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	// Position for shaderProgram
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	// Color of our light which is natural sunlight
	glm::vec4 lightColor2 = glm::vec4(1.0f, 1.0f, 0.7f, 1.0f);
	// Position of our light
	glm::vec3 lightPos2 = glm::vec3(1.9f, 0.5f, 1.9f);
	// Light model 
	glm::mat4 lightModel2 = glm::mat4(1.0f);
	lightModel2 = glm::translate(lightModel2, lightPos2);
	lightShader2.Activate();
	// Matrices for our light shader 
	// Model for lightShader, comment this line out to make the cube not show
	glUniformMatrix4fv(glGetUniformLocation(lightShader2.ID, "model2"), 1, GL_FALSE, glm::value_ptr(lightModel2));
	// Color for lightShader
	glUniform4f(glGetUniformLocation(lightShader2.ID, "lightColor2"), lightColor2.x, lightColor2.y, lightColor2.z, lightColor2.w);
	// Activating shader program
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model2"), 1, GL_FALSE, glm::value_ptr(lightModel2));
	// Color for shaderProgram
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor2"), lightColor2.x, lightColor2.y, lightColor2.z, lightColor2.w);
	// Position for shaderProgram
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos2"), lightPos2.x, lightPos2.y, lightPos2.z);


	// Prepping our Textures
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
	// Leaf Texture for Pyramid
	Texture leafTex("leaf.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	leafTex.texUnit(shaderProgram, "tex0", 0);
	// Lemon Texture for Cube
	Texture lemonTex("lemon.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	lemonTex.texUnit(shaderProgram, "tex0", 0);
	// Metal Texture for Plane
	Texture metalTex("metal.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	metalTex.texUnit(shaderProgram, "tex0", 0);
	// Wood Texture for Pole
	Texture woodTex("wood.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	woodTex.texUnit(shaderProgram, "tex0", 0);
	// Black Metallic Texture for Water Bottle
	Texture blackTex("black.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	blackTex.texUnit(shaderProgram, "tex0", 0);
	// Black Plastic Texture for Water Bottle Cap
	Texture plasticTex("plastic.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	plasticTex.texUnit(shaderProgram, "tex0", 0);

	// Enable the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Setting up our Camera
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// Main render loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.5f, 1.0f, 1.0f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Specify the Shader Program to be used by OpenGL
		shaderProgram.Activate();

		// Exporting our camera pos to Fragment Shader for our lighting
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);

		// Setting up our camera and inputs
		glfwSetWindowUserPointer(window, &camera);
		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
		// Press P to toggle projection view 
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		{
			camera.ToggleProjectionMode();
		}

		// Bind the VAO to render the Pyramid
		VAO1.Bind();
		// Binding our leaf texture for our Pyramid
		leafTex.Bind();
		// Drawing our leafy pyramid
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		// Bind the VAO to render the small cube
		VAO2.Bind();
		// Binding our lemon texture for our Cube
		lemonTex.Bind();
		// Drawing our small cube
		glDrawElements(GL_TRIANGLES, sizeof(indices2) / sizeof(int), GL_UNSIGNED_INT, 0);

		// Bind the VAO to render the Plane
		VAO3.Bind();
		// Binding our metal texture for our Plane
		metalTex.Bind();
		// Drawing our desk plane
		glDrawElements(GL_TRIANGLES, sizeof(indices3) / sizeof(int), GL_UNSIGNED_INT, 0);

		// Bind the VAO to render the Water Bottle
		VAO4.Bind();
		blackTex.Bind();
		// Drawing our Water Bottle
		glDrawElements(GL_TRIANGLES, sizeof(indices4) / sizeof(int), GL_UNSIGNED_INT, 0);

		// Bind the VAO to render the Water Cap
		VAO5.Bind();
		plasticTex.Bind();
		// Drawing our Water Cap
		glDrawElements(GL_TRIANGLES, sizeof(indices5) / sizeof(int), GL_UNSIGNED_INT, 0);

		// Bind the VAO to render the Wooden Pole
		VAO6.Bind();
		woodTex.Bind();
		// Drawing our Wooden Pole
		glDrawElements(GL_TRIANGLES, sizeof(indices6) / sizeof(int), GL_UNSIGNED_INT, 0);


		// Activating light shader
		lightShader.Activate();
		camera.Matrix(45.0f, 0.1f, 100.0f, lightShader, "camMatrix");
		// Binding the VAO to render the cube
		lightVAO.Bind();
		// Drawing our light cube
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		// Activating light shader
		lightShader2.Activate();
		camera.Matrix(45.0f, 0.1f, 100.0f, lightShader2, "camMatrix");
		// Binding the VAO to render the cube2
		lightVAO2.Bind();
		// Drawing our light cube2
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices2) / sizeof(int), GL_UNSIGNED_INT, 0);

		// Swap the front and back buffers
		glfwSwapBuffers(window);
		// Poll for any events
		glfwPollEvents();
	}

	// Clean up time
	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	VAO2.Delete();
	VBO2.Delete();
	EBO2.Delete();
	VAO3.Delete();
	VBO3.Delete();
	EBO3.Delete();
	VAO4.Delete();
	VBO4.Delete();
	EBO4.Delete();
	VAO5.Delete();
	VBO5.Delete();
	EBO5.Delete();
	VAO6.Delete();
	VBO6.Delete();
	EBO6.Delete();
	lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	lightVAO2.Delete();
	lightVBO2.Delete();
	lightEBO2.Delete();
	leafTex.Delete();
	lemonTex.Delete();
	metalTex.Delete();
	blackTex.Delete();
	plasticTex.Delete();
	woodTex.Delete();
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}