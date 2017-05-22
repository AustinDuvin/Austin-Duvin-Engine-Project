#include "Timer.h"



float Timer::prev = (float)glfwGetTime();
float Timer::cur = Timer::prev;
float Timer::t = 0;
float Timer::dt = 0;
float Timer::fps = 0;

Timer::Timer() {
	//prev = cur = clock();
	//t = dt = fps = 0;
}


Timer::~Timer() {
}

void Timer::update() {
	prev = cur;
	cur = (float)glfwGetTime();
	dt = (cur - prev);
	t += dt;
	fps = 1 / dt;
}
