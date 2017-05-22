#include "Camera.h"



Camera::Camera() {
	transform.location = { 0, 0, 2 };  // Initial location of the camera
	transform.rotation = { 0, 0, 0 };  // Initial rotation vector of the camera

	rotMat = (glm::mat3)glm::yawPitchRoll(transform.rotation.y, transform.rotation.x, transform.rotation.z); // Rotation matrix of the camera

	walkMat = (glm::mat3)glm::yawPitchRoll(transform.rotation.y, 0.0f, transform.rotation.z);  // Almost identical to the the camera matrix except that I lock the x axis rotation to 0.0f so I can make the camera move as if it is a person walking on the ground

	//buildMatrices();
}

Camera::Camera(GLFWwindow * window, glm::vec3 t, glm::vec3 r, glm::vec3 s, int controlLeft, int controlRight, int controlUp, int controlDown, bool controllable, colliderType collider, const GameObject& parent) : GameObject(window, t, r, s, controlLeft, controlRight, controlUp, controlDown, collider, false) {
	this->controllable = controllable;

	rotMat = (glm::mat3)glm::yawPitchRoll(r.y, r.x, r.z); // Rotation matrix of the camera

	walkMat = (glm::mat3)glm::yawPitchRoll(transform.rotation.y, 0.0f, transform.rotation.z);  // Almost identical to the the camera matrix except that I lock the x axis rotation to 0.0f so I can make the camera move as if it is a person walking on the ground

	zoom = 1.0f;
	width = 800;
	height = 600;

	fovy = 3.14159f * 0.4f / zoom;
	aspect = (float)width / (float)height;
	zNear = 0.01f;
	zFar = 1000.0f;

	this->window = window;

	this->parent = parent;
}


Camera::~Camera() {
}

void Camera::update() {
	worldview = perspectiveMat * lookAtMat;

	glUniformMatrix4fv(1, 1, GL_FALSE, &worldview[0][0]);  // Uploads the worldview matrix to the camera matrix in the vShader
	glUniform3fv(5, 1, &transform.location.x);  // Uploads the camers's location vec3 to the camera position in the fShader

	move();

	applyMovement();

	force *= 0;
}

void Camera::move() {
	glm::vec3 direction;

	float sens = 0.005;
	double x, y;
	x = width;
	y = height;
	glfwGetCursorPos(window, &x, &y);

	if (controllable) {
		transform.rotation.y -= sens * (x - width * 0.5f);
		transform.rotation.x -= sens * (y - height * 0.5f);
	}

	transform.rotation.x = glm::clamp(transform.rotation.x, -0.5f * 3.14f, 0.5f * 3.14f);

	glfwSetCursorPos(window, width * 0.5f, height * 0.5f);

	rotMat = (glm::mat3)glm::yawPitchRoll(transform.rotation.y, transform.rotation.x, transform.rotation.z);

	walkMat = (glm::mat3)glm::yawPitchRoll(transform.rotation.y, 0.0f, transform.rotation.z);

	if (controllable) {
		GameObject::move();
	}

	if (!controllable) {
		transform.location = parent.transform.location;
		transform.location += parent.direction * glm::vec3(0.0f, 2.0f, 5.0f);
		transform.rotation = parent.transform.rotation;
	}

	rotMat = (glm::mat3)glm::yawPitchRoll(transform.rotation.y, transform.rotation.x, transform.rotation.z);

	buildMatrices();

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

// Remember: I have to call this after declaring my camera in main
void Camera::buildMatrices() {
	eye = transform.location;
	center = eye + rotMat * glm::vec3(0, 0, -1);
	up = rotMat * glm::vec3(0, 1, 0);

	lookAtMat = glm::lookAt(eye, center, up);

	perspectiveMat = glm::perspective(fovy, aspect, zNear, zFar);

	worldview = perspectiveMat * lookAtMat;
}

void Camera::setParent(const GameObject& parent) {
	this->parent = parent;
}

glm::mat4 Camera::getWorldview()
{
	return worldview;
}
