#include "Mesh/Plane.hpp"

Plane::Plane(const unsigned int& nbElemWidth, const unsigned int& nbElemHeight, const float& width, const float& height):
	Mesh{},
	_widthRes{nbElemWidth},
	_heightRes{nbElemHeight},
	_width{width},
	_height{height}
{
	float elemWidth = _width / _widthRes;
	float elemHeight = _height / _heightRes;


	for (int y = 0; y <= _heightRes; y++)
	{
		for (int x = 0; x <= _widthRes; x++) 
		{
			// Calculate the x, y and z components of the current vertex
			Vec3<GLfloat> position = {x * elemWidth - _width / 2.f, y * elemHeight - _height / 2.f, 0.0f};
			Vec3<GLfloat> normal = { 0.f, 0.f, 1.f };
			Vec2<GLfloat> texCoord = { static_cast<double>(x) / _widthRes, static_cast<double>(y) / _heightRes };
			Vertex v{};
			v._position = position;
			v._normal = normal;
			v._texCoord = texCoord;
			
			// Push the x, y and z components of the vertex
			_vertices.push_back(v);


			if (x < _widthRes && y < _heightRes) // Don't need to define the triangles for the last column and the last row
			{
				unsigned int count = y * (_widthRes + 1) + x; // the id of the vertex currently created
				//Vec3<GLuint> triangle1 = { count, count + 1, _widthRes + 1 };

				//Vec3<GLuint> triangle2 = { count + _widthRes + 2, count + 1, count + _widthRes + 1 };

				// Bottom left triangle
				_triangles.push_back(Triangle{ count, count + 1, count + _widthRes + 1 });
				//_indices.emplace_back(count, count + 1, _widthRes + 1);
				// Top right triangle
				_triangles.push_back(Triangle{ count + _widthRes + 2, count + 1, count + _widthRes + 1 });

				//_indices.push_back(count); // Lower left corner
				//_indices.push_back(count + 1); // Lower right corner
				//_indices.push_back(count + _widthRes + 1); // Top left corner
				//
				//// Top right triangle
				//_indices.push_back(count + _widthRes + 2); // Top right corner
				//_indices.push_back(count + 1); // Lower right corner
				//_indices.push_back(count + _widthRes + 1); // Top left corner
			}

		}
	}


}

