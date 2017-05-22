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

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
class Model
{
private:
	GLuint vertArr;
	unsigned int vertCount;
public:
	glm::vec3 maxXYZ;
	float maxX;
	float maxY;
	float maxZ;

	Model();
	~Model();

	bool buffer(std::string objFile);
	void render();
};

struct Vertex {
	glm::vec3 location;
	glm::vec2 uv;
	glm::vec3 normal;
};

struct VertInd {
	glm::uint locInd;
	glm::uint uvInd;
	glm::uint normInd;

	VertInd(glm::uint l, glm::uint u, glm::uint n) {
		locInd = l;
		uvInd = u;
		normInd = n;
	}
};