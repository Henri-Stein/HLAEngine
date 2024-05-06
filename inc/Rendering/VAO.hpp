#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include "VBO.hpp"

class VAO

{
public:
	VAO();
	//~VAO(){ glDeleteVertexArrays(1, &_ID); }
	
	/*
	* @param vbo: the VBO containing the attribute
	* @param layout: corresponding layout in the shader file
	* @param numComponents: the number of components composing the current attribute (for instance, a 3D position has 3 components, that is x y and z)
	* @param type: the type of attribute
	* @param stride: the stride in bits between two elements in the VBO
	* @param offset: the index at which the current attribute is starting
	*/
	void LinkAttrib(const VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void Bind() const;
	void Unbind() const;
	void Delete();

	inline GLuint getID() { return _ID; };

private:
	GLuint _ID;
};

#endif
