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

#include "renderer.hpp"
#include "shader.hpp"
#include "batch.hpp"
#include "renderable.hpp"
#include "font.hpp"
#include "fontglyph.hpp"

Renderer::Renderer()
{
	;
}

Renderer::~Renderer()
{
	if (m_VAOID != 0)
		glDeleteVertexArrays(1, &m_VAOID);
	if (m_VBOID != 0)
		glDeleteBuffers(1, &m_VBOID);
}

void Renderer::Begin()
{
	m_Shader->Bind();
	m_Batch->Begin(m_VAOID, m_VBOID);
}

void Renderer::Draw(const Renderable *object)
{
	m_Batch->Draw(object);
}

void Renderer::DrawText(std::string text, glm::vec2 pos, glm::vec4 color,
                        Font &font)
{
	float pen_x = 0.0f;
	float pen_y = (float)font.GetTexHeight();
	
	for (size_t i = 0; i < text.size(); i++) {
		FontGlyph glyph = font.GetChar(text[i]);
		glyph.SetColor(color);
		glyph.SetPos(pos.x + pen_x + glyph.GetPenX(), pos.y + pen_y - glyph.GetPenY());
		pen_x += (float)glyph.GetAdvanceX();
		
		m_Batch->Draw(&glyph);
	}
}

void Renderer::End()
{
	m_Batch->End();
}

void Renderer::Present()
{
	m_Batch->Present();
}
