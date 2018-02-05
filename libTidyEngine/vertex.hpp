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

#pragma once

#ifdef _WIN32
#include <cstdint>
#endif

#include <vector>
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
	RenderBatch(unsigned int tex, uint64_t vertices, uint64_t offset) : Tex(tex),
			Vertices(vertices), Offset(offset)
	{
		;
	}

	unsigned int Tex = 0;
	uint64_t Vertices = 0;
	uint64_t Offset = 0;
};

class MeshBatch {
public:
	MeshBatch() {;}
	MeshBatch(const Material *mat, uint64_t offset, uint64_t indices):
	          Mat(mat), Offset(offset), Indices(indices) {;}

	const Material *Mat = nullptr;
	uint64_t Offset = 0;
	uint64_t Indices = 0;
};
