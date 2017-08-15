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

#include "modelrenderer.hpp"
#include "shader.hpp"
#include "camera.hpp"

ModelRenderer::ModelRenderer()
{
	;	
}

ModelRenderer::~ModelRenderer()
{
	if (m_EBOID != 0)
		glDeleteBuffers(1, &m_EBOID);
	if (m_VAOID != 0)
		glDeleteVertexArrays(1, &m_VAOID);
	if (m_VBOID != 0)
		glDeleteBuffers(1, &m_VBOID);
}

void ModelRenderer::Initialise(Shader *shader)
{
	m_Shader = shader;

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

void ModelRenderer::Present(const Camera *camera)
{
	if (camera != nullptr) {
		m_Shader->SetUniformMat4("projection", camera->GetProj());
		m_Shader->SetUniformMat4("view", camera->GetView());
		m_Shader->SetUniformMat4("model", camera->GetModel());
	}

	glBindVertexArray(m_VAOID);
	for (size_t i = 0; i < m_RenderBatches.size(); i++) {
		m_RenderBatches[i].Mat->Bind(m_Shader);
		glDrawArrays(GL_TRIANGLES, (GLsizei)m_RenderBatches[i].Offset,
		            (GLsizei)m_RenderBatches[i].Vertices);
	}
}

void ModelRenderer::CreateBatches()
{
	size_t num_vert_total = 0;
	for (size_t i = 0; i < m_SortedGlyphs.size(); i++)
		num_vert_total += m_SortedGlyphs[i]->GetVertices().size();

	std::vector<Vertex> vertex_data;
	uint64_t offset = 0;
	
	m_RenderBatches.emplace_back(m_SortedGlyphs[0]->GetMat(),
	                             m_SortedGlyphs[0]->GetVertices().size(),
	                             offset, m_SortedGlyphs[0]->GetIndices());
	offset += m_RenderBatches[0].Vertices;

	vertex_data.resize(num_vert_total);
	for (size_t i = 0; i < m_SortedGlyphs[0]->GetVertices().size(); i++)
		vertex_data[i] = m_SortedGlyphs[0]->GetVertices()[i];

	for (size_t g = 1; g < m_SortedGlyphs.size(); g++) {
		const Material *temp_mat = m_SortedGlyphs[g]->GetMat();
		size_t num_vert = m_SortedGlyphs[g]->GetVertices().size();
		std::vector<uint64_t> indices = m_SortedGlyphs[g]->GetIndices();
		

		if (temp_mat != m_SortedGlyphs[g - 1]->GetMat())
			m_RenderBatches.emplace_back(temp_mat, num_vert,
			                             offset, indices);
		else
			m_RenderBatches.back().Vertices += num_vert;

		size_t i = offset;
		size_t size_vert = m_SortedGlyphs[g]->GetVertices().size();

		for (; (i - offset) < size_vert; i++)
			vertex_data[i] = m_SortedGlyphs[g]->
			                 GetVertices()[i - offset];

		offset += num_vert;
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertex_data.size(), 
	                vertex_data.data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}