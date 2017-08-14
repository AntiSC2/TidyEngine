/*
TidyEngine
Copyright (C) 2017 Jakob Sinclair

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

#pragma once

#include <vector>
#include "renderable.hpp"
#include "vertex.hpp"
#include "material.hpp"

class Mesh: public Renderable {
public:
	Mesh();
	Mesh(std::vector<Vertex> &vertices, std::vector<uint32_t> &indices, std::vector<GLuint> &textures);
	virtual ~Mesh();

	virtual void Render();
	virtual Material *GetMat();
protected:
	GLuint m_VAOID = 0;
	GLuint m_EBOID = 0;
	GLuint m_VBOID = 0;
	std::vector<uint32_t> m_Indices;
	Material *m_Material;
};