/*
 * TidyEngine
 * Copyright (c) 2018 Jakob Sinclair <sinclair.jakob@mailbox.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "mesh.hpp"
#ifdef _WIN32
#define APIENTRY __stdcall
#endif
#include <glad/glad.h>
#include "shader.hpp"

Mesh::Mesh()
{
	;
}

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<uint32_t> &indices, Material *mat)
{
	m_Vertices = vertices;
	m_Indices = indices;
	m_Mat = mat;

	if (m_VAOID != 0)
		glDeleteVertexArrays(1, &m_VAOID);
	if (m_VBOID != 0)
		glDeleteBuffers(1, &m_VBOID);
	if (m_EBOID != 0)
		glDeleteBuffers(1, &m_EBOID);
	
	glGenVertexArrays(1, &m_VAOID);
	glBindVertexArray(m_VAOID);

	glGenBuffers(1, &m_VBOID);
	glGenBuffers(1, &m_EBOID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOID);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), (void*)&m_Vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBOID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(uint32_t), (void*)&m_Indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(void*)offsetof(Vertex, Position));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex),
			(void*)offsetof(Vertex, Color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(void*)offsetof(Vertex, TexUV));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
	        (void*)offsetof(Vertex, Normal));

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	if (m_Mat != nullptr)
		delete m_Mat;
	if (m_EBOID != 0)
		glDeleteBuffers(1, &m_EBOID);
	if (m_VBOID != 0)
		glDeleteBuffers(1, &m_VBOID);
	if (m_VAOID != 0)
		glDeleteVertexArrays(1, &m_VAOID);
}

bool Mesh::Textured()
{
	if (m_Mat != nullptr)
		m_Mat->Textured();
	else
		return false;
}

void Mesh::Render(Shader *shader)
{
	if (m_Mat != nullptr)
		m_Mat->Bind(shader);

	glBindVertexArray(m_VAOID);
	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}