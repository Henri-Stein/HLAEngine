#ifndef HLA_ENGINE_UTILS_H
#define HLA_ENGINE_UTILS_H

#include <string>
#include "glm/glm.hpp"
#include <glad/glad.h>

template<typename NumT>
struct Vec2
{
	NumT _x;
	NumT _y;
};

template<typename NumT>
struct Vec3
{
	NumT _x;
	NumT _y;
	NumT _z;
};

template<typename NumT>
struct Vec4
{
	NumT _x;
	NumT _y;
	NumT _z;
	NumT _w;
};


// Return the content of the file 'filename' as a std::string
std::string get_file_contents(const char* filename);
void printGlmMat(glm::mat4 mat);

#endif