#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeImage.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

#include "Shader.h"
#include "Model.h"
#include "Texture.h"
#include "Rigidbody.h"
#include "GameObject.h"
class Player :
	public GameObject
{
public:
	Player();
	Player(std::string modelFilename, std::string textureFilename, glm::vec3 t, glm::vec3 r, glm::vec3 s, GLFWwindow * window, int controlLeft, int controlRight, int controlUp, int controlDown, float mass, colliderType collider, bool applyGravity, float speed);
	~Player();

	void update() override;
	void move();
	glm::vec3 input(glm::vec3 df) override;
};

