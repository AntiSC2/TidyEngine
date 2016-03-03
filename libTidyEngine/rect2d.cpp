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

Rect2D::Rect2D()
{
	;
}

Rect2D::Rect2D(float x, float y, float w, float h)
{
	SetRect(x, y, w, h);
}

Rect2D::Rect2D(glm::vec2 position, glm::vec2 dimensions)
{
	SetRect(position.x, position.y, dimensions.x, dimensions.y);
}

Rect2D::Rect2D(glm::vec4 rect)
{
	SetRect(rect.x, rect.y, rect.z, rect.w);
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
	temp.Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	temp.Position = glm::vec3(x, y, 0.0f);
	AddVertex(temp);

	temp.Position = glm::vec3(x + w, y, 0.0f);
	AddVertex(temp);

	temp.Position = glm::vec3(x, y + h, 0.0f);
	AddVertex(temp);

	temp.Position = glm::vec3(x, y + h, 0.0f);
	AddVertex(temp);

	temp.Position = glm::vec3(x + w, y, 0.0f);
	AddVertex(temp);

	temp.Position = glm::vec3(x + w, y + h, 0.0f);
	AddVertex(temp);

}
