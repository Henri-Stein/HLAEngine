#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>
#include <iostream>

class VBO
{
public:
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(const GLfloat* vertices, GLsizeiptr size);

	void Bind() const;
	void Unbind() const;
	void Delete();
	
	inline GLuint getID() const { return _ID; };

private:
	// reference ID of the Vertex Buffer Object
	GLuint _ID;
};

#endif