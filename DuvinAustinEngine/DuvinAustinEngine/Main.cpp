// include with " " looks in project directory
// #include "include\FreeImage.h"

// include with < > looks in a list of possible locations
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeImage.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

#include <iostream>
#include <vector>
#include <ctime>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"
#include "Timer.h"
#include "GameObject.h"
#include "Player.h"

int main() {
	// Initialize the window library
	if (glfwInit() == GL_FALSE) {
		return -1;
	}

	// Create a windowed mode window
	GLFWwindow* GLFWwindowPtr = glfwCreateWindow(800, 600, "Austin Duvin DSA1 Engine", NULL, NULL);

	// Make it the currently active window, or quit
	if (GLFWwindowPtr != nullptr) glfwMakeContextCurrent(GLFWwindowPtr);
	else {
		glfwTerminate();
		return -1;
	}

	// Initialize GLEW or quit
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		return -1;
	}

	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);

	// Create a vector of gameObjects (personal note: vectors in c++ are similar to lists in c#)
	std::vector<GameObject> gameObjects;
	// Create a vector of collectables, these have no effect on gameplay
	std::vector<GameObject> collectables;

	Player player = Player("models/PlayerShip.obj", "textures/PlayerTexture.png", glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), GLFWwindowPtr, GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_W, GLFW_KEY_S, 1.0f, sphere, true, 50.0f);

	gameObjects.push_back(GameObject("models/Track.obj", "textures/TrackTexture.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 10.0f), GLFWwindowPtr, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), axisAligned, false));
	gameObjects.push_back(GameObject("models/Track.obj", "textures/TrackTexture.png", glm::vec3(25.5f, 0.0f, -31.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 1.0f, 1.0f), GLFWwindowPtr, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), axisAligned, false));
	gameObjects.push_back(GameObject("models/Track.obj", "textures/TrackTexture.png", glm::vec3(56.5f, 0.0f, -56.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 10.0f), GLFWwindowPtr, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), axisAligned, false));
	gameObjects.push_back(GameObject("models/Track.obj", "textures/TrackTexture.png", glm::vec3(82.0f, 0.0f, -87.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 1.0f, 1.0f), GLFWwindowPtr, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), axisAligned, false));
	gameObjects.push_back(GameObject("models/Track.obj", "textures/TrackTexture.png", glm::vec3(112.5f, 0.0f, -62.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 10.0f), GLFWwindowPtr, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), axisAligned, false));
	gameObjects.push_back(GameObject("models/Track.obj", "textures/TrackTexture.png", glm::vec3(112.5f, 0.0f, -6.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 10.0f), GLFWwindowPtr, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), axisAligned, false));
	gameObjects.push_back(GameObject("models/Track.obj", "textures/TrackTexture.png", glm::vec3(59.0f, 0.0f, 25.25f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(20.0f, 1.0f, 1.0f), GLFWwindowPtr, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), axisAligned, false));

	collectables.push_back(GameObject("models/Collectable.obj", "textures/CollectableTexture.png", glm::vec3(0.0f, 1.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), GLFWwindowPtr, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), sphere, false));
	collectables.push_back(GameObject("models/Collectable.obj", "textures/CollectableTexture.png", glm::vec3(56.5f, 1.0f, -50.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), GLFWwindowPtr, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), sphere, false));
	collectables.push_back(GameObject("models/Collectable.obj", "textures/CollectableTexture.png", glm::vec3(112.5f, 1.0f, -62.0f), glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), GLFWwindowPtr, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), sphere, false));
	collectables.push_back(GameObject("models/Collectable.obj", "textures/CollectableTexture.png", glm::vec3(59.0f, 1.0f, 25.25f), glm::vec3(0.0f, 1.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), GLFWwindowPtr, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), sphere, false));

	GameObject floor = GameObject("models/Track.obj", "textures/FloorTexture.png", glm::vec3(59.0f, -10.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(100.0f, 1.0f, 100.0f), GLFWwindowPtr, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), axisAligned, false);

	// Initialize the shader
	Shader shader;
	if (shader.load() == true) {
		shader.use();
	}

	// Load the models and textures of all game objects
	player.loadModelTexture();
	floor.loadModelTexture();

	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i].loadModelTexture();
	}

	for (int i = 0; i < collectables.size(); i++) {
		collectables[i].loadModelTexture();
	}

	// Initialize the camera
	Camera camera(GLFWwindowPtr, glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), GLFW_KEY_LEFT, GLFW_KEY_RIGHT, GLFW_KEY_UP, GLFW_KEY_DOWN, false, colliderless, player);
	camera.buildMatrices();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);

	glm::vec3 light = glm::vec3(50.0f, 100.0f, 50.0f);  // Light location vector

	// Uploads light location
	glUniform3fv(4, 1, &light.x);

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(GLFWwindowPtr)) {
		Timer::update();
		// Update physical simulation
		// Draw buffered models
		// Process input/window events

		// Clear the canvas
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Check for collisions between the player and track
		for (int i = 0; i < gameObjects.size(); i++) {
			if (player.collidesWith(gameObjects[i])) {
				player.transform.location.y = gameObjects[i].transform.location.y + gameObjects[i].maxY + player.maxY;
				player.applyForce(player.gravity * -1.0f / Timer::dt);
				player.velocity.y = 0.0f;
			}
		}

		// Check for collisions between the player and collectables
		for (int i = 0; i < collectables.size(); i++) {
			if (player.collidesWith(collectables[i])) {
				collectables[i].shouldRender = false;
			}
		}

		// Check for collisions between the player and floor, which resets the player's position
		if (player.collidesWith(floor)) {
			player.transform.location = glm::vec3(0.0f, 3.0f, 0.0f);
		}

		// Update everything
		player.update();
		floor.update();
		
		for (int i = 0; i < gameObjects.size(); i++) {
			gameObjects[i].update();
		}

		for (int i = 0; i < collectables.size(); i++) {
			collectables[i].update();
		}

		// Apply movement to all objects
		player.applyMovement();

		for (int i = 0; i < gameObjects.size(); i++) {
			gameObjects[i].applyMovement();
		}

		for (int i = 0; i < collectables.size(); i++) {
			collectables[i].applyMovement();
		}

		// Swap the front (what the screen displays) and
		// back (what OpenGL draws to) buffers
		glfwSwapBuffers(GLFWwindowPtr);

		// Process queued window, mouse & keyboard callback events
		glfwPollEvents();

		camera.setParent(player);

		camera.update();

		if (glfwGetKey(GLFWwindowPtr, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(GLFWwindowPtr, GLFW_TRUE);
		}
	}

	// Unload textures
	player.unloadTexture();
	floor.unloadTexture();

	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i].unloadTexture();
	}

	for (int i = 0; i < collectables.size(); i++) {
		collectables[i].unloadTexture();
	}

	glfwTerminate();
	return 0;
}