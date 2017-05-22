#include "Texture.h"



Texture::Texture() {
}

Texture::Texture(const char* filename) {
	texFile = filename;
}


Texture::~Texture() {
}

void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, texID);
}

void Texture::unload() {
	glDeleteTextures(1, &texID);
}

void Texture::load() {
	FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType(texFile, 0), texFile);

	if (image == nullptr) {
		std::cout << "Error: Texture Filename: " << texFile << " did not load correctly." << std::endl;
	}

	FIBITMAP* image32Bit = FreeImage_ConvertTo32Bits(image);

	FreeImage_Unload(image);

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, FreeImage_GetWidth(image32Bit), FreeImage_GetHeight(image32Bit), 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(image32Bit));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	FreeImage_Unload(image32Bit);

	glBindTexture(GL_TEXTURE_2D, 0);
}
