#include "utils.hpp"

#include <iostream>
#include <fstream>

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	}

	throw(errno);
}

void printGlmMat(glm::mat4 mat)
{
	for (int l = 0; l < 4; l++)
	{
		std::cout << "[";
		for (int c = 0; c < 4; c++)
		{
			std::cout << " " << mat[c][l];
		}
		std::cout << "]" << std::endl;
	}
}