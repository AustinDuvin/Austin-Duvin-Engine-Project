#include "Player.h"



Player::Player() {
}

Player::Player(std::string modelFilename, std::string textureFilename, glm::vec3 t, glm::vec3 r, glm::vec3 s, GLFWwindow * window, int controlLeft, int controlRight, int controlUp, int controlDown, float mass, colliderType collider, bool applyGravity, float speed) : GameObject(modelFilename, textureFilename, t, r, s, window, controlLeft, controlRight, controlUp, controlDown, mass, collider, applyGravity, speed) {
}


Player::~Player() {
}

void Player::update() {
	// Moves the object
	if (controllable) {
		move();
	}
	
	if (applyGravity) {
		applyForce(gravity / Timer::dt);
	}

	// Recalculates the matrix
	transform.objectWorldTransform = glm::translate(transform.location) * glm::yawPitchRoll(transform.rotation.y, transform.rotation.x, transform.rotation.z) * glm::scale(transform.scale);

	// Uploads objectWorldTransform matrix to the vShader
	glUniformMatrix4fv(8, 1, GL_FALSE, &transform.objectWorldTransform[0][0]);

	// Binds current texture to the model
	texture.bind();

	// Render game objects
	model.render();
}

void Player::move() {
	glm::vec3 df(0.0f, 0.0f, 0.0f);

	df += input(df);

	glm::mat3 r = (glm::mat3)glm::yawPitchRoll(transform.rotation.y, transform.rotation.x, transform.rotation.z);  // Makes forces relative to rotation

	direction = r;

	df = r * df;

	df *= speed;

	applyForce(df);
	applyForce(friction * velocity);
}

glm::vec3 Player::input(glm::vec3 df) {
	if (glfwGetKey(window, controlLeft)) {
		transform.rotation += glm::vec3(0.0f, 3.0f, 0.0f) * Timer::dt;
		std::cout << transform.rotation.y << std::endl;
	}
	if (glfwGetKey(window, controlRight)) {
		transform.rotation += glm::vec3(0.0f, -3.0f, 0.0f) * Timer::dt;
		std::cout << transform.rotation.y << std::endl;
	}
	if (glfwGetKey(window, controlUp)) {
		df += glm::vec3(0, 0, -1);
	}
	if (glfwGetKey(window, controlDown)) {
		df += glm::vec3(0, 0, 1);
	}

	return df;
}
