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

#include <vector>
#include "vertex.hpp"

class Material;
typedef unsigned int GLuint;

class Renderable {
public:
	Renderable();
	virtual ~Renderable();
	
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
