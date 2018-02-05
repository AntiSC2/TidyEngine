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

#ifdef _WIN32
#define APIENTRY __stdcall
#endif

#include <algorithm>
#include <glad/glad.h>
#include "camera.hpp"
#include "renderer.hpp"
#include "shader.hpp"
#include "renderable.hpp"
#include "font.hpp"
#include "fontglyph.hpp"

IRenderer::~IRenderer()
{
	if (m_VAOID != 0) {
		glDeleteVertexArrays(1, &m_VAOID);
		m_VAOID = 0;
	}
	if (m_VBOID != 0) {
		glDeleteBuffers(1, &m_VBOID);
		m_VBOID = 0;
	}	
}

void IRenderer::SetCamera(Camera *camera)
{
	m_Camera = camera;
}

void IRenderer::Begin()
{
	m_Shader->Bind();
	m_Glyphs.clear();
	m_SortedGlyphs.clear();
	m_RenderBatches.clear();
}

void IRenderer::Draw(Renderable *object)
{
	object->Render();
	m_Glyphs.emplace_back(*object);
}

void IRenderer::DrawText(std::string text, glm::vec2 pos, glm::vec4 color,
                        Font &font)
{
	float pen_x = 0.0f;
	float pen_y = (float)font.GetTexHeight();
	
	for (size_t i = 0; i < text.size(); i++) {
		FontGlyph glyph = font.GetChar(text[i]);
		glyph.SetColor(color);
		glyph.SetPos(pos.x + pen_x + glyph.GetPenX(),
		             pos.y + pen_y - glyph.GetPenY());
		pen_x += (float)glyph.GetAdvanceX();
		
		Draw(&glyph);
	}
}

void IRenderer::End()
{
	if (m_Glyphs.empty())
		return;

	m_SortedGlyphs.resize(m_Glyphs.size());

	for (size_t i = 0; i < m_Glyphs.size(); i++)
		m_SortedGlyphs[i] = &m_Glyphs[i];

	SortGlyphs();
	CreateBatches();
}

void IRenderer::Present()
{
	glBindVertexArray(m_VAOID);
	for (size_t i = 0; i < m_RenderBatches.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, m_RenderBatches[i].Tex);
		glDrawArrays(GL_TRIANGLES, (GLsizei)m_RenderBatches[i].Offset,
		            (GLsizei)m_RenderBatches[i].Vertices);
	}
}

void IRenderer::SortGlyphs()
{
	std::stable_sort(m_SortedGlyphs.begin(), m_SortedGlyphs.end(), Order);
}

void IRenderer::CreateBatches()
{
	size_t num_vert_total = 0;
	for (size_t i = 0; i < m_SortedGlyphs.size(); i++)
		num_vert_total += m_SortedGlyphs[i]->GetVertices().size();

	std::vector<Vertex> vertex_data;
	uint64_t offset = 0;
	
	m_RenderBatches.emplace_back(m_SortedGlyphs[0]->GetTex(),
	                             m_SortedGlyphs[0]->GetVertices().size(),
	                             offset);
	offset += m_RenderBatches[0].Vertices;

	vertex_data.resize(num_vert_total);
	for (size_t i = 0; i < m_SortedGlyphs[0]->GetVertices().size(); i++)
		vertex_data[i] = m_SortedGlyphs[0]->GetVertices()[i];

	for (size_t g = 1; g < m_SortedGlyphs.size(); g++) {
		GLuint temp_tex = m_SortedGlyphs[g]->GetTex();
		size_t num_vert = m_SortedGlyphs[g]->GetVertices().size();

		if (temp_tex != m_SortedGlyphs[g - 1]->GetTex())
			m_RenderBatches.emplace_back(temp_tex, num_vert,
			                             offset);
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
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * vertex_data.size(), 
	                vertex_data.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

bool CompareTex(Renderable *a, Renderable *b)
{
	return a->GetTex() < b->GetTex();
}