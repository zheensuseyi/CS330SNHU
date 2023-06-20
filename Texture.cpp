#include"Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	// Set the type of the texture to the texture object
	type = texType;

	// Store the width, height, and color channels of the image
	int widthImg, heightImg, numColCh;
	// Flip the image to make it appear right side up
	stbi_set_flip_vertically_on_load(true);
	// Read the image from a file and store it in bytes
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	// Generate an OpenGL texture object
	glGenTextures(1, &ID);
	// Assign the texture to a Texture Unit
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	// Configure the algorithm used to resize the image
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configure how the texture repeats
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Assign the image to the OpenGL Texture object
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	// Generate MipMaps
	glGenerateMipmap(texType);

	// Free the image data as it is already in the OpenGL Texture object
	stbi_image_free(bytes);

	// Unbind the OpenGL Texture object to prevent accidental modifications
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Get the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// Activate the shader
	shader.Activate();
	// Set the value of the uniform
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	// Bind the texture to the current OpenGL context
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	// Unbind the texture from the current OpenGL context
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	// Delete the texture object from OpenGL
	glDeleteTextures(1, &ID);
}