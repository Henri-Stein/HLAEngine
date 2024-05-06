#include "rendering/EBO.hpp"

//EBO::EBO()
//{
//	glGenBuffers(1, &_ID);
//}

EBO::EBO(const GLuint* indices, GLsizeiptr size)
{
	glGenBuffers(1, &_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::init(const GLuint* indices, GLsizeiptr size) const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}


void EBO::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
}

void EBO::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
	glDeleteBuffers(1, &_ID);
}