#ifndef BOX_HPP
#define BOX_HPP

#include "Mesh/Mesh.hpp"

class Box : public Mesh
{
public:
	Box(const float& width = 1.f, const float& height = 1.f, const float& depth = 1.f);

private:
	float _width; // Length in X-Axis
	float _height; // Length in Y-Axis
	float _depth; // Length in Z-Axis
};

#endif