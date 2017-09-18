/*
TidyEngine
Copyright (C) 2017 Jakob Sinclair

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
Contact the author at: jakob.sinclair99@gmail.com
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

void Mesh::Render(Shader *shader)
{
	if (m_Mat != nullptr) {
		m_Mat->Bind(shader);
	}
	glBindVertexArray(m_VAOID);
	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}