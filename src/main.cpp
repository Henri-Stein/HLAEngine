#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <tiffio.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Rendering/Shader.hpp"
#include "Rendering/VAO.hpp"
#include "Rendering/VBO.hpp"
#include "Rendering/EBO.hpp"
#include "Rendering/MeshRenderer.hpp"
#include "Rendering/Texture.hpp"
#include "Camera/FlyCamera.hpp"
#include "Camera/FPSCamera.hpp"
#include "Mesh/Plane.hpp"
#include "Mesh/Box.hpp"

#include <optional>


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

bool key_c_pressed = false;
bool key_z_pressed = false;
bool shouldRecompileShaders = false;
bool wireframeMode = false;

/*
* Camera default settings
*/
FlyCamera camera(glm::vec3(0.0f, 0.0f, 3.0f));

bool firstMouse = true;

float deltaTime = 0.0f; // Time between the start of the current frame and the start of the last frame (or the computation time of the last frame)
float lastFrame = 0.0f; // Time of last frame

float lastMouseX = WINDOW_WIDTH / 2.0, lastMouseY = WINDOW_HEIGHT / 2.0;

glm::vec3 sunPos(1.2f, 2.0f, 2.0f);
glm::vec3 sunDir(-0.2f, -1.0f, -0.3f);
glm::vec3 sunColor(1.f, 1.f, 1.f);


glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};

glm::vec3 pointLightColors[] = {
	glm::vec3(0.2f,  0.3f,  1.0f),
	glm::vec3(0.2f,  0.3f,  1.0f),
	glm::vec3(0.2f,  0.3f,  1.0f),
	glm::vec3(0.2f,  0.3f,  1.0f)
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse) // Initially set to true, then false after capturing the cursor for the first time
	{
		lastMouseX = xPos;
		lastMouseY = yPos;
		firstMouse = false;
	}

	float xOffset = xPos - lastMouseX;
	float yOffset = lastMouseY - yPos; // Reversed since y-coordinates range from bottom to top
	lastMouseX = xPos;
	lastMouseY = yPos;
	camera.ProcessMouseMovement(xOffset, yOffset);
}


void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	camera.ProcessMouseScroll(yOffset);
}

// Caution, GLFW is in QWERTY no matter what is the user keyboard configuration
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && !key_c_pressed) // Condition is true only once after pressing 'C', and not each frames while pressing 'C'
	{
		key_c_pressed = true;
		shouldRecompileShaders = true;
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE)
		key_c_pressed = false;

	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS && !key_z_pressed) // Condition is true only once after pressing 'Z', and not each frames while pressing 'Z'
	{
		key_z_pressed = true;
		wireframeMode = !wireframeMode;
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_RELEASE)
		key_z_pressed = false;


	// Camera Mmovements
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::RIGHT, deltaTime);
}

std::string getShaderPath(std::string filename)
{
	return std::string(RESOURCES_PATH) + std::string("/shaders/") + filename;
}

std::optional<Texture> loadTexture(std::string filepath)
{
	int width, height, nbChannels;

	unsigned char* data = stbi_load(filepath.c_str(),
		&width,
		&height,
		&nbChannels,
		0);
	if (data)
	{
		GLenum format = GL_RED;
		if (nbChannels == 1)
			format = GL_RED;
		else if (nbChannels == 3)
			format = GL_RGB;
		else if (nbChannels == 4)
			format = GL_RGBA;

		Texture tex{ data, static_cast<uint32_t>(width), static_cast<uint32_t>(height), GL_TEXTURE_2D, format, GL_UNSIGNED_BYTE};
		stbi_image_free(data);
		return tex;
	}
	else
	{
		std::cout << "Texture failed to load at path: " << filepath << std::endl;
	}
	stbi_image_free(data);
	return {};
}

