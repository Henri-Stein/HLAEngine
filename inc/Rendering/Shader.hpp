#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include "utils.hpp"


class Shader
{
public:
	Shader(const std::string& vertexFile, const std::string& fragmentFile);

	// Activates the Shader Program
	void Activate() const;

	// Deletes the Shader Program
	void Delete() const;

	// (Re-)Compile the vertex and fragment shaders and create a shader program object
	void Compile();
	
	inline GLuint getID() const { return _ID; };

	// utility uniform functions
	void setUniform(const std::string& name, bool value) const;
	void setUniform(const std::string& name, int value) const;
	void setUniform(const std::string& name, float value) const;
	void setUniform(const std::string& name, const glm::vec3& vec) const;
	void setUniform(const std::string& name, const glm::vec4& vec) const;
	void setUniform(const std::string& name, const glm::mat4& matrix) const;
	//void setUniform(const std::string& name, glm::vec3) const;

private:
	void compileErrors(unsigned int shader, const char* type);


private:
	GLuint _ID;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
	std::string _vertexFile;
	std::string _fragmentFile;
};

#endif