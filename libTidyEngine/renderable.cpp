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

#include "renderable.hpp"
#include "material.hpp"

#ifdef _WIN32
#define APIENTRY __stdcall
#endif

#include <glad/glad.h>

Renderable::Renderable()
{
	;
}

Renderable::~Renderable()
{
	;
}

void Renderable::Render()
{
	;
}

void Renderable::AddVertex(const Vertex &vertex)
{
	m_Vertices.push_back(vertex);
}

void Renderable::SetVertices(std::vector<Vertex> &vertices)
{
	m_Vertices = vertices;
}

void Renderable::DelVertex(size_t index)
{
	if (index < m_Vertices.size())
		m_Vertices.erase(m_Vertices.begin() + index);
}

void Renderable::SetPos(const glm::vec3 &pos)
{
	glm::vec3 offset(0.0f, 0.0f, 0.0f);

	if (m_Vertices.empty() == false)
		offset = m_Vertices[0].Position;
	
	for (size_t i = 0; i < m_Vertices.size(); i++) {
		m_Vertices[i].Position -= offset;
		m_Vertices[i].Position += pos;
	}
}

const std::vector<Vertex> &Renderable::GetVertices() const
{
	return m_Vertices;
}

GLuint Renderable::GetTex() const
{
	return m_Tex;
}

void Renderable::SetTex(GLuint id)
{
	m_Tex = id;
}

void Renderable::SetMat(Material *mat)
{
	m_Mat = mat;
}

const Material *Renderable::GetMat() const
{
	return m_Mat;
}

const std::vector<uint32_t> &Renderable::GetIndices() const
{
	return m_Indices;
}