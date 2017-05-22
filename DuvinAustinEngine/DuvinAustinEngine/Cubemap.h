#pragma once
#include "Texture.h"
class Cubemap :
	public Texture
{
private:
	GLuint id;
public:
	Cubemap();
	~Cubemap();

	void bind() override;
	void load() override;
};

