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
class Texture
{
private:
	GLuint texID;
	const char* texFile;
public:
	Texture();
	Texture(const char* filename);
	~Texture();

	virtual void bind();
	void unload();
	virtual void load();
};

