﻿/*
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

#include "renderable.hpp"
#include "material.hpp"

Renderable::Renderable()
{
	;
}

Renderable::~Renderable()
{
	;
}

std::string Renderable::Type() {
	return "Renderable";
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

void Renderable::AddTex(GLuint tex) 
{
	m_Textures.push_back(tex);
}

void Renderable::DelTex(size_t index)
{
	if (index < m_Textures.size())
		m_Textures.erase(m_Textures.begin() + index);
}

const std::vector<Vertex> &Renderable::GetVertices() const
{
	return m_Vertices;
}

GLuint Renderable::GetTex(size_t index) const
{
	if (index >= m_Textures.size())
		return 0;
	return m_Textures[index];
}

const std::vector<GLuint> &Renderable::GetTextures() const
{
	return m_Textures;
}

Material *Renderable::GetMat()
{
	return nullptr;
}