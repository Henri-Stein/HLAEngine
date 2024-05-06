#include "Mesh/Mesh.hpp"
#include "Rendering/VBO.hpp"
#include "Rendering/EBO.hpp"

Mesh::Mesh() :
	_vertices{},
	_triangles{}
{}

VBO Mesh::makeFullVBO() const
{
	//VBO;
	//std::vector<GLfloat> vertices{};
	std::vector<GLfloat> vertices{}; // 15 because 15 GLfloat attribute's components attributes per vertex
	vertices.reserve(_vertices.size() * 15);
	for (const auto& v : _vertices)
	{
		// Position
		vertices.push_back(v._position._x);
		vertices.push_back(v._position._y);
		vertices.push_back(v._position._z);
		
		// Normal
		vertices.push_back(v._normal._x);
		vertices.push_back(v._normal._y);
		vertices.push_back(v._normal._z);

		// Tangent
		vertices.push_back(v._tangent._x);
		vertices.push_back(v._tangent._y);
		vertices.push_back(v._tangent._z);

		// Color
		vertices.push_back(v._color._x);
		vertices.push_back(v._color._y);
		vertices.push_back(v._color._z);
		vertices.push_back(v._color._w);

		// Tex coord
		vertices.push_back(v._texCoord._x);
		vertices.push_back(v._texCoord._y);
	}

	VBO vbo( vertices.data(), vertices.size() * sizeof(GLfloat) );
	return vbo;
}

std::array<VBO, 5> Mesh::makeAllVBO() const // Return a VBO for each vertex attribute
{
	std::vector<GLfloat> positions{};
	positions.reserve(_vertices.size() * 3);

	std::vector<GLfloat> normals{};
	normals.reserve(_vertices.size() * 3);

	std::vector<GLfloat> tangents{};
	tangents.reserve(_vertices.size() * 3);

	std::vector<GLfloat> colors{};
	colors.reserve(_vertices.size() * 3);

	std::vector<GLfloat> texCoords{};
	texCoords.reserve(_vertices.size() * 3);

	for (const auto& v : _vertices)
	{
		// Position
		positions.push_back(v._position._x);
		positions.push_back(v._position._y);
		positions.push_back(v._position._z);

		// Normal
		normals.push_back(v._normal._x);
		normals.push_back(v._normal._y);
		normals.push_back(v._normal._z);

		// Tangent
		tangents.push_back(v._tangent._x);
		tangents.push_back(v._tangent._y);
		tangents.push_back(v._tangent._z);

		// Color
		colors.push_back(v._color._x);
		colors.push_back(v._color._y);
		colors.push_back(v._color._z);
		colors.push_back(v._color._w);

		// Tex coord
		texCoords.push_back(v._texCoord._x);
		texCoords.push_back(v._texCoord._y);
	}

	VBO vboPos  { positions.data(), static_cast<GLsizeiptr>( positions.size() * sizeof(GLfloat) ) };
	VBO vboNorm { normals.data(),   static_cast<GLsizeiptr>( normals.size()   * sizeof(GLfloat) ) };
	VBO vboTan  { tangents.data(),  static_cast<GLsizeiptr>( tangents.size()  * sizeof(GLfloat) ) };
	VBO vboCol  { colors.data(),    static_cast<GLsizeiptr>( colors.size()    * sizeof(GLfloat) ) };
	VBO vboTexCo{ texCoords.data(), static_cast<GLsizeiptr>( texCoords.size() * sizeof(GLfloat) ) };
	return { vboPos, vboNorm, vboTan, vboCol, vboTexCo };
}

VBO Mesh::makePositionVBO() const
{
	std::vector<GLfloat> positions{}; 
	positions.reserve(_vertices.size() * 3);
	for (const auto& v : _vertices)
	{
		// Position
		positions.push_back(v._position._x);
		positions.push_back(v._position._y);
		positions.push_back(v._position._z);
	}
	VBO vbo{ (GLfloat*)positions.data(), static_cast<GLsizeiptr>(positions.size() * sizeof(GLfloat)) };
	return vbo;
}

