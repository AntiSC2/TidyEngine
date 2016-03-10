/*
TidyEngine
Copyright (C) 2016 Jakob Sinclair

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

#include "batch.hpp"
#include <algorithm>

Batch::Batch()
{
	;
}

Batch::~Batch()
{
	;
}

void Batch::Begin(GLuint vaoid, GLuint vboid)
{
	m_VAOID = vaoid;
	m_VBOID = vboid;
	m_Glyphs.clear();
	m_SortedGlyphs.clear();
        m_RenderBatches.clear();
}

void Batch::End()
{
	if (m_Glyphs.empty())
		return;

	m_SortedGlyphs.resize(m_Glyphs.size());

	for (size_t i = 0; i < m_Glyphs.size(); i++)
		m_SortedGlyphs[i] = &m_Glyphs[i];

	SortGlyphs();
	CreateBatches();
}

void Batch::Draw(const Renderable &object)
{
	m_Glyphs.push_back(object);
}

void Batch::Present()
{
	glBindVertexArray(m_VAOID);
	for (size_t i = 0; i < m_RenderBatches.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, m_RenderBatches[i].Tex);
		glDrawArrays(GL_TRIANGLES, (GLsizei)m_RenderBatches[i].Offset,
				(GLsizei)m_RenderBatches[i].Vertices);
	}
	glBindVertexArray(0);
}

void Batch::SortGlyphs()
{
	std::stable_sort(m_SortedGlyphs.begin(), m_SortedGlyphs.end(),
			CompareTex);
}

void Batch::CreateBatches()
{
        uint32_t num_vert = 0;
        for (size_t i = 0; i < m_SortedGlyphs.size(); i++)
                num_vert += m_SortedGlyphs[i]->GetVertices().size();
	std::vector<Vertex> vertex_data;
	uint64_t offset = 0;
	
	m_RenderBatches.emplace_back(m_SortedGlyphs[0]->GetTex(),
			m_SortedGlyphs[0]->GetVertices().size(), offset);
	offset += m_RenderBatches[0].Vertices;

        vertex_data.resize(num_vert);
        for (size_t i = 0; i < m_SortedGlyphs[0]->GetVertices().size(); i++)
                vertex_data[i] = m_SortedGlyphs[0]->GetVertices()[i];

	for (size_t g = 1; g < m_SortedGlyphs.size(); g++) {
		GLuint temp_tex = m_SortedGlyphs[g]->GetTex();
		uint64_t num_vert = m_SortedGlyphs[g]->GetVertices().size();

		if (temp_tex != m_SortedGlyphs[g - 1]->GetTex()) {
			m_RenderBatches.emplace_back(temp_tex, num_vert,
					offset);
		} else {
			m_RenderBatches.back().Vertices += num_vert;
		}

                for (size_t i = 0; i < m_SortedGlyphs[g]->GetVertices().size();
                                i++)
                        vertex_data[i] = m_SortedGlyphs[g]->GetVertices()[i];
		offset += num_vert;
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertex_data.size(), 
			vertex_data.data(), GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

bool Batch::CompareTex(Renderable *a, Renderable *b)
{
	return a->GetTex() < b->GetTex();
}
