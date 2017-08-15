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

#pragma once

#ifdef _WIN32
#include <cstdint>
#endif

#include <vector>
#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>
#include "material.hpp"

class Vertex {
public:
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec4 Color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	glm::vec2 TexUV = glm::vec2(0.0f, 0.0f);
	glm::vec3 Normal = glm::vec3(0.0f, 0.0f, 0.0f);
};

class RenderBatch {
public:
	RenderBatch(GLuint tex, uint64_t vertices, uint64_t offset) : Tex(tex),
			Vertices(vertices), Offset(offset)
	{
		;
	}

	GLuint Tex = 0;
	uint64_t Vertices = 0;
	uint64_t Offset = 0;
};

class MeshBatch {
public:
	MeshBatch() {;}
	MeshBatch(const Material *mat, uint64_t vertices, uint64_t offset, uint64_t indices):
	          Mat(mat), Vertices(vertices), Offset(offset), Indices(indices) {;}

	const Material *Mat = nullptr;
	uint64_t Vertices = 0;
	uint64_t Offset = 0;
	uint64_t Indices;
};
