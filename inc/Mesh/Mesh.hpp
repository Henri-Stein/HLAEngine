#ifndef MESH_HPP
#define MESH_HPP

#include "Transform.hpp"
#include "Rendering/VBO.hpp"
#include "utils.hpp"
#include <glad/glad.h>
#include <vector>
#include <array>

class VBO;
class EBO;

class Mesh
{
public:

	struct Vertex {
		Vec3<GLfloat> _position = { 0.f, 0.f, 0.f };
		Vec3<GLfloat> _normal = { 1.f, 0.f, 0.f };
		Vec3<GLfloat> _tangent = { 0.f, 1.f, 0.f };
		Vec4<GLfloat> _color = { 0.3f, 0.3f, 0.3f, 1.f};
		Vec2<GLfloat> _texCoord = { 1.f, 1.f};
	};

	struct Triangle {
		Vec3<GLuint> _indices;
	};

	Mesh();

	VBO makeFullVBO() const; // Make the vbo with all the attributes of the Vertex struct
	std::array<VBO, 5> makeAllVBO() const; // Return a VBO for each vertex attribute
	VBO makePositionVBO() const; // Make a vbo with only the position attribute
	VBO makeNormalVBO() const; // Make a vbo with only the normal attribute
	VBO makeTangentVBO() const; // Make a vbo with only the tangent attribute
	VBO makeColorVBO() const; // Make a vbo with only the color attribute
	VBO makeTexCoordVBO() const; // Make a vbo with only the texture coordinates attribute
	EBO makeEBO() const;

	//virtual bool hasNormals() const final;
	//virtual bool hasTangentes() const final;
	//virtual bool hasColors() const final;
	//virtual bool hasTexCoords() const final;


	//size_t getSizeOfVertices() const;
	//size_t getNbOfVertices() const;
	const std::vector<Vertex>& getVertices() const;

	std::vector<Vec3<GLfloat>> Mesh::getPositions() const; // Get only the positions
	std::vector<Vec3<GLfloat>> getNormals() const; // Get only the normals
	std::vector<Vec3<GLfloat>> getTangents() const; // Get only the tangents
	std::vector<Vec4<GLfloat>> getColors() const; // Get only the colors
	std::vector<Vec2<GLfloat>> getTexCoords() const; // Get only the texture coordinates

	const std::vector<Triangle>& getTriangles() const;
	const unsigned int getNbTriangles() const;

protected:
	std::vector<Vertex> _vertices;
	std::vector<Triangle> _triangles;
};


#endif // !MESH_HPP
