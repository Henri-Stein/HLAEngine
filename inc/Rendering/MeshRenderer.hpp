#ifndef MESH_RENDERER_HPP
#define MESH_RENDERER_HPP

#include "VAO.hpp"
#include "EBO.hpp"
#include "Mesh/Mesh.hpp"

class MeshRenderer
{
public:
	enum class DrawMode
	{
		TRIANGLES,
		POINTS
	};

	MeshRenderer() = delete;
	MeshRenderer(const MeshRenderer& other) = delete; // No duplication, otherwise freeing the VAO and EBO's memory as it's currently done in the destructor would be risky
	~MeshRenderer();
	
	MeshRenderer(
		const Mesh& mesh,
		int layoutPos   = 0, // set to a negative number if you don't want to link the attribute
		int layoutNorm  = 1,
		int layoutTan   = 2,
		int layoutCol   = 3,
		int layoutTexCo = 4);
	
	//void Delete();

	bool useLayout(int layout) const;

	bool addAttrib(const VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

	void draw(DrawMode drawMode = DrawMode::TRIANGLES);

	VAO _vao;
	EBO _ebo; // EBO defining the triangles
private:
	unsigned int _nbIndices;
	std::vector<int> _usedLayout;
};

#endif // !MESH_RENDERER_HPP
