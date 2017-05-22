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

#include "Timer.h"
#include "GameObject.h"
class Camera :
	public GameObject
{
private:
	bool controllable;
	glm::mat4 worldview;
	glm::vec3 velocity;
	glm::mat3 rotMat;
	glm::mat3 walkMat; // Identical to the rotation matrix except it is fixed at 0.0f on the x axis so the camera can move as if it is a person walking instead of a flying camera
	glm::vec3 camRot;
	float speed;
	glm::vec3 location;
	glm::vec3 eye;
	glm::vec3 center;
	glm::vec3 up;
	glm::mat4 lookAtMat;
	float zoom;
	int width;
	int height;
	float fovy;
	float aspect;
	float zNear;
	float zFar;
	glm::mat4 perspectiveMat;
	GLFWwindow *window;
	GameObject parent;
public:
	Camera();
	Camera(GLFWwindow * window, glm::vec3 t, glm::vec3 r, glm::vec3 s, int controlLeft, int controlRight, int controlUp, int controlDown, bool controllable, colliderType collider, const GameObject& parent);
	~Camera();

	void update();
	void move();
	void buildMatrices();
	void setParent(const GameObject& parent);

	glm::mat4 getWorldview();
};

