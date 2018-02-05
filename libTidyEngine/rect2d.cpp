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

#include "rect2d.hpp"
#include "cache.hpp"

Rect2D::Rect2D()
{
	m_Tex = Res.LoadTex("default")->GetTex();
}

Rect2D::Rect2D(float x, float y, float w, float h)
{
	SetRect(x, y, w, h);
	m_Tex = Res.LoadTex("default")->GetTex();
}

Rect2D::Rect2D(glm::vec2 position, glm::vec2 dimensions)
{
	SetRect(position.x, position.y, dimensions.x, dimensions.y);
	m_Tex = Res.LoadTex("default")->GetTex();
}

Rect2D::Rect2D(glm::vec4 rect)
{
	SetRect(rect.x, rect.y, rect.z, rect.w);
	m_Tex = Res.LoadTex("default")->GetTex();
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
