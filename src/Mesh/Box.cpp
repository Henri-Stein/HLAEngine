#include "Mesh/Box.hpp"

Box::Box(const float& width, const float& height, const float& depth) :
	Mesh{},
	_width{ width },
	_height{ height },
	_depth{ depth }

{
	float halfWidth = width / 2.f;
	float halfHeight = height / 2.f;
	float halfDepth = depth / 2.f;

	Vec3<GLfloat> boxPositions[] = {
		/* Back face (looking in -Z direction) */
		{  halfWidth, -halfHeight, -halfDepth }, // Back bottom right
		{ -halfWidth, -halfHeight, -halfDepth }, // Back bottom left
		{ -halfWidth,  halfHeight, -halfDepth }, // Back top left
		{  halfWidth,  halfHeight, -halfDepth }, // Back top right

		/* Front face */
		{ -halfWidth, -halfHeight,  halfDepth }, // Front bottom left
		{  halfWidth, -halfHeight,  halfDepth }, // Front bottom right
		{  halfWidth,  halfHeight,  halfDepth }, // Front top right
		{ -halfWidth,  halfHeight,  halfDepth }, // Front top left

		/* Left face */
		{ -halfWidth, -halfHeight, -halfDepth }, // Back bottom left
		{ -halfWidth, -halfHeight,  halfDepth }, // Front bottom left
		{ -halfWidth,  halfHeight,  halfDepth }, // Front top left
		{ -halfWidth,  halfHeight, -halfDepth }, // Back top left

		/* Right face */
		{  halfWidth, -halfHeight,  halfDepth }, // Front bottom right
		{  halfWidth, -halfHeight, -halfDepth }, // Back bottom right
		{  halfWidth,  halfHeight, -halfDepth }, // Back top right
		{  halfWidth,  halfHeight,  halfDepth }, // Front top right

		/* Top face */
		{ -halfWidth,  halfHeight,  halfDepth }, // Front top left
		{  halfWidth,  halfHeight,  halfDepth }, // Front top right
		{  halfWidth,  halfHeight, -halfDepth }, // Back top right
		{ -halfWidth,  halfHeight, -halfDepth }, // Back top left

		/* Bottom face */
		{ -halfWidth, -halfHeight, -halfDepth},  // Back bottom left
		{  halfWidth, -halfHeight, -halfDepth},  // Back bottom right
		{  halfWidth, -halfHeight,  halfDepth},  // Front bottom right
		{ -halfWidth, -halfHeight,  halfDepth},  // Front bottom left
	};

	Vec3<GLfloat> boxNormals[] = {
		/* Back face (looking in -Z direction) */
		{  0.f,  0.f, -1.f }, // Back bottom right
		{  0.f,  0.f, -1.f }, // Back bottom left
		{  0.f,  0.f, -1.f }, // Back top left
		{  0.f,  0.f, -1.f }, // Back top right

		/* Front face */
		{  0.f,  0.f,  1.f }, // Front bottom left
		{  0.f,  0.f,  1.f }, // Front bottom right
		{  0.f,  0.f,  1.f }, // Front top right
		{  0.f,  0.f,  1.f }, // Front top left

		/* Left face */
		{ -1.f,  0.f,  0.f }, // Back bottom left
		{ -1.f,  0.f,  0.f }, // Front bottom left
		{ -1.f,  0.f,  0.f }, // Front top left
		{ -1.f,  0.f,  0.f }, // Back top left

		/* Right face */
		{ 1.f,  0.f,  0.f }, // Front bottom right
		{ 1.f,  0.f,  0.f }, // Back bottom right
		{ 1.f,  0.f,  0.f }, // Back top right
		{ 1.f,  0.f,  0.f }, // Front top right

		/* Top face */
		{ 0.f,  1.f,  0.f }, // Front top left
		{ 0.f,  1.f,  0.f }, // Front top right
		{ 0.f,  1.f,  0.f }, // Back top right
		{ 0.f,  1.f,  0.f }, // Back top left

		/* Bottom face */
		{ 0.f, -1.f,  0.f },  // Back bottom left
		{ 0.f, -1.f,  0.f },  // Back bottom right
		{ 0.f, -1.f,  0.f },  // Front bottom right
		{ 0.f, -1.f,  0.f },  // Front bottom left
	};

	Vec2<GLfloat> boxTexCoords[] = {
		/* Back face (looking in -Z direction) */
		{  0.f,  0.f}, // Back bottom right
		{  1.f,  0.f}, // Back bottom left
		{  1.f,  1.f}, // Back top left
		{  0.f,  1.f}, // Back top right

		/* Front face */
		{  0.f,  0.f}, // Front bottom left
		{  1.f,  0.f}, // Front bottom right
		{  1.f,  1.f}, // Front top right
		{  0.f,  1.f}, // Front top left

		/* Left face */
		{ 0.f,  0.f}, // Back bottom left
		{ 1.f,  0.f}, // Front bottom left
		{ 1.f,  1.f}, // Front top left
		{ 0.f,  1.f}, // Back top left

		/* Right face */
		{ 0.f,  0.f,}, // Front bottom right
		{ 1.f,  0.f,}, // Back bottom right
		{ 1.f,  1.f,}, // Back top right
		{ 0.f,  1.f,}, // Front top right

		/* Top face */
		{ 0.f,  0.f,}, // Front top left
		{ 1.f,  0.f,}, // Front top right
		{ 1.f,  1.f,}, // Back top right
		{ 0.f,  1.f,}, // Back top left

		/* Bottom face */
		{ 0.f, 0.f,},  // Back bottom left
		{ 1.f, 0.f,},  // Back bottom right
		{ 1.f, 1.f,},  // Front bottom right
		{ 0.f, 1.f,},  // Front bottom left
	};

	Vec3<GLuint> boxTriangles[] = {
		// Back
		{ 0, 1, 3 },
		{ 3, 1, 2 },

		// Front
		{ 4, 5, 7 },
		{ 7, 5, 6 },

		// Left
		{ 8, 9, 11 },
		{ 11, 9, 10 },

		// Right
		{ 12, 13, 15 },
		{ 15, 13, 14 },

		// Top
		{ 16, 17, 19 },
		{ 19, 17, 18 },

		// Bottom
		{ 20, 21, 23 },
		{ 23, 21, 22 }
	};


	for (int i = 0; i < 24; i++)
	{
		Vertex v{};
		v._position = boxPositions[i];
		v._normal = boxNormals[i];
		v._texCoord = boxTexCoords[i];
		_vertices.push_back(v);
	}

	for (const auto& t : boxTriangles)
	{
		_triangles.push_back(Triangle{ t });
	}
}