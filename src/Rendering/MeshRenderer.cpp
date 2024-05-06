#include "Rendering/MeshRenderer.hpp"

MeshRenderer::MeshRenderer(
	const Mesh& mesh,
	int layoutPos,
	int layoutNorm,
	int layoutTan,
	int layoutCol,
	int layoutTexCo
)
	:
	_nbIndices(mesh.getNbTriangles() * 3),
	_vao{},
	_ebo{ mesh.makeEBO() },
	_usedLayout{}
{
	_vao.Bind();
	_ebo.Bind();

	if (   layoutPos   >= 0 
		&& layoutNorm  >= 0 
		&& layoutTan   >= 0 
		&& layoutCol   >= 0 
		&& layoutTexCo >= 0)
	{

		VBO& vboAllAttributes = mesh.makeFullVBO();
		addAttrib(vboAllAttributes, layoutPos,   3, GL_FLOAT, 15 * sizeof(float), (void*)(0));
		addAttrib(vboAllAttributes, layoutNorm,  3, GL_FLOAT, 15 * sizeof(float), (void*)(3 * sizeof(float)));
		addAttrib(vboAllAttributes, layoutTan,   3, GL_FLOAT, 15 * sizeof(float), (void*)(6 * sizeof(float)));
		addAttrib(vboAllAttributes, layoutCol,   4, GL_FLOAT, 15 * sizeof(float), (void*)(9 * sizeof(float)));
		addAttrib(vboAllAttributes, layoutTexCo, 2, GL_FLOAT, 15 * sizeof(float), (void*)(13 * sizeof(float)));
		vboAllAttributes.Delete();
	}
	else
	{
		//std::cout << "Make VBOs one by one" << std::endl;
		if (layoutPos >= 0)
		{
			VBO& vboPos = mesh.makePositionVBO();
			addAttrib(vboPos, layoutPos, 3, GL_FLOAT, 3 * sizeof(float), (void*)(0));
			vboPos.Delete();
		}
		if (layoutNorm >= 0)
		{
			VBO& vboNorm = mesh.makeNormalVBO();
			addAttrib(vboNorm, layoutNorm, 3, GL_FLOAT, 3 * sizeof(float), (void*)(0));
			vboNorm.Delete();
		}
		if (layoutTan >= 0)
		{
			VBO& vboTan = mesh.makeTangentVBO();
			addAttrib(vboTan, layoutTan, 3, GL_FLOAT, 3 * sizeof(float), (void*)(0));
			vboTan.Delete();
		}
		if (layoutCol >= 0)
		{
			VBO& vboCol = mesh.makeColorVBO();
			addAttrib(vboCol, layoutCol, 4, GL_FLOAT, 4 * sizeof(float), (void*)(0));
			vboCol.Delete();
		}
		if (layoutTexCo >= 0)
		{
			VBO& vboTexCo = mesh.makeTexCoordVBO();
			addAttrib(vboTexCo, layoutTexCo, 2, GL_FLOAT, 2 * sizeof(float), (void*)(0));
			vboTexCo.Delete();
		}
	}
	_vao.Unbind();
	_ebo.Unbind();
	std::cout << "In MeshRenderer constructor: _vao._ID = " << _vao.getID() << std::endl;
}

//MeshRenderer::MeshRenderer(const MeshRenderer& other) : 
//	_vao{other._vao},
//	_ebo{other._ebo},
//	_nbIndices{other._nbIndices},
//	_usedLayout{other._usedLayout}
//{
//}

MeshRenderer::~MeshRenderer()
{
	_vao.Delete();
	_ebo.Delete();
}

//void MeshRenderer::Delete()
//{
//	std::cout << "Delete mesh renderer (freeing vao and vbo's memory)" << std::endl;
//	_vao.Delete();
//	_ebo.Delete();
//}

bool MeshRenderer::useLayout(int layout) const
{
	for (const auto l : _usedLayout)
	{
		if (l == layout)
			return true;
	}
	return false;
}

bool MeshRenderer::addAttrib(const VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	//std::cout << layout << std::endl;
	if (useLayout(layout))
	{
		std::cerr << "The layout " << layout << " is already used for another attribute" << std::endl;
		return false;
	}
	//std::cout << "Layout " << layout << " is available" << std::endl;
	_vao.Bind();
	_vao.LinkAttrib(vbo, layout, numComponents, type, stride, offset);
	_usedLayout.push_back(layout);
	_vao.Unbind();
	return true;
}


void MeshRenderer::draw(DrawMode drawMode)
{
	_vao.Bind();
	switch (drawMode)
	{
	case DrawMode::TRIANGLES:
		glDrawElements(GL_TRIANGLES, _nbIndices, GL_UNSIGNED_INT, 0);
		break;
	case DrawMode::POINTS:
		glDrawElements(GL_POINTS, _nbIndices, GL_UNSIGNED_INT, 0);
		break;
	default:
		glDrawElements(GL_POINTS, _nbIndices, GL_UNSIGNED_INT, 0);
		break;
	}
}