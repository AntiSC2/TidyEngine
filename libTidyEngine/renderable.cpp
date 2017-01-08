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

#include "renderable.hpp"

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

void Renderable::Update(bool render)
{
	;
}

void Renderable::AddVertex(const Vertex& vertex)
{
	m_Vertices.push_back(vertex);
}

void Renderable::DelVertex(size_t index)
{
	if (index < m_Vertices.size())
		m_Vertices.erase(m_Vertices.begin() + index);
}

const std::vector<Vertex> &Renderable::GetVertices() const
{
	return m_Vertices;
}

GLuint Renderable::GetTex()
{
	return m_Tex;
}
