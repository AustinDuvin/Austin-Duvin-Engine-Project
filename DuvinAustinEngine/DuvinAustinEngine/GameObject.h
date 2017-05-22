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

enum colliderType { colliderless, axisAligned, sphere };

struct Transform {
	glm::vec3 location;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 objectWorldTransform;
};

class GameObject
{
private:
	std::string modelFile;  // The model's filename
	std::string textureFile;  // The texture's filename
	
	glm::vec3 acceleration;
	glm::vec3 forceSave;
	bool canMove;
	bool canRotate;
public:
	glm::vec3 velocity;
	glm::vec3 force;
	Transform transform;  // The gameObject's transform
	float radius;
	bool applyGravity;
	float maxX;
	float maxY;
	float maxZ;
	glm::vec3 gravity;
	glm::vec3 between;
	glm::mat3 direction;
	bool shouldRender = true;

	GameObject();
	GameObject(GLFWwindow * window, glm::vec3 t, glm::vec3 r, glm::vec3 s, int controlLeft, int controlRight, int controlUp, int controlDown, colliderType collider, bool applyGravity);
	GameObject(std::string modelFilename, std::string textureFilename, glm::vec3 t, glm::vec3 r, glm::vec3 s, GLFWwindow * window, float mass, glm::vec3 force, colliderType collider, bool applyGravity);
	GameObject(std::string modelFilename, std::string textureFilename, glm::vec3 t, glm::vec3 r, glm::vec3 s, GLFWwindow * window, int controlLeft, int controlRight, int controlUp, int controlDown, float mass, colliderType collider, bool applyGravity, float speed);
	~GameObject();

	colliderType getCollider() const;
	Transform getTransform() const;

	void loadModelTexture();
	virtual void update();
	void unloadTexture();
	void move();
	virtual glm::vec3 input(glm::vec3 df);
	void applyForce(glm::vec3 deltaForce);
	void applyMovement();
	bool collidesWith(const GameObject& other);
protected:
	Model model;  // The model used by the gameObject
	Texture texture;  // The texture used by the gameObject
	bool controllable;
	GLFWwindow *window;
	float mass;
	float friction;
	float speed = 1.0f;
	colliderType collider;
	int controlLeft;
	int controlRight;
	int controlUp;
	int controlDown;
};

