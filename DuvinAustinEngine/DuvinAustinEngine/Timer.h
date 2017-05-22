#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeImage.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

#include <ctime>
class Timer
{
private:
	static float cur;
	static float prev;
public:
	static float t;
	static float dt;
	static float fps;

	Timer();
	~Timer();

	static void update();
};

