#include "GameObject.h"



GameObject::GameObject() {
}

GameObject::GameObject(GLFWwindow * window, glm::vec3 t, glm::vec3 r, glm::vec3 s, int controlLeft, int controlRight, int controlUp, int controlDown, colliderType collider, bool applyGravity) {
	transform.location = t;
	transform.rotation = r;
	transform.scale = s;

	this->controlLeft = controlLeft;
	this->controlRight = controlRight;
	this->controlUp = controlUp;
	this->controlDown = controlDown;

	this->window = window;

	mass = 1.0f;
	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	force = glm::vec3(0.0f, 0.0f, 0.0f);

	friction = -1.0f;
	this->collider = collider;
	this->applyGravity = applyGravity;
}

GameObject::GameObject(std::string modelFilename, std::string textureFilename, glm::vec3 t, glm::vec3 r, glm::vec3 s, GLFWwindow * window, float mass, glm::vec3 force, colliderType collider, bool applyGravity) {
	this->window = window;
	
	modelFile = modelFilename;
	textureFile = textureFilename;

	transform.location = t;
	transform.rotation = r;
	transform.scale = s;

	controllable = false;
	this->mass = mass;
	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	this->force = force;
	forceSave = force;
	this->collider = collider;
	this->applyGravity = applyGravity;
}

GameObject::GameObject(std::string modelFilename, std::string textureFilename, glm::vec3 t, glm::vec3 r, glm::vec3 s, GLFWwindow * window, int controlLeft, int controlRight, int controlUp, int controlDown, float mass, colliderType collider, bool applyGravity, float speed) {
	this->window = window;

	modelFile = modelFilename;
	textureFile = textureFilename;

	transform.location = t;
	transform.rotation = r;
	transform.scale = s;

	controllable = true;
	this->controlLeft = controlLeft;
	this->controlRight = controlRight;
	this->controlUp = controlUp;
	this->controlDown = controlDown;
	this->mass = mass;
	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	force = glm::vec3(0.0f, 0.0f, 0.0f);
	gravity = mass * glm::vec3(0, -1, 0);

	friction = -1.0f;
	this->collider = collider;
	this->applyGravity = applyGravity;
	this->speed = speed;
}


GameObject::~GameObject() {
}

colliderType GameObject::getCollider() const {
	return collider;
}

Transform GameObject::getTransform() const
{
	return transform;
}

// Loads the gameObject's model and texture
void GameObject::loadModelTexture() {
	model.buffer(modelFile);

	/*if (!model.buffer()) {
	return false;
	}*/

	texture = Texture(textureFile.c_str());

	texture.load();

	// Sets up the initial Model-World Transform Matrix
	transform.objectWorldTransform = glm::translate(transform.location) * glm::yawPitchRoll(transform.rotation.y, transform.rotation.x, transform.rotation.z) * glm::scale(transform.scale);

	radius = glm::length(transform.scale * model.maxXYZ);

	maxX = model.maxX * transform.scale.x;
	maxY = model.maxY * transform.scale.y;
	maxZ = model.maxZ * transform.scale.z;
}

void GameObject::update() {
	// Moves the object
	if (controllable) {
		move();
	}

	else {
		force = forceSave;
		glm::vec3 dv = force * Timer::dt / mass;
		velocity += dv;
		transform.location += velocity * Timer::dt;
	}

	if (applyGravity) {
		applyForce(gravity / Timer::dt);
	}

	// Recalculates the matrix
	transform.objectWorldTransform = glm::translate(transform.location) * glm::yawPitchRoll(transform.rotation.y, transform.rotation.x, transform.rotation.z) * glm::scale(transform.scale);

	// Uploads objectWorldTransform matrix to the vShader
	glUniformMatrix4fv(8, 1, GL_FALSE, &transform.objectWorldTransform[0][0]);

	if (shouldRender) {
		// Binds current texture to the model
		texture.bind();

		// Render game objects
		model.render();
	}
}

void GameObject::unloadTexture() {
	texture.unload();
}

// Moves the object
void GameObject::move() {
	glm::vec3 df(0.0f, 0.0f, 0.0f);

	df += input(df);

	glm::mat3 r = (glm::mat3)glm::yawPitchRoll(transform.rotation.y, transform.rotation.x, transform.rotation.z);  // Makes forces relative to rotation

	direction = r;

	df = r * df;

	df *= speed;
	
	applyForce(df);
	applyForce(friction * velocity);
}

// Gets input for movement method
glm::vec3 GameObject::input(glm::vec3 df) {
	if (glfwGetKey(window, controlLeft)) {
		df += glm::vec3(-1, 0, 0);
	}
	if (glfwGetKey(window, controlRight)) {
		df += glm::vec3(1, 0, 0);
	}
	if (glfwGetKey(window, controlUp)) {
		df += glm::vec3(0, 0, -1);
	}
	if (glfwGetKey(window, controlDown)) {
		df += glm::vec3(0, 0, 1);
	}

	return df;
}

// Apply any force to the gameObject
void GameObject::applyForce(glm::vec3 deltaForce) {
	force += deltaForce;
}

// Apply movement to the object
void GameObject::applyMovement() {
	glm::vec3 dv = force * Timer::dt / mass;
	velocity += dv;
	transform.location += velocity * Timer::dt;
	force *= 0;
}

// Checks for collisions
bool GameObject::collidesWith(const GameObject& other) {
	between = transform.location - other.transform.location;
	
	if (getCollider() == colliderless || other.getCollider() == colliderless) {
		return false;
	}

	else if (getCollider() == sphere && other.getCollider() == sphere) {
		float distance = glm::length(between);

		if (std::abs(distance) > radius + other.radius) {
			return false;
		}

		//std::cout << "Collision" << std::endl;
		return true;
	}

	else if (getCollider() == axisAligned && other.getCollider() == axisAligned) {
		glm::vec3 distance = between;
		glm::vec3 ea = transform.scale * model.maxXYZ;
		glm::vec3 eb = other.transform.scale * other.model.maxXYZ;

		if (std::abs(distance.x) > std::abs(ea.x) + std::abs(eb.x) || std::abs(distance.y) > std::abs(ea.y) + std::abs(eb.y) || std::abs(distance.z) > std::abs(ea.z) + std::abs(eb.z)) {
			return false;
		}

		//std::cout << "Collision" << std::endl;
		return true;
	}

	else if (getCollider() == sphere && other.getCollider() == axisAligned) {
		glm::vec3 distance = between;
		glm::vec3 e = other.transform.scale * other.model.maxXYZ;
		glm::vec3 closestPoint = other.transform.location + glm::clamp(distance, -e, e);
		float distanceClosestPoint = glm::length(transform.location - closestPoint);

		if (std::abs(distanceClosestPoint) > radius) {
			return false;
		}

		//std::cout << "Collision" << std::endl;
		return true;
	}

	return false;
}