VBO Mesh::makeNormalVBO() const
{
	std::vector<GLfloat> normals{};
	normals.reserve(_vertices.size() * 3);
	for (const auto& v : _vertices)
	{
		// Normal
		normals.push_back(v._normal._x);
		normals.push_back(v._normal._y);
		normals.push_back(v._normal._z);
	}
	VBO vbo{ (GLfloat*)normals.data(), static_cast<GLsizeiptr>(normals.size() * sizeof(GLfloat)) };
	return vbo;
}

VBO Mesh::makeTangentVBO() const // Make a vbo with only the tangent attribute
{
	std::vector<GLfloat> tangents{};
	tangents.reserve(_vertices.size() * 3);
	for (const auto& v : _vertices)
	{
		// Tangent
		tangents.push_back(v._tangent._x);
		tangents.push_back(v._tangent._y);
		tangents.push_back(v._tangent._z);
	}
	VBO vbo{ (GLfloat*)tangents.data(), static_cast<GLsizeiptr>(tangents.size() * sizeof(GLfloat)) };
	return vbo;
}

VBO Mesh::makeColorVBO() const // Make a vbo with only the color attribute
{
	std::vector<GLfloat> colors{};
	colors.reserve(_vertices.size() * 4);
	for (const auto& v : _vertices)
	{
		// Color
		colors.push_back(v._color._x);
		colors.push_back(v._color._y);
		colors.push_back(v._color._z);
		colors.push_back(v._color._w);
	}
	VBO vbo{ (GLfloat*)colors.data(), static_cast<GLsizeiptr>(colors.size() * sizeof(GLfloat)) };
	return vbo;
}

VBO Mesh::makeTexCoordVBO() const // Make a vbo with only the texture coordinates attribute
{
	std::vector<GLfloat> texCoords{};
	texCoords.reserve(_vertices.size() * 2);
	for (const auto& v : _vertices)
	{
		// Tex coord
		texCoords.push_back(v._texCoord._x);
		texCoords.push_back(v._texCoord._y);
	}
	VBO vbo{ (GLfloat*)texCoords.data(), static_cast<GLsizeiptr>(texCoords.size() * sizeof(GLfloat)) };
	return vbo;
}

EBO Mesh::makeEBO() const
{
	std::vector<GLuint> indices{};
	indices.reserve(_triangles.size() * 3);
	for (const auto& t : _triangles)
	{
		indices.push_back(t._indices._x);
		indices.push_back(t._indices._y);
		indices.push_back(t._indices._z);
	}
	EBO ebo{ indices.data(), static_cast<GLsizeiptr>(indices.size() * sizeof(GLuint)) };
	return ebo;
}

std::vector<Vec3<GLfloat>> Mesh::getPositions() const
{
	std::vector<Vec3<GLfloat>> positions(_vertices.size());
	for (const auto& v : _vertices)
	{
		positions.push_back(v._position);
	}
	return positions;
}

std::vector<Vec3<GLfloat>> Mesh::getNormals() const
{
	std::vector<Vec3<GLfloat>> normals(_vertices.size());
	for (const auto& v : _vertices)
	{
		normals.push_back(v._normal);
	}
	return normals;
}

std::vector<Vec3<GLfloat>> Mesh::getTangents() const
{
	std::vector<Vec3<GLfloat>> tangents(_vertices.size());
	for (const auto& v : _vertices)
	{
		tangents.push_back(v._tangent);
	}
	return tangents;
}

std::vector<Vec4<GLfloat>> Mesh::getColors() const
{
	std::vector<Vec4<GLfloat>> colors(_vertices.size());
	for (const auto& v : _vertices)
	{
		colors.push_back(v._color);
	}
	return colors;
}

std::vector<Vec2<GLfloat>> Mesh::getTexCoords() const
{
	std::vector<Vec2<GLfloat>> texCoords(_vertices.size());
	for (const auto& v : _vertices)
	{
		texCoords.push_back(v._texCoord);
	}
	return texCoords;
}

//size_t Mesh::getNbOfVertices() const
//{
//	return _vertices.size();
//}
//
//size_t Mesh::getSizeOfVertices() const
//{
//	return _vertices.size() * sizeof(Vec3<GLfloat>);
//}

const std::vector<Mesh::Vertex>& Mesh::getVertices() const
{
	return _vertices;
}

const std::vector<Mesh::Triangle>& Mesh::getTriangles() const
{
	return _triangles;
}

const unsigned int Mesh::getNbTriangles() const
{
	return _triangles.size();
}