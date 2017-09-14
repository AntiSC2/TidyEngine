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
along with this program. If not, see <http://www.gnu.org/licenses/>.
Contact the author at: jakob.sinclair99@gmail.com
*/

#pragma once

#include <vector>
#include "vertex.hpp"
#include "resource.hpp"

class Material;
typedef unsigned int GLuint;

class Renderable {
public:
	Renderable();
	virtual ~Renderable();
	
	virtual std::string Type();
	
	virtual void Render();
	virtual void AddVertex(const Vertex &vertex);
	virtual void DelVertex(size_t index);
	virtual void SetVertices(std::vector<Vertex> &vertices);
	virtual const std::vector<Vertex> &GetVertices() const;
	virtual void SetPos(const glm::vec3 &pos);
	virtual void SetTex(GLuint tex);
	virtual GLuint GetTex() const;
	virtual void SetMat(Material *mat);
	virtual const Material *GetMat() const;
	virtual const std::vector<uint32_t> &GetIndices() const;
protected:
	GLuint m_Tex = 0;
	Material *m_Mat = nullptr;
	std::vector<Vertex> m_Vertices;
	std::vector<uint32_t> m_Indices;
};
