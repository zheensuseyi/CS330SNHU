#version 330 core

// Making our colors in RGBA
out vec4 FragColor;
out vec4 FragColor2;
// Getting the colors from the Vertex Shader
in vec3 color;
// Getting the texture coordinates from the Vertex Shader
in vec2 texCoord;
// Getting the normals from the Vertex Shader
in vec3 Normal;
// Getting the current position from the Vertex Shader
in vec3 crntPos;
in vec3 crntPos2;

// Texture from the main function
uniform sampler2D tex0;
// Color of the light from main function
uniform vec4 lightColor;
uniform vec4 lightColor2;
// Position of the light from main function
uniform vec3 lightPos;
uniform vec3 lightPos2;
// Position of the camera from  main function
uniform vec3 camPos;

void main()
{
	// Ambient lighting (key light) at 120% for entire scene
	float ambient = 1.2f;

	// Diffuse lighting left at default for both
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	vec3 lightDirection2 = normalize(lightPos2 - crntPos2);
	float diffuse = max(dot(normal, lightDirection), 0.0f);
	float diffuse2 = max(dot(normal, lightDirection2), 0.0f);

	// Specular lighting (fill light) at 8% for both light sources
	float specularLight = 0.08f;
	float specularLight2 = 0.08f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 viewDirection2 = normalize(camPos - crntPos2);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	vec3 reflectionDirection2 = reflect(-lightDirection2, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.1f), 4);
	float specAmount2 = pow(max(dot(viewDirection2, reflectionDirection2), 0.2f), 8);
	float specular = specAmount * specularLight;
	float specular2 = specAmount2 * specularLight2;
	// Final color and lighting
	FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient + specular);
	FragColor2 = texture(tex0, texCoord) * lightColor2 * (diffuse2 + ambient + specular2);

}