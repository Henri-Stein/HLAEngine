#include "Rendering/Texture.hpp"

Texture::Texture(const void* data,
	const uint32_t width,
	const uint32_t height,
	GLenum texType,
	GLenum format,
	GLenum pixelType)
	:
	_type{texType}
{
	glGenTextures(1, &_ID);
	//glActiveTexture(slot);
	glBindTexture(_type, _ID);

	// takes the nearest mipmap to match the pixel size and uses nearest neighbor interpolation for texture sampling.
	glTexParameteri(_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	/* 
	*  Notice: setting one of the mipmap filtering options as the magnification filter doesn't have any effect
	*  since mipmaps are primarily used for when textures get downscaled texture magnification doesn't use mipmaps
	*  and giving it a mipmap filtering option will generate an OpenGL GL_INVALID_ENUM error code.
	*/
	glTexParameteri(_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(_type, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(_type, 0, GL_RGBA, width, height, 0, format, pixelType, data);
	glGenerateMipmap(_type);

	glBindTexture(_type, 0);
}


void Texture::Activate(uint8_t unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(_type, _ID);
}

//void Texture::texUnit(Shader shader, std::string uniformName, GLuint unit)
//{
//	//glActiveTexture(GL_TEXTURE0 + unit);
//	GLuint uTexID = glGetUniformLocation(shader.getID(), uniformName.c_str());
//	shader.Activate();
//	glUniform1i(uTexID, unit);
//}

void Texture::Bind()
{
	glBindTexture(_type, _ID);
}

void Texture::Unbind()
{
	glBindTexture(_type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &_ID);
}