int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using
	// In this case, we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Tell GLFW we are using the CORE profile
	// So that mean we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWindow object of 800 by 800 pixels
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "HLAEngine", NULL, NULL);

	// Error check if the window fails to create 
	if (window == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it's configure OpenGL
	gladLoadGL();

	// Specify the viewport of OpenGL in the window
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	// Set a callback that gets called each time the window is resized
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// tell GLFW that it should hide the cursor and capture it
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Set cursor callback
	glfwSetCursorPosCallback(window, mouse_callback);

	glfwSetScrollCallback(window, scroll_callback);

	// Generate Shader object using shaders default.vert and default.frag
	Shader lightingShaderProgram(getShaderPath("lighting.vert"), getShaderPath("lighting.frag"));
	Shader lightCubeShaderProgram(getShaderPath("light_cube.vert"), getShaderPath("light_cube.frag"));

	/* Meshes */
	Box meshCube{ 1, 1, 1 };
	Box meshLight{ 1, 1, 1 };

	/* Mesh Renderers */
	MeshRenderer cubeRenderer(meshCube);
	MeshRenderer lightRenderer(meshLight, 0, -1, -1, -1, -1);

	/* Transforms */
	Transform cubeTrans{};

	/* Load textures */
	std::string pathTexContainerDif = std::string(TEXTURES_PATH) + std::string("/container.png");
	std::optional<Texture> texContainer = loadTexture(pathTexContainerDif);

	std::string pathTexContainerSpec = std::string(TEXTURES_PATH) + std::string("/container_specular.png");
	std::optional<Texture> texContainerSpec = loadTexture(pathTexContainerSpec);

	std::string pathTexContainerEmi = std::string(TEXTURES_PATH) + std::string("/matrix_emission_map.jpg");
	std::optional<Texture> texContainerEmi = loadTexture(pathTexContainerEmi);


	/* Get maximum number of vertex attribute per VAO */
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;


	std::vector<glm::vec3> cubePositions = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	std::vector<Transform> cubeTransforms{}; // All cube should render the same, so no need to recreate a Mesh and a MeshRenderer for each of them
	for (int i = 0; i < cubePositions.size(); ++i)
	{
		cubeTransforms.emplace_back();
		cubeTransforms[i].setPosition(cubePositions[i]);
		float angle = 20.0f * i;
		cubeTransforms[i].setRotation(angle, glm::vec3(1.f, 0.3f, 0.5f));
	}

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Inputs
		processInput(window);
		if (shouldRecompileShaders)
		{
			lightCubeShaderProgram.Compile();
			lightingShaderProgram.Compile();
			glUseProgram(0);
			shouldRecompileShaders = false;
			std::cout << "Recompiled" << std::endl;
		}
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.03f, 0.07f, 0.09f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, wireframeMode ? GL_LINE : GL_FILL); // User can switch between wireframeMode anf fill mode using the QWERTY key 'w'
		glPointSize(5.f);

		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera._zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.f);
		//lightPos = { cos(glfwGetTime() * 0.5f) * 3.f, 2.f, sin(glfwGetTime() * 0.5f) * 3.f };
		//lightColor = { (sin(glfwGetTime() * 2.0f) + 1.f) / 2.f, (sin(glfwGetTime() * 0.7f) + 1.f) / 2.f, (sin(glfwGetTime() * 1.3f) + 1.f) / 2.f };
		glm::vec3 sunDiffuse = sunColor * glm::vec3(0.5f);
		glm::vec3 sunAmbient = sunDiffuse * glm::vec3(0.2f);
		glm::vec3 sunSpecular = sunColor * glm::vec3(1.f, 1.f, 1.f);

		/*********************/
		// Draw the cube
		lightingShaderProgram.Activate();
		if (texContainer.has_value())
		{
			texContainer->Activate(0);
			lightingShaderProgram.setUniform("material.diffuse", 0);
		}
		if (texContainerSpec.has_value())
		{
			texContainerSpec->Activate(1);
			lightingShaderProgram.setUniform("material.specular", 1);
		}
		if (texContainerEmi.has_value())
		{
			texContainerEmi->Activate(2);
			lightingShaderProgram.setUniform("material.emission", 2);
		}
		lightingShaderProgram.setUniform("material.shininess", 32.0f);

		// Directional light (the Sun)
		lightingShaderProgram.setUniform("dirLight.direction", sunDir);
		lightingShaderProgram.setUniform("dirLight.ambient", sunAmbient);
		lightingShaderProgram.setUniform("dirLight.diffuse", sunDiffuse);
		lightingShaderProgram.setUniform("dirLight.specular", sunSpecular);

		// Point light
		for (int i = 0; i < 4; ++i)
		{
			std::string uniformName = std::string{ "pointLights[" } + std::to_string(i) + std::string{ "]" };
			lightingShaderProgram.setUniform(uniformName + std::string{ ".position" }, pointLightPositions[i]);
			lightingShaderProgram.setUniform(uniformName + std::string{ ".constant" }, 1.0f);
			lightingShaderProgram.setUniform(uniformName + std::string{ ".linear" }, 0.09f);
			lightingShaderProgram.setUniform(uniformName + std::string{ ".quadratic" }, 0.032f );

			glm::vec3 pointLightDiffuse = pointLightColors[i] * glm::vec3(0.5f);
			glm::vec3 pointLightAmbient = pointLightDiffuse * glm::vec3(0.2f);
			glm::vec3 pointLightSpecular = pointLightColors[i] * glm::vec3(1.f, 1.f, 1.f);

			lightingShaderProgram.setUniform(uniformName + std::string{ ".ambient" }, pointLightAmbient);
			lightingShaderProgram.setUniform(uniformName + std::string{ ".diffuse" }, pointLightDiffuse);
			lightingShaderProgram.setUniform(uniformName + std::string{ ".specular" }, pointLightSpecular);
		}

		// Flashlight on the camera
		glm::vec3 spotLightColor = glm::vec3(0.09f, 1.f, 0.02f);
		glm::vec3 spotLightDiffuse = spotLightColor * glm::vec3(0.5f);
		glm::vec3 spotLightAmbient = spotLightDiffuse * glm::vec3(0.2f);
		glm::vec3 spotLightSpecular = spotLightColor * glm::vec3(1.f, 1.f, 1.f);
		lightingShaderProgram.setUniform("spotLight.position", camera._position);
		lightingShaderProgram.setUniform("spotLight.direction", camera._front);
		lightingShaderProgram.setUniform("spotLight.cutOff", glm::cos(glm::radians(8.5f)));
		lightingShaderProgram.setUniform("spotLight.outerCutOff", glm::cos(glm::radians(10.5f)));
		lightingShaderProgram.setUniform("spotLight.constant", 1.0f);
		lightingShaderProgram.setUniform("spotLight.linear", 0.09f);
		lightingShaderProgram.setUniform("spotLight.quadratic", 0.032f);
		lightingShaderProgram.setUniform("spotLight.ambient", spotLightAmbient);
		lightingShaderProgram.setUniform("spotLight.diffuse", spotLightDiffuse);
		lightingShaderProgram.setUniform("spotLight.specular", spotLightSpecular);



		lightingShaderProgram.setUniform("time", static_cast<float>(glfwGetTime()));
		lightingShaderProgram.setUniform("view", view);
		lightingShaderProgram.setUniform("projection", projection);

		for (int i = 0; i < cubeTransforms.size(); ++i)
		{
			//cubeTransforms[i].rotate(glm::radians(30.f * deltaTime), glm::vec3(0.f, 1.f, 0.f));
			lightingShaderProgram.setUniform("model", cubeTransforms[i].getModelMat());
			cubeRenderer.draw(); // One renderer to draw each transform
		}

		/*********************/
		// Draw the point lights
		for (int i = 0; i < 4; ++i)
		{
			Transform lightTrans{ pointLightPositions[i] };
			lightTrans.setScale(glm::vec3(0.2f));
			lightCubeShaderProgram.Activate();
			lightCubeShaderProgram.setUniform("lightColor", pointLightColors[i]);
			lightCubeShaderProgram.setUniform("model", lightTrans.getModelMat());
			lightCubeShaderProgram.setUniform("view", view);
			lightCubeShaderProgram.setUniform("projection", projection);
			lightRenderer.draw();
		}

		// Swaps front and back buffers
		glfwSwapBuffers(window);
		// Takes care of all GLFW events (such as window resizing or closing)
		glfwPollEvents();
	}

	lightingShaderProgram.Delete();
	lightCubeShaderProgram.Delete();

	glfwDestroyWindow(window);
	// Properly clean/delete all of GLFW's ressources that were allocated
	glfwTerminate(); 
	
	return 0;
}