#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <tiff.h>

#include "Shader.hpp"

class Texture
{
public:
	Texture(const void* data, const uint32_t width, const uint32_t height, GLenum texType, GLenum format, GLenum pixelType);
	//void texUnit(Shader shader, std::string uniformName, GLuint unit);
	void Activate(uint8_t unit);
	void Bind();
	void Unbind();
	void Delete();

private:
	GLuint _ID;
	GLenum _type;
};

#endif