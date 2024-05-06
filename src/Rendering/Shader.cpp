#include "Rendering/Shader.hpp"

#include <iostream>
#include <glm/gtc/type_ptr.hpp>


Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile):
	_vertexFile{vertexFile},
	_fragmentFile{fragmentFile},
	_ID{0}
{
	Compile();
}

void Shader::Compile()
{
	// Read _vertexFile and _fragmentFile and store the strings
	std::string vertexCode = get_file_contents(_vertexFile.c_str());
	std::string fragmentCode = get_file_contents(_fragmentFile.c_str());

	// Convert the shader source strings into characters
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create OpenGL shader object and get its reference
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	// Assign the shader source code to the shader object
	glShaderSource(_vertexShaderID, 1, &vertexSource, NULL);
	// Compile the shader
	glCompileShader(_vertexShaderID);
	compileErrors(_vertexShaderID, "VERTEX");

	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_fragmentShaderID, 1, &fragmentSource, NULL);
	glCompileShader(_fragmentShaderID);
	compileErrors(_fragmentShaderID, "FRAGMENT");

	// Create a shader program object
	if(_ID) // Check if we didn't created a shader program before. If so, we delete the previous program
		glDeleteProgram(_ID);
	_ID = glCreateProgram();
	// Attach the vertex shader to the program
	glAttachShader(_ID, _vertexShaderID);
	// Attach the fragment shader to the program
	glAttachShader(_ID, _fragmentShaderID);

	// Link the program to the current context
	glLinkProgram(_ID);
	compileErrors(_ID, "PROGRAM");

	// We can delete the shaders as they are now part of the program
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}


void Shader::Activate() const
{
	glUseProgram(_ID);
}

void Shader::Delete() const
{
	glDeleteProgram(_ID);
}

void Shader::setUniform(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(_ID, name.c_str()), static_cast<int>(value));
}

void Shader::setUniform(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(_ID, name.c_str()), value);
}

void Shader::setUniform(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(_ID, name.c_str()), value);
}

void Shader::setUniform(const std::string& name, const glm::vec3& vec) const
{
	glUniform3fv(glGetUniformLocation(_ID, name.c_str()), 1, glm::value_ptr(vec));
}

void Shader::setUniform(const std::string& name, const glm::vec4& vec) const
{
	glUniform4fv(glGetUniformLocation(_ID, name.c_str()), 1, glm::value_ptr(vec));
}


void Shader::setUniform(const std::string& name, const glm::mat4& matrix) const
{
	glUniformMatrix4fv(glGetUniformLocation(_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}
