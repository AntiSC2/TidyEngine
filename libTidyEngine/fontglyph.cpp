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

#include "fontglyph.hpp"

FontGlyph::FontGlyph()
{
	;
}

FontGlyph::FontGlyph(float x, float y, float w, float h, GLuint tex)
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

	m_Tex = tex;
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