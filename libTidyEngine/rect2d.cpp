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

#include "rect2d.hpp"
#include "cache.hpp"

Rect2D::Rect2D()
{
	m_Tex = Resources.GetTexture("default")->GetTex();
}

Rect2D::Rect2D(float x, float y, float w, float h)
{
	SetRect(x, y, w, h);
	m_Tex = /*Resources.GetTexture("default")->GetTex()*/2;
}

Rect2D::Rect2D(glm::vec2 position, glm::vec2 dimensions)
{
	SetRect(position.x, position.y, dimensions.x, dimensions.y);
	m_Tex = Resources.GetTexture("default")->GetTex();
}

Rect2D::Rect2D(glm::vec4 rect)
{
	SetRect(rect.x, rect.y, rect.z, rect.w);
	m_Tex = Resources.GetTexture("default")->GetTex();
}

Rect2D::~Rect2D()
{
	;
}

void Rect2D::SetRect(float x, float y, float w, float h)
{
	if (!m_Vertices.empty())
		m_Vertices.clear();
	Vertex temp;
	temp.Color = m_Color;

	temp.Position = glm::vec3(x, y, 0.0f);
	temp.TexUV = glm::vec2(0.0f, 0.0f);
	AddVertex(temp);

	temp.Position = glm::vec3(x + w, y, 0.0f);
	temp.TexUV = glm::vec2(1.0f, 0.0f);
	AddVertex(temp);

	temp.Position = glm::vec3(x, y + h, 0.0f);
	temp.TexUV = glm::vec2(0.0f, 1.0f);
	AddVertex(temp);

	temp.Position = glm::vec3(x, y + h, 0.0f);
	temp.TexUV = glm::vec2(0.0f, 1.0f);
	AddVertex(temp);

	temp.Position = glm::vec3(x + w, y, 0.0f);
	temp.TexUV = glm::vec2(1.0f, 0.0f);
	AddVertex(temp);

	temp.Position = glm::vec3(x + w, y + h, 0.0f);
	temp.TexUV = glm::vec2(1.0f, 1.0f);
	AddVertex(temp);
}

void Rect2D::SetPos(float x, float y)
{
	glm::vec3 offset(0.0f, 0.0f, 0.0f);

	if (m_Vertices.empty() == false)
		offset = m_Vertices[0].Position;
	
	for (size_t i = 0; i < m_Vertices.size(); i++) {
		m_Vertices[i].Position -= offset;
		m_Vertices[i].Position += glm::vec3(x, y, 0.0f);
	}
}

void Rect2D::SetColor(glm::vec4 color)
{
	m_Color = color;
	for (size_t i = 0; i < m_Vertices.size(); i++)
		m_Vertices[i].Color = m_Color;
}

void Rect2D::SetColor(float r, float g, float b, float a)
{
	SetColor(glm::vec4(r, g, b, a));
}
