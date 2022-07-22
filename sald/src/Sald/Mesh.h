#pragma once
#include "Core.h"

#include <glad/glad.h>

namespace Sald
{
	class Mesh
	{
	public:
		SALD_API Mesh();
		SALD_API ~Mesh();

		SALD_API void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numberOfIndices, bool vertices_includes_uv);

		SALD_API void RenderMesh();
		SALD_API void ClearMesh();

	private:
		GLuint m_VAO, m_VBO, m_IBO;
		GLsizei m_IndexCount;
	};
}
