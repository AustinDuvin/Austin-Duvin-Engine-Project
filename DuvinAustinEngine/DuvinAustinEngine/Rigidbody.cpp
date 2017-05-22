#include "Rigidbody.h"



/*Rigidbody::Rigidbody() {
}

Rigidbody::Rigidbody(GLFWwindow * window, float mass, Transform transform, bool controllable, glm::vec3 force) {
	this->window = window;

	this->controllable = controllable;
	this->mass = mass;
	this->transform = transform;

	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	this->force = force;
}

Rigidbody::Rigidbody(GLFWwindow * window, int controlLeft, int controlRight, int controlUp, int controlDown, float mass, Transform transform, bool controllable) {
	this->window = window;

	this->controllable = controllable;
	this->controlLeft = controlLeft;
	this->controlRight = controlRight;
	this->controlUp = controlUp;
	this->controlDown = controlDown;
	this->mass = mass;
	this->transform = transform;

	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	force = glm::vec3(0.0f, 0.0f, 0.0f);
}


Rigidbody::~Rigidbody() {
}

void Rigidbody::update() {
	if (controllable) {
		move();
	}
	
	glm::vec3 dv = force * (Timer::dt / mass);
	velocity = dv;
	transform.location = velocity * Timer::dt;
}

void Rigidbody::move() {
	if (glfwGetKey(window, GLFW_KEY_LEFT)) {
		force += glm::vec3(-1, 0, 0);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
		force += glm::vec3(1, 0, 0);
	}
	if (glfwGetKey(window, GLFW_KEY_UP)) {
		force += glm::vec3(0, 0, -1);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN)) {
		force += glm::vec3(0, 0, 1);
	}

	float speed = 1.0f;
	if (force != glm::vec3()) {
		force = glm::normalize(velocity) * speed;
	}

	//transform.location += velocity * Timer::dt;
}*/
