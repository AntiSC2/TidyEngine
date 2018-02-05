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

#include "fontglyph.hpp"

FontGlyph::FontGlyph()
{
	;
}

FontGlyph::FontGlyph(float x, float y, float w, float h)
{
	m_Rect.x = x;
	m_Rect.y = y;
	m_Rect.z = w;
	m_Rect.w = h;
	
	Vertex temp;
	temp.Color = m_Color;
	temp.Position = glm::vec3(x, y, 0.0f);
	temp.TexUV = glm::vec2(m_TexCoords.x, m_TexCoords.y);
	AddVertex(temp);

	temp.Position = glm::vec3(x + w, y, 0.0f);
	temp.TexUV = glm::vec2(m_TexCoords.z, m_TexCoords.y);
	AddVertex(temp);

	temp.Position = glm::vec3(x, y + h, 0.0f);
	temp.TexUV = glm::vec2(m_TexCoords.x, m_TexCoords.w);
	AddVertex(temp);

	temp.Position = glm::vec3(x, y + h, 0.0f);
	temp.TexUV = glm::vec2(m_TexCoords.x, m_TexCoords.w);
	AddVertex(temp);

	temp.Position = glm::vec3(x + w, y, 0.0f);
	temp.TexUV = glm::vec2(m_TexCoords.z, m_TexCoords.y);
	AddVertex(temp);

	temp.Position = glm::vec3(x + w, y + h, 0.0f);
	temp.TexUV = glm::vec2(m_TexCoords.z, m_TexCoords.w);
	AddVertex(temp);
}

FontGlyph::~FontGlyph()
{
	;
}

void FontGlyph::SetPos(float x, float y)
{
	m_Rect.x = x;
	m_Rect.y = y;
	glm::vec3 offset(0.0f, 0.0f, 0.0f);

	if (m_Vertices.empty() == false)
		offset = m_Vertices[0].Position;
	
	for (size_t i = 0; i < m_Vertices.size(); i++) {
		m_Vertices[i].Position -= offset;
		m_Vertices[i].Position += glm::vec3(x, y, 0.0f);
	}
}

void FontGlyph::SetColor(glm::vec4 color)
{
	m_Color = color;
	for (size_t i = 0; i < m_Vertices.size(); i++)
		m_Vertices[i].Color = m_Color;

}

void FontGlyph::SetTexUV(glm::vec4 coords)
{
	m_TexCoords = coords;
	if (m_Vertices.size() == 6) {
		m_Vertices[0].TexUV = glm::vec2(m_TexCoords.x, m_TexCoords.y);
		m_Vertices[1].TexUV = glm::vec2(m_TexCoords.z, m_TexCoords.y);
		m_Vertices[2].TexUV = glm::vec2(m_TexCoords.x, m_TexCoords.w);
		m_Vertices[3].TexUV = glm::vec2(m_TexCoords.x, m_TexCoords.w);
		m_Vertices[4].TexUV = glm::vec2(m_TexCoords.z, m_TexCoords.y);
		m_Vertices[5].TexUV = glm::vec2(m_TexCoords.z, m_TexCoords.w);
	}
}

void FontGlyph::SetPenX(int32_t pen_x)
{
	m_Left = pen_x;
}

void FontGlyph::SetPenY(int32_t pen_y)
{
	m_Top = pen_y;
}

int32_t FontGlyph::GetPenX()
{
	return m_Left;
}

int32_t FontGlyph::GetPenY()
{
	return m_Top;
}

void FontGlyph::SetAdvanceX(int32_t pen_x)
{
	m_AdvanceX = pen_x;
}

void FontGlyph::SetAdvanceY(int32_t pen_y)
{
	m_AdvanceY = pen_y;
}

int32_t FontGlyph::GetAdvanceX()
{
	return m_AdvanceX;
}

int32_t FontGlyph::GetAdvanceY()
{
	return m_AdvanceY;
}

glm::vec4 FontGlyph::GetRect()
{
	return m_Rect;
}