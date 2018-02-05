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

class Camera;
class Shader;

typedef unsigned int GLuint;

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <string>
#include "vertex.hpp"
#include "renderable.hpp"
#include "font.hpp"

extern bool CompareTex(Renderable *a, Renderable *b);

class IRenderer {
public:
	IRenderer() = default;
	virtual ~IRenderer();

	virtual void Initialise(Shader *shader) = 0;
	virtual void SetCamera(Camera *camera);
	virtual void Begin();
	virtual void Draw(Renderable *object);
	virtual void DrawText(std::string text, glm::vec2 pos,
	                      glm::vec4 color, Font &font);
	virtual void End();
	virtual void Present();
protected:
	virtual void SortGlyphs();
	virtual void CreateBatches();
	bool (*Order)(Renderable*, Renderable*) = &CompareTex;
 
	Camera *m_Camera = nullptr;
	Shader *m_Shader = nullptr;
	GLuint m_VAOID = 0;
	GLuint m_VBOID = 0;
	std::vector<Renderable> m_Glyphs;
	std::vector<Renderable*> m_SortedGlyphs;
	std::vector<RenderBatch> m_RenderBatches;
};