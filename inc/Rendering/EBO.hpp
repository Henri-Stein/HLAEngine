#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>

class EBO
{
public:
	// Constructor that generates an Element Buffer Object and links it to indices
	EBO(const GLuint* indices, GLsizeiptr size);
	//~EBO(){ glDeleteBuffers(1, &_ID); }
	//EBO(GLuint* indices, GLsizeiptr size);
	void init(const GLuint* indices, GLsizeiptr size) const;
	void Bind() const;
	void Unbind() const;
	void Delete();

	inline GLuint getID() const { return _ID; };

private:
	// reference ID of the Element Buffer Object
	GLuint _ID;
};

#endif
