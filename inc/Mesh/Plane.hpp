#ifndef PLANE_H
#define PLANE_H

#include <glad/glad.h>
#include <vector>
#include "Mesh.hpp"

class Plane : public Mesh
{
public:
	Plane(const unsigned int& nbElemWidth = 1, const unsigned int& nbElemHeight = 1, const float& width = 1.f, const float& height = 1.f);

private:
	unsigned int _widthRes; // Nb of grid element (square made of 2 triangles) in X-axis
	unsigned int _heightRes; // Nb of grid element (square made of 2 triangles) in Y-axis
	float _width; // Total length of the plane in X-Axis
	float _height; // Total length of the plane in Y-Axis
};

#endif // !define PLANE_H
