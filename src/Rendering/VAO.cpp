#include "Rendering/VAO.hpp"

VAO::VAO()
{
	glGenVertexArrays(1, &_ID);
	std::cout << "Default VAO with ID = " << _ID << std::endl;
}

void VAO::LinkAttrib(const VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	vbo.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(layout);
	vbo.Unbind();
}

void VAO::Bind() const
{
	glBindVertexArray(_ID);
}

void VAO::Unbind() const
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &_ID);
}